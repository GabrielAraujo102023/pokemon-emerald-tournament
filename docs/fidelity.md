# Fidelity ledger

Nothing here currently establishes an Emerald-accurate battle simulator.

- Trainer party fields: compiled directly from upstream declarations/initializers; population and format invariants tested. Item identifier aliases fixed in extraction schema v2; canonical names now come only from the item enum. Names exported as readable source text, not game-encoded bytes. No ROM ABI claim.
- Eligibility: provisional lexical references and explicit rematch-table membership. Reachability, paired encounters and special behavior not verified; supported=false for every entry.
- IV/EV interpretation: source-audited. Raw inventory records scaled fixed IV and zero EV; no full CreateMon differential test yet.
- Personality and fixed-IV constructor arguments: all 1,825 members match captured calls from original CreateNPCTrainerParty compiled for host.
- Nature/gender/ability/default moves/stats/PP/friendship/experience: implemented using compiled source data and audited formulas; fixture and duplicate-move tests. Full CreateMon/ARM differential validation remains pending; OT ID and construction RNG consumption are omitted explicitly.
- RNG Random(): implemented and compared against compiled upstream random.c for 1000 outputs from 0xffffffff. Full 32-bit state input differs deliberately from the game's 16-bit SeedRng API. Frame schedule and Random32 call order are not validated.
- Damage, type immunity, crits, accuracy, status, weather, multi-turn/volatile effects, held items, turn order/speed ties: source locations identified; no simulator implementation or runtime validation.
- AI move scoring, switching, trainer items, faint replacement: source inspected; no symmetric adapter or differential tests.
- Doubles, simultaneous KOs, victory/defeat edge cases: unsupported.
- Replay, database, tournament/resume, rankings, statistical analysis: design only; no results generated.

Validation gate: complete construction oracle, seeded battle traces in both orientations, focused mechanic fixtures, and audited event/state equivalence. Then a small repeated round robin can measure throughput and storage. Do not infer battle fidelity from successful extraction or RNG tests.


## Explicit initialization/address gates

The isolated OT rejection-loop test compiles original source with random.c and exercises a rejected shiny candidate. Canonical JSON record repeatability is tested for Sawyer/Wallace, but this is not byte-for-byte GBA party memory. Target Random32 half order and interrupt schedule remain unvalidated. OT affects player obedience and encrypted storage; it is not discarded.

The local -m32/i386 executable probes failed. Operand inventory covers 202 macro .4byte sites and 249 candidate interpreter reads; semantic review is incomplete. First runtime target is now ARM/GBA emulation. No real-engine deterministic integration test has passed. config/validation_milestones.json records the policy gate; no tournament runner exists that could enforce or bypass it yet.


Latest runtime evidence (2026-09-12): [successful ARM build, emulator and construction validation](runtime_status.md). This supersedes earlier statements that the binaries, bridge and construction checkpoint do not exist. Full trainer-vs-trainer battle validation is still pending.
