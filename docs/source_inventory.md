# Source inventory

Inspected checkout: `5eff78649e7170a877b961ef0b3da13b81a16038`. Paths below are relative to `pokeemerald/`. This is a source investigation, not a claim of runtime validation. Existing loose prototype files in the project root are left intact; extraction uses the upstream checkout only.

## Data and encounters

- `src/data/trainers.h`: `gTrainers`, designated by trainer ID. Class, displayed name, presentation/gender byte, party macro, AI mask, battle items, double flag. 855 entries including NONE.
- `src/data/trainer_parties.h`: all four ordinary party formats; IV parameter, level, species, optional moves and held item.
- `include/data.h`: authoritative Trainer and four TrainerMon layouts; party macros expand sizes and format flags. The host extractor copies this declaration section into a temporary header and compiles the original initializers.
- `include/constants/opponents.h`: ordinary trainer IDs. `include/constants/trainers.h`: classes, pictures, music/gender and special trainer IDs. Special numeric namespaces must not be indiscriminately merged with gTrainers.
- `src/battle_setup.c`: encounter setup and `gRematchTable`; `data/maps/*/scripts.inc` and `data/scripts/*.inc`: story/paired encounter usage. Textual references alone do not establish reachability. Full script control-flow analysis remains pending.
- `src/data/battle_frontier/battle_frontier_trainers.h`, `battle_frontier_mons.h`, `battle_frontier_trainer_mons.h`: separate facility trainer and rental/team pools. `battle_tent.h`, `trainer_hill.h`, `apprentice.h` add distinct contexts. They are not ordinary gTrainers parties. Secret Base and e-Reader creation also need separate adapters.
- `src/data/pokemon/species_info.h`: base stats, types, gender ratio, base friendship, growth rate, ability slots and other species attributes.
- `src/data/pokemon/level_up_learnsets.h`, `level_up_learnset_pointers.h`: ordered default move learning data. `experience_tables.h`: level/experience lookup.
- `src/data/battle_moves.h`: power, type, accuracy, PP, target, priority, effect and flags. `include/constants/moves.h`, `battle_move_effects.h`: identifiers. Move effect behavior is code/scripts, not this table alone.
- `src/data/items.h`, `src/data/pokemon/item_effects.h`, `include/constants/items.h`, `hold_effects.h`: items and effect data; actual activation is spread across the battle code.
- `src/data/text/species_names.h`, `charmap.txt`: required for personality hashing; displayed Unicode/ASCII is not the game encoding.

## Pokémon construction

`src/battle_main.c:CreateNPCTrainerParty` is the ordinary NPC construction authority (line 1960 at this pin). It excludes Secret Base and bypasses Frontier/e-Reader/Trainer Hill paths; two-opponent battles cap each trainer to three slots. `src/pokemon.c:CreateMon`, `CreateBoxMon`, `CalculateMonStats`, `GiveBoxMonInitialMoveset`, `GetNatureFromPersonality` determine the resulting Pokémon. See trainer_generation.md for findings and unresolved extraction work.

## Battle execution and AI

- `src/battle_main.c`: initialization, controller dispatch, action selection, `GetWhoStrikesFirst`, turn ordering, `gTypeEffectiveness`. Speed badges and random ties are handled here. `VBlankCB_Battle` also calls Random in ordinary battles.
- `src/pokemon.c:CalculateBaseDamage`: physical/special stats, badge boosts and damage arithmetic. Type/crit/random modifiers also involve script commands; calling this function alone is not a complete damage simulator.
- `src/battle_script_commands.c`: script command dispatch, `Cmd_accuracycheck`, `Cmd_critcalc`, `Cmd_typecalc`, `Cmd_tryfaintmon`, effect application, move failure and victory-related processing. Exact ordering matters.
- `data/battle_scripts_1.s`, `data/battle_scripts_2.s`, `include/constants/battle_script_commands.h`: battle bytecode and opcodes. Multi-turn moves, recoil, faint processing and move effects require the interpreter.
- `src/battle_util.c`: `AbilityBattleEffects`, `ItemBattleEffects`, turn-end processing, status/weather/volatile interactions and switch-in effects. `include/battle.h` and `include/constants/battle.h` define the shared structures/status bitfields.
- `src/battle_ai_script_commands.c`: `BattleAI_SetupAIData`, move scoring and script interpreter. Enabled scripts come from opponent-specific IDs, with special battle-type overrides. Four initial move scores are 100 where enabled, unusable moves zeroed, and per-move simulated damage RNG generated.
- `data/battle_ai_scripts.s`, `include/constants/battle_ai.h`: scoring logic and AI masks. This is scripted scoring plus random branches, not a generic strongest-move chooser.
- `src/battle_ai_switch_items.c`: `AI_TrySwitchOrUseItem`, `ShouldSwitch`, `GetMostSuitableMonToSwitchInto`, `ShouldUseItem`. Switch checks precede item selection. Party selection partly supports either side, but inventory/history and some per-battler indexing are not safely independent for both sides.
- `src/battle_controller_opponent.c`, `battle_controller_player.c`, `battle_controller_player_partner.c`, `battle_controllers.c`: controller command scheduling, selection, replacement and acknowledgments. Partner AI is useful precedent, not proof of symmetrical trainer behavior.
- `src/random.c`, `include/random.h`: two RNG states, LCG algorithm, SeedRng and Random32. Call order includes creation, AI, move resolution and presentation/frame work.
- `Makefile`, `ld_script.txt`, `include/global.h`, `include/gba/`: ARM/GBA build assumptions, memory/register definitions and linking. Host compilation of isolated data works; this does not prove host battle-engine portability.

## Surprises and unresolved questions

The name hash accumulates across party slots; all ordinary personality low bytes are even, hence ability slot zero. OT creation still consumes RNG despite fixed personality and IVs. Trainer item policy uses party-count gates and original inventory length. Ordinary player-side badge bonuses create real side asymmetry. VBlank RNG makes presentation removal a semantic change unless the RNG schedule is explicitly defined.

Pending: exact controller completion/faint/outcome sequencing, simultaneous final KO rules, partner AI hard-coded assumptions, all player-side obedience/experience/save-state dependencies, environmental weather selection, special script reachability, and a full call-site RNG audit. No doubles or battle mechanic is yet certified by tests.
