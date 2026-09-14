# Replay and result logging strategy

Current implementation: host-drained bounded GBA ring, with the complete ordered event stream stored on the host. The same ROM instrumentation is used in ordinary and observed runs. Additional host observations read paused memory without stepping extra frames or consuming emulated RNG.

A compact result contains trainer IDs, seed, frame cap, outcome, terminal-from-engine flag, turn counter, construction RNG, terminal RNG when reached, RNG at host stop, initial/stopped party hashes, trace hash and event count, plus pinned ROM/ELF/checkpoint/bridge/compiler/adapter provenance. A timeout retains `rng_final: null` and a distinct `rng_at_stop`; it is never a draw.

Detailed validation runs retain initial party bytes, decoded initial records, stopped-party bytes, raw ordered events and JSONL events. Engine-terminal runs additionally retain the adapter's final-party snapshot. Optional observations retain HP/status/stages/PP/abilities/held items/inventories, acting battler, script address and RNG at a recorded observation. They are frame samples, not complete interpreter traces.

Replay must restore the exact checkpoint with matching ROM/ELF/bridge hashes and repeat trainer IDs, seed, rules and frame cap. Compare the ordered event hash and stopped-party hash. Enabling richer host observation must not change the emulated trajectory. This equivalence has baseline switch evidence from the earlier build; explicit compact-versus-observed replay testing remains a release gate for ABI v2.

The intended tournament store will persist compact records immutably and locate detailed artifacts by deterministic match identity. The SQLite store, replay lookup CLI and a proven compact-to-detailed replay smoke test are not yet implemented. No full tournament is authorized by this document.

Overflow is always an invalid run. Partial diagnostic records may be retained, but cannot count as a win, loss or draw. A deliberately undrained real-engine run validates this failure path; see `evidence/ring-v2-cycle/ring-v2-long/validation.json`.

## Implemented SQLite workflow

The runner now stores immutable compact JSON records in `results.sqlite`, with their SHA-256, deterministic identity, schedule ordinal and relative artifact directory. Full raw event and party artifacts are retained per unique attempt. Failed attempts are recorded separately; an interrupted pre-commit attempt may remain as an orphan directory, and resume safely recomputes the missing identity without overwriting it. An exclusive run lock prevents concurrent runners sharing a store.

Use `.venv/bin/python -m emerald_tournament.replay --run runs/smoke-v2 --match MATCH_ID_OR_UNIQUE_PREFIX --output build/reports/replay-new`. Replay checks pinned backend source/runtime hashes and the exact ROM/ELF/checkpoint/bridge manifest, then restores one instance and enables detailed observation. The result and original event/party bytes must match. Both terminal and timeout compact-to-detailed replays passed for smoke-v1; release-v2 repeats this check after host hardening.

The historical paragraphs describing SQLite as pending are superseded by this implementation. Current engine RNG includes its normal VBlank behavior under the pinned single-frame controller schedule; it is not a VBlank-free custom simulator.
