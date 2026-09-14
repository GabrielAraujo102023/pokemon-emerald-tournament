"""Ordinary trainer battle-field reconstruction; OT identity remains unresolved.

No RNG is consumed here. Do not use this as a substitute for CreateMon's OT-ID
rejection loop when initializing a battle engine's shared RNG state.
"""
from __future__ import annotations


def default_moves(learnset: list[list[int]], level: int) -> list[int]:
    moves: list[int] = []
    for learned_level, move in learnset:
        if learned_level > level:
            break
        if move in moves:
            continue
        if len(moves) == 4:
            moves.pop(0)
        moves.append(move)
    return moves + [0] * (4 - len(moves))


def reconstruct(trainer: dict, data: dict) -> dict:
    if not trainer["party"]:
        raise ValueError("Empty trainer party cannot be reconstructed for battle")
    species_by_name = {s["constant"]: (int(i), s) for i, s in data["species"].items()}
    moves_by_name = {m["constant"]: int(i) for i, m in data["moves"].items()}
    name_hash = 0
    party = []
    for mon in trainer["party"]:
        species_id, species = species_by_name[mon["species"]]
        name_hash += sum(data["trainer_name_bytes"][str(trainer["id"])]) + sum(species["name_bytes"])
        low = 0x80 if trainer["double_battle"] else (0x78 if trainer["encounter_music_gender"] & 0x80 else 0x88)
        personality = ((name_hash << 8) + low) & 0xFFFFFFFF
        nature = personality % 25
        iv = mon["iv_parameter"] * 31 // 255
        level = mon["level"]
        stats = [(2 * base + iv) * level // 100 + 5 for base in species["base_stats"]]
        stats[0] += level + 5
        if mon["species"] == "SPECIES_SHEDINJA":
            stats[0] = 1
        for i, modifier in enumerate(data["nature_modifiers"][str(nature)], 1):
            # Preserve the source's u16 intermediate (BUGFIX disabled).
            if modifier:
                stats[i] = ((stats[i] * (110 if modifier == 1 else 90)) & 0xFFFF) // 100
        moves = [moves_by_name[m] for m in mon["moves"]] if mon["moves"] is not None else default_moves(species["learnset"], level)
        gender_ratio = species["gender_ratio"]
        gender = gender_ratio if gender_ratio in (0, 254, 255) else (254 if gender_ratio > (personality & 255) else 0)
        slot = personality & 1 if species["abilities"][1] else 0
        party.append(dict(slot=mon["slot"], species=mon["species"], species_id=species_id, level=level,
            personality=personality, nature_id=nature, ivs=[iv]*6, evs=[0]*6, stats=dict(zip(["hp", "attack", "defense", "speed", "sp_attack", "sp_defense"], stats)),
            current_hp=stats[0], gender_id=gender, ability_slot=slot, ability_id=species["abilities"][slot],
            friendship=species["friendship"], experience=data["experience"][str(species["growth_rate"])][level],
            moves=[data["moves"][str(m)]["constant"] for m in moves], pp=[data["moves"][str(m)]["pp"] for m in moves], pp_bonuses=0,
            held_item=mon["held_item"], status=0, shiny=False, ot_id=None))
    return dict(trainer_id=trainer["id"], trainer=trainer["constant"], party=party,
        construction_policy="ordinary-full-party-v1", source_commit=data["pokeemerald_commit"],
        limitations=["OT ID and construction RNG consumption not reconstructed", "Not a packed Pokemon struct or save-state image", "Special/paired encounter construction not supported"])
