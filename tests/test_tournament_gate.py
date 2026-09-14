import json
from pathlib import Path
import pytest
from emerald_tournament.tournament import preflight
ROOT=Path(__file__).resolve().parents[1]
def test_unapproved_full_configuration_rejected_before_execution(tmp_path):
 cfg=json.loads((ROOT/'config/smoke_singles.json').read_text());cfg.update(mode='full',pairing='all_pairs',tournament_authorized=False)
 p=tmp_path/'unapproved.json';p.write_text(json.dumps(cfg))
 with pytest.raises(ValueError,match='authorized'):preflight(p)
def test_unknown_run_mode_rejected(tmp_path):
 cfg=json.loads((ROOT/'config/smoke_singles.json').read_text());cfg['mode']='ungated'
 p=tmp_path/'unknown.json';p.write_text(json.dumps(cfg))
 with pytest.raises(ValueError,match='Unknown run mode'):preflight(p)
