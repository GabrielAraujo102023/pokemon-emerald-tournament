# Tournament event ABI v1 (proposed; hooks not implemented)

adapter/tournament_protocol.h is the layout contract. All records are little-endian u32 words; no host pointers are serialized. Each event is 32 bytes: sequence, turn, kind, battler, value0, value1, rng, phase. Sequence starts at zero. battler is the actual engine battler index (0/1 in this singles slice); use UINT32_MAX when not applicable. Host decoding preserves raw values and adds the event name.

Kinds, starting at 1, in order: battle_start, send_out, turn_start, move_selected, switch_selected, trainer_item_selected, move_execution, miss, fail, damage, healing, critical, effectiveness, status, stat_stage, weather, ability, held_item, faint, replacement, battle_end, rng_call.

Payload contract: selection/execution use value0=move/species/item/party-slot identifier as appropriate and value1=target battler where applicable. HP changes carry old/new HP; status/weather carry old/new bitfields; stat_stage carries stat ID/new stage; critical carries multiplier/attacker; effectiveness carries source result flags/target; ability/held_item carry ID/effect code; battle_end carries engine outcome/turn count. rng_call carries before/after gRngValue, with rng equal to the after state. Document any payload amendments by ABI version; do not infer events from host approximations.

Use a bounded append-only ARM buffer in this first prototype. Export count/capacity; set event_overflow and terminate with error on exhaustion. No ring wrap or silent truncation. Hooks must not call Random, allocate memory, display messages, or alter engine action decisions. Buffer writes still cost ARM cycles and can change frame RNG timing; compare instrumented builds and pin the chosen build/schedule. Non-RNG-consuming does not mean timing-free.

Record RNG calls at least during party initialization with a nonrecursive write hook. More extensive logging may require draining a barrier-controlled ring in a future ABI. Current runner reads the append-only buffer at terminal/timeout and rejects overflow. It hashes exact event bytes with SHA-256, preserving events.bin alongside JSONL. Missing required start/selection/execution/end events fails integration.

Initial and final raw party buffers contain concatenated A then B arrays in ARM layout, exported with lengths. Decoded initial records use the 28-word TournamentMonSnapshot fields in the header, filled via actual Emerald accessors. The host never reconstructs substitute party bytes. Final decoded fields are not exported in v1, but raw final bytes are retained.

## Minimal ARM events validated 2026-09-12

The existing 128-record buffer is retained: 32 bytes per record, 4096 bytes total. It is bounded, not wrapping. Overflow invalidates the run (adapter error 2); no records are silently discarded as a valid result. Detailed all-turn RNG logging is deliberately absent.

Construction emits `rng_call` records only during phase 3. Battle events include `battle_start`, `send_out`, `turn_start`, `move_selected`, `switch_selected`, `trainer_item_selected`, `move_execution`, `faint`, `replacement`, and `battle_end` where those paths occur. All store the observed current RNG without calling Random. Trace SHA-256 is calculated by the host over raw records; final RNG is captured when the outcome is first observed.

`send_out` currently observes a battler species change on the frame poll, not the exact animation command. Replacements with the same species may not emit another send_out; the selection hook emits replacement separately. Faints observe positive-to-zero HP. `turn` is the original engine counter: a first-turn knockout can report zero completed turns. Move execution records are attack-string command observations; the log does not yet identify every miss, damage, held-item, ability or status event. These limitations preclude using this minimal log as a complete battle replay.

Hooks add CPU cycles and can move interrupts. Determinism is tested within a pinned instrumented ROM/checkpoint. Timing equivalence to uninstrumented Emerald is not asserted. Event examples and terminal results are in `docs/evidence/battle-entry-{a,b,c}/`.

### Optional host engine observations

`run_battle(observe_engine=True)` additionally writes `engine_observations.jsonl` when selected RAM fields change at frame boundaries. This host-side diagnostic does not allocate GBA RAM or execute additional emulator frames. It reads the pinned ARM `BattlePokemon` layout (size 0x58, HP offset 0x28, maximum HP offset 0x2C), the u16 party-slot array, acting battler, last item and current script pointer. It is sampled evidence, not an instruction-by-instruction trace. These records are separate from the adapter's raw event hash.

Potion fixtures require positive HP updates within the ELF-symbol range of `BattleScript_OpponentUsesHealItem`, the potion ID, the correct acting side, unchanged party slots, the expected capped +20 HP change and unchanged opposing HP. An observed selection alone is insufficient.

On harness errors, bounded mailbox and partial-event snapshots are retained where the bridge still responds. They are explicitly diagnostic and never produce a valid result from a failed battle.

Host observations now also include loaded species and the mailbox event count. Switch validation uses that count to bracket a `switch_selected` event and confirms a living, different party member loads and remains active at its next AI move selection. A species or slot change by itself is insufficient: faint replacements are explicitly excluded from voluntary-switch evidence. These fields affect only host diagnostic output, not the adapter ABI or raw event hash.

## ABI v2: host-drained event ring

ABI v2 supersedes the v1 append-only transport above. The mailbox remains 23 words; `event_count` is now a monotonic producer sequence, not a bounded array length. The ELF exports `gTournamentEventRead`, a four-byte host acknowledgment cursor. Records occupy `sequence % event_capacity` in the same 128 × 32-byte buffer. The producer rejects invalid cursors or 128 outstanding unread records before writing. It sets overflow and error 2; no record is silently overwritten.

The host pauses at each frame boundary, reads up to two physical spans, verifies every sequence/kind, copies the bytes into host storage, then acknowledges the consumed sequence. Only then does it execute another frame. The host hashes the complete ordered stream. Writes are limited to the protocol acknowledgment; logging calls consume no RNG. Instrumentation still adds CPU cycles, so ABI-v2 timing must be validated separately from earlier ROMs.

`docs/evidence/ring-v2-cycle/ring-v2-long/validation.json` proves deterministic collection of 173 records, exceeding capacity, and identical stopped-party bytes/RNG across two 24000-frame runs. With acknowledgments deliberately withheld, the real adapter reaches error 2, phase 8, event_count 128 at frame 16012. These long runs are timeouts, not engine terminal battles. The separately retained ABI-v2 baseline validates terminal same/different-seed outcomes.

Static EWRAM is 257812/262144 bytes: 4332 bytes free. The ring added four bytes, not another event buffer. mGBA transport handshake ABI 1 is distinct from the ROM mailbox ABI 2. Old ROM/host protocol pairs are rejected.
