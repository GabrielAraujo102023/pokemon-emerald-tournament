# Minimal real battle milestone — 2026-09-12

Construction validation still passes. A single actual Emerald battle instance now reaches both trainer AI move selectors and an engine terminal outcome. No full tournament was run.

Sawyer (1) versus Wallace (335), seed 12345, completed twice in 1847 frames with Wallace winning. Full initial/final party bytes, decoded initial fields, outcome, final RNG and raw event bytes/hash matched. Final RNG was 2426787468. Seed 12346 also completed with Wallace winning, in 3105 frames; final RNG was 719512582 and its trace differed. These are source-engine outcomes, not synthesized results. The original turn counter can remain zero for a first-turn knockout.

Evidence: [battle comparisons and pinned provenance](evidence/battle-entry-validation.json), [construction in the final battle build](evidence/battle-build-construction.json), [uninstrumented reference](evidence/construction-uninstrumented.json), [preserved traced construction reference](evidence/construction-traced-reference.json). Exact ROM/ELF/checkpoint/adapter hashes are in these reports. Both construction reference artifact sets remain under `build/references/`.

The final build uses 257808 bytes EWRAM (98.35%), leaving 4336 bytes. This adds 1368 bytes over the traced construction build: two private histories and a final party snapshot. The existing 4096-byte event buffer is reused. IWRAM is 30428/32768 bytes. These are static linker figures, not a dynamic heap high-water measurement.

Changed project files: `adapter/tournament_adapter.c`, new `adapter/tournament_battle.h`, new `tools/apply_battle_adapter.py`, new `tools/validate_battle_entry.py`, and status/evidence documentation. `doctor` reports prerequisite checks separately from battle validation. The complete upstream-function patch inventory and guard rationale are in [tournament_symmetry.md](tournament_symmetry.md). `pokeemerald` remains unchanged; executable source patches are in `build/pokeemerald`.

Validation: 19 tests passed, including actual ARM construction and real-emulator same/different-seed integration. No execution blocker remains for this tested matchup. Remaining coverage gates are swapped-side trials, trainer-item use, voluntary switches, forced replacements, self-targeting moves, and wider ability/status coverage. The compact log can overflow in longer battles; overflow is an explicit invalid run. Same-species send-outs and detailed effect events are not fully observed. Instrumentation may perturb timing; no equivalence to the uninstrumented reference or retail-matching ROM is claimed.

Next milestone: dedicated small fixtures that actually exercise those item/switch/side-symmetry paths, with assertions against engine state, before expanding tournament coverage.

## Reproduce

Use the installed toolchain and existing pinned mGBA bridge. From the project root:

```sh
.venv/bin/python tools/apply_battle_adapter.py
.venv/bin/python tools/build_rom.py
.venv/bin/python tools/validate_arm_construction.py
.venv/bin/python tools/validate_battle_entry.py
```

The battle probe refuses to overwrite existing `build/reports/battle-entry-{a,b,c}` outputs; preserve or move them before rerunning. It stops at the first unsuccessful battle. Construction-only validation ends at phase 4 and never releases battle execution.

Run the complete tests with the actual artifacts configured:

```sh
EMERALD_ROM="$PWD/build/pokeemerald/pokeemerald_modern.gba" \
EMERALD_ELF="$PWD/build/pokeemerald/pokeemerald_modern.elf" \
EMERALD_CHECKPOINT="$PWD/build/reports/constructor-ready.ss" \
EMERALD_MANIFEST="$PWD/build/reports/battle-manifest.json" \
PATH="/opt/devkitpro/devkitARM/bin:$PATH" \
.venv/bin/python -m pytest -q
```

## Subsequent milestone: side routing and potion execution

The new `tools/validate_symmetry.py` runs bounded natural-team fixtures without replacing Pokémon, levels, moves or AI decisions. Swapped Sawyer/Wallace and Roxanne/Wallace in both orientations reached terminal results with both AI selectors. Roxanne's faint replacements were observed on each side. These checks passed again on the item-fix ROM.

