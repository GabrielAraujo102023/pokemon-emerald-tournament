"""Read-only direct effect checks on the natural Marill/Torchic fixture."""
import argparse,json
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
proofs={'defense_curl':[],'scratch_damage':[]};repeat={}
for side in 'ab':
 d=Path('build/reports/curl-scratch-v2')/f'pair-{side}'
 states=[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()]
 for before,after in zip(states,states[1:]):
  actor=after['attacker']
  if actor not in (0,1) or before['species']!=after['species'] or before['slots']!=after['slots']:continue
  if after['current_move']==111 and after['stages'][actor][2]==before['stages'][actor][2]+1 and after['stages'][1-actor]==before['stages'][1-actor]:proofs['defense_curl'].append({'side':actor,'before':before,'after':after})
  if after['current_move']==10 and after['hp'][1-actor]<before['hp'][1-actor]:proofs['scratch_damage'].append({'side':actor,'before':before,'after':after})
 for n in ['events.bin','initial_parties.bin','final_parties.bin','engine_observations.jsonl','battle_result.json']:
  repeat[f'{side}/{n}']=(d/n).read_bytes()==(Path('build/reports/curl-scratch-v2-repeat')/f'pair-{side}'/n).read_bytes()
report={'passed':all(proofs.values()) and all(repeat.values()),'proofs':proofs,'repeat':repeat}
(a.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n');assert report['passed'];print('curl/scratch passed')
