import copy,json
from pathlib import Path
from emerald_tournament.evidence import damage_transitions,dig_cycles
BASE=Path(__file__).resolve().parents[1]/'docs/evidence/effects-v2'
def obs(folder):return [json.loads(x) for x in (BASE/folder/'engine_observations.jsonl').read_text().splitlines()]
def test_dig_requires_charge_release_hit_and_one_pp():
 states=obs('dig-sandslash-magnemite-v2/pair-a')
 assert len(dig_cycles(states,0,0))==3
 for state in states:state['pp'][0][0]=10
 assert not dig_cycles(states,0,0)
def test_dig_requires_underground_flag_and_damage():
 states=obs('dig-sandslash-magnemite-v2/pair-a')
 for state in states:state['status3'][0]=0
 assert not dig_cycles(states,0,0)
def test_critical_requires_damage_and_multiplier():
 report=json.loads((BASE/'effect-proof-v2-pp/validation.json').read_text())
 proof=report['proofs']['critical_damage'][0]
 pair=[proof['before'],proof['after']]
 assert damage_transitions(pair,critical=True)
 pair[1]['crit_multiplier']=1
 assert not damage_transitions(pair,critical=True)
