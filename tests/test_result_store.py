import copy,json,sqlite3
from pathlib import Path
import pytest
from emerald_tournament.result_store import connect,append_result,rows
from emerald_tournament.ranking import standings
ROOT=Path(__file__).resolve().parents[1]
def actual():
 r=json.loads((ROOT/'docs/evidence/guards-v2/guard-state-v2/normal/battle_result.json').read_text())
 m={k:r[k] for k in ('trainer_a','trainer_b','seed')};m.update(match_id='actual-evidence',ordinal=0,repetition=0,orientation=0)
 return m,r

def test_results_immutable_deduplicated_and_resume_pinned(tmp_path):
 m,r=actual();db=connect(tmp_path/'results.sqlite',{'source':'real guard evidence'})
 append_result(db,m,r,'capture')
 with pytest.raises(sqlite3.IntegrityError):append_result(db,m,r,'second-capture')
 with pytest.raises(sqlite3.IntegrityError):db.execute('UPDATE results SET outcome=\'draw\'')
 with pytest.raises(sqlite3.IntegrityError):db.execute('DELETE FROM results')
 db.close()
 db=connect(tmp_path/'results.sqlite',{'source':'real guard evidence'});assert len(rows(db))==1;db.close()
 with pytest.raises(ValueError,match='mismatch'):connect(tmp_path/'results.sqlite',{'source':'changed'})

def test_nonterminal_win_and_validation_intervention_rejected(tmp_path):
 m,r=actual();db=connect(tmp_path/'r.sqlite',{})
 invalid=copy.deepcopy(r);invalid['terminal_from_engine']=False
 with pytest.raises(ValueError,match='terminal'):append_result(db,m,invalid,'invalid')
 invalid=copy.deepcopy(r);invalid['validation_overrides']={'badges':'all'}
 with pytest.raises(ValueError,match='intervention'):append_result(db,m,invalid,'override')
 assert not rows(db);db.close()

def test_ranking_from_real_outcome_conserves_elo(tmp_path):
 m,r=actual();db=connect(tmp_path/'r.sqlite',{});append_result(db,m,r,'capture')
 config=json.loads((ROOT/'config/ranking.yaml').read_text())
 ranked=standings(rows(db),[1,335],config)
 assert ranked[0]['trainer_id']==335 and ranked[0]['wins']==1 and ranked[0]['elo']==1516
 assert ranked[1]['losses']==1 and sum(x['elo'] for x in ranked)==3000
 db.close()

def test_actual_smoke_timeouts_excluded_from_ratings():
 d=ROOT/'docs/evidence/smoke-v1/smoke-v1'
 db=sqlite3.connect(d/'results.sqlite');records=rows(db);db.close()
 cfg=json.loads((ROOT/'config/ranking.yaml').read_text());ids=[114,136,320,523,526,532,535,605]
 all_ranks=standings(records,ids,cfg)
 terminal_ranks=standings([r for r in records if r['record']['outcome']!='timeout'],ids,cfg)
 assert [r['elo'] for r in all_ranks]==[r['elo'] for r in terminal_ranks]
 assert sum(r['timeouts'] for r in all_ranks)==10
 assert sum(r['games_played'] for r in all_ranks)==54
