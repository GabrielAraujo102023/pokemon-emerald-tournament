"""Real spawn-worker equivalence, resume, individual failure and process interruption."""
import argparse,concurrent.futures as futures,json,multiprocessing,os,signal,sqlite3,subprocess,sys,time
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.parallel_plan import prepare,ROOT
from emerald_tournament.parallel_runner import run
from emerald_tournament.parallel_worker import initialize,execute
from emerald_tournament.parallel_store import Store
from emerald_tournament.parallel_tasks import tasks
from emerald_tournament.parallel_benchmark import logical_hashes
from emerald_tournament.parallel_export import export_capture

def wait_committed(process,directory,count=1):
 deadline=time.monotonic()+90
 while time.monotonic()<deadline:
  if process.poll() is not None:raise RuntimeError('Runner exited before interruption checkpoint')
  try:
   db=sqlite3.connect(directory/'results.sqlite');n=db.execute('SELECT count(*) FROM results').fetchone()[0];db.close()
   if n>=count:return logical_hashes(directory/'results.sqlite')
  except sqlite3.OperationalError:pass
  time.sleep(.1)
 raise RuntimeError('No committed result before watchdog')

def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
 report={'passed':False,'checks':{}}
 plan,context=prepare(ROOT/'config/parallel_validation.json')
 try:
  first=run(plan,context,out/'one',workers=1,limit=8)
  part=run(plan,context,out/'two',workers=2,limit=4)
  before=logical_hashes(out/'two/results.sqlite')
  resume=run(plan,context,out/'two',workers=2,limit=4)
  after=logical_hashes(out/'two/results.sqlite')
  report['checks']['partial_resume_preserves_commits']=set(before)<=set(after) and len(after)==8 and resume['completed_this_session']==4
  report['checks']['spawn_worker_equivalence']=after==logical_hashes(out/'one/results.sqlite')
  report['checks']['workers_persist']=len(first['worker_pids'])==1 and first['completed_this_session']==8 and len(part['worker_pids'])==2
  export_capture(out/'two',after[0][0],out/'exported')
  report['checks']['archive_export']=True
  # Run a real backend input validation failure and persist it without inventing a result.
  bad=next(tasks(plan));bad=dict(bad,trainer_a=0,match_id='invalid-input-validation')
  with futures.ProcessPoolExecutor(max_workers=1,mp_context=multiprocessing.get_context('spawn'),initializer=initialize,initargs=(dict(context,work_root=out/'failure-work'),)) as pool:
   failure=pool.submit(execute,bad).result(timeout=90)
  store=Store(out/'failure.sqlite',plan);store.commit(bad,failure)
  report['checks']['failure_not_success']=not failure['ok'] and store.state(bad['match_id'])=='failed' and store.counts()['completed']==0
  store.close()
  for label,hard in [('sigint',False),('killed',True)]:
   directory=out/label
   command=[sys.executable,str(ROOT/'tournament.py'),'run','--config',str(ROOT/'config/parallel_validation.json'),'--output',str(directory),'--workers','2','--inflight','2','--progress-seconds','1']
   with (out/f'{label}.log').open('w') as log:
    process=subprocess.Popen(command,stdout=log,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NEW_PROCESS_GROUP if os.name=='nt' else 0)
    try:
     committed=wait_committed(process,directory)
     if hard:process.kill()
     elif os.name=='nt':process.send_signal(signal.CTRL_BREAK_EVENT)
     else:process.send_signal(signal.SIGINT)
     process.wait(timeout=90)
    finally:
     if process.poll() is None:process.kill();process.wait()
   kept=logical_hashes(directory/'results.sqlite')
   report['checks'][label+'_commits_survive']=set(committed)<=set(kept)
   if not hard:report['checks']['sigint_clean_exit']=process.returncode==130
   # Resume interrupted stores to completion, then verify a completed run schedules nothing.
   resumed=run(plan,context,directory,workers=2)
   final=logical_hashes(directory/'results.sqlite')
   idle=run(plan,context,directory,workers=2)
   report['checks'][label+'_resume_deduplicates']=len(final)==plan['total_battles'] and set(kept)<=set(final) and idle['completed_this_session']==0 and resumed['complete']
  report['checks']['both_recoveries_equivalent']=logical_hashes(out/'sigint/results.sqlite')==logical_hashes(out/'killed/results.sqlite')
  report['passed']=all(report['checks'].values());assert report['passed'],report
 finally:(out/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
 print(json.dumps(report,indent=2))
if __name__=='__main__':main()
