"""One-battle runner for the proposed ARM adapter; rejects absent/unvalidated inputs."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import selectors
import subprocess
from pathlib import Path

from .emu_protocol import ABI, EVENT_FIELDS, EVENT_NAMES, FIELDS, MON_FIELDS, control, digest, elf_symbol, ram_range, words, ring_spans


class Bridge:
    def __init__(self, binary: Path, rom: Path, checkpoint: Path, stderr):
        self.process = subprocess.Popen([str(binary), str(rom), str(checkpoint)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=stderr, bufsize=0)
        self.buffer = b""
        try:
            if self.line() != "READY 1":
                raise ValueError("mGBA bridge handshake failed")
        except Exception:
            self.close()
            raise

    def line(self) -> str:
        # A wall-clock watchdog reports harness failure, never an engine draw.
        with selectors.DefaultSelector() as selector:
            selector.register(self.process.stdout, selectors.EVENT_READ)
            while b"\n" not in self.buffer:
                if not selector.select(30):
                    raise RuntimeError("Bridge watchdog expired; inspect emulator.stderr")
                chunk = os.read(self.process.stdout.fileno(), 65536)
                if not chunk:
                    raise RuntimeError("Bridge exited before completing the command")
                self.buffer += chunk
            line, self.buffer = self.buffer.split(b"\n", 1)
        return line.decode("ascii")

    def command(self, text: str) -> str:
        self.process.stdin.write((text + "\n").encode("ascii"))
        return self.line()

    def read(self, address: int, size: int) -> bytes:
        if not ram_range(address, size):
            raise ValueError("Adapter buffer lies outside GBA RAM")
        data = b"".join(bytes.fromhex(self.command(f"R {address+i} {min(32768, size-i)}")) for i in range(0, size, 32768))
        if len(data) != size:
            raise ValueError("Bridge returned incorrect memory length")
        return data

    def write(self, address: int, value: int) -> None:
        if not 0 <= value <= 0xFFFFFFFF or address % 4 or not ram_range(address, 4):
            raise ValueError("Invalid mailbox write")
        if self.command(f"W {address} {value}") != "OK":
            raise RuntimeError("Bridge write failed")

    def frame(self) -> None:
        if self.command("F 1") != "OK":
            raise RuntimeError("Frame execution failed")

    def close(self) -> None:
        if self.process.poll() is None:
            self.process.terminate()
            try:
                self.process.wait(timeout=3)
            except subprocess.TimeoutExpired:
                self.process.kill()
                self.process.wait()
        self.process.stdin.close()
        self.process.stdout.close()


def check_manifest(manifest: dict, rom: Path, elf: Path, checkpoint: Path, bridge: Path) -> None:
    for key, path in [("rom_sha256", rom), ("elf_sha256", elf), ("checkpoint_sha256", checkpoint), ("bridge_sha256", bridge)]:
        if manifest.get(key) != digest(path):
            raise ValueError(f"Missing or mismatched {key}")
    for field in ["compiler_version", "emulator_version", "adapter_version", "rules_version", "pokeemerald_commit", "checkpoint_entry", "validation_evidence"]:
        if not manifest.get(field):
            raise ValueError(f"Missing checkpoint provenance: {field}")
    if manifest.get("abi_version") != ABI:
        raise ValueError("Unsupported manifest ABI")


def run_battle(*, trainer_a: int, trainer_b: int, seed: int, rom: Path, elf: Path,
               checkpoint: Path, manifest_path: Path, bridge: Path, output: Path, max_frames: int = 36000, observe_engine: bool = False, validation_all_badges: bool = False) -> dict:
    if not bridge.is_file() or not os.access(bridge, os.X_OK):
        raise FileNotFoundError("Missing executable mGBA bridge; see docs/emulator_backend.md")
    if not 0 <= seed <= 0xFFFFFFFF or not 0 < trainer_a <= 0xFFFF or not 0 < trainer_b <= 0xFFFF or max_frames <= 0:
        raise ValueError("Invalid trainer IDs, seed or frame budget")
    manifest = json.loads(manifest_path.read_text())
    check_manifest(manifest, rom, elf, checkpoint, bridge)
    address = elf_symbol(elf, "gTournamentControl")
    if address % 4 or not ram_range(address, 4 * len(FIELDS)):
        raise ValueError("Mailbox symbol is not aligned GBA RAM")
    output.mkdir(parents=True, exist_ok=False)
    client = None
    streamed = bytearray()
    consumed = 0
    read_cursor_address = elf_symbol(elf, "gTournamentEventRead")
    with (output / "emulator.stderr").open("wb") as stderr:
        try:
            client = Bridge(bridge, rom, checkpoint, stderr)
            def state():
                return control(client.read(address, 4 * len(FIELDS)))
            def drain(observed):
                nonlocal consumed
                if observed['event_overflow']:
                    raise RuntimeError("Adapter event buffer overflow; trace is invalid")
                parts = [client.read(observed['event_address']+slot*32, count*32)
                         for slot,count in ring_spans(consumed, observed['event_count'], observed['event_capacity'])]
                chunk = b''.join(parts)
                for i in range(0,len(chunk),32):
                    record = words(chunk[i:i+32], EVENT_FIELDS)
                    if record['sequence'] != consumed+i//32 or not 1 <= record['kind'] <= len(EVENT_NAMES):
                        raise ValueError("Invalid streamed event sequence/kind")
                streamed.extend(chunk)
                consumed = observed['event_count']
                client.write(read_cursor_address, consumed)
            def set_field(name, value):
                client.write(address + 4 * FIELDS.index(name), value)
            current = state()
            if current["phase"] != 2 or current["event_count"] or current["event_overflow"]:
                raise ValueError("Checkpoint is not clean CHECKPOINT_READY")
            if validation_all_badges:
                # Explicit test-only intervention. Never admitted to a tournament store.
                layout = json.loads((Path(__file__).resolve().parents[2]/"build/layout/layout.json").read_text())
                save = int.from_bytes(client.read(elf_symbol(elf,"gSaveBlock1Ptr"),4),"little")
                byte_address = save + layout['save_flags'] + layout['badge_first']//8
                aligned = byte_address & ~3
                value = int.from_bytes(client.read(aligned,4),"little")
                mask = sum(1 << (((save+layout['save_flags']+flag//8)-aligned)*8+flag%8) for flag in range(layout['badge_first'],layout['badge_last']+1))
                client.write(aligned,value|mask)
                (output/'validation_override.json').write_text(json.dumps({'kind':'all_badges','address':aligned,'before':value,'after':value|mask})+"\n")
            for key, value in [("trainer_a", trainer_a), ("trainer_b", trainer_b), ("seed", seed), ("rules_version", manifest["rules_version"])]:
                set_field(key, value)
            set_field("phase", 1)  # Commit request last. ROM performs the actual RNG write.
            observations = []
            observer_symbols = {name: elf_symbol(elf, name) for name in
                ("gBattleMons", "gBattlerPartyIndexes", "gBattlerAttacker", "gLastUsedItem", "gBattlescriptCurrInstr", "gMoveResultFlags", "gCritMultiplier", "gCurrentMove", "gLastUsedAbility", "gBattleWeather", "gRngValue", "sHistory", "gStatuses3")} if observe_engine else {}
            previous_observation = None
            initial = None
            decoded = []
            for frame in range(1, max_frames + 1):
                client.frame()
                current = state()
                if observe_engine and current["phase"] in (5, 7):
                    # Pinned ARM BattlePokemon layout in include/pokemon.h: 0x58 bytes.
                    mons = client.read(observer_symbols["gBattleMons"], 0x58 * 2)
                    histories = client.read(observer_symbols["sHistory"],84*2)
                    observation = {
                        "inventory": [[int.from_bytes(histories[side*84+72+i*2:side*84+74+i*2],"little") for i in range(4)] for side in range(2)],
                        "event_count": current["event_count"],
                        "status1": [int.from_bytes(mons[i*0x58+0x4C:i*0x58+0x50], "little") for i in range(2)],
                        "status2": [int.from_bytes(mons[i*0x58+0x50:i*0x58+0x54], "little") for i in range(2)],
                        "status3": [int.from_bytes(client.read(observer_symbols["gStatuses3"]+i*4,4),"little") for i in range(2)],
                        "stages": [list(mons[i*0x58+0x18:i*0x58+0x20]) for i in range(2)],
                        "pp": [list(mons[i*0x58+0x24:i*0x58+0x28]) for i in range(2)],
                        "abilities": [mons[i*0x58+0x20] for i in range(2)],
                        "types": [list(mons[i*0x58+0x21:i*0x58+0x23]) for i in range(2)],
                        "held_items": [int.from_bytes(mons[i*0x58+0x2E:i*0x58+0x30], "little") for i in range(2)],
                        "move_flags": client.read(observer_symbols["gMoveResultFlags"],1)[0],
                        "crit_multiplier": client.read(observer_symbols["gCritMultiplier"],1)[0],
                        "current_move": int.from_bytes(client.read(observer_symbols["gCurrentMove"],2),"little"),
                        "last_ability": client.read(observer_symbols["gLastUsedAbility"],1)[0],
                        "weather": int.from_bytes(client.read(observer_symbols["gBattleWeather"],2),"little"),
                        "species": [int.from_bytes(mons[i*0x58:i*0x58+2], "little") for i in range(2)],
                        "hp": [int.from_bytes(mons[i*0x58+0x28:i*0x58+0x2A], "little") for i in range(2)],
                        "max_hp": [int.from_bytes(mons[i*0x58+0x2C:i*0x58+0x2E], "little") for i in range(2)],
                        "slots": [int.from_bytes(client.read(observer_symbols["gBattlerPartyIndexes"]+i*2, 2), "little") for i in range(2)],
                        "attacker": client.read(observer_symbols["gBattlerAttacker"], 1)[0],
                        "item": int.from_bytes(client.read(observer_symbols["gLastUsedItem"], 2), "little"),
                        "script": int.from_bytes(client.read(observer_symbols["gBattlescriptCurrInstr"], 4), "little"),
                    }
                    if observation != previous_observation:
                        observations.append(dict(frame=frame, rng=int.from_bytes(client.read(observer_symbols["gRngValue"],4),"little"), **observation))
                        previous_observation = observation
                drain(current)
                if current["phase"] >= 4 and current["phase"] != 8 and initial is None:
                    size, count = current["initial_party_size"], current["decoded_count"]
                    if not 0 < size <= 4096 or not 2 <= count <= 12:
                        raise ValueError("Invalid initial party export")
                    initial = client.read(current["initial_party_address"], size)
                    decoded_raw = client.read(current["decoded_address"], count * len(MON_FIELDS) * 4)
                    stride = len(MON_FIELDS)*4
                    decoded = [words(decoded_raw[i:i+stride], MON_FIELDS) for i in range(0, len(decoded_raw), stride)]
                    if len({(m["side"], m["slot"]) for m in decoded}) != count or any(m["side"] > 1 or m["slot"] > 5 for m in decoded):
                        raise ValueError("Invalid decoded party slots")
                    (output / "initial_parties.bin").write_bytes(initial)
                    for side, name in [(0, "a"), (1, "b")]:
                        (output / f"party_{name}.json").write_text(json.dumps([m for m in decoded if m["side"] == side], indent=2) + "\n")
                    if current["phase"] == 4:
                        set_field("phase", 5)  # Release the adapter's constructor barrier.
                if current["phase"] in (7, 8):
                    break
            if current["phase"] == 8:
                raise RuntimeError(f"Adapter error {current['error_code']}")
            terminal = current["phase"] == 7
            if terminal and (initial is None or current["outcome"] not in (1, 2, 3)):
                raise ValueError("Invalid terminal adapter result")
            count, capacity = current["event_count"], current["event_capacity"]
            if count != consumed or capacity > 8192:
                raise ValueError("Invalid event buffer count/capacity")
            raw = bytes(streamed)
            events = [words(raw[i:i+32], EVENT_FIELDS) for i in range(0, len(raw), 32)]
            if any(e["sequence"] != i or not 1 <= e["kind"] <= len(EVENT_NAMES) for i, e in enumerate(events)):
                raise ValueError("Invalid event sequence/kind")
            for event in events:
                event["event"] = EVENT_NAMES[event["kind"] - 1]
            if terminal and (not events or events[-1]["event"] != "battle_end"):
                raise ValueError("Terminal result has no battle_end hook")
            (output / "events.bin").write_bytes(raw)
            (output / "events.jsonl").write_text("".join(json.dumps(e, sort_keys=True) + "\n" for e in events))
            if terminal:
                size = current["final_party_size"]
                if size != len(initial):
                    raise ValueError("Initial/final party export sizes differ")
                (output / "final_parties.bin").write_bytes(client.read(current["final_party_address"], size))
            stopped = client.read(elf_symbol(elf,"gPlayerParty"),600)+client.read(elf_symbol(elf,"gEnemyParty"),600)
            (output / "stopped_parties.bin").write_bytes(stopped)
            rng_at_stop = int.from_bytes(client.read(elf_symbol(elf,"gRngValue"),4),"little")
            result = dict(rng_at_stop=rng_at_stop, stopped_party_sha256=hashlib.sha256(stopped).hexdigest(), trace_event_count=len(raw)//32, trainer_a=trainer_a, trainer_b=trainer_b, seed=seed,
                          outcome={1:"a_win", 2:"b_win", 3:"draw"}[current["outcome"]] if terminal else "timeout",
                          terminal_from_engine=terminal, frames=frame, turns=current["turns"],
                          rng_start=current["rng_start"], rng_after_party_init=current["rng_after_party_init"], rng_final=current["rng_final"] if terminal else None,
                          initial_party_sha256=hashlib.sha256(initial).hexdigest() if initial else None,
                          trace_sha256=hashlib.sha256(raw).hexdigest(), max_frames=max_frames, provenance=manifest)
            if validation_all_badges: result["validation_overrides"]={"badge_flags":"all"}
            (output / "battle_result.json").write_text(json.dumps(result, indent=2) + "\n")
            return result
        except Exception as error:
            failure = {"error": str(error), "battle_validation_passed": False}
            # Preserve bounded observations even when overflow invalidates a run.
            # Diagnostics never convert a failed run into a battle result.
            if client:
                try:
                    observed = control(client.read(address, 4 * len(FIELDS)))
                    failure["control"] = observed
                    count, capacity = observed["event_count"], observed["event_capacity"]
                    chunk = b''.join(client.read(observed['event_address']+slot*32, n*32)
                                     for slot,n in ring_spans(consumed,count,capacity))
                    raw = bytes(streamed)+chunk
                    (output / "partial_events.bin").write_bytes(raw)
                    partial = [words(raw[i:i+32], EVENT_FIELDS) for i in range(0, len(raw), 32)]
                    (output / "partial_events.json").write_text(json.dumps(partial, indent=2) + "\n")
                except Exception as diagnostic_error:
                    failure["diagnostic_error"] = str(diagnostic_error)
            (output / "harness_error.json").write_text(json.dumps(failure, indent=2) + "\n")
            raise
        finally:
            if observe_engine and 'observations' in locals():
                (output / "engine_observations.jsonl").write_text("".join(json.dumps(o, sort_keys=True) + "\n" for o in observations))
            if client:
                client.close()


def main() -> None:
    parser = argparse.ArgumentParser(description="Real emulated battle runner prototype; requires patched ROM and validated checkpoint")
    parser.add_argument("--trainer-a", required=True)
    parser.add_argument("--trainer-b", required=True)
    parser.add_argument("--seed", required=True, type=int)
    for option in ("rom", "elf", "checkpoint", "manifest"):
        parser.add_argument("--" + option, required=True, type=Path)
    parser.add_argument("--bridge", type=Path, default=Path("build/emulator/emerald-mgba-bridge"))
    parser.add_argument("--output", type=Path, default=Path("runs/smoke"))
    parser.add_argument("--max-frames", type=int, default=36000)
    parser.add_argument("--trainers", type=Path, default=Path("data/generated/trainers.json"))
    args = parser.parse_args()
    try:
        trainers = json.loads(args.trainers.read_text())["trainers"]
        def ident(value):
            trainer = next((t for t in trainers if value in (str(t["id"]), t["constant"])), None)
            if not trainer or not trainer["party"] or trainer["double_battle"]:
                raise ValueError(f"Not a nonempty single-flagged trainer: {value}")
            return trainer["id"]
        result = run_battle(trainer_a=ident(args.trainer_a), trainer_b=ident(args.trainer_b), seed=args.seed,
                            rom=args.rom.resolve(), elf=args.elf.resolve(), checkpoint=args.checkpoint.resolve(),
                            manifest_path=args.manifest.resolve(), bridge=args.bridge.resolve(), output=args.output,
                            max_frames=args.max_frames)
        print(json.dumps(result, indent=2))
    except (ValueError, OSError, RuntimeError) as error:
        parser.exit(2, f"Emulated battle unavailable/failed: {error}\n")


if __name__ == "__main__":
    main()