Roxanne/Brawly at seed 12346 exposed a real side-asymmetry in `Cmd_useitemonopponent`: the command always passed an enemy-party Pokémon into `PokemonUseItemEffects`. The HP eligibility check could therefore inspect the wrong Pokémon during side-0 item use. The guarded patch now passes the player-party Pokémon only for an active tournament side-0 user, retaining the original path otherwise. This adds no EWRAM: static usage remains 257808 bytes, with 4336 bytes free. The previous battle ROM/checkpoint/manifest are preserved in `build/references/minimal-battle-v1`.

The fixed ROM passed Roxanne/Brawly in both orientations at seed 12346. Each observed Roxanne potion selection corresponded to a healing update inside the actual NPC heal-item script: +20 HP capped at the user's maximum, with no opponent HP change during that update. Self-targeted move selections were also observed. This validates ordinary potion healing, not every trainer-item category or a complete inventory-isolation proof.

Host observation is optional and consumes no emulated frames or RNG calls beyond the runner's existing single-frame stepping. It records HP, maximum HP, party slots, acting battler, last item and script pointer. The layout is pinned to this source's `BattlePokemon` structure. Failed harness runs now preserve bounded mailbox and partial-event diagnostics rather than losing the trace on overflow.

Evidence: `docs/evidence/symmetry-natural-fixed/validation.json`, `docs/evidence/symmetry-potions-fixed/validation.json`, and `docs/evidence/item-fix-*` contain the exact build/checkpoint provenance and regression results. The original same/different-seed three-run battle check and construction check passed on the fixed build; the 19-test suite also passed.

Reproduce the new checks after rebuilding and refreshing the checkpoint/manifest as above, with unused output directories:

```sh
.venv/bin/python tools/validate_symmetry.py --output build/reports/new-natural-check
.venv/bin/python tools/validate_symmetry.py --items --seed 12346 --require-potions --output build/reports/new-potion-check
```

Remaining gates: voluntary switching, status-cure/full-restore/X-item behavior, simultaneous inventory use, wider ability/status interactions, and detailed send-out/effect logging. No full tournament is authorized by this milestone. The next concrete fixture should exercise a voluntary AI switch and assert the selected slot is the slot actually loaded.

## 2026-09-13: voluntary-switch path validated

`tools/validate_switch.py` now proves a voluntary trainer-AI switch in both orientations of Julie (100) versus Bernie 5 (210), using unchanged natural teams. Side 0 uses seed 12345: living Sandslash has 98 HP before selection, Ninetales slot 1 loads at frame 1808, and its next AI move selection is observed at frame 2474. Side 1 uses seed 7: Sandslash has 82 HP before selection, slot 1 loads at frame 6816, and Ninetales reaches its next AI move selection at frame 7734.

The assertions require a `switch_selected` event, a living outgoing Pokémon, a different valid party slot, the selected Pokémon's actual species and positive HP after loading, no intervening faint or additional switch before its next move selection, and the same selected slot/species still active at that selection. A faint replacement alone cannot pass. Host observations now include event count and loaded species so RAM state can be correlated with AI events.

Both pinned orientations were repeated. Full initial parties, decoded party exports, raw event bytes, host observations and bounded-run results matched exactly within each orientation. This does not claim that reversing trainer order preserves an RNG trajectory; construction order and subsequent execution differ. Evidence and pinned ROM/ELF/checkpoint provenance: `docs/evidence/voluntary-switch/validation.json` and its per-side captures.

These are **bounded switch-path validations, not complete battle validations**. Both runs retain `outcome: timeout`, `terminal_from_engine: false` at 12000 frames; no winner or final RNG was fabricated. The initial Julie/Michelle discovery also timed out and produced only a faint replacement, so it was not counted. Earlier short/no-switch trials remain under `build/reports/switch-*` for audit.

No ARM adapter or battle-engine changes were needed; EWRAM remains 257808 bytes with 4336 free. Four evidence-checker regression tests accept the real capture and reject forced-replacement-only records, wrong loaded species, and missing subsequent AI action. The full test suite now has 23 passing tests, including the real-emulator construction and terminal baseline regressions.

Reproduce with a fresh output path:

```sh
.venv/bin/python tools/validate_switch.py --side-seeds 12345 7 --max-frames 12000 --output build/reports/new-switch-validation
```

