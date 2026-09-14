"""Auditable OT initialization experiment, not full Emerald party initialization.

The caller must specify Random32 half ordering until target execution validates
it. Serialization is canonical JSON of recorded fields, never a GBA memory image.
"""
from __future__ import annotations

import json

from .rng import EmeraldRng
from .teams import reconstruct


def generate_ot(rng: EmeraldRng, personality: int, *, half_order: str) -> dict:
    if half_order not in ("low_first", "high_first"):
        raise ValueError("Specify low_first or high_first; target order is not yet certified")
    if not 0 <= personality <= 0xFFFFFFFF:
        raise ValueError("Personality must fit u32")
    attempts = []
    while True:
        before = rng.state
        first, second = rng.random16(), rng.random16()
        low, high = (first, second) if half_order == "low_first" else (second, first)
        ot = low | (high << 16)
        shiny_value = low ^ high ^ (personality & 0xFFFF) ^ (personality >> 16)
        attempts.append(dict(state_before=before, outputs=[first, second], ot_id=ot,
                             shiny_value=shiny_value, rejected=shiny_value < 8, state_after=rng.state))
        if shiny_value >= 8:
            return dict(ot_id=ot, attempts=attempts)


def initialization_record(trainer_a: dict, trainer_b: dict, seed: int, data: dict, *, half_order: str) -> bytes:
    rng = EmeraldRng(seed)
    teams = []
    for trainer in (trainer_a, trainer_b):
        team = reconstruct(trainer, data)
        for mon in team["party"]:
            record = generate_ot(rng, mon["personality"], half_order=half_order)
            mon["ot_id"] = record["ot_id"]
            mon["ot_trace"] = record["attempts"]
        team["limitations"] = ["Recorded fields only; full CreateMon, save state and packed bytes not validated"]
        teams.append(team)
    result = dict(schema_version=1, policy="ot-initialization-experiment-v1", half_order=half_order,
                  seed=seed, party_order="A then B, source slot order", teams=teams,
                  post_construction_rng=rng.state, calls=rng.calls,
                  engine_validation="not_run", frame_rng="not modeled during this isolated experiment")
    return (json.dumps(result, sort_keys=True, separators=(",", ":")) + "\n").encode()
