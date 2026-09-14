# Ranking from immutable engine outcomes

SQLite retains each raw result and its hash under a unique match identity. Standings are regenerable views: changing a rating never edits raw results. `config/ranking.yaml` pins initial Elo 1500, K 32, draw score 0.5 and schedule-ordinal order (sorted unordered pair, repetition, orientation). Both ratings update from their pre-match values. Query order does not change Elo; schedule order does.

Wins, losses and natural engine draws count as games played. Win rate is wins divided by those games. Timeouts have a separate counter and are excluded from games played, win rate and Elo. Attempts include timeouts. Failed/overflowed runs never enter rankings. No draw has been observed in the smoke evidence; draw arithmetic is implemented but no natural-draw coverage is claimed.

The first supported league contains eight narrowly admitted trainer entries. Its rankings describe that population only, with actual source levels, and cannot identify Emerald's strongest trainer overall. Later analyses must retain raw outcomes, configuration, schedule and artifact provenance. No level-normalized battle engine is used.
