"""Real emulator tests only. No transport mocks or synthetic battle outcomes."""
import json
import os
import shutil
import tempfile
import unittest
from pathlib import Path

from emerald_tournament.emu_battle import run_battle

ROOT = Path(__file__).resolve().parents[2]


class EmulatedBattleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.bridge = Path(os.environ.get("EMERALD_BRIDGE", ROOT / "build/emulator/emerald-mgba-bridge")).resolve()
        missing = []
        if not cls.bridge.is_file() or not os.access(cls.bridge, os.X_OK):
            missing.append(f"executable mGBA bridge: {cls.bridge}")
        if not shutil.which("arm-none-eabi-gcc"):
            missing.append("ARM compiler: arm-none-eabi-gcc")
        if missing:
            raise unittest.SkipTest("REAL BATTLE NOT VALIDATED; missing " + "; ".join(missing) + ". See docs/emulator_backend.md")
        # Once required binaries exist, missing/bad artifacts are errors, not skips.
        cls.inputs = {name: Path(os.environ[f"EMERALD_{name.upper()}"]).resolve() for name in ("rom", "elf", "checkpoint", "manifest")}

    def battle(self, directory, seed):
        result = run_battle(trainer_a=1, trainer_b=335, seed=seed, bridge=self.bridge,
                            output=directory, manifest_path=self.inputs["manifest"],
                            **{k:v for k,v in self.inputs.items() if k != "manifest"})
        self.assertTrue(result["terminal_from_engine"])
        self.assertIn(result["outcome"], ("a_win", "b_win", "draw"))
        self.assertEqual(result["rng_start"], seed)
        events = [json.loads(line) for line in (directory / "events.jsonl").read_text().splitlines()]
        kinds = {event["event"] for event in events}
        self.assertTrue({"battle_start", "move_selected", "move_execution", "battle_end"} <= kinds)
        self.assertEqual({e["battler"] for e in events if e["event"] == "move_selected"}, {0, 1})
        return result

    def test_same_seed_full_bytes_result_rng_and_trace(self):
        with tempfile.TemporaryDirectory() as temp:
            a, b = Path(temp)/"a", Path(temp)/"b"
            first, second = self.battle(a, 12345), self.battle(b, 12345)
            self.assertEqual(first, second)
            for filename in ("initial_parties.bin", "final_parties.bin", "party_a.json", "party_b.json", "events.bin"):
                self.assertEqual((a/filename).read_bytes(), (b/filename).read_bytes())

    def test_different_seed_recorded_rng_difference(self):
        with tempfile.TemporaryDirectory() as temp:
            a, b = Path(temp)/"a", Path(temp)/"b"
            first, second = self.battle(a, 12345), self.battle(b, 12346)
            self.assertNotEqual(first["rng_after_party_init"], second["rng_after_party_init"])
            self.assertNotEqual(first["trace_sha256"], second["trace_sha256"])
            for path, seed in [(a, 12345), (b, 12346)]:
                events = [json.loads(line) for line in (path/"events.jsonl").read_text().splitlines()]
                rng_events = [e for e in events if e["event"] == "rng_call"]
                self.assertTrue(rng_events, "Integration requires initialization RNG-call evidence")
                self.assertEqual(rng_events[0]["value0"], seed)
                for event in rng_events:
                    self.assertEqual(event["value1"], (1103515245*event["value0"]+24691)&0xFFFFFFFF)
                    self.assertEqual(event["rng"], event["value1"])
