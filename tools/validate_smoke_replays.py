import argparse,json,sqlite3,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.replay import replay
p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
db=sqlite3.connect(a.run/'results.sqlite');checks={}
for name,condition in [('terminal',"outcome != 'timeout'"),('timeout',"outcome = 'timeout'")]:
 mid=db.execute('SELECT match_id FROM results WHERE '+condition+' ORDER BY ordinal LIMIT 1').fetchone()[0]
 checks[name]=replay(a.run.resolve(),mid,(a.output/name).resolve())
db.close();(a.output/'validation.json').write_text(json.dumps({'passed':all(x['passed'] for x in checks.values()),'replays':checks},indent=2)+'\n')
