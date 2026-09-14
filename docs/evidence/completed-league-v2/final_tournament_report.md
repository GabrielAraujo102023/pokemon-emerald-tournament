# Configured Emerald singles tournament — completed

The evidence-authorized eight-entry league completed all 112 battles: 112 wins/losses, 0 natural draws and 0 censored timeouts; 0 failed attempts. This is the covered subset of 855 extracted entries, not a ranking of all Emerald trainers. The other 847 entries retain explicit exclusions in the population manifest.

[Open the full standings, W/L/D/timeout table, matchup table, upsets and level-stratified analysis](/Users/gaby/Desktop/the box/pokemon-tournament/runs/covered-normal-singles-v2/report.html). [All derived data](/Users/gaby/Desktop/the box/pokemon-tournament/runs/covered-normal-singles-v2/analysis.json), [immutable raw results](/Users/gaby/Desktop/the box/pokemon-tournament/runs/covered-normal-singles-v2/results.sqlite), [exact preflight](/Users/gaby/Desktop/the box/pokemon-tournament/runs/covered-normal-singles-v2/preflight.json).

Final Elo ranks **Josh (320)** highest (1731.5; 28–0–0) and **Brendan Route 103 Treecko (523)** lowest (1330.5; 6–22–0). These conclusions apply only to the admitted population and actual source levels.

The largest per-game Elo-change standard deviation belongs to Winston 1 (136) (13.28). The widest matchup variation by win-rate standard deviation belongs to Janice (605) (0.394). The HTML report lists individual low-expectation upsets and lower-level wins with their exact replay identities. These descriptive outliers are not evidence of engine errors or calibrated predictions.

Level analysis groups completed games against lower-, equal- and higher-level opponents. It does not change team levels or claim a causal level adjustment. Timeouts remain separate and never contribute to W/L/D, win-rate denominators or Elo. Both orientations and two deterministic seeds are present for every unordered pair. Elo starts at 1500, K=32, in sorted pair/repetition/orientation order.

Run identity: `0e7465d80c315d77e94520866cd6b25828806f343540e7b0a04d063bfd408ba5`. Source commit: `5eff78649e7170a877b961ef0b3da13b81a16038`. All executable, checkpoint, adapter, host and runtime hashes are in the preflight. Release authorization: [authorization.json](/Users/gaby/Desktop/the box/pokemon-tournament/docs/evidence/release-v2/authorization.json).

Replay any listed match, retaining the pinned artifacts and using a fresh output directory:

```sh
.venv/bin/python -m emerald_tournament.replay --run runs/covered-normal-singles-v2 --match MATCH_ID --output build/reports/replay-new
```

Resume verification (a complete run executes zero additional battles):

```sh
.venv/bin/python -m emerald_tournament.tournament --config config/tournament_singles.yaml --output runs/covered-normal-singles-v2
```

Final validation: **56 tests passed**, no skips. Every one of 112 captures passed the completion audit, the completed resume executed zero additional battles, and a detailed replay of a lower-level win matched all original result/event/party bytes. Evidence: `docs/evidence/completed-league-v2/`. No blocker remains for the configured league; broader trainer coverage remains explicitly outside this authorization.
