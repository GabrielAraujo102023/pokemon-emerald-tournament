# Host adapter feasibility probe

Run `python3 tools/probe_host.py` from any directory. Diagnostics and compiler identity are saved in host_probe.json. The probe builds upstream mapjson in a temporary directory, generates the required map-group and layout headers there, and checks four untouched upstream translation units with the host compiler. No upstream writes occur. This is a syntax probe, not a linked backend or a timing benchmark.

Observed on Apple Clang / macOS:

- battle_ai_switch_items.c passes syntax checking with the generated headers.
- battle_main.c and battle_ai_script_commands.c fail on GBA ELF section attributes unsupported by Mach-O.
- battle_script_commands.c requires upstream asset preprocessing for INCGFX macros.
- AI bytecode pointer reads also warn about constructing native pointers from 32-bit integer operands. Removing section annotations alone cannot solve the 32-bit bytecode address representation on a 64-bit host.

These results favor a staged adapter over indiscriminate stubs: first an explicit address-space strategy for bytecode, then controller/event hooks and narrowly defined presentation shims. The original C interpreter contains pointer-bearing bytecode; executing it safely requires translated offsets, a checked 32-bit address model, or ARM execution. No decision to truncate host pointers is acceptable.

There is useful original-code reuse already: random.c is compiled for the RNG differential test, and CreateNPCTrainerParty is compiled with captured CreateMon arguments for the construction tests. The latter proves only constructor arguments; its stubs do not create Pokémon or perform battle mechanics.

AI symmetry remains a separate requirement. Opponent and player-partner controllers both call AI_TrySwitchOrUseItem, but shared trainerItems/itemsNo state and gActiveBattler / 2 item indexing need adaptation: ordinary battlers 0 and 1 both map to index zero. Inventory isolation therefore cannot be achieved solely by invoking the existing AI twice. Record each such patch with tests for both orientations.

Next native experiment: choose and demonstrate the bytecode address model, link the switching unit with actual battle state and constrained accessor dependencies, and verify independent inventory/state behavior. Full battle execution and performance remain unmeasured. An emulator-backed oracle is still required before declaring the host adapter canonical in practice.
