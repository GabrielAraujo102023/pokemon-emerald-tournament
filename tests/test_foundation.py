import json
import subprocess
import tempfile
import unittest
from pathlib import Path

from emerald_tournament.extract import extract
from emerald_tournament.rng import EmeraldRng

PROJECT = Path(__file__).resolve().parents[1]
UPSTREAM = PROJECT / "pokeemerald"


class ExtractionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = extract(UPSTREAM, PROJECT)
        cls.entries = {t["constant"]: t for t in cls.data["trainers"]}

    def test_pinned_population_and_party_invariants(self):
        self.assertEqual(len(self.entries), 855)
        self.assertEqual(sum(t["double_battle"] for t in self.entries.values()), 77)
        for trainer in self.entries.values():
            self.assertEqual(trainer["party_size"], len(trainer["party"]))
            for mon in trainer["party"]:
                self.assertTrue(1 <= mon["level"] <= 100)
                self.assertTrue(0 <= mon["fixed_iv"] <= 31)
                self.assertEqual(mon["moves"] is not None, bool(trainer["party_format"] & 1))
                if mon["moves"] is not None:
                    self.assertEqual(len(mon["moves"]), 4)

    def test_known_source_examples(self):
        sawyer = self.entries["TRAINER_SAWYER_1"]
        self.assertEqual(sawyer["party_size"], 1)
        self.assertEqual(sawyer["party"][0]["species"], "SPECIES_GEODUDE")
        self.assertEqual(sawyer["party"][0]["level"], 21)
        self.assertIn("ITEM_FULL_RESTORE", self.entries["TRAINER_WALLACE"]["battle_items"])
        self.assertEqual(self.entries["TRAINER_NONE"]["category"], "unused")
        self.assertEqual(self.entries["TRAINER_ROSE_2"]["category"], "rematch")

    def test_generated_artifact_is_reproducible(self):
        saved = json.loads((PROJECT / "data/generated/trainers.json").read_text())
        self.assertEqual(saved, self.data)


class RngTests(unittest.TestCase):
    def test_against_compiled_upstream_random_c(self):
        with tempfile.TemporaryDirectory() as temp:
            work = Path(temp)
            (work / "global.h").write_text("#include <stdint.h>\ntypedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;\n#define EWRAM_DATA\n#define COMMON_DATA\n")
            (work / "main.c").write_text('#include <stdio.h>\n#include "global.h"\n#include "random.h"\nint main(void) { gRngValue=0xffffffffu; for(int i=0;i<1000;i++) printf("%u\\n",Random()); }\n')
            subprocess.run(["cc", "-I", str(work), "-I", str(UPSTREAM / "include"), str(UPSTREAM / "src/random.c"), str(work / "main.c"), "-o", str(work / "rng")], check=True)
            actual = subprocess.check_output([str(work / "rng")], text=True)
        rng = EmeraldRng(0xFFFFFFFF)
        self.assertEqual([rng.random16() for _ in range(1000)], [int(x) for x in actual.splitlines()])
        self.assertEqual(rng.calls, 1000)

    def test_seed_range_and_first_value(self):
        self.assertEqual(EmeraldRng(0).random16(), 0)
        for invalid in (-1, 2**32):
            with self.assertRaises(ValueError):
                EmeraldRng(invalid)


if __name__ == "__main__":
    unittest.main()
