"""Natural same-trainer Magikarp repeat, PP exhaustion and Struggle recoil."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_protocol import elf_symbol
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
base=Path('build/reports/struggle-magikarp-v2');d=base/'pair-a'
events=[json.loads(x) for x in (d/'events.jsonl').read_text().splitlines()]
obs=[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()]
start=elf_symbol(Path('build/pokeemerald/pokeemerald_modern.elf'),'BattleScript_DoRecoil');end=elf_symbol(Path('build/pokeemerald/pokeemerald_modern.elf'),'BattleScript_RecoilEnd')
proof=[]
for i,(before,after) in enumerate(zip(obs,obs[1:])):
 side=after['attacker']
 if side not in (0,1) or after['current_move']!=165 or any(after['pp'][side]) or not start<=after['script']<end:continue
 if before['hp'][side]<=after['hp'][side]:continue
 hit=next(((x,y) for x,y in reversed(list(zip(obs[:i+1],obs[1:i+2]))) if y['current_move']==165 and y['attacker']==side and x['hp'][1-side]>y['hp'][1-side]),None)
 if hit and before['hp'][side]-after['hp'][side]==min(before['hp'][side],max(1,(hit[0]['hp'][1-side]-hit[1]['hp'][1-side])//4)):
  proof.append(dict(side=side,damage_before=hit[0],damage_after=hit[1],before=before,after=after))
first=min(e['sequence'] for e in events if e['event']=='move_execution' and e['value0']==165)
splashes={side:sum(e['event']=='move_execution' and e['value0']==150 and e['battler']==side and e['sequence']<first for e in events) for side in (0,1)}
repeat={name:(d/name).read_bytes()==(base/'pair-b'/name).read_bytes() for name in ['events.bin','initial_parties.bin','final_parties.bin','engine_observations.jsonl','battle_result.json']}
report=dict(passed={x['side'] for x in proof}=={0,1} and all(v==40 for v in splashes.values()) and all(repeat.values()),proofs=proof,splashes_before_struggle=splashes,repeat=repeat,scope='Unmodified Darian 696 versus same concrete entry: repeat, not side-symmetry proof or tournament result')
(a.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n');assert report['passed'];print('Struggle exhaustion and recoil passed',len(proof))
