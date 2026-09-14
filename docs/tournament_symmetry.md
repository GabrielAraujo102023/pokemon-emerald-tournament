# Tournament symmetry patch requirements

Status: planned changes, none yet applied to upstream. All must be gated by an explicit tournament-mode variable, not broad Frontier/link flags. One authoritative battle state and RNG stream serve both trainers.

- Party destination: adapt CreateNPCTrainerParty clearing to the actual requested destination in tournament mode. Construct player/A then enemy/B through CreateMon; preserve ordinary enemy behavior outside tournament mode. Avoid CB2_InitBattleInternal creating B a second time.
- Controller selection: route side-zero action/move/replacement selection through trainer AI while retaining player-side presentation/controller acknowledgments where needed. Copying an opponent controller wholesale is unsafe because its party accesses may be enemy-specific. Audit each command's party lookup and completion bit.
- Trainer identity: BattleAI_SetupAIData selects the active side's trainer AI flags. Special battle-type overrides must not accidentally supersede those masks.
- History: separate per-side observed history and trainer inventory; maintain actual information visibility rather than exposing all moves/abilities by convenience. Shared AI scratch state may be reused only after each decision finishes and it is cleared correctly.
- Items: replace trainerItems/itemsNo assumptions and every gActiveBattler/2-derived item index with an explicit trainer/side mapping for singles. Audit chosenItem, AI_itemType and AI_itemFlags readers as well as writers. Reset inventories from each trainer definition for every match. Test both orientations and item exhaustion.
- Switching: reuse ShouldSwitch/GetMostSuitableMonToSwitchInto and source replacement policy, with side-relative party/active/absent checks. Test active-slot exclusion, faint replacement and forced switch constraints on both sides.
- Obedience: return NPC obedience for tournament-controlled battlers before player OT/level checks; retain original OT and encrypted data. Do not solve this by assigning matching player OT IDs.
- Badges: suppress tournament stat/speed badge boosts at their guarded source sites. Do not give both sides badges because that changes NPC stats.
- Friendship: suppress the one-sided league-entry adjustment; preserve constructor base friendship. This affects Return/Frustration and must have targeted tests.
- Experience: bypass award logic only in tournament mode, so defeated Pokémon do not change level, moves, friendship or stats mid-match.
- Timing: controller acknowledgments must be deterministic without dropping script-visible state updates. Initially keep actual frame execution and record the schedule; graphics removal is a separate change requiring trace comparison.

Acceptance requires same-seed full bytes and traces, reversed-side scenarios, independent item-use and switching traces, no badge/obedience privilege, and an ordinary non-tournament regression scenario. Current host protocol tests do not validate these patches.

## 2026-09-12: minimal real battle adapter

The authoritative state is one Emerald battle in mGBA. `BATTLE_TYPE_TRAINER` is the only battle type selected; no Frontier, link, or partner flags are borrowed. `tools/apply_battle_adapter.py` applies the following overlay to `build/pokeemerald`, never to `pokeemerald`.

- `CB2_InitBattleInternal`: preserve the already constructed parties instead of constructing enemy party again; suppress league friendship adjustment. Normal resource allocation and battle initialization remain in use.
- `BattleMainCB2`: poll small observations and capture the engine outcome before returning to the overworld, rewards, or save processing.
- `PlayerHandleChooseAction/ChooseMove/ChoosePokemon/ChooseItem` and the corresponding `OpponentHandle...` functions: invoke the same tournament trainer-AI wrappers, emit the original controller responses, and retain the normal controller acknowledgment and graphics paths.
- `BattleAI_SetupAIData`: select the active side's actual trainer AI flags. The original AI scoring implementation is retained. Scratch thinking state is reset for each synchronous selection; persistent histories are separate per side.
- `ClearBattlerMoveHistory`: clear both private observers' records for a replaced battler. The wrapper selects a side-local `BattleHistory` for AI evaluation and restores the allocated engine pointer afterward. Public observed ability/item records are copied from the engine; each history retains its own discovered moves and trainer item inventory.
- `ShouldUseItem` and `HandleAction_UseItem`: index NPC item type/flags/chosen-item storage by side in tournament mode, and use NPC item scripts on either side. Inventory comes from each trainer's actual item list. Upstream item classification and restrictions remain unchanged.
- `IsMonDisobedient`: return obedient during the tournament battle. `ShouldGetStatBadgeBoost` and `GetWhoStrikesFirst`: suppress badge stat/speed boosts. `AdjustFriendship`: suppress battle friendship mutation, including faint adjustments. `Cmd_getexp`: take the existing no-EXP branch.
- Battle message auto-scroll is enabled during tournament execution; battle style is SET. These avoid message acknowledgment and shift prompts. `Cmd_attackstring` adds an observation of actual move execution.

