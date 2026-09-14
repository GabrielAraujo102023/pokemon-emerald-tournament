import struct
import tempfile
import unittest
from pathlib import Path

from emerald_tournament.emu_protocol import ABI, FIELDS, MAGIC, control, elf_symbol, ram_range


class ProtocolTests(unittest.TestCase):
    def test_mailbox_validation(self):
        values = [MAGIC, ABI, 2] + [0]*(len(FIELDS)-3)
        self.assertEqual(control(struct.pack("<23I", *values))["phase"], 2)
        values[0] = 0
        with self.assertRaises(ValueError):
            control(struct.pack("<23I", *values))
        with self.assertRaises(ValueError):
            control(b"short")

    def test_ram_bounds(self):
        self.assertTrue(ram_range(0x02000000, 0x40000))
        self.assertFalse(ram_range(0x0203FFFF, 2))
        self.assertFalse(ram_range(0x08000000, 4))
        self.assertFalse(ram_range(0x02000000, 0))

    def test_arm_symbol_resolution_without_native_casts(self):
        # Small ELF format fixture, not a ROM or a mocked battle.
        ident = b"\x7fELF\x01\x01\x01" + bytes(9)
        header = struct.pack("<HHIIIIIHHHHHH", 2, 40, 1, 0, 0, 52, 0, 52, 0, 0, 40, 3, 0)
        names = b"\0gTournamentControl\0"
        sections = bytes(40) + struct.pack("<10I", 0, 3, 0, 0, 172, len(names), 0, 0, 1, 0)
        sections += struct.pack("<10I", 0, 2, 0, 0, 172+len(names), 16, 1, 0, 4, 16)
        symbol = struct.pack("<IIIBBH", 1, 0x02001000, 92, 0x11, 0, 1)
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)/"test.elf"
            path.write_bytes(ident+header+sections+names+symbol)
            self.assertEqual(elf_symbol(path, "gTournamentControl"), 0x02001000)
            with self.assertRaises(ValueError):
                elf_symbol(path, "absent")
            path.write_bytes(b"invalid")
            with self.assertRaises(ValueError):
                elf_symbol(path, "gTournamentControl")
