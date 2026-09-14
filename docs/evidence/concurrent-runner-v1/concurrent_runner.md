# Concurrent, durable local runner

Use `tournament.py` or `python -m emerald_tournament.parallel_cli`. The original sequential runner and its released eight-entry results remain unchanged. New concurrent stores have their own schema and execution identity; they cannot be mixed with legacy stores.

The immediate full schedule contains 777 nonempty singles entries and 1,205,904 matches (two seeds per unordered pair, both orientations). Trainer data is already present. **769 of those singles still lack mechanics admission**, so the full-population command refuses execution. Concurrency is infrastructure, not an authorization to treat unvalidated mechanics as supported. The separate benchmark mode is explicitly bounded and unranked, and includes natural five/six-member teams.

## Commands

From the repository, using its Python environment:

```sh
# Inspect the complete 777-entry schedule without materializing all tasks.
.venv/bin/python tournament.py plan --config config/parallel_singles.json

# A bounded, admitted eight-entry validation run. Rerun to resume automatically.
.venv/bin/python tournament.py run --workers auto --output runs/concurrent-validation
.venv/bin/python tournament.py run --workers 4 --output runs/concurrent-validation
.venv/bin/python tournament.py status --output runs/concurrent-validation

# Explicit resume requires existing state; --new requires a fresh output directory.
.venv/bin/python tournament.py run --resume --output runs/concurrent-validation
.venv/bin/python tournament.py run --new --output runs/concurrent-validation-new

# Retry failed logical matches. At most two additional retries per task this invocation.
.venv/bin/python tournament.py run --retry-failed --retries 2 --output runs/concurrent-validation

# Unranked natural full-party fixtures; fresh output required.
.venv/bin/python tournament.py benchmark --workers 1 4 6 8 --output runs/benchmark-new

# Extract a digest-verified raw capture from SQLite into a new directory.
.venv/bin/python tournament.py export --output runs/concurrent-validation --match UNIQUE_PREFIX --destination build/reports/export-new
```

Use `python` or `.venv\Scripts\python.exe` on Windows. `--inflight` defaults to twice the worker count and must be at least that count. `--limit` caps newly scheduled logical matches for a bounded partial run; it does not change battle IDs or configuration compatibility. `--progress-seconds` defaults to 10; per-battle output requires `--verbose`. Explicit worker counts are never inferred to be optimal.

## Architecture and inspection findings

The existing `emu_battle.run_battle()` executes one authoritative Emerald instance through `tools/emulator/bridge.c`. The bridge loads the ROM, creates the mGBA core/video buffer, restores the checkpoint and then accepts paused RAM reads, mailbox writes and single-frame steps. There is no reset/reload command validated for reuse between matches. Each battle therefore retains a fresh native core. Persistent **Python** workers process many tasks and cache ELF symbols and trainer/admission data. They do not inherit or share an emulator state.

The host and emulator are separate processes. A spawn-based `ProcessPoolExecutor` supplies multicore parallelism; the parent alone opens the writable database. A small process-local Windows pipe-reader thread provides timeout-capable anonymous-pipe reads, since Windows selectors cannot select those pipes. A parent-watchdog thread terminates the active native child and exits the worker after coordinator death. Neither thread executes battle mechanics. Ordinary per-battle failures remain isolated and do not kill the pool; a broken pool or changed pinned backend stops further scheduling.

`parallel_tasks.py` lazily emits deterministic tasks from sorted IDs. Seeds retain the existing SHA-256 encoding of seed version, master seed, sorted pair, repetition and orientation. IDs additionally bind the configuration and execution provenance. Worker count, PID, timestamps, completion order, output directory and retry count cannot affect seeds or match IDs.

The preflight loads the trainer and generation JSON once. Singles require a nonempty party and `double_battle == false`; category alone is insufficient, because some doubles carry rematch categories. Production/validation admission also checks the existing capability policy. Explicit diagnostic benchmarks can run natural unsupported singles, up to 16 entries/128 matches, and cannot be reported as an admitted tournament.

## Durability and recovery

