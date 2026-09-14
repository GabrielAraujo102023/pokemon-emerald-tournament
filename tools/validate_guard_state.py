"""Actual terminal party growth and explicit test-only badge-state validation."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
from emerald_tournament.party_inspection import decode_growth
ROOT=Path(__file__).resolve().parents[1]
def check_growth(folder):
 before=decode_growth((folder/'initial_parties.bin').read_bytes(),ROOT/'pokeemerald/src/pokemon.c')
 after=decode_growth((folder/'final_parties.bin').read_bytes(),ROOT/'pokeemerald/src/pokemon.c')
 for side in (0,1):
  exported=json.loads((folder/f'party_{"ab"[side]}.json').read_text())
  for slot,mon in enumerate(exported):
   raw=before[side*6+slot]
   assert all(raw[k]==mon[k] for k in raw), (raw,mon)
 assert all(all(a[k]==b[k] for k in ('species','experience','friendship','level','personality','ot_id')) for a,b in zip(before,after))
 return {'initial':before,'final':after,'experience_friendship_level_unchanged':True}
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);p.add_argument('--swapped',action='store_true');args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
 report={'passed':False,'runs':[]}
 try:
  for name,a,b in [('normal',1,335),('badges',1,335)]:
   d=args.output/name
   if args.swapped:a,b=b,a
   result=run_battle(trainer_a=a,trainer_b=b,seed=12345,rom=ROOT/'build/pokeemerald/pokeemerald_modern.gba',elf=ROOT/'build/pokeemerald/pokeemerald_modern.elf',checkpoint=ROOT/'build/reports/constructor-ready.ss',manifest_path=ROOT/'build/reports/battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=d,max_frames=36000,observe_engine=True,validation_all_badges=name=='badges')
   assert result['terminal_from_engine']
   report['runs'].append({'name':name,'result':result,'growth':check_growth(d)})
  report['badge_equivalence']={n:(args.output/'normal'/n).read_bytes()==(args.output/'badges'/n).read_bytes() for n in ('events.bin','initial_parties.bin','final_parties.bin','engine_observations.jsonl')}
  assert all(report['badge_equivalence'].values()), report['badge_equivalence']
  report['passed']=True
 finally:
  (args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
 print('guard state passed')
if __name__=='__main__':main()
