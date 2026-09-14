"""Prove representative status applications from actual paused-memory captures."""
from pathlib import Path
import json,sys,argparse
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.evidence import status_applications
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
 report={'passed':False,'proofs':{}}
 pairs=[('paralysis','status-magnemite-gloom-v2','status1',64,{78,84,85,86,87,209}),('confusion','status-magnemite-gloom-v2','status2',7,{48,109,352}),('sleep','sleep-skitty-magnemite-v2','status1',7,{47})]
 for name,folder,field,mask,moves in pairs:
  proofs=[]
  for side in ['a','b']:
   d=ROOT/'build/reports'/folder/f'pair-{side}';o=[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()]
   for proof in status_applications(o,field,mask):
    if proof['after']['current_move'] in moves:proofs.append(dict(capture=str(d.relative_to(ROOT)),**proof))
  report['proofs'][name]=proofs
  assert proofs,('Required status application not observed',name)
 report['passed']=True;(args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n');print({k:len(v) for k,v in report['proofs'].items()})
if __name__=='__main__':main()
