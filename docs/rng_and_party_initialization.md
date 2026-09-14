# RNG and party initialization validation milestone

Status: **partial; real-engine integration gate not passed**. Source pin: 5eff78649e7170a877b961ef0b3da13b81a16038. No tournament execution is permitted by this milestone's current evidence.

## Ordinary cartridge path

`src/random.c` owns gRngValue and gRng2Value. Random advances the first state by `state = (1103515245 * state + 24691) mod 2^32` and returns the upper 16 bits. Random2 advances the second state separately. SeedRng takes u16, while the stored state is u32. The default, unpatched startup in `src/main.c:AgbMain` does not call SeedRngWithRtc: that call/function are under BUGFIX. `SeedRngAndSetTrainerId` seeds from timer 1 during trainer-ID initialization. Ordinary battle setup does not reseed at the enemy-party constructor. Its RNG state is inherited from prior gameplay and elapsed frames, not determinable from the opposing trainer ID.

`CB2_InitBattle` reaches `CB2_InitBattleInternal` in battle_main.c. That routine establishes graphics/controller state, invokes SetUpBattleVarsAndBirchZigzagoon, sets VBlankCB_Battle, selects the start callback, and calls CreateNPCTrainerParty for the enemy in an ordinary non-link/non-recorded battle. The second trainer path is conditional on TWO_OPPONENTS. SetWildMonHeldItem follows, but its ordinary trainer guard prevents its wild-item RNG branch. The player's existing party is not ordinarily reconstructed here. A tournament creating both parties is necessarily a documented adaptation.

**Correction to the earlier frame audit:** `main.c:VBlankIntr` calls Random for ordinary battles; `battle_main.c:VBlankCB_Battle` also calls Random. When that callback is installed and the ordinary flags hold, a VBlank can therefore consume two RNG calls. Animation/controller timing is relevant. VBlank is installed before enemy construction; faithfully reproducing cartridge initialization also requires interrupt timing, not just a list of synchronous C calls.

## Construction calls versus battle calls

For ordinary party slots, CreateNPCTrainerParty computes a fixed personality from cumulative encoded trainer/species-name bytes and scales the fixed IV. Neither step calls Random. CreateMon clears the record, calls CreateBoxMon and calculates stats. With the fixed-personality/fixed-IV arguments, the only explicit RNG calls inside CreateBoxMon are OT generation: Random32, repeated until GET_SHINY_VALUE is at least SHINY_ODDS (8). Each attempt consumes two Random outputs. IV random branches and random personality creation are bypassed. Default moves, friendship assignment and stat calculation do not explicitly consume RNG in these ordinary branches.

After construction, do not reseed unless a new rules version explicitly defines that different experiment. AI setup consumes Random for each simulated move damage factor (and doubles targeting); scoring scripts, switching, item/ability effects, ordering and battle scripts consume the same stream. VBlank continues to interleave with those calls in cartridge execution. A complete runtime call trace is still needed; the static inventory is not claimed to enumerate every transitive/frame call.

Random32 is `(Random() | (Random() << 16))`. The source does not explicitly sequence the two operand evaluations. The chosen target compiler must establish which output is the low half. Swapping the halves leaves the XOR shininess check unchanged, so the number of OT retry pairs and final RNG state are invariant to this ordering, but the OT ID bytes are not. The new isolated test compiles the original OT rejection-loop text with original random.c and accepts either observed half order; that is intentionally not ARM validation.

## OT and personality relevance

Personality determines nature (modulo 25), ability slot when available (low bit), gender (low byte versus species ratio), and the encrypted Pokémon substructure permutation. Nature affects stored stats; gender matters to effects such as attraction; the relevant resulting properties can affect AI decisions. Personality and OT jointly determine shininess and encrypt the secure Pokémon record (EncryptBoxMon/DecryptBoxMon XOR both values).

**OT is not proven irrelevant, and is demonstrably relevant to unadapted player-side behavior.** battle_util.c:IsMonDisobedient checks IsOtherTrainer against the save's trainer ID/name for player-side Pokémon. Ordinary opponent-side Pokémon return obedient before this check. Random opponent OT IDs moved to side zero can therefore produce different actions and additional RNG consumption. battle_script_commands.c also uses traded status for experience. OT is carried in BattlePokemon by controllers and participates in shiny presentation. No direct OT-based move-scoring branch was identified in the two AI units, but that narrower negative search does not remove the obedience path or byte-level identity requirement.

