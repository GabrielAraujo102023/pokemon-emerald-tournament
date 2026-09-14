import copy,json
from pathlib import Path
from emerald_tournament.admission import build_population,evaluate
ROOT=Path(__file__).resolve().parents[1]
def test_population_accounts_for_every_entry_and_unknowns():
 r=build_population(ROOT)
 assert r['total_entries']==855 and r['supported_ids']==[114,136,320,523,526,532,535,605]
 assert all(t['reasons'] for t in r['entries'])
 assert all(not t['supported'] for t in r['entries'] if t['category'] in ('unknown','unused','standard_double'))
def test_unvalidated_move_and_double_cannot_be_admitted():
 trainers=json.loads((ROOT/'data/generated/trainers.json').read_text())['trainers'];g=json.loads((ROOT/'data/generated/generation.json').read_text());policy=json.loads((ROOT/'config/admission_policy.json').read_text())
 t=copy.deepcopy(trainers[114]);t['double_battle']=True
 assert not evaluate(t,g,policy,ROOT/'pokeemerald')['supported']
 t=copy.deepcopy(trainers[114]);t['party'][0]['moves']=['MOVE_ATTRACT','MOVE_NONE','MOVE_NONE','MOVE_NONE']
 r=evaluate(t,g,policy,ROOT/'pokeemerald');assert not r['supported'] and 'unvalidated move: MOVE_ATTRACT' in r['reasons']
