"""Versioned mailbox protocol for one authentic engine instance. No simulation."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

MAGIC = 0x45544F55
ABI = 2
FIELDS = "magic abi phase trainer_a trainer_b seed rules_version outcome turns rng_start rng_after_party_init rng_final event_count event_overflow event_address event_capacity initial_party_address initial_party_size final_party_address final_party_size decoded_address decoded_count error_code".split()
MON_FIELDS = "side slot species level personality ot_id nature ability gender hp max_hp attack defense speed sp_attack sp_defense status held_item move0 move1 move2 move3 pp0 pp1 pp2 pp3 friendship experience".split()
EVENT_FIELDS = "sequence turn kind battler value0 value1 rng phase".split()
EVENT_NAMES = "battle_start send_out turn_start move_selected switch_selected trainer_item_selected move_execution miss fail damage healing critical effectiveness status stat_stage weather ability held_item faint replacement battle_end rng_call".split()


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def ram_range(address: int, size: int) -> bool:
    return size > 0 and any(start <= address and address + size <= end for start, end in [(0x02000000, 0x02040000), (0x03000000, 0x03008000)])


def words(raw: bytes, fields: list[str]) -> dict:
    if len(raw) != 4 * len(fields):
        raise ValueError("Wrong ABI record size")
    return dict(zip(fields, struct.unpack("<" + "I" * len(fields), raw)))


def control(raw: bytes) -> dict:
    result = words(raw, FIELDS)
    if result["magic"] != MAGIC or result["abi"] != ABI:
        raise ValueError("ROM/checkpoint does not expose tournament ABI v2")
    if result["phase"] > 8:
        raise ValueError("Invalid adapter phase")
    return result


def elf_symbol(path: Path, wanted: str) -> int:
    """Read an ELF32 little-endian ARM symbol; no host address casts."""
    data = path.read_bytes()
    if data[:7] != b"\x7fELF\x01\x01\x01" or len(data) < 52:
        raise ValueError("Expected little-endian ELF32")
    header = struct.unpack_from("<HHIIIIIHHHHHH", data, 16)
    if header[1] != 40:
        raise ValueError("ELF is not ARM")
    shoff, shentsize, shnum = header[5], header[10], header[11]
    if shentsize != 40 or not shnum or shoff + shentsize * shnum > len(data):
        raise ValueError("Invalid or unsupported ELF section table")
    sections = [struct.unpack_from("<10I", data, shoff + i*40) for i in range(shnum)]
    for sec in sections:
        if sec[1] != 2:
            continue
        offset, size, link, entry = sec[4], sec[5], sec[6], sec[9]
        if entry != 16 or size % 16 or link >= shnum or offset + size > len(data):
            raise ValueError("Invalid ELF symbol table")
        strings = sections[link]
        if strings[4] + strings[5] > len(data):
            raise ValueError("Invalid ELF string table")
        names = data[strings[4]:strings[4]+strings[5]]
        for pos in range(offset, offset + size, entry):
            name, value, _, _, _, section = struct.unpack_from("<IIIBBH", data, pos)
            if name >= len(names):
                raise ValueError("Invalid ELF symbol name")
            end = names.find(b"\0", name)
            if end < 0:
                raise ValueError("Unterminated ELF symbol name")
            symbol = names[name:end].decode("ascii")
            if symbol == wanted and section:
                return value
    raise ValueError(f"ELF is missing {wanted}; apply the tournament adapter first")


def ring_spans(consumed: int, produced: int, capacity: int) -> list[tuple[int, int]]:
    """Return bounded physical spans; reject cursor loss before reading RAM."""
    if not 0 < capacity <= 8192 or not 0 <= consumed <= produced <= 0xFFFFFFFF or produced-consumed > capacity:
        raise ValueError("Invalid event ring cursors/capacity or lost events")
    count = produced-consumed
    first = min(count, capacity-consumed % capacity)
    return [(consumed % capacity, first)] + ([(0, count-first)] if count>first else []) if count else []
