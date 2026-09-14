"""Ownership checker regressions using inventory transitions from real captures."""
import importlib.util,json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('item_evidence',ROOT/'tools/validate_item_evidence.py')
mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)

def captured_transition():
    root=ROOT/'docs/evidence/fullrestore-cycle-v2/healing-a'
    observations=[json.loads(x) for x in (root/'engine_observations.jsonl').read_text().splitlines()]
    events=[json.loads(x) for x in (root/'events.jsonl').read_text().splitlines()]
    for before,after in zip(observations,observations[1:]):
        choices=[e for e in events if e['event']=='trainer_item_selected' and before['event_count']<=e['sequence']<after['event_count']]
        if choices:return before['inventory'],after['inventory'],choices
    raise AssertionError('Saved fixture contains no item selection')

def test_real_owner_consumption_passes():
    assert mod.inventory_transition_valid(*captured_transition())

def test_consuming_opponents_inventory_rejected():
    before,after,choices=captured_transition()
    changed=[dict(c,battler=1-c['battler']) for c in choices]
    assert not mod.inventory_transition_valid(before,after,changed)

def test_missing_consumption_rejected():
    before,after,choices=captured_transition()
    assert not mod.inventory_transition_valid(before,before,choices)

def test_unlogged_consumption_rejected():
    before,after,choices=captured_transition()
    assert not mod.inventory_transition_valid(before,after,[])
