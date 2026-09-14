import json
import unittest
from pathlib import Path

from emerald_tournament.generation_data import extract_generation
from emerald_tournament.teams import default_moves, reconstruct

PROJECT = Path(__file__).resolve().parents[1]


class TeamTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = extract_generation(PROJECT / "pokeemerald", PROJECT)
        cls.trainers = json.loads((PROJECT / "data/generated/trainers.json").read_text())["trainers"]

    def test_all_constructor_arguments_against_original_function(self):
        count = 0
        for trainer in self.trainers:
            if not trainer["party"]:
                continue
            party = reconstruct(trainer, self.data)["party"]
            actual = [dict(species_id=m["species_id"], level=m["level"], iv=m["ivs"][0], personality=m["personality"]) for m in party]
            self.assertEqual(actual, self.data["constructor_calls"][str(trainer["id"])] , trainer["constant"])
            count += len(party)
            for mon in party:
                self.assertEqual(mon["ability_slot"], 0)
                self.assertEqual(mon["current_hp"], mon["stats"]["hp"])
                self.assertEqual(len(mon["pp"]), 4)
        self.assertEqual(count, 1825)

    def test_duplicate_move_does_not_shift_oldest(self):
        self.assertEqual(default_moves([[1, 1], [2, 2], [3, 3], [4, 4], [5, 2], [6, 5]], 5), [1, 2, 3, 4])
        self.assertEqual(default_moves([[1, 1], [2, 2], [3, 3], [4, 4], [5, 2], [6, 5]], 6), [2, 3, 4, 5])
        self.assertEqual(default_moves([[1, 1], [4, 2]], 3), [1, 0, 0, 0])

    def test_sawyer_source_fixture(self):
        trainer = next(t for t in self.trainers if t["constant"] == "TRAINER_SAWYER_1")
        mon = reconstruct(trainer, self.data)["party"][0]
        # Emerald bytes: SAWYER + GEODUDE = 2570; first-slot low byte 0x88.
        self.assertEqual(mon["personality"], 2570 * 256 + 136)
        self.assertEqual(mon["stats"]["hp"], 47)
        self.assertEqual(mon["moves"], ["MOVE_MUD_SPORT", "MOVE_ROCK_THROW", "MOVE_MAGNITUDE", "MOVE_SELF_DESTRUCT"])
        self.assertEqual(mon["held_item"], "ITEM_NONE")
        self.assertEqual(mon["pp"], [15, 15, 30, 5])

    def test_reproducible_generation_artifact(self):
        self.assertEqual(self.data, json.loads((PROJECT / "data/generated/generation.json").read_text()))

    def test_empty_party_rejected(self):
        with self.assertRaises(ValueError):
            reconstruct(self.trainers[0], self.data)


if __name__ == "__main__":
    unittest.main()
