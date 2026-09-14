"""Evidence-checker regressions using captured real-engine fixture records."""
import importlib.util
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('validate_switch',ROOT/'tools/validate_switch.py')
module=importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


def fixture():
    root=ROOT/'docs/evidence/voluntary-switch/side-0'
    return ([json.loads(x) for x in (root/'events.jsonl').read_text().splitlines()],
            [json.loads(x) for x in (root/'engine_observations.jsonl').read_text().splitlines()],
            json.loads((root/'party_a.json').read_text()))


def test_real_capture_proves_switch():
    assert module.verify(*fixture(),0)


def test_forced_replacement_is_not_voluntary():
    events,observations,party=fixture()
    for event in events:
        if event['event']=='switch_selected':event['event']='replacement'
    assert not module.verify(events,observations,party,0)


def test_wrong_loaded_species_rejected():
    events,observations,party=fixture()
    for observation in observations:observation['species'][0]=0
    assert not module.verify(events,observations,party,0)


def test_no_subsequent_ai_action_rejected():
    events,observations,party=fixture()
    events=[e for e in events if e['event']!='move_selected']
    assert not module.verify(events,observations,party,0)