Another asymmetry: CB2_InitBattleInternal calls AdjustFriendship(FRIENDSHIP_EVENT_LEAGUE_BATTLE) on the player party. The function's leader/Elite Four/champion gate can change friendship and therefore friendship-based move power; this cannot silently remain one-sided.

## Required state and proposed initialization contract

CreateBoxMon reads gSaveBlock2Ptr (trainer ID in other OT modes, player name and gender), game language/version, species/experience/learnset/move tables, and GetCurrentRegionMapSectionId. CreateMon/CalculateMonStats touch gBattleScripting. GetCurrentRegionMapSectionId and initialization additionally require map/save globals. Full initialization needs allocated save blocks, valid pointers, initialized heap/resources/controller buffers, flags, party buffers, RNG states, and a known battle environment. Uninitialized placeholders are not acceptable.

The selected implementation target is ARM/GBA execution with a **versioned checkpoint and adapter**, pending implementation. Exact proposed ordering:

1. Restore a validated initialization checkpoint, recording its content hash, ROM/ELF hashes, compiler, emulator version, adapter version and rules. It must include initialized save/global/controller state. No checkpoint currently exists, so no arbitrary save bytes are substituted.
2. At a defined emulator instruction boundary, set the full gRngValue to the supplied u32 seed. Record the checkpoint's gRng2Value. Construct A then B, each in source slot order, through the actual ordinary constructor/CreateMon. Use a reviewed destination-buffer adapter because ZeroEnemyPartyMons unconditionally clears the enemy buffer. No reseeding between parties.
3. Record every Random call with caller/phase and before/after state, OT rejection attempts, full party bytes and decoded fields. Emulator execution, including interrupts, is deterministic from the checkpoint. Pin any interrupt suppression explicitly if later introduced; it is not currently approved as equivalent to ordinary frame behavior.
4. Enter battle through a dedicated adapter that avoids constructing B again. Use each trainer's own AI state/items. Enforce NPC obedience on both sides through a narrow tournament-mode change, suppress player-only badge bonuses and league-friendship adjustments, and disable in-match experience gains. These are explicit symmetric experiment decisions, not ordinary player rules. No broad Frontier flag is used.
5. Preserve the post-construction RNG stream, run the real interpreter/controllers, trace resolved events, and stop at the real terminal outcome. A deterministic instruction/frame budget must separately report timeout, not invent a draw. Record final bytes and trace hash.

This is an implementation specification, **not yet an exact working initialization procedure**: checkpoint contents, adapter entry point, target compiler half order and full runtime call schedule remain unresolved. No arbitrary OT IDs, pointer values or save constants have been introduced to bypass them.

## Tests and remaining gate

`tests/test_initialization.py` exercises the original extracted OT retry loop with compiled upstream random.c, forces a shiny first candidate to test retries, and checks deterministic canonical record bytes for Sawyer/Wallace at seed 12345 plus controlled state changes at 12346. Only OT fields change with seed in this isolated construction model; personality/stats remain fixed. `initialization_record` requires explicit half ordering and labels itself an experiment. Its bytes are canonical JSON, **not initialized GBA party bytes**.

Full byte-for-byte party-memory equivalence, real battle result equivalence, both-side AI, correct script execution, terminal outcome and event trace have **not** been obtained. There is deliberately no skipped/mock integration test represented as a passing battle test. Both validation milestones remain open.


Latest runtime evidence (2026-09-12): [successful ARM build, emulator and construction validation](runtime_status.md). This supersedes earlier statements that the binaries, bridge and construction checkpoint do not exist. Full trainer-vs-trainer battle validation is still pending.

## Reference preservation and real battle verification (2026-09-12)

The uninstrumented construction reference passed repeated seed 12345 full-party/decoded/RNG equality and seed 12346 divergence. Exact ROM/ELF/checkpoint/adapter hashes are in `docs/evidence/construction-uninstrumented.json`. The prior trace construction build is retained separately under `build/references/construction-traced/`.

Construction still passes in the battle-capable ROM, independently at phase 4. There are 50 observed RNG calls through constructor completion and four further calls during snapshot export (54 traced total). The post-construction RNG states remain 1510019643 for seed 12345 and 3782091108 for seed 12346. The isolated 14-call model is not the ARM execution trace.

Real battle tests compare full initial and final party bytes, decoded initial fields, terminal result, final RNG, and raw event bytes/hash across repeats. Seed divergence means valid different trajectories; it does not require a different winner. Instrumented traces have a separate timing identity from the uninstrumented reference.
