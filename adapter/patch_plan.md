# Minimal ARM adapter patch plan

This is the requested documented patch plan, **not a compilable/applicable ROM patch**. tournament_protocol.h only defines the proposed ABI. No ordinary ROM exports gTournamentControl yet.

1. Add src/tournament_adapter.c and include/tournament_adapter.h in a separate pinned pokeemerald checkout. Use upstream global.h types and static assertions for control=92 bytes, event=32 bytes, decoded mon=112 bytes. Reserve buffers through an explicit memory budget that fits EWRAM; do not assume unused memory at an arbitrary address. Export gTournamentControl in the ELF.
2. Add a bootstrap entry after valid normal save/map/global initialization. Establish CHECKPOINT_READY, valid buffers and an empty result. Capture/reload that state and verify addresses/bytes before accepting requests. Reject wrong rules versions, invalid IDs, empty parties and double flags on ARM as well as host.
3. In battle_main.c, expose a narrow tournament wrapper around CreateNPCTrainerParty. Clear the requested party only in tournament mode; construct A then B using the same actual CreateMon functions. Seed gRngValue once immediately before this sequence and log states. Preserve initial arrays with memcpy and decoded records through GetMonData. Expose phase 4 and wait for phase 5; snapshot bytes must remain unchanged.
4. Add the two-side AI, inventory, obedience, badge, friendship and experience guards described in docs/tournament_symmetry.md. Audit every selected controller command rather than copying the opponent controller wholesale. Do not alter bytecode, damage formulas or move implementations.
5. Enter the existing battle setup at an audited point that does not recreate parties or reset request RNG. Keep real controller scheduling until a demonstrated need for deterministic acknowledgment changes. Document phase transitions and preserve one battle state.
6. Add append-only hooks at resolved engine events: controller action selection, actual move execution, HP/status/stage changes, switch/replacement, abilities/items/faint and final outcome. Place battle_end after terminal outcome is determined and final party/RNG snapshots are captured. RESULT_READY is published last. Handle buffer overflow and invalid state as ERROR.
7. Build ARM ROM/ELF, run the bridge, generate the validated checkpoint manifest, then run tests/integration/test_emulated_battle.py. Test normal mode separately to establish that guards preserve ordinary behavior. Until these steps pass, the backend is an unvalidated prototype.

States: IDLE=0, REQUEST_LOADED=1, CHECKPOINT_READY=2, RNG_SEEDED=3, PARTIES_CONSTRUCTED=4, RUNNING=5, COMPLETE=6, RESULT_READY=7, ERROR=8. Host stops/starts emulation explicitly; no asynchronous external inputs. A frame budget expiry is a host timeout, never a draw. The real engine may export outcome 1/2/3; timeout/error are distinct experiment statuses.


Latest runtime evidence (2026-09-12): [successful ARM build, emulator and construction validation](../docs/runtime_status.md). This supersedes earlier statements that the binaries, bridge and construction checkpoint do not exist. Full trainer-vs-trainer battle validation is still pending.
