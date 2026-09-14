# Deterministic checkpoint contract

No checkpoint has been generated or validated. An ordinary saved game alone is not the adapter checkpoint.

The planned ARM bootstrap runs normal platform, save-pointer and new-game/map initialization to obtain valid save blocks, heap, map context and battle globals. A dedicated tournament-ready callback then allocates adapter buffers, clears request/events, and exposes CHECKPOINT_READY. Checkpoint capture must occur at a documented instruction boundary in that callback after initialization completes. Do not construct arbitrary save bytes or hard-code pointers. Record the bootstrap path and initialized save/map values in validation evidence.

Capture with mGBA's named state API including SAVEDATA and RTC. The current bridge only restores a checkpoint; capture tooling remains to implement alongside the ARM ready callback. Freeze external input and RTC source/configuration, retain emulator/library build identity, and test reload equivalence before using the artifact. A checkpoint ready loop must not mutate game/RNG state while the emulator is stopped.

Required JSON manifest fields: rom_sha256, elf_sha256, checkpoint_sha256, bridge_sha256, abi_version (1), compiler_version, emulator_version, adapter_version, rules_version (integer), pokeemerald_commit, checkpoint_entry, validation_evidence. The evidence must include linked mGBA library hash, build options, map/save identity, ready instruction address, and successful capture/restore state checks. The runner enforces presence and file hashes; it cannot establish scientific validity from a self-authored manifest. There is intentionally no populated example manifest with fictitious hashes.

After restore, the host requires phase CHECKPOINT_READY and empty event counters. It sets request IDs/seed/rules, then REQUEST_LOADED last. Only the ARM adapter writes gRngValue at the defined seeding instruction; trace the constructor's RNG stream with interrupts included or an explicitly reviewed timing policy. Construct A then B without reseeding, preserve full bytes immediately, then expose PARTIES_CONSTRUCTED. The adapter waits for RUNNING from the host before battle execution.

A frame poll can overshoot the ready instruction, so the mailbox barrier must retain immutable constructor snapshots. Any wait-loop VBlank RNG behavior must be pinned and traced; host capture must not be assumed to stop interrupts retroactively. No validated instruction/frame schedule exists yet.


Latest runtime evidence (2026-09-12): [successful ARM build, emulator and construction validation](runtime_status.md). This supersedes earlier statements that the binaries, bridge and construction checkpoint do not exist. Full trainer-vs-trainer battle validation is still pending.

## Preserved references and battle checkpoint (2026-09-12)

`build/references/construction-traced/` preserves the previous successful construction-only adapter, ROM/ELF and checkpoint. `build/references/construction-uninstrumented/` preserves the separately tested no-RNG-trace reference. Their validation reports record exact artifact hashes. The uninstrumented reference remains the construction timing reference; equal observed construction results do not prove trace timing neutrality.

The new battle build still stops at phase 2 after actual normal new-game initialization. Host phase 1 commits trainer/seed/rules, phase 4 is the independently testable construction barrier, and host phase 5 releases the real battle. Phase 7 exports an engine terminal result. Every trial restores the same fixed-RTC checkpoint into a fresh emulator core. The host manifest pins ROM, ELF, bridge and checkpoint hashes; reference checkpoints must never be paired with a different ROM.

Current build hashes are recorded in `docs/evidence/battle-build-construction.json`; battle provenance and comparisons are in `docs/evidence/battle-entry-validation.json`. A terminal capture stops before normal return-to-overworld/reward handling. It is not a checkpoint intended to resume normal gameplay.

The item-command correction creates a new ROM/checkpoint pair. Its pinned hashes are in `docs/evidence/item-fix-construction.json` and `item-fix-battle-manifest.json`. The preceding battle milestone is retained under `build/references/minimal-battle-v1`; use its own ROM with its own checkpoint.
