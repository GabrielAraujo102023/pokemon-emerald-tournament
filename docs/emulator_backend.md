# Emulated backend prototype

Status: host protocol/runner and bridge source implemented; **no bridge binary, patched ROM/ELF, checkpoint or successful battle exists here**. Missing runtime prerequisites are not replaced with host battle logic. The real integration test reports a prerequisite skip, not a passing battle.

The selected library API is mGBA 0.10.3. The [pinned core header](https://github.com/mgba-emu/mgba/blob/0.10.3/include/mgba/core/core.h) supplies core creation, file loading, memory access and deterministic stepping. tools/emulator/bridge.c uses a single core, restores a state with savedata/RTC, clears controller keys and accepts R (RAM read), W (aligned RAM write), and F (bounded frame stepping). It never selects moves or calculates damage. This bridge source has not compiled/run locally; API/link/runtime validation remains required. No actual installed emulator version is reported as though found.

## Setup/build procedure

Run `python3 tools/emulator_probe.py` for actual availability. Current host has no arm-none-eabi-gcc, cmake or built bridge. An mGBA GUI executable alone does not supply this bridge.

Use the upstream pokeemerald/INSTALL.md instructions for your platform's ARM tools and libpng. Prefer a matching agbcc build for the first oracle; a modern build is a distinct pinned build, not byte-identical retail Emerald. Make all ROM changes in a separate checkout/copy, retaining the original source pin. Apply the adapter plan in adapter/patch_plan.md only when its implementation exists; currently there is no applicable complete patch. Build with the upstream make procedure and preserve the produced GBA, ELF, map and exact compiler versions. Do not mistake the bundled multiboot GBA assets for the game ROM.

For the host library, obtain mGBA at tag 0.10.3 and record the resolved commit. Build/install its library and development headers into a project-local prefix, with matching configuration headers. Use that prefix for this bridge:

```sh
cmake -S tools/emulator -B build/emulator -DCMAKE_PREFIX_PATH=/absolute/path/to/mgba-prefix
cmake --build build/emulator
build/emulator/emerald-mgba-bridge --version
```

These are setup instructions, not claims that the dependency build was executed. Follow mGBA's own build instructions for the selected platform. The bridge executable and linked library/build identity must be retained together; a binary SHA alone does not identify a changed shared library. Record the library hash in checkpoint provenance as part of validation_evidence.

## Runner

```sh
PYTHONPATH=src python3 -m emerald_tournament.emu_battle \
  --trainer-a TRAINER_SAWYER_1 --trainer-b TRAINER_WALLACE --seed 12345 \
  --rom /absolute/path/tournament.gba --elf /absolute/path/tournament.elf \
  --checkpoint /absolute/path/ready.ss --manifest /absolute/path/ready.json \
  --bridge /absolute/path/emerald-mgba-bridge --output runs/smoke
```

`tools/run_emulated_battle.py` is an equivalent repository-local entry point. Paths must refer to real artifacts. The runner verifies manifest hashes before starting and reads gTournamentControl from the ELF32 little-endian ARM symbol table, not a hard-coded GBA address. A missing symbol or mailbox magic rejects an ordinary unpatched ROM.

One fresh process/core is used per battle. The host writes request words while execution is stopped and commits phase last. The ARM adapter seeds at its defined boundary, constructs both parties and pauses at PARTIES_CONSTRUCTED. The runner captures preserved constructor exports and releases the barrier. It steps one frame per poll with a fixed frame budget. The 30-second command watchdog reports harness failure, not a deterministic game outcome. No two battle instances are synchronized.

Outputs are battle_result.json, events.bin/JSONL, initial/final party binaries, decoded party_a/b.json and emulator.stderr. Output directories must be new to avoid overwriting prior evidence. Trace SHA-256 covers raw event bytes. A frame timeout remains timeout and cannot validate a battle; final party/RNG fields are not invented when the adapter has not exported them.

## Validation

`PYTHONPATH=src python3 -m unittest discover -s tests -v` includes tests/integration/test_emulated_battle.py. Missing executable bridge or ARM compiler produces an explicit prerequisite skip. Once binaries exist, missing artifact environment variables or invalid artifacts are failures, not skips. Set EMERALD_BRIDGE, EMERALD_ROM, EMERALD_ELF, EMERALD_CHECKPOINT, EMERALD_MANIFEST to run. The tests require an actual non-timeout terminal outcome, both-side selections, equal full party bytes/decoded fields/final RNG/events for repeated seeds, and trace/RNG evidence for different seeds. They never substitute a mock core.


Latest runtime evidence (2026-09-12): [successful ARM build, emulator and construction validation](runtime_status.md). This supersedes earlier statements that the binaries, bridge and construction checkpoint do not exist. Full trainer-vs-trainer battle validation is still pending.
