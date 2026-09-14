"""Actual ARM construction test; intentionally distinct from a battle test."""
from pathlib import Path
import subprocess,sys,unittest
ROOT=Path(__file__).resolve().parents[1]
class ArmConstructionRuntimeTests(unittest.TestCase):
    def test_same_and_different_seed_in_real_emulator(self):
        bridge=ROOT/'build/emulator/emerald-mgba-bridge'
        if not bridge.is_file():self.skipTest('Missing compiled mGBA bridge; ARM construction not validated')
        subprocess.run([sys.executable,str(ROOT/'tools/validate_arm_construction.py')],cwd=ROOT,check=True,capture_output=True,text=True)
