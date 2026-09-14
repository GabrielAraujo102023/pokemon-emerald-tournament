"""Natural simultaneous Full Restore eligibility, isolation, and exact replay."""
from pathlib import Path
import sys,json,argparse
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
from emerald_tournament.evidence import simultaneous_fullrestore_eligible
from validate_item_evidence import validate
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
 build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports';tr={t['id']:t for t in json.load(open(ROOT/'data/generated/trainers.json'))['trainers']}
 report={'passed':False,'runs':[],'checks':{}}
 try:
  for name in ['observed-a','observed-b']:
   out=args.output/name
   result=run_battle(trainer_a=114,trainer_b=136,seed=10,rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=reports/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=out,max_frames=36000,observe_engine=True)
   proof=validate(out,tr,build/'pokeemerald_modern.elf');assert all(proof['checks'].values())
   es=[json.loads(x) for x in (out/'events.jsonl').read_text().splitlines()];obs=[json.loads(x) for x in (out/'engine_observations.jsonl').read_text().splitlines()]
   choices=[e for e in es if e['event']=='trainer_item_selected' and e['turn']==10]
   assert {e['battler'] for e in choices}=={0,1} and all(e['value0']==19 for e in choices)
   before=[o for o in obs if o['event_count']<=min(e['sequence'] for e in choices)][-1]
   # Emerald Full Restore AI uses integer hp < maxHP/4 for the healing branch.
   assert simultaneous_fullrestore_eligible(before),before
   report['runs'].append({'result':result,'eligibility_before':before,'selections':choices,'item_proof':proof})
   print(name,'concurrent eligibility and inventory isolation passed',flush=True)
  compact=reports/'concurrent-search-v2/seed-10';a=args.output/'observed-a';b=args.output/'observed-b'
  for f in ['events.bin','initial_parties.bin','final_parties.bin','stopped_parties.bin','battle_result.json']:
   report['checks']['compact_vs_observed_'+f]=(compact/f).read_bytes()==(a/f).read_bytes()
   report['checks']['observed_repeat_'+f]=(a/f).read_bytes()==(b/f).read_bytes()
  report['checks']['observation_repeat']=(a/'engine_observations.jsonl').read_bytes()==(b/'engine_observations.jsonl').read_bytes()
  assert all(report['checks'].values()),report['checks'];report['passed']=True
 finally:(args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__':main()
