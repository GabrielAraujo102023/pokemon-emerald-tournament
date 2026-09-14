"""Natural Shadow Tag restriction and no-reserve negative switch checks."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
from emerald_tournament.evidence import shadow_tag_active,no_reserve_switches
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
 b=ROOT/'build/pokeemerald';r=ROOT/'build/reports';report={'passed':False,'runs':[]}
 try:
  for side,(a,c) in enumerate([(88,475),(475,88)]):
   out=args.output/f'trapped-side-{side}'
   result=run_battle(trainer_a=a,trainer_b=c,seed=12345,rom=b/'pokeemerald_modern.gba',elf=b/'pokeemerald_modern.elf',checkpoint=r/'constructor-ready.ss',manifest_path=r/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=out,max_frames=18000,observe_engine=True)
   es=[json.loads(x) for x in (out/'events.jsonl').read_text().splitlines()];obs=[json.loads(x) for x in (out/'engine_observations.jsonl').read_text().splitlines()]
   party=json.loads((out/f"party_{'a' if side==0 else 'b'}.json").read_text());assert len(party)>1 and all(m['hp']>0 for m in party)
   blocked=[]
   for e in es:
    if e['event'] not in ['move_selected','trainer_item_selected','switch_selected'] or e['battler']!=side:continue
    before=[o for o in obs if o['event_count']<=e['sequence']]
    if not before:continue
    o=before[-1]
    if not shadow_tag_active(o,side):continue
    assert e['event']!='switch_selected',('Illegal switch under Shadow Tag',e,o)
    # Reserve health is proven here before any target-side faint in this fixture.
    if not any(f['event']=='faint' and f['battler']==side and f['sequence']<e['sequence'] for f in es):blocked.append(dict(action=e,state=o))
   assert blocked,('No trapped living-reserve AI decision observed',side)
   report['runs'].append(dict(side=side,result=result,trapped_actions_with_reserve=blocked));print('Shadow Tag side',side,'passed',len(blocked),flush=True)
  noreserve=ROOT/'docs/evidence/fullrestore-cycle-v2/healing-a'
  es=[json.loads(x) for x in (noreserve/'events.jsonl').read_text().splitlines()]
  for side,name in [(0,'a'),(1,'b')]:
   assert no_reserve_switches(json.loads((noreserve/f'party_{name}.json').read_text()),es,side)
  report['no_reserve_evidence']=str(noreserve.relative_to(ROOT));report['passed']=True
 finally:(args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__':main()