Remaining scope: other switch heuristics (e.g. Perish Song and Natural Cure), trapping restrictions, broader item categories, and longer-battle event collection before wider tournament runs. The existing 128-record limit is unchanged. This milestone closes the specific voluntary-selection-to-loaded-slot coverage gap on both sides.

## 2026-09-13: readiness mission baseline

| Coverage | Current evidence | Scope |
| --- | --- | --- |
| ARM construction, repeated/different seeds | `evidence/item-fix-construction.json` | Sawyer/Wallace sample |
| Terminal same/different-seed battle | `evidence/item-fix-battle-entry-validation.json` | Sawyer/Wallace |
| Potion execution | `evidence/symmetry-potions-fixed/validation.json` | Both orientations, correct HP delta |
| Forced replacements | `evidence/symmetry-natural-fixed/validation.json` | Both sides observed |
| Voluntary switches | `evidence/voluntary-switch/validation.json` | Selection, living outgoing mon, correct load, next AI action |
| Full tournament | Not authorized | See `tournament_readiness_gate.md` |

Existing evidence directories are preserved. New executable generations and their checkpoint/manifest pairs receive separate report/reference directories. Selected cycle: remove the longer-battle logging bottleneck without increasing the 4096-byte event storage or silently truncating traces.

## Resume inspection and logging-cycle results

The project is an untracked subdirectory of `/Users/gaby/Desktop/the box`, on its unborn `gibs-games` branch; no project commits exist. The nested upstream `pokeemerald` checkout is clean at `5eff78649e7170a877b961ef0b3da13b81a16038`. Doctor passes devkitARM, mGBA, bridge and host prerequisites; it does not assert battle readiness.

The current executable uses mailbox ABI v2 and a host-drained event ring. Construction and all three Sawyer/Wallace terminal baseline runs passed on this build. Two longer Julie/Michelle runs collected 173 records each with identical raw events, stopped-party bytes, stopped RNG and timeout outcome. Deliberately withholding ring acknowledgments reached explicit overflow error 2 at 128 records. This closes the observed-capacity logging gap, while compact-result persistence and replay lookup remain pending. Exact evidence is preserved in `docs/evidence/ring-v2-cycle/`.

The last failed fixture was `build/reports/ring-v2-fullrestore-probe`: Julie/Bernie at seed 7 timed out at 12000 frames with no item selection in the first orientation; the terminal-required harness stopped before the second. Classification: frame-budget timeout and missing requested mechanic coverage, not a proven crash or incorrect item effect. Full Restore is not validated by that run.

An ARM-compiled layout probe confirms BattlePokemon size 88, history size 84, inventory offset 72 and party-mon size 100. The host observer now reads status/stage/ability/held-item/inventory fields from those actual offsets. This is observation infrastructure, not evidence that the corresponding mechanics are correct. A trainer-inventory search found Potion, Super Potion, Hyper Potion and Full Restore among single-flagged entries; no natural X-item or standalone status-cure inventory was found. A pinned inventory audit and explicit scope decision are still required.

Next selected target after the ring regressions: a fixture that actually selects Full Restore and permits before/after HP/status plus side-local inventory assertions. Broader status/switch restrictions, population admission, SQLite smoke/ranking and final authorization remain open. Tournament authorized: no.

## Item cycle following the resume inspection

After the ring checks passed, the next successful natural fixtures were Cindy 1/Winston 1 (114/136) and Cindy 3/Catherine 1 (120/559), each in both orientations at seed 12345 with a 36000-frame cap. All four battles reached engine terminal outcomes and repeated identically in raw events, initial/final/stopped party bytes, host observations and result records.

Cindy 1/Winston 1 proves Full Restore healing on both sides within the same battle: original trainer inventories match the extracted data, each selection consumes one item from its owner, the user's HP reaches maximum and the opponent's HP/status/stages remain unchanged at the item update. Cindy 3/Catherine 1 additionally proves poison application and a side-0 Full Restore clearing that poison and healing. Status curing on side 1 and other status conditions are not inferred from this evidence. No simultaneous-eligibility claim is made.

Evidence: `docs/evidence/fullrestore-cycle-v2/validation.json`, per-fixture captures, and `inventory-audit.json`. Failed/no-coverage probes remain preserved. The single-flagged inventory audit found only Potion, Super Potion, Hyper Potion and Full Restore. Standalone status-cure and X/stat-item inventories are absent; the proposed scope rejects newly encountered categories pending validation instead of enabling untested item handling. Held-item effects are a separate coverage area.

