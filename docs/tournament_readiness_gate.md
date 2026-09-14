# Singles tournament readiness gate

Tournament authorized: yes

This gate applies to one authoritative Emerald ARM battle in mGBA. Historical evidence is useful for regression; a release requires evidence tied to the exact executable/checkpoint/configuration being authorized. Unknown or unsupported paths are excluded explicitly or remain blockers. A passing sample never validates all Gen III mechanics.

## Backend

- [x] Baseline ROM/ELF and headless mGBA work; real source engine executes.
- [x] Baseline construction and same/different-seed terminal battles pass.
- [x] Both-side move selection and narrow symmetry patches documented.
- [x] Release artifacts, all changed/generated build sources and host source preserved in evidence/release-v2; mGBA/libpng/compiler runtime hashes also pinned in smoke-v2 preflight.
- [x] Release regression: 54 passed, no skips (release-v2/build/reports/release-v2-regression.log); release smoke and replays pass.

## Battle mechanics

- [x] Baseline normal move selection, HP loss and fainting observed.
- [x] Forced replacements observed on both sides; voluntary selection/load/next-action proof on both sides.
- [x] Ordinary potion execution proven on both sides.
- [x] Full Restore healing on both sides and poison cure on side 0 tested with repeats; other statuses remain unvalidated (fullrestore-cycle-v2).
- [x] Single-flagged inventory audit found no X/stat items; proposed singles policy rejects any item outside the audited healing categories.
- [x] Natural simultaneous Full Restore eligibility and independent consumption/effects proven at seed 10 (concurrent-items-v2).
- [x] Sampled Shadow Tag with living reserve in both orientations and single-member no-reserve cases pass (restrictions-status-v2); Perish Song/Natural Cure remain excluded pending validation.
- [x] Both orientations with ordinary/all-badge save flags have identical traces and party bytes; terminal EXP/friendship/level unchanged (guards-v2), including high-level side-0 Wallace.
- [x] Representative paralysis/poison/sleep/confusion, Growl/Tail Whip, Intimidate, Psychic immunity, Tackle miss/critical and Dig charge/release/one-PP proofs (restrictions-status-v2, effects-v2). Oran Berry activation proven; attraction remains unvalidated and excluded.
- [x] Repeated bounded ring and switch fixtures preserve timeout outcomes and stopped state, never fabricated draws (ring-v2-cycle, voluntary-switch).

## Logging and replay

- [x] Baseline terminal results retain IDs, seed, final RNG, trace hash and initial/final party bytes.
- [x] ABI-v2 bounded-memory host-drained logging validated over buffer capacity (173 records; ring-v2-cycle evidence).
- [x] Deliberate undrained overflow fails closed with error 2 and diagnostic evidence.
- [x] Immutable compact SQLite records, deterministic lookup and terminal/timeout detailed replay equivalence pass (smoke-v2).

## Population and execution

- [x] All 855 entries retained with category and admission reasons in population-v2/population.json.
- [x] covered-normal-singles-v2 policy admits exactly eight concrete ordinary singles entries; all other entries explicitly excluded.
- [x] Full configuration: 36000 frames per battle; censored timeouts excluded from W/L/D/Elo. Struggle exhaustion and recoil validated separately.
- [x] SQLite uniqueness, append-only guards, partial/completed resume and deterministic reruns pass (smoke-v2; storage tests).
- [x] Eight-trainer smoke: 32 records, 27 terminal outcomes, five timeouts, two seeds/both orientations. Producer overflow is separately proven fail-closed on this exact ROM by ring-v2-cycle. No invalid outcome enters the store.
- [x] W/L/D/timeouts, games/attempts, win rate and Elo derive from raw records; ordering/config pinned and timeout exclusion/conservation tested.
- [x] Executable preflight pins population/config/source/runtime/ROM/checkpoint/ranking; configured full league is eight entries, 28 pairs, two repetitions, two orientations, 112 battles. Exact authorization binds config/population/execution identity before execution.

Full run and final report remain blocked until all applicable unchecked requirements have direct evidence or an explicit conservative exclusion. Exclusions must not silently redefine the trainer-entry population. The authorized full configuration, final results, matchup records, outliers/upsets, normalized analyses and replay instructions must retain exact run provenance.

## Release scope and authorization audit

The configured first league is deliberately limited to IDs 114, 136, 320, 523, 526, 532, 535 and 605. It does not claim to rank all Emerald trainers. All excluded entries remain documented; teams are never substituted. No attraction, Natural Cure/Perish Song heuristic, unlisted move/item/ability, or special script is silently enabled.

The final authorization audit must verify archived evidence and hashes and write `evidence/release-v2/authorization.json` before changing the status above. Full execution also checks that record against the exact full configuration, population and execution identity. Authorization does not extend to future changes or larger populations.

## Execution completed

Run `0e7465d80c315d77e94520866cd6b25828806f343540e7b0a04d063bfd408ba5` completed all 112 scheduled battles with no failures, timeouts or draws. All captures and a no-op resume passed the completion audit. Final regression: 56 passed, no skips. See `docs/evidence/completed-league-v2/` and `docs/final_tournament_report.md`. This authorization remains restricted to the pinned eight-entry league.
