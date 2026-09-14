# Ordinary trainer Pokémon generation

Authority: `src/battle_main.c:CreateNPCTrainerParty` and `src/pokemon.c:CreateMon/CreateBoxMon` at the pinned commit.

The party `iv` is scaled using integer arithmetic: `iv * 31 / 255`, truncated, and assigned equally to all six IVs. It is not an IV total or random range. Examples: 0→0, 100→12, 200→24, 255→31. Ordinary construction zeroes the Pokémon and does not award EVs: all six EVs start at zero.

A `nameHash` starts at zero once per party creation, outside the slot loop. For each slot add the bytes of the trainer's Emerald-encoded name and that slot's species name, excluding EOS. Personality is `(nameHash << 8) + lowByte`; lowByte is 0x80 for double-flagged trainers, otherwise 0x78 for female presentation or 0x88 for male presentation. The hash is cumulative across slots. Nature is personality modulo 25. Gender follows species gender ratio and personality low byte. Ability selection uses personality & 1 when a second ability exists. All three low bytes are even: these ordinary teams use ability slot zero.

Do not hash the UTF-8 trainer names in the JSON. The host extractor's `_` macro preserves readable source strings rather than Emerald encoding. The separate generation.json artifact now uses the upstream preproc tool and charmap to supply encoded trainer and species bytes. The --reconstruct CLI consumes those bytes; the original raw inventory remains separate.

Creation generates a random OT ID until its shiny calculation is non-shiny. Fixed personality therefore does not eliminate RNG consumption. Random32 is a macro with two Random calls; evaluation order must be checked against the target compiler before a host port claims identical consumption. The original game SeedRng takes 16 bits; replay from a saved gRngValue needs 32 bits.

CreateBoxMon initializes species base friendship and experience from the species growth curve. Default moves traverse the species learnset in order through the current level, using GiveMoveToBoxMon; when full, delete the oldest move. Duplicate handling must follow that helper, not merely take the final four table rows. Explicit moves replace all four slots and set PP from each move's base PP. Held items are assigned only for the corresponding party formats. Freshly zeroed status/PP bonuses and CalculateMonStats provide pristine HP; Shedinja has its special one-HP branch.

HP is `floor((2*baseHP + IV + floor(EV/4))*level/100)+level+10`, except Shedinja. Other stats use the analogous expression plus 5, followed by the source nature adjustment with integer truncation. Battle badge boosts are separate from stored stats.

Implemented generation.json includes 412 species records, 355 move records, all corresponding learnsets, encoded names, nature modifiers and experience tables. The helper builds the upstream text preprocessor in a temporary directory and compiles original data initializers without modifying upstream.

The host harness runs the original CreateNPCTrainerParty function for all 854 nonempty entries and captures CreateMon arguments. All 1,825 species/level/fixed-IV/personality tuples match Python reconstruction. This oracle stubs CreateMon, SetMonData and ZeroEnemyPartyMons; it does NOT validate encryption, OT IDs, final Pokémon structs, RNG consumption, full stats or default moves. Those distinctions are deliberate.

Reconstruction includes stats, current HP, nature, ability, gender, friendship, experience, moves, PP, held item and initial status. Default-move duplicate/overflow behavior has focused tests; Sawyer's level-21 Geodude is a source-derived fixture (personality 658056, HP 47, Mud Sport/Rock Throw/Magnitude/Self-Destruct). Nature adjustment retains the original u16 intermediate, including the unpatched overflow behavior. Special encounter party truncation is not applied by ordinary-full-party-v1.

OT ID is null; no construction RNG calls are invented. The policy is seed-independent battle-field reconstruction, not complete exact initialization. Next: compare the full CreateMon result and OT rejection-loop RNG trace with ARM execution, then expand source-derived/differential tests for stats and move generation.
