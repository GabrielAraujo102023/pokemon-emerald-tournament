# Current state

Concurrent orchestration is implemented and validated. Read `concurrent_runner.md` for commands, architecture, benchmark results and file list. Final regressions: 63 passed. Real spawn/SIGINT/kill/resume checks passed; five worker counts produced identical full-party benchmark results.

```sh
.venv/bin/python tournament.py run --workers 6 --output runs/concurrent-validation
.venv/bin/python tournament.py status --output runs/concurrent-validation
```

The same run command resumes automatically. The measured recommendation is six workers on this Mac; benchmark the Ryzen separately after configuring its backend/runtime paths. Evidence: `evidence/concurrent-runner-v1/`.

The original authorized eight-entry league remains complete and unchanged. The 777-singles schedule contains 1,205,904 logical matches, but 769 singles still lack mechanics admission. Do not expand authorization or bypass this gate merely because concurrency is available. Existing evidence and upstream must remain intact.
