# Current status — configured league complete

The authoritative current state is in [progress.md](progress.md), [final_tournament_report.md](final_tournament_report.md) and [tournament_readiness_gate.md](tournament_readiness_gate.md): 112/112 configured battles complete, 56 tests passed. The following earlier runtime notes are historical.

> Historical construction milestone. Current battle status: [progress.md](progress.md). Statements below about unimplemented battle execution describe the earlier build.

# Runtime milestone — 2026-09-12

The modern ARM build now succeeds with devkitARM r68-1 / GCC 16.1.0 using `make modern DINFO=1 -j4`. The original source checkout is unchanged. The modified copy is build/pokeemerald. Logs, source-overlay hashes, commands and ROM/ELF hashes are in build/reports/build-modern.json and build-modern.log. This is not a retail-matching agbcc build.

Host tool ordering matters: use devkitARM/bin for the ARM tools, then Homebrew/bin before devkitPro/tools/bin so host pkg-config can find host libpng. The first attempt failed on png.h because devkitPro's pkg-config was selected; the corrected build succeeded. `python -m emerald_tournament doctor` now exists.

mGBA 0.10.5 (26b7884bc25a5933960f3cdcd98bac1ae14d42e2) was built as a local shared library; the bridge compiled and runs. Setup is reproducible through tools/build_emulator.py after fetching that source revision and installing CMake in .venv. The bridge redirects emulator logs to stderr, allocates a video buffer and saves states with read/write file access. Those fixes were validated by actual execution.

## What ran

The baseline ROM ran for 600 frames twice with fixed RTC epoch zero and no inputs. RNG traces and named save-state bytes were identical. Restoring the same state twice yielded identical 120-frame RNG traces. See evidence/boot-validation.json. This baseline state is NOT a tournament-ready checkpoint.

The construction adapter now compiles and runs on ARM. It hooks normal copyright/save initialization, runs CB2_NewGame and the normal map-load path, then enters TournamentReady. It does not handcraft save bytes. The host captures phase CHECKPOINT_READY after 212 frames in this build. Capturing is frame-boundary based, not an instruction breakpoint; the retained ready state fixes CPU and interrupt timing.

The adapter seeds once, constructs Sawyer then Wallace through original CreateNPCTrainerParty/CreateMon, clears the correct destination, and preserves both complete six-slot arrays (1200 bytes). Seven decoded records come from GetMonData and the actual gender/nature/ability functions. Same seed 12345 produced identical raw and decoded parties, post-construction RNG and initialization RNG trace. Seed 12346 produced different raw bytes and post-construction RNG. See evidence/constructor-validation.json and the detailed binaries/records under build/reports/constructor-*.

Observed post-construction RNG: 1510019643 for 12345, 3782091108 for 12346. Initialization logging captured 54 calls, including four after the recorded party-construction boundary during snapshot/export. The first 50 calls reach that boundary. Every logged LCG transition is verified. The frame-free OT model predicted only 14 calls and does not represent this live initialization. First OT low/high outputs match low-first in this compiled scenario; this is not a universal compiler claim.

## Narrow patch and limitations

adapter/tournament_adapter.c and tools/apply_constructor_adapter.py implement the construction slice. Apply only to the disposable build copy. TOURNAMENT_MODE is enabled there; upstream is unchanged. RNG hooks log only phase 3 into a 128-record bounded buffer. Instrumentation consumes no Random calls but adds cycles; the instrumented build/checkpoint are separately hashed. Buffer overflow fails construction. EWRAM usage is now 256440/262144 bytes (97.82%), so future events cannot simply add large static buffers.

RUNNING requests intentionally return error 100. Both-side AI/history/items, symmetry patches, battle entry, terminal outcome and battle event hooks are still unimplemented. No battle test has passed. The full battle integration test must fail on missing artifacts now that the bridge exists; do not report the earlier prerequisite skip as current battle validation.

Next milestone: split/reuse a bounded event buffer and route player-side action selection through source trainer AI with side-local history/items, then enter the existing battle setup without reconstructing or reseeding parties. Validate obedience/badge/friendship/experience guards before accepting a battle result.