`TournamentAIMove` preserves self-target correction. `TournamentReplacement` consumes an already queued AI replacement or calls the original replacement selector and scans the active side's six slots as fallback. Original switching heuristics already select party storage by battler side.

All external source changes use `TOURNAMENT_MODE` guards. Runtime behavior hooks additionally require the active mailbox phase; normal battle paths remain available when inactive. Party construction and checkpoint-entry hooks are specific to the tournament build. Each host battle restores the checkpoint into a fresh core; the terminal barrier prevents persistent overworld/reward processing. HP/PP/status mutations in battle party arrays are the intended exported result.

Validated scope: Sawyer versus Wallace at seeds 12345 and 12346 reaches both AI move selectors and an engine loss for side A. This does **not** establish complete symmetry across Emerald. Dedicated swapped-side, trainer-item, voluntary-switch, forced-replacement, ability, and self-target fixtures remain necessary before broader simulation. Double-flagged, empty and out-of-range trainer requests are rejected. Special flee/watch AI returns are explicit adapter error 101.

### Verified potion command correction

The subsequent natural-team fixtures found an additional required source patch: `Cmd_useitemonopponent` passed `gEnemyParty[...]` unconditionally into `PokemonUseItemEffects`. Even with side-aware action/inventory routing, the healing eligibility and full-heal amount therefore depended on the wrong party for side 0. The tournament guard now chooses the active user's party; the ordinary Emerald path is unchanged. Roxanne/Brawly, seed 12346, verifies both orientations through real script execution and HP observations. Do not infer status-cure, revive, full-restore or X-item coverage from the potion result.

Swapped Sawyer/Wallace and forced replacements in Roxanne/Wallace passed on the same fixed ROM. Natural-team fixture code and explicit assertions are in `tools/validate_symmetry.py`; immutable evidence is under `docs/evidence/symmetry-*-fixed/`. Voluntary switching remains a coverage gap.

### Voluntary-switch evidence (2026-09-13)

Julie/Bernie 5 now passes the bounded voluntary-switch path on both sides. The pinned seeds are 12345 for Julie on side 0 and 7 for Julie on side 1. The verifier correlates the actual AI `switch_selected` record with living outgoing HP, selected party slot/species loading, and a subsequent AI move selection from that slot. Both orientations repeated byte-for-byte. See `docs/evidence/voluntary-switch/validation.json` and `tools/validate_switch.py`.

These tests do not require or report terminal battle success: each 12000-frame run retains a host-budget timeout. They establish correct switch routing and continued AI execution for this fixture, not complete symmetry of all switching heuristics or equal trajectories under swapped sides. No ROM patch or additional EWRAM was necessary.

### Full Restore and inventory ownership on mailbox ABI v2

The `fullrestore-cycle-v2` evidence validates HP restoration on both sides of Cindy 1/Winston 1 battles and poison curing on side 0 in Cindy 3/Catherine 1. The observer reads the two private BattleHistory inventories using offsets compiled by devkitARM against the actual build headers (size 84; trainerItems offset 72). For every inventory transition, the checker matches the exact side/item selections since the previous event count, requires exactly one owned item consumed per selection and rejects opposite-side or unlogged consumption.

Both orientations and both fixtures reached terminal outcomes and repeated byte-for-byte at seed 12345. The fixtures exercise both inventories in the same battle, but do not prove simultaneous eligibility. Full Restore's unobserved status variants and other item categories are not automatically validated. All single-flagged extracted inventories were audited: no standalone status cure or X/stat item was found. The proposed singles policy explicitly rejects categories outside the audited healing list.
