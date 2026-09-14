# Executed rules: covered-normal-singles-v2

The first configured league ranks eight concrete trainer entries independently at their original source levels. All 855 source entries retain classification/admission reasons; 847 are explicitly excluded. Only the capability-bounded ordinary singles population in `config/admission_policy.json` is admitted. Teams, moves, items, abilities and AI flags are never replaced.

Each match restores the exact clean checkpoint into one authoritative Emerald ARM instance in mGBA, constructs both natural trainer parties using source code, and shares one battle/RNG state. Both sides run source trainer AI with their own inventory/history. The guarded player obedience, badge, EXP and friendship policies have direct state evidence. Engine VBlank RNG behavior remains under the pinned single-frame controller schedule; no claim of arbitrary human-paced cartridge timing is made.

Eight entries create 28 unordered pairs. Each pair has two repetitions and both orientations: 112 battles. Seeds are the first eight hexadecimal digits of SHA-256 over canonical JSON `[seed_version, master_seed, smaller_id, larger_id, repetition, orientation]`. The seed version, master seed, resulting seed and schedule are pinned in preflight.

The frame cap is 36000 per full-run battle. A host timeout is a separate censored record, never a draw or win. Engine terminal outcomes alone define wins/losses/natural draws. Overflow and unsupported execution are failures and cannot enter results. Struggle's implicit PP-exhaustion/recoil path is directly validated. Ordinary new-game starting state and original source teams are used; no environmental or level-normalization experiment is mixed into this league.

SQLite raw results are append-only, uniquely identified by run/configuration and pair/repetition/orientation. Attempts use fresh directories. Resume skips committed identities and never overwrites an interrupted attempt. Elo starts at 1500, K=32, in sorted pair/repetition/orientation order; timeouts do not contribute. Raw results survive regeneration of derived analyses.

Only `docs/evidence/release-v2/authorization.json` plus the explicit readiness-gate status authorizes the pinned full configuration. A change to population, configuration or execution provenance requires a new release audit. The current configured league completed all 112 matches successfully.