SQLite uses WAL, `synchronous=FULL`, and full-fsync/checkpoint-full-fsync where supported. Each returned result is validated and committed in its own transaction before new tasks are scheduled. The schema records deterministic identity, IDs, orientation, repetition, seed, outcome, frames, turns, task runtime, completion time, worker PID, compact JSON and integrity hashes. Shared provenance is stored once in immutable metadata.

Raw captures are compressed ZIP blobs in the same transaction as their results. This avoids creating millions of permanent per-battle directories. Both the compact record and archive carry SHA-256 digests. The exported archive includes the original result, raw events, party bytes and diagnostics. Temporary working directories may survive a hard kill but are never treated as completed results. The database, not a directory or last-number file, is authoritative.

Resume checks database identity before mutating an existing store, then uses indexed match-ID lookups while lazily scanning the schedule. Completed outcomes, including explicit frame-budget timeouts, are skipped. Failures are append-only records with task identity, exception type/message/traceback and diagnostics; by default they are reported and skipped. `--retry-failed` revisits them. `--retries N` bounds additional attempts per selected task per invocation. There is no infinite automatic retry loop.

Ctrl+C/SIGINT and SIGTERM stop submission, drain the bounded in-flight set, commit returned results, close/checkpoint the database and print a summary. A second Ctrl+C does not discard committed work; use forced termination if waiting is undesirable. Already-running tasks can take their frame budget or bridge watchdog time to finish. After forced termination/reboot, uncommitted tasks rerun with identical seeds, and committed tasks are skipped. The OS releases the run lock on process death. Local filesystem SQLite durability still depends on the underlying storage honoring flushes; do not run the store on a network filesystem or copy only the `.sqlite` file while its WAL is active.

## Portability and configuration

Orchestration explicitly uses `spawn`, guarded entry points and top-level pickleable worker functions. Locks use `msvcrt` on Windows and `fcntl` on Unix. The Windows anonymous-pipe transport has a portable implementation. Actual Windows/Linux execution has not been validated on this Mac; cross-platform support also requires a locally built compatible mGBA bridge and GBA artifacts.

The checked-in configurations describe this Mac's existing backend. On another machine, provide `backend_paths` (`rom`, `elf`, `checkpoint`, `manifest_path`, `bridge`) and `runtime_files` for mGBA and other non-system dynamic libraries, or the static executable. Paths are repository-relative unless absolute. File content hashes, not path strings, define identity. Different binaries/provenance cause a safe resume refusal; moving an identical run directory alone does not. Do not transfer work between different backend builds without a separate equivalence and provenance decision.

Auto uses logical CPU count, caps its conservative starting point at eight workers and approximately half the logical count, and applies a 512 MiB/worker memory budget when available. macOS memory discovery reserves most total RAM; restricted discovery falls back to CPU-based selection. Measured pool RAM is an estimate from worker/native-child high-water RSS, not a simultaneous global measurement. Windows RAM telemetry may be unavailable. Benchmark on the target machine; an 8-core/16-thread Ryzen does not imply 16 workers are best.

## Benchmark interpretation

The default benchmark runs Sidney, Glacia, Drake and Wallace, all with five or six original Pokémon, across all pairs and orientations. Each worker count receives identical tasks and seeds. It measures end-to-end startup, battle execution, validation, compression and durable commit time, plus per-task runtime and approximate memory. It checks exact logical result equality across worker counts and recommends the smallest measured count within 95% of maximum throughput.

Projected time is `1,205,904 / measured battles_per_second`, not ideal core scaling. Twelve fixture matches are a short benchmark and can include timeouts at the configured frame cap. They are a better full-party sample than the first league, but are not a complete runtime distribution for 777 trainers. Increase the benchmark configuration's frame-budget repetitions for a longer comparison, while retaining the diagnostic size cap.

## Validation and legacy compatibility

`tools/validate_parallel_runner.py` exercises actual mGBA battles under spawn: sequential/parallel equivalence, persistent worker PIDs, partial resume, capture export, real invalid-input failure, graceful SIGINT, forced coordinator kill, restart and completed-run no-op. Unit tests cover deterministic IDs/seeds, lazy million-match generation, WAL/durability settings, immutability, duplicates, mismatch protection, locks and bounded failure retries.

