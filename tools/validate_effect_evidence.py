"""Representative source-engine effect proofs; no damage or AI simulation."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.evidence import damage_transitions,dig_cycles
ROOT=Path(__file__).resolve().parents[1]
def load(folder,side='a'):
 d=ROOT/'build/reports'/folder/f'pair-{side}'
 return d,[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()],[json.loads(x) for x in (d/'events.jsonl').read_text().splitlines()]
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
 proofs={name:[] for name in ['type_immunity','accuracy_miss','critical_damage','move_stat_stage','intimidate','held_berry','dig_charge_release']}
 for suffix in ['a','b']:
  d,obs,events=load('immunity-psychic-dark-v2',suffix)
  for before,after in zip(obs,obs[1:]):
   side=after['attacker'];target=1-side
   if side in (0,1) and after['current_move']==94 and after['move_flags']&8 and not before['move_flags']&8 and 17 in after['types'][target] and before['hp'][target]==after['hp'][target]:
    proofs['type_immunity'].append(dict(capture=str(d),before=before,after=after))
  d,obs,events=load('intimidate-mightyena-linoone-v2',suffix)
  first_choice=min(e['sequence'] for e in events if e['event']=='move_selected')
  for before,after in zip(obs,obs[1:]):
   if before['species']!=after['species'] or before['slots']!=after['slots']:continue
   for side in (0,1):
    if after['event_count']<=first_choice and after['abilities'][1-side]==22 and after['last_ability']==22 and after['current_move']==0 and before['stages'][side][1]==6 and after['stages'][side][1]==5:
     proofs['intimidate'].append(dict(side=side,capture=str(d),before=before,after=after))
  d=ROOT/'build/reports/fullrestore-cindy-winston-v1'/f'pair-{suffix}'
  obs=[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()]
  # This fixture has Tackle/Growl/Tail Whip; it cannot introduce Protect misses.
  for before,after in zip(obs,obs[1:]):
   if before['slots']!=after['slots'] or before['species']!=after['species']:continue
   if after['move_flags']&1 and not before['move_flags']&1 and after['current_move']==33:
    proofs['accuracy_miss'].append(dict(capture=str(d),before=before,after=after))
   if after['current_move'] in (39,45) and before['stages']!=after['stages']:
    proofs['move_stat_stage'].append(dict(capture=str(d),before=before,after=after))
  proofs['critical_damage'] += [dict(capture=str(d),**v) for v in damage_transitions(obs,critical=True)]
  d=ROOT/'build/reports/potions-held-berry-v2'/f'items-{suffix}'
  obs=[json.loads(x) for x in (d/'engine_observations.jsonl').read_text().splitlines()]
  for i,(before,after) in enumerate(zip(obs,obs[1:])):
   if before['slots']!=after['slots'] or before['species']!=after['species'] or after['item']!=139:continue
   for side in (0,1):
    if not 0<before['hp'][side]<after['hp'][side] or after['hp'][side]!=min(before['hp'][side]+10,after['max_hp'][side]):continue
    earlier=next((v for v in reversed(obs[:i+1]) if v['held_items'][side]==139 and v['slots']==after['slots'] and v['species']==after['species']),None)
    removed=next((v for v in obs[i+1:] if v['held_items'][side]==0 and v['slots']==after['slots'] and v['species']==after['species']),None)
    if earlier and removed and removed['event_count']==after['event_count'] and before['hp'][1-side]==after['hp'][1-side]:
     proofs['held_berry'].append(dict(side=side,capture=str(d),held_before=earlier,before=before,after=after,removed=removed))
  d,obs,events=load('dig-sandslash-magnemite-v2',suffix)
  party=[json.loads((d/f'party_{side}.json').read_text()) for side in 'ab']
  for side in (0,1):
   slots=[slot for slot in range(4) if party[side][0][f'move{slot}']==91]
   if slots:proofs['dig_charge_release'] += [dict(capture=str(d),**v) for v in dig_cycles(obs,side,slots[0])]
 report={'passed':all(proofs.values()),'proofs':proofs}
 (args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
 print({k:len(v) for k,v in proofs.items()});assert report['passed']
if __name__=='__main__':main()
