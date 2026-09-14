"""Bounded natural-team seed search; saves every actual engine run."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);p.add_argument('--seeds',type=int,default=16);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
 build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports';summary={'found':False,'trials':[]}
 try:
  for seed in range(a.seeds):
   out=a.output/f'seed-{seed}'
   result=run_battle(trainer_a=114,trainer_b=136,seed=seed,rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=reports/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=out,max_frames=36000)
   events=[json.loads(x) for x in (out/'events.jsonl').read_text().splitlines()];turns={}
   for e in events:
    if e['event']=='trainer_item_selected':turns.setdefault(e['turn'],set()).add(e['battler'])
   matched=[turn for turn,sides in turns.items() if sides=={0,1}]
   summary['trials'].append({'seed':seed,'result':result,'same_turn_items':matched});print(seed,result['outcome'],'same-turn',matched,flush=True)
   if matched:summary.update(found=True,seed=seed,turns=matched);break
 finally:(a.output/'search.json').write_text(json.dumps(summary,indent=2)+'\n')
if __name__=='__main__':main()
