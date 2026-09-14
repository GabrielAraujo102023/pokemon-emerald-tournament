"""Concurrent eligibility assertions against a saved real-engine pre-action snapshot."""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
from emerald_tournament.evidence import simultaneous_fullrestore_eligible as eligible
def snapshot():
 return json.loads((ROOT/'docs/evidence/concurrent-items-v2/validation.json').read_text())['runs'][0]['eligibility_before']
def test_both_real_sides_eligible():
 assert eligible(snapshot())
def test_one_side_healthy_is_not_simultaneous():
 s=snapshot();s['hp'][1]=s['max_hp'][1];assert not eligible(s)
def test_opponent_inventory_cannot_supply_missing_item():
 s=snapshot();s['inventory'][0]=[0]*4;assert not eligible(s)