The next unclosed validation target is simultaneous item eligibility/inventory isolation or a switch restriction (trapped/no living reserve). Representative sleep, paralysis, confusion, immunity, ability impact, critical/recharge and remaining guard-state checks still require direct assertions. Population admission, SQLite smoke/resume/ranking, compact replay lookup and release authorization remain unfinished. Tournament authorized: no.

Final regression result for this cycle: **33 passed in 14.45s**, no skips. The exact pytest output is preserved in `docs/evidence/fullrestore-cycle-v2/pytest.log`. Upstream remains clean.

## Autonomous cycle: concurrent item eligibility and replay

A bounded natural Cindy 1/Winston 1 seed search (0–10) found simultaneous Full Restore selection on turn 10 at seed 10. Two detailed replays prove that both living Pokémon were below Emerald's integer maxHP/4 threshold with their own Full Restore available before either selection. Each inventory consumed its own item, and both healing effects passed the existing ownership/HP checker.

The compact discovery run and both detailed replays match in complete raw events, initial/final/stopped party bytes and result/RNG fields. Detailed observations also repeat exactly. Evidence: `docs/evidence/concurrent-items-v2/`. No ROM patch was needed. This closes the concurrent-eligibility sample and compact-versus-observed trajectory-equivalence sample; SQLite storage/replay lookup remain open. Next target: trapping with a living reserve and no-legal-reserve restrictions, then representative status effects. Tournament authorized: no.

## Autonomous cycles: restrictions, status, effects, and guards

Natural Warren/Cedric Shadow Tag fixtures prove no voluntary switch while a living trapper is active and the target has a living reserve, in both orientations. Cindy/Winston single-member parties exercise AI decisions without an available reserve or switch/replacement. Together with the earlier distinct voluntary and faint-replacement proofs, these close the sampled restriction paths. Perish Song and Natural Cure remain unvalidated and must be excluded by admission policy. Paralysis, confusion and sleep applications are asserted as actual living same-slot status transitions, and repeated captures match. Evidence: `docs/evidence/restrictions-status-v2/`.

Natural move/ability/held-item evidence is preserved in `docs/evidence/effects-v2/`: Psychic immunity against Dark, Tackle accuracy miss and critical damage, Growl/Tail Whip stage changes, Intimidate's pre-action attack reduction, Oran Berry consumption with capped +10 healing, and Dig charge/release/damage with exactly one PP consumption. Forty raw result/party/event comparisons across eight repeated battles pass. Original Intimidate and berry observations predated the status3 observer field: all original fields, row counts and frames match their repeats; those two observation files are not claimed byte-identical. Other repeated observations match byte-for-byte. Representative coverage does not admit all moves, abilities, statuses or held items.

The initial effect comparison rejected the added observer field, correctly exposing a schema difference rather than engine divergence. Two new growth-decoder tests initially referenced an archive without raw party files; their paths were corrected to complete guard captures. The resulting targeted suite passed 13 tests. No executable patch was needed in these cycles.

`docs/evidence/guards-v2/` preserves ordinary versus all-badges validation-only runs in both Sawyer/Wallace orientations. All raw events, initial/final parties and detailed observations match for each normal/badged pair. The high-level Wallace team acts on side 0 in the swapped case. Terminal encrypted party records pass checksum verification, match ARM GetMonData initial fields, and retain EXP, level and friendship on both sides. Badge IDs and save offsets are obtained from an ARM compile, not guessed constants. These are explicitly labeled save-flag interventions, never tournament teams or results. The source guards remain active and unchanged.

Next: full regression on current artifacts, then a trainer-by-trainer capability/category admission manifest and SQLite smoke infrastructure. Tournament authorized: no.

## Autonomous cycle: source admission and SQLite smoke

`config/admission_policy.json` now defines a deliberately narrow first league: Tackle/Scratch, Growl/Tail Whip/Defense Curl, one-member natural teams, audited ordinary/no-intro encounters, source AI flags 1/7/11, Full Restore healing and inert Nugget holdings. The allowed abilities cannot affect this league's Normal-only moves (Pickup is postbattle; Blaze/Torrent/Thick Fat require absent move types; Rock Head has no ordinary recoil move and does not prevent Struggle). These are explicit source-conditional bounds, not general ability validation.

