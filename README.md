# Emerald trainer tournament research

The original Emerald ARM engine now executes seeded trainer-versus-trainer battles through a guarded adapter and headless mGBA. The evidence-authorized first league completed **112 battles across eight conservatively admitted trainer entries**, with no failures or timeouts. **This is not an all-Emerald ranking:** 847 of 855 extracted entries remain explicitly excluded pending broader coverage. Final regressions: 56 passed.

Start with [the final report](docs/final_tournament_report.md), [current progress](docs/progress.md), [readiness gate](docs/tournament_readiness_gate.md), and [executed rules](docs/tournament_rules.md). The raw SQLite ledger and interactive tables are in `runs/covered-normal-singles-v2/`.

Uses the existing `pokeemerald/` checkout at `5eff78649e7170a877b961ef0b3da13b81a16038`, kept unchanged. Existing root prototype files are not used by this package. Requirements: Python 3.10+, Git, a C11 host compiler (`cc`) and a C++11 compiler (`c++`) for the upstream text preprocessor. No third-party Python runtime packages.

From this directory:

```sh
PYTHONPATH=src python3 -m emerald_tournament extract
PYTHONPATH=src python3 -m emerald_tournament trainers list
PYTHONPATH=src python3 -m emerald_tournament trainers show TRAINER_SAWYER_1 --reconstruct
PYTHONPATH=src python3 -m unittest discover -s tests -v
```

`--project` and `--upstream` options precede the command and allow explicit paths. Rebuild generated data rather than editing it. The C helper consumes upstream declarations and party macros; Python adds conservative classifications and provenance. Compilation warnings are errors. The native helper is built in a temporary directory.

Read [source inventory](docs/source_inventory.md), [trainer inventory](docs/trainer_inventory.md), [generation findings](docs/trainer_generation.md), [architecture decision](docs/architecture_decision.md), [executed rules](docs/tournament_rules.md) and [fidelity ledger](docs/fidelity.md).

Team reconstruction now emits battle-relevant fields (stats, personality, nature, gender, ability, moves, PP, friendship and experience). Constructor arguments are checked against the original function for all 1,825 party members. OT IDs and construction RNG consumption remain unresolved; this is not yet a complete engine initialization. See [generation findings](docs/trainer_generation.md) and the [host probe](docs/host_adapter.md).

Next milestone: full CreateMon/OT-RNG validation and one deterministic actual-engine battle with independent AI/item state on both sides. Only after validation expand to eight trainers, replay/SQLite persistence, repeated matches and rankings. Runs and databases must remain outside version control by default.


The RNG/address validation milestones are documented in [RNG initialization](docs/rng_and_party_initialization.md) and [script addresses](docs/script_addresses.md). ARM/GBA emulation is now the first backend target; the native port is deferred. Both runtime gates remain open. `python3 tools/audit_validation.py` reproduces the address inventory and local compiler probes. The initialization tests validate an isolated OT experiment, not full GBA party memory or battle outcomes.


## Emulated backend prototype

Start with [emulator setup and runner](docs/emulator_backend.md), [checkpoint requirements](docs/checkpoint.md), [symmetry patches](docs/tournament_symmetry.md), [event ABI](docs/event_log_format.md), and the [ARM adapter patch plan](adapter/patch_plan.md). [Native hosting](docs/native_backend_future.md) remains secondary.

```sh
python3 tools/emulator_probe.py
python3 tools/run_emulated_battle.py --help
PYTHONPATH=src python3 -m unittest discover -s tests -v
```

The runner accepts ROM/ELF/checkpoint/manifest paths plus trainer IDs and seed, and rejects missing or mismatched artifacts. The ARM ROM, headless bridge, deterministic construction checkpoint, both-side AI routing and minimal battle-event hooks now run. Sawyer versus Wallace reached an engine terminal result at seeds 12345 and 12346; repeated seed 12345 matched party bytes, outcome, final RNG and trace. This is a small battle milestone, not full tournament validation.

See [current progress and reproducible commands](docs/progress.md), [battle evidence](docs/evidence/battle-entry-validation.json), and [remaining symmetry coverage](docs/tournament_symmetry.md).

## Completed league and replay

The following command safely verifies/resumes the completed configuration; it executes no duplicate battles:

```sh
.venv/bin/python -m emerald_tournament.tournament --config config/tournament_singles.yaml --output runs/covered-normal-singles-v2
```

Use a match ID from the report with `.venv/bin/python -m emerald_tournament.replay --run runs/covered-normal-singles-v2 --match MATCH_ID --output build/reports/replay-new`. Keep the pinned executable/checkpoint/runtime and use a fresh output directory. Admission, persistence, deterministic replay, W/L/D/timeouts and Elo are implemented. Larger populations require new validation and release authorization.

## Concurrent execution

A new spawn-based runner supports persistent Python workers, durable SQLite WAL results and compressed raw captures, lazy schedules, retries, Ctrl+C/kill recovery, and hardware benchmarks. Existing released results and the sequential CLI remain unchanged. See [concurrent runner instructions](docs/concurrent_runner.md).

```sh
.venv/bin/python tournament.py run --workers auto --output runs/concurrent-validation
.venv/bin/python tournament.py status --output runs/concurrent-validation
.venv/bin/python tournament.py benchmark --workers 1 4 6 8 --output runs/benchmark-new
```

Rerunning the same `run` command resumes committed work automatically. The complete 777-singles schedule can be inspected with `tournament.py plan`; execution of unvalidated entries still fails closed. Benchmark fixtures are unranked and do not expand tournament admission.
