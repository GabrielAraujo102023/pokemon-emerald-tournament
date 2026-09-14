"""Audit actual persisted smoke records and prove a completed resume is a no-op."""
import argparse,json,sqlite3,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.tournament import run
from emerald_tournament.result_store import rows
from emerald_tournament.ranking import standings
p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--config',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
def snapshot():
 db=sqlite3.connect(a.run/'results.sqlite');records=rows(db);metadata=json.loads(db.execute('SELECT preflight FROM metadata').fetchone()[0]);errors=db.execute('SELECT count(*) FROM failures').fetchone()[0];db.close();return records,metadata,errors
before,preflight,failures=snapshot();artifacts=sorted(p.name for p in (a.run/'battles').iterdir())
summary=run(a.config.resolve(),a.run.resolve());after,_,_=snapshot()
assert summary['newly_completed']==0 and summary['complete'] and before==after and artifacts==sorted(p.name for p in (a.run/'battles').iterdir())
assert {r['match_id'] for r in after}=={m['match_id'] for m in preflight['schedule']}
ranked=standings(after,preflight['supported_ids'],preflight['ranking'])
assert ranked==standings(list(reversed(after)),preflight['supported_ids'],preflight['ranking'])
counts={k:sum(r['record']['outcome']==k for r in after) for k in ('a_win','b_win','draw','timeout')}
assert counts['timeout']>0 and counts['a_win']+counts['b_win']>0
assert sum(r['wins'] for r in ranked)==sum(r['losses'] for r in ranked)==counts['a_win']+counts['b_win']
assert sum(r['timeouts'] for r in ranked)==counts['timeout']*2
assert abs(sum(r['elo'] for r in ranked)-len(ranked)*1500)<1e-8
report=dict(passed=True,run_id=preflight['run_id'],counts=counts,resume=summary,failures=failures,immutable_records_unchanged=True,no_new_battle_directories=True,ranking_order_independent_of_query_order=True,overflow_evidence='docs/evidence/ring-v2-cycle/ring-v2-long/validation.json')
(a.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n');print(counts)
