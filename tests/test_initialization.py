import json
import subprocess
import tempfile
import unittest
from pathlib import Path

from emerald_tournament.initialization import generate_ot, initialization_record
from emerald_tournament.rng import EmeraldRng

PROJECT = Path(__file__).resolve().parents[1]
UPSTREAM = PROJECT / "pokeemerald"


class InitializationTests(unittest.TestCase):
    def test_original_ot_rejection_loop_host_oracle(self):
        source = (UPSTREAM / "src/pokemon.c").read_text()
        start = source.index("        u32 shinyValue;", source.index("void CreateBoxMon("))
        end = source.index("    }\n    else if", start)
        loop = source[start:end]
        # Choose PID from first pair so the first candidate is guaranteed shiny,
        # testing the rejection branch without searching or changing Random().
        rng = EmeraldRng(12345)
        personality = rng.random16() | (rng.random16() << 16)
        with tempfile.TemporaryDirectory() as temp:
            work = Path(temp)
            (work / "global.h").write_text('#include <stdint.h>\ntypedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;\n#define EWRAM_DATA\n#define COMMON_DATA\n')
            macro = next(line for line in (UPSTREAM / "include/pokemon.h").read_text().splitlines() if line.startswith("#define GET_SHINY_VALUE"))
            code = '#include <stdio.h>\n#include "global.h"\n#include "random.h"\n#include "constants/pokemon.h"\n#define HIHALF(n) ((n)>>16)\n#define LOHALF(n) ((n)&65535)\n' + macro
            code += '\nint main(void) { u32 value; u32 personality=' + str(personality) + '; gRngValue=12345;\n' + loop + '\nprintf("%u %u\\n", value, gRngValue); }\n'
            (work / "oracle.c").write_text(code)
            subprocess.run(["cc", "-I", str(work), "-I", str(UPSTREAM / "include"), str(work / "oracle.c"), str(UPSTREAM / "src/random.c"), "-o", str(work / "oracle")], check=True)
            observed = tuple(map(int, subprocess.check_output([str(work / "oracle")], text=True).split()))
        candidates = []
        for order in ("low_first", "high_first"):
            rng = EmeraldRng(12345)
            record = generate_ot(rng, personality, half_order=order)
            self.assertTrue(record["attempts"][0]["rejected"])
            self.assertGreaterEqual(len(record["attempts"]), 2)
            candidates.append((record["ot_id"], rng.state))
        # Host compiler must match one order; this does not certify the ARM build.
        self.assertIn(observed, candidates)
        self.assertEqual(candidates[0][1], candidates[1][1])

    def test_repeatable_records_and_changed_seed(self):
        data = json.loads((PROJECT / "data/generated/generation.json").read_text())
        trainers = json.loads((PROJECT / "data/generated/trainers.json").read_text())["trainers"]
        a = next(t for t in trainers if t["constant"] == "TRAINER_SAWYER_1")
        b = next(t for t in trainers if t["constant"] == "TRAINER_WALLACE")
        first = initialization_record(a, b, 12345, data, half_order="low_first")
        self.assertEqual(first, initialization_record(a, b, 12345, data, half_order="low_first"))
        changed = initialization_record(a, b, 12346, data, half_order="low_first")
        self.assertNotEqual(first, changed)
        self.assertNotEqual(json.loads(first)["post_construction_rng"], json.loads(changed)["post_construction_rng"])
        for original, other in zip(json.loads(first)["teams"], json.loads(changed)["teams"]):
            for x, y in zip(original["party"], other["party"]):
                self.assertEqual(x["stats"], y["stats"])
                self.assertEqual(x["personality"], y["personality"])

    def test_half_order_is_explicit(self):
        with self.assertRaises(ValueError):
            generate_ot(EmeraldRng(0), 0, half_order="guess")


if __name__ == "__main__":
    unittest.main()
