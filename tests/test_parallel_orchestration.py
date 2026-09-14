"""Pure scheduler/store checks using real captured outcomes where an outcome is needed."""
import hashlib,json,sqlite3,time,tracemalloc,uuid
from pathlib import Path
import pytest
from emerald_tournament.parallel_tasks import tasks,count_tasks,SEED_VERSION
from emerald_tournament.result_store import identity
from emerald_tournament.parallel_store import Store,status
from emerald_tournament.parallel_platform import worker_count,run_lock
from emerald_tournament.parallel_worker import archive
ROOT=Path(__file__).resolve().parents[1]

def plan():
 return dict(plan_id='test-plan',trainer_ids=[1,335],pairing='all_pairs',master_seed=20260913,frame_budgets=[36000,36000],total_battles=4)

def captured():
 folder=ROOT/'docs/evidence/guards-v2/guard-state-v2/normal'
 r=json.loads((folder/'battle_result.json').read_text());p=plan();p['provenance']=r['provenance']
 task=dict(ordinal=0,trainer_a=r['trainer_a'],trainer_b=r['trainer_b'],repetition=0,orientation=0,seed=r['seed'],max_frames=r['max_frames'],match_id='real-capture')
 msg=dict(ok=True,record=r,runtime_seconds=1.,completed_at='validation-fixture',worker_pid=1,artifact=archive(folder))
 return p,task,msg

def test_deterministic_ids_seeds_and_distinct_orientation():
 a=list(tasks(plan()));assert a==list(tasks(plan()))
 assert len({t['match_id'] for t in a})==4 and len({t['seed'] for t in a})==4
 assert a[0]['seed']==int(identity([SEED_VERSION,20260913,1,335,0,0])[:8],16)
 p=plan();p['master_seed']+=1;assert list(tasks(p))[0]['match_id']!=a[0]['match_id']

def test_million_task_schedule_is_lazy_and_bounded():
 p=plan();p['trainer_ids']=list(range(1,778));p['total_battles']=1205904
 assert count_tasks(p['trainer_ids'],'all_pairs',2)==1205904
 tracemalloc.start();iterator=tasks(p)
 for _ in range(2000):next(iterator)
 _,peak=tracemalloc.get_traced_memory();tracemalloc.stop()
 assert peak<2_000_000

def test_durable_resume_duplicates_and_configuration_mismatch(tmp_path):
 p,t,m=captured();path=tmp_path/'r.sqlite';s=Store(path,p);s.commit(t,m)
 assert s.state(t['match_id'])=='completed'
 with pytest.raises(sqlite3.IntegrityError):s.commit(t,m)
 with pytest.raises(sqlite3.IntegrityError):s.db.execute('DELETE FROM results')
 assert s.db.execute('PRAGMA journal_mode').fetchone()[0]=='wal'
 assert s.db.execute('PRAGMA synchronous').fetchone()[0]==2
 s.close();s=Store(path,p);assert s.counts()['completed']==1;s.close()
 with pytest.raises(ValueError,match='Incompatible'):Store(path,dict(p,master_seed=42))
 assert status(path)['completed']==1

def test_failure_is_not_a_completed_result(tmp_path):
 p,t,m=captured();s=Store(tmp_path/'r.sqlite',p)
 # Invalid terminal metadata is rejected, never persisted as a fake result.
 m['record']=dict(m['record'],terminal_from_engine=False)
 with pytest.raises(ValueError,match='terminal'):s.commit(t,m)
 assert s.counts()['completed']==0;s.close()

def test_portable_lock_and_worker_bounds(tmp_path):
 assert worker_count('1')==1 and worker_count('auto')>=1
 with pytest.raises(ValueError):worker_count(0)
 with run_lock(tmp_path/'lock'):
  with pytest.raises(RuntimeError):
   with run_lock(tmp_path/'lock'):pass
 with run_lock(tmp_path/'lock'):pass

def test_existing_legacy_store_is_not_modified(tmp_path):
 import shutil
 original=ROOT/'docs/evidence/smoke-v1/smoke-v1/results.sqlite';copy=tmp_path/'legacy.sqlite';shutil.copyfile(original,copy)
 before=hashlib.sha256(copy.read_bytes()).hexdigest()
 p,_,_=captured()
 with pytest.raises(ValueError,match='legacy'):Store(copy,p)
 assert hashlib.sha256(copy.read_bytes()).hexdigest()==before