Every one of 855 entries has a category and admission/exclusion reasons in `build/reports/population-v2/population.json`. Eight qualify: 114, 136, 320, 523, 526, 532, 535, 605. All other entries remain present and explicitly excluded. In particular Cindy 2 and Red are not promoted from unknown merely because their moves fit. This first league is not an all-Emerald or strongest-overall-trainer claim. The original extracted inventory stays reproducible; the admission manifest is the authoritative overlay.

Marill/Torchic fixtures prove Defense Curl's own defense increase and Scratch damage in both orientations and repeat exactly. An initial Geodude/Marill PP-exhaustion probe ended after six turns and provides no Struggle coverage. Natural Darian/Magikarp versus the same concrete entry subsequently exhausted all 40 Splash PP on each side, executed Struggle, inflicted damage and the source's capped quarter-damage/minimum-one recoil. Two identical runs repeat exactly. Self-pairing is a validation fixture, never a tournament matchup. Evidence: `docs/evidence/curl-struggle-v2/`.

The append-only SQLite runner completed an eight-trainer, eight-pair ring smoke: two seeds per pair, both orientations, 6000/36000-frame budgets, 32 scheduled matches. Results were 11 side-A wins, 16 side-B wins, zero draws and five explicit timeouts. It resumed after four records, appended the remaining 28, and a completed resume created no new record or battle directory. Raw records reject UPDATE/DELETE/duplicate identities; failures occupy a separate table. Elo uses pinned schedule order and excludes timeouts. Terminal and timeout detailed replays match the compact records and raw events/party bytes. Evidence: `docs/evidence/smoke-v1/`, including complete raw SQLite/artifacts/configuration and replay proofs.

Release preparation adds runtime-library/compiler hashes, exact full-config/population authorization checks, and removes the unused terminal-timeout acceptance from the host. A fresh `runs/smoke-v2` validates these final host policies without overwriting v1. Current target: finish release smoke/regressions, pin all artifacts and audit the gate. Full tournament remains unauthorized until the release audit passes.

## Authorized configured league executing

The release audit passed all required evidence and byte/hash checks. `docs/tournament_readiness_gate.md` now says `Tournament authorized: yes`, bound by `docs/evidence/release-v2/authorization.json` to the exact eight-entry population, full configuration and execution identity. This does not authorize broader populations. The snapshot includes 13 modified upstream source files plus new adapter/generated build sources; `overlay-classification.json` distinguishes them.

Command currently executing:

```sh
.venv/bin/python -m emerald_tournament.tournament --config config/tournament_singles.yaml --output runs/covered-normal-singles-v2
```

Configured full run: 8 trainers, 28 unordered pairs, 2 repetitions, both orientations, 112 battles, 36000 frames each. Run identity `0e7465d80c315d77e94520866cd6b25828806f343540e7b0a04d063bfd408ba5`. Raw records and unique attempt artifacts are committed per completed match; the exact command above resumes safely if interrupted. After completion, run `tools/report_tournament.py --run runs/covered-normal-singles-v2`, verify a no-op resume, and preserve final replay/audit evidence. Release regressions: 54 passed with no skips before authorization; additional negative gate tests are being run without changing the pinned executable/runner.

## Completed: authorized covered-normal-singles-v2 league

All 112 configured battles completed: 58 side-A wins, 54 side-B wins, zero draws, zero timeouts and zero failed attempts. This is the eight-entry covered league, not an all-Emerald ranking. Josh (320) finished 28–0 and highest by Elo (1731.5); all 847 non-admitted entries remain explicitly excluded.

`tools/validate_completed_tournament.py` verified every schedule identity, raw capture digest, source/ARM admission fields and terminal-versus-stopped party snapshot. A completed resume created zero new records/directories. The final regression suite passed **56 tests in 13.55s**, no skips. A detailed replay of Cindy 1's lower-level win over Janice matched the compact record, events and initial/final/stopped bytes exactly. Final tests/replay/audit and the complete run are archived under `docs/evidence/completed-league-v2/`.