The legacy CLI remains `.venv/bin/python -m emerald_tournament.tournament`. Its old schema, exact authorization and artifacts remain intact. New full concurrent execution requires an authorization file whose `plan_id` matches the concurrent preflight and a positive readiness gate; the old release authorization does not silently cover new orchestration or the 777-entry population.

## Measured results on this Mac

The saved benchmark is `docs/evidence/concurrent-runner-v1/concurrent-benchmark-v1/benchmark.json`. The machine reported 11 logical CPUs on macOS ARM64. All five runs produced identical logical results for the same 12 full-party fixtures: ten engine-terminal outcomes and two explicit 36000-frame timeouts.

- 1 worker: 131.86 seconds, 0.091 battles/s, baseline, 153.4-day projection.
- 2 workers: 73.67 seconds, 0.163 battles/s, 1.79× speedup, 85.7-day projection.
- 4 workers: 41.79 seconds, 0.287 battles/s, 3.15× speedup, 48.6-day projection.
- 6 workers: 32.02 seconds, 0.375 battles/s, 4.12× speedup, 37.2-day projection.
- 8 workers: 31.41 seconds, 0.382 battles/s, 4.20× speedup, 36.5-day projection.

Six workers achieved 98.1% of the maximum measured throughput and used approximately 685 MiB of estimated pool peak RSS, versus 912 MiB at eight. Auto remains a conservative starting point of five on this 11-logical-CPU host; use `--workers 6` to apply the measured recommendation. These numbers are not predictions for the Ryzen; benchmark it with its local backend, including 8/10/12/16 workers.

The larger natural teams explain why these projections differ from extrapolating the earlier 3.12-second single-Pokémon league. Each projection is exactly 1,205,904 divided by measured throughput. At six workers, the estimate is about 37.2 days of uninterrupted execution **for this fixture cost distribution and frame cap**, not an unconditional full-tournament forecast. The 12-match sample and two censored battles limit precision.

Compressed captures totaled 1,004,183 bytes per 12-match sample, about 84 kB each. A straight extrapolation is approximately 101 GB of archive payload for 1,205,904 battles, before SQLite overhead and storage headroom. Memory remains bounded by workers/in-flight results rather than total match count.

The one-worker benchmark consumed 131.76 worker/native-child CPU seconds over 131.86 wall seconds: this workload is CPU-bound in aggregate. A separate profiled 26,507-frame battle made 79,704 bridge commands. Bridge creation/restoration took about 8 ms, while `frame()` took 11.47 seconds cumulatively and the whole profiled task took 14.18 seconds. Thus reusing native cores is not presently justified by initialization cost. Python's reply-wait time includes actual native emulation and must not be mistaken for pure IPC overhead. The next targeted experiment would combine step/mailbox/acknowledgment transport while preserving every frame and ring invariant; no such engine/transport change is included here.

## Changed files

- `tournament.py`, `parallel_cli.py`, and the `pyproject.toml` console entry provide the new CLI.
- `parallel_plan.py` and `parallel_tasks.py` handle pinned configuration/admission and lazy deterministic scheduling.
- `parallel_runner.py`, `parallel_worker.py`, and `parallel_platform.py` handle the persistent pool, isolated backend calls, interruption, parent death, portability and worker selection.
- `parallel_store.py` and `parallel_export.py` handle durable immutable storage and capture lookup/export.
- `parallel_benchmark.py` measures actual worker-count comparisons.
- `config/parallel_validation.json`, `parallel_singles.json`, and `parallel_benchmark.json` separate admitted validation, the blocked complete population, and unranked full-party benchmarks.
- `tests/test_parallel_orchestration.py`, `tests/test_parallel_spawn.py`, `tools/validate_parallel_runner.py`, and `tools/profile_parallel_battle.py` provide regression, real-engine crash/recovery and profiling checks.
- README, progress/resume notes, and this document describe operation and measured limits.

The existing `emu_battle.py`, ARM adapter, native bridge, upstream `pokeemerald`, legacy runner/store and released database were not modified. Final regression: **63 passed**, no skips. The legacy completed league still resumes as a no-op.
