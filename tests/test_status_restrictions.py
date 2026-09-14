import json
from pathlib import Path
from emerald_tournament.evidence import status_applications,shadow_tag_active,no_reserve_switches
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'docs/evidence/restrictions-status-v2'
def observations(folder):return [json.loads(x) for x in (BASE/folder/'engine_observations.jsonl').read_text().splitlines()]
def test_real_paralysis_and_confusion():
 obs=observations('status-magnemite-gloom-v2/pair-a')
 assert status_applications(obs,'status1',64)
 assert status_applications(obs,'status2',7)
def test_real_sleep():
 assert status_applications(observations('sleep-skitty-magnemite-v2/pair-a'),'status1',7)
def test_party_loading_cannot_prove_status_application():
 obs=observations('sleep-skitty-magnemite-v2/pair-a')
 proof=status_applications(obs,'status1',7)[0]
 before,after=proof['before'],proof['after']
 before['slots']=[9,9]
 assert not status_applications([before,after],'status1',7)
def test_shadow_tag_state_is_live_opponent():
 report=json.loads((BASE/'switch-restrictions-v2/validation.json').read_text())
 state=report['runs'][0]['trapped_actions_with_reserve'][0]['state']
 assert shadow_tag_active(state,0)
 state['hp'][1]=0
 assert not shadow_tag_active(state,0)
def test_no_reserve_capture_rejects_added_switch():
 d=ROOT/'docs/evidence/fullrestore-cycle-v2/healing-a'
 party=json.loads((d/'party_a.json').read_text());events=[json.loads(x) for x in (d/'events.jsonl').read_text().splitlines()]
 assert no_reserve_switches(party,events,0)
 assert not no_reserve_switches(party,events+[{'event':'switch_selected','battler':0}],0)
