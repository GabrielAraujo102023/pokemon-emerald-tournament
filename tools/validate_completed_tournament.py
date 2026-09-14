"""Audit every completed capture, schedule identity and no-op resume."""
import argparse,json,sqlite3,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.tournament import preflight,verify_capture,run
from emerald_tournament.result_store import rows,identity
p=argparse.ArgumentParser();p.add_argument('--config',type=Path,required=True);p.add_argument('--run',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
report,inputs,population=preflight(a.config.resolve());db=sqlite3.connect(a.run/'results.sqlite');records=rows(db);failures=db.execute('SELECT count(*) FROM failures').fetchone()[0];db.close()
assert len(records)==report['expected_battles'];schedule={m['match_id']:m for m in report['schedule']};assert set(schedule)=={r['match_id'] for r in records}
for entry in records:
 match=schedule[entry['match_id']];folder=a.run/entry['artifact'];r=verify_capture(folder,match,report,population)
 assert r==entry['record'] and entry['ordinal']==match['ordinal']
 assert all(r[k]==match[k] for k in ('trainer_a','trainer_b','seed','max_frames'))
 if r['terminal_from_engine']:assert (folder/'final_parties.bin').read_bytes()==(folder/'stopped_parties.bin').read_bytes()
before=identity(records);artifacts=sorted(x.name for x in (a.run/'battles').iterdir());summary=run(a.config.resolve(),a.run.resolve())
db=sqlite3.connect(a.run/'results.sqlite');after=rows(db);db.close()
assert identity(after)==before and summary['newly_completed']==0 and summary['complete']
assert artifacts==sorted(x.name for x in (a.run/'battles').iterdir())
result=dict(passed=True,run_id=report['run_id'],verified_captures=len(records),failed_attempts=failures,no_op_resume=summary,record_set_sha256=before,counts={k:sum(r['record']['outcome']==k for r in records) for k in ('a_win','b_win','draw','timeout')})
(a.output/'validation.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
