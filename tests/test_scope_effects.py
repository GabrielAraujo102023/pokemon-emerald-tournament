import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'docs/evidence/curl-struggle-v2'
def test_pp_exhaustion_and_actual_recoil_evidence():
 r=json.loads((BASE/'struggle-proof-v2/validation.json').read_text())
 assert r['passed'] and set(r['splashes_before_struggle'].values())=={40}
 assert {p['side'] for p in r['proofs']}=={0,1}
 for p in r['proofs']:
  s=p['side'];assert not any(p['after']['pp'][s]) and p['before']['hp'][s]>p['after']['hp'][s]
def test_defense_curl_self_stage_and_scratch_damage():
 r=json.loads((BASE/'curl-scratch-proof-v2/validation.json').read_text())
 assert r['passed']
 for p in r['proofs']['defense_curl']:
  s=p['side'];assert p['after']['stages'][s][2]==p['before']['stages'][s][2]+1
  assert p['after']['stages'][1-s]==p['before']['stages'][1-s]
