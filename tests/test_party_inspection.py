from pathlib import Path
import pytest,json
from emerald_tournament.party_inspection import decode_growth
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'pokeemerald/src/pokemon.c'
def test_decoded_growth_matches_arm_getmondata():
 d=ROOT/'docs/evidence/guards-v2/guard-state-v2/normal'
 mons=decode_growth((d/'initial_parties.bin').read_bytes(),SOURCE)
 for side in (0,1):
  for slot,export in enumerate(json.loads((d/f'party_{"ab"[side]}.json').read_text())):
   assert all(export[k]==v for k,v in mons[side*6+slot].items())
def test_corruption_rejected():
 d=ROOT/'docs/evidence/guards-v2/guard-state-v2/normal'
 raw=bytearray((d/'initial_parties.bin').read_bytes());raw[32]^=1
 with pytest.raises(ValueError,match='checksum'):decode_growth(bytes(raw),SOURCE)
 with pytest.raises(ValueError,match='complete'):decode_growth(bytes(raw[:-1]),SOURCE)