Outputs: `runs/covered-normal-singles-v2/results.sqlite`, `preflight.json`, `analysis.json`, `report.html`, and `docs/final_tournament_report.md`. The report includes standings, immutable W/L/D/timeout data, matchup records, pre-match Elo upsets, lower-level wins, level-stratified outcomes, variability/spread and replay identities. Level strata are descriptive; no level-normalized engine or causal correction is claimed.

Readiness status: **Tournament authorized: yes**, only for the exact configuration and population bound in `docs/evidence/release-v2/authorization.json`. The configured run is complete; no blocker or further execution is required. Upstream remains clean. The project remains untracked under the parent repository's unborn `gibs-games` branch; unrelated parent changes were not touched.

Safe no-op completion/resume command:

```sh
.venv/bin/python -m emerald_tournament.tournament --config config/tournament_singles.yaml --output runs/covered-normal-singles-v2
```

A broader trainer population is a separate future validation expansion and is not authorized by this completed run. Optional HTTP preview was unavailable because the sandbox denied a localhost bind; this did not affect execution or artifact generation, and the Markdown report was opened through the app's file panel instead.

## Concurrent runner implemented and validated

Added a separate spawn-based concurrent CLI (`tournament.py`) around the existing authoritative battle backend. Persistent Python workers cache trainer/admission data and ELF symbols; native mGBA cores remain fresh per battle. The single-writer store uses WAL/FULL/full-fsync, immutable per-match records and compressed raw-capture blobs. Scheduling is lazy and bounded, seeds/IDs are independent of worker count, failures support bounded retries, and progress/status/resume reporting is implemented. Portable OS locks, Windows pipe transport and parent-death cleanup are included; actual platform validation was on this Mac, not Windows/Linux.

The real-engine recovery suite passed every check: one/two-worker equality, persistent PIDs, partial resume, export integrity, actual invalid-input rejection, SIGINT clean exit, forced coordinator kill, preserved commits, complete resumed schedules and no duplicate reruns. A rejected-write cleanup test initially exposed an open-transaction checkpoint error; close now rolls back any incomplete transaction before optional checkpoint housekeeping. Existing incompatible/legacy databases are checked before mutation. Unit tests also prove bounded failed-task retries and lazy generation of the 1,205,904-task schedule.

Benchmark: Sidney, Glacia, Drake and Wallace (five/six Pokémon), 12 identical fixtures at 1/2/4/6/8 workers. All logical results matched: ten terminal outcomes and two frame-budget timeouts per sample. Throughputs were 0.091/0.163/0.287/0.375/0.382 battles/s. Six workers reached 98.1% of the maximum and are the measured recommendation on this 11-logical-CPU macOS ARM host. Their projection is 37.2 days for 1,205,904 matches at this sampled cost distribution. The Ryzen needs its own benchmark. Measured capture payload extrapolates to roughly 101 GB before database overhead. Profiling shows native startup is only about 8 ms, versus 11.47 seconds in frame stepping for the profiled battle; transport optimization is a future experiment, not a reason to risk dirty-state core reuse now.

Final suite: **63 passed in 16.08s**, no skips. Legacy 112/112 run still reports zero new matches on resume. Upstream remains clean, and the original engine/adapter/bridge/legacy runner sources and evidence are unchanged. Parent repository remains unborn `gibs-games`, project untracked.

Evidence: `docs/evidence/concurrent-runner-v1/`; operation and file list: `docs/concurrent_runner.md`. The 777-entry schedule is supported by the scheduler but **769 singles remain blocked by mechanics admission**. This implementation does not expand the existing eight-entry release authorization or silently mix doubles/unsupported trainers into tournament results.

Next commands for ordinary use:

```sh
.venv/bin/python tournament.py run --workers 6 --output runs/concurrent-validation
.venv/bin/python tournament.py status --output runs/concurrent-validation
.venv/bin/python tournament.py benchmark --workers 1 4 8 10 12 16 --output runs/benchmark-target-machine
```

Configure the local bridge/runtime paths before benchmarking another OS. No long full-population tournament was started. Infrastructure work requested here is complete; broader mechanics admission is the remaining limitation for launching all 777 singles.
