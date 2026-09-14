# ADR 001: actual Emerald engine as canonical target

Status: selected direction; feasibility gate remains open. No battle backend is implemented or certified. Source pin: `5eff78649e7170a877b961ef0b3da13b81a16038`.

## A. Reuse the original engine — selected

Reuse the C battle core, battle bytecode, AI interpreter and scripts. Python handles extraction, orchestration, SQLite and derived analysis. Preserve upstream and keep any adapter/patch set separately versioned. First compare a host adapter against a GBA execution oracle; if host adaptation cannot preserve semantics, investigate deterministic emulator execution as the canonical implementation of this approach.

Mechanical and AI fidelity have the highest ceiling here, but neither is automatic. Global save state, controller acknowledgments, GBA registers, memory layouts and bytecode address representation obstruct a simple executable wrapper. The repository Makefile targets ARM, not a supported host battle library; arm-none-eabi-gcc was not found on the current PATH. Existing partner AI shows AI can act on a player-side battler, but setup reads opponent trainer IDs and shared history stores opponent items. Indexing such as gActiveBattler / 2 must be audited before allocating independent inventories.

Performance is unmeasured. A host core may be fast; emulation may cost substantially more. Reproduction requires pinned code, adapter, compiler, initial save state, controller schedule and RNG policy. Event hooks must capture resolved actions and state without introducing RNG calls. Testing should compare complete state traces to the original engine; maintenance should track a small reviewed adapter rather than wholesale source copies.

## B. Standalone port — deferred

A clean standalone implementation would be easier to isolate, log, parallelize and unit-test. It would also require porting both bytecode systems, integer arithmetic/order, switching, item heuristics, status interactions and source bugs. Maintaining equivalent behavior across hundreds of effects is the dominant cost. Throughput is plausible but unmeasured. Deterministic seeds are easy; equivalent RNG consumption is not. Use only if A fails a concrete prototype, with per-mechanic differential tests and explicit unsupported errors. Do not substitute a simple damage loop as a vertical slice.

## C. Showdown — reference candidate, not canonical

Inspected [Gen III scripts](https://raw.githubusercontent.com/smogon/pokemon-showdown/master/data/mods/gen3/scripts.ts) and [conditions](https://raw.githubusercontent.com/smogon/pokemon-showdown/master/data/mods/gen3/conditions.ts) on 2026-09-11. Its Gen III implementation inherits other generations with overrides, applies type-based physical/special categories and staged RSE damage modifiers. This is useful reference code, but not evidence of Emerald execution equivalence. No pinned Showdown dependency or differential compatibility suite was established.

A backend would still need Emerald team creation, trainer move/switch/item policy, inventories and RNG schedule. Its event model supports inspection, and a mature battle implementation could reduce mechanics work; no throughput measurement was made. Exact handling of bugs, simultaneous KOs, PP initialization, cartridge RNG and competitive rule modifications remains unverified. Ability/nature/IV inputs alone do not reproduce generated OT identity or shared RNG history. Do not use its output for canonical rankings until those differences are measured and accepted.

## Gate and next milestone

Build a controller adapter for one seeded singles battle; provide independent trainer IDs, AI flags, history and inventory per side. Suppress presentation RNG under an explicitly versioned headless ruleset, retaining a deterministic-frame oracle for comparison. Clear badge flags and identify other player privileges without setting a broad Frontier flag that silently changes AI. Trace move selection, RNG calls and complete turn states in both orientations.

Then use eight source-selected trainers spanning one/multiple Pokémon, default/custom moves, held items, battle items, low/high levels and AI masks. Require team reconstruction and representative damage/status/accuracy/crit/switch/item tests before adding the SQLite/replay/repeated-match/Elo slice. The requested full battle vertical slice is deferred because this feasibility and correctness gate has not passed.

## Follow-up evidence

The reproducible [host probe](host_adapter.md) now gets past generated map-header dependencies. Switching/item AI passes host syntax checks; the main engine and AI interpreter encounter GBA section attributes, graphics preprocessing, and bytecode pointer-width issues. This supports continuing the bounded adapter investigation but does not establish a working engine. The construction harness now validates 1,825 original constructor argument tuples; full CreateMon and battle traces remain the next fidelity gates.

## ADR 002: validate ARM execution before a native host port

The explicit RNG/address milestones supersede the earlier host-first preference. Select ARM/GBA emulation as the first implementation target; retain typed virtual-address relocation as a future optimization. See script_addresses.md and rng_and_party_initialization.md for evidence and incomplete gates. No validated runtime exists yet. The full tournament remains disabled by validation_milestones.json.
