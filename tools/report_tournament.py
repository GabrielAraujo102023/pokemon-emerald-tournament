"""Derive a complete, provenance-bound report from immutable engine results."""
import argparse,html,json,math,sqlite3,statistics,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.result_store import rows
from emerald_tournament.ranking import standings
ROOT=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);a=p.parse_args();run=a.run.resolve()
db=sqlite3.connect(f'file:{run/"results.sqlite"}?mode=ro',uri=True)
records=rows(db);preflight=json.loads(db.execute('SELECT preflight FROM metadata').fetchone()[0]);failures=db.execute('SELECT count(*) FROM failures').fetchone()[0];db.close()
assert len(records)==preflight['expected_battles'] and {r['match_id'] for r in records}=={m['match_id'] for m in preflight['schedule']},'Report requires complete schedule'
population=json.loads((ROOT/preflight['config']['population_manifest']).read_text())
people={t['id']:t for t in population['entries'] if t['supported']}
levels={i:statistics.mean(m['level'] for m in t['party']) for i,t in people.items()}
ranked=standings(records,preflight['supported_ids'],preflight['ranking'])
elo={i:float(preflight['ranking']['initial_elo']) for i in people};changes={i:[] for i in people};upsets=[];lower_wins=[];matchups={};groups={i:{k:[0,0] for k in ('lower','equal','higher')} for i in people}
for entry in records:
 r=entry['record'];x,y=r['trainer_a'],r['trainer_b'];key=tuple(sorted((x,y)))
 pair=matchups.setdefault(key,dict(trainer_a=key[0],trainer_b=key[1],a_wins=0,b_wins=0,draws=0,timeouts=0,turns=[],match_ids=[]))
 pair['turns'].append(r['turns']);pair['match_ids'].append(entry['match_id'])
 if r['outcome']=='timeout':pair['timeouts']+=1;continue
 expected=1/(1+10**((elo[y]-elo[x])/400))
 score={'a_win':1,'b_win':0,'draw':.5}[r['outcome']]
 if r['outcome']=='draw':pair['draws']+=1
 else:
  winner,loser=(x,y) if score else (y,x)
  pair['a_wins' if winner==key[0] else 'b_wins']+=1
  probability=expected if winner==x else 1-expected
  item=dict(match_id=entry['match_id'],winner=winner,loser=loser,seed=r['seed'],turns=r['turns'],winner_level=levels[winner],loser_level=levels[loser],prematch_win_probability=probability)
  if probability<.5:upsets.append(item)
  if levels[winner]<levels[loser]:lower_wins.append(item)
 for own,other,won in [(x,y,score==1),(y,x,score==0)]:
  group='higher' if levels[other]>levels[own] else 'lower' if levels[other]<levels[own] else 'equal'
  groups[own][group][0]+=int(won);groups[own][group][1]+=1
 change=preflight['ranking']['k']*(score-expected);elo[x]+=change;elo[y]-=change;changes[x].append(change);changes[y].append(-change)
for pair in matchups.values():pair['mean_turns']=statistics.mean(pair.pop('turns'))
for r in ranked:
 i=r['trainer_id'];r.update(constant=people[i]['constant'],level=levels[i],elo_change_sd=statistics.pstdev(changes[i]) if changes[i] else 0,level_strata={g:dict(wins=w,games=n,win_rate=w/n if n else None) for g,(w,n) in groups[i].items()})
 rates=[]
 for pair in matchups.values():
  if i not in (pair['trainer_a'],pair['trainer_b']):continue
  n=pair['a_wins']+pair['b_wins']+pair['draws']
  if n:rates.append(pair['a_wins' if i==pair['trainer_a'] else 'b_wins']/n)
 r['matchup_win_rate_spread']=max(rates)-min(rates) if rates else None
 r['matchup_win_rate_sd']=statistics.pstdev(rates) if rates else None
 assert abs(r['elo']-elo[i])<1e-8
counts={k:sum(x['record']['outcome']==k for x in records) for k in ('a_win','b_win','draw','timeout')}
analysis=dict(run_id=preflight['run_id'],scope='Eight covered singles entries out of 855; not all-Emerald rankings',counts=counts,failed_attempts=failures,standings=ranked,matchups=list(matchups.values()),upsets=sorted(upsets,key=lambda r:r['prematch_win_probability']),lower_level_wins=sorted(lower_wins,key=lambda r:(r['winner_level']-r['loser_level'],r['prematch_win_probability'])),normalization='Descriptive win-rate strata against equal/higher/lower-level opponents; no simulated level changes or causal adjustment',preflight=preflight)
(run/'analysis.json').write_text(json.dumps(analysis,indent=2)+'\n')
def name(i):return people[i]['constant'].removeprefix('TRAINER_').replace('_',' ').title()+f' ({i})'
def esc(x):return html.escape(str(x))
def table(head,body):return '<div class="scroll"><table><thead><tr>'+''.join('<th>'+esc(x)+'</th>' for x in head)+'</tr></thead><tbody>'+''.join('<tr>'+''.join('<td>'+esc(x)+'</td>' for x in row)+'</tr>' for row in body)+'</tbody></table></div>'
def pct(x):return '—' if x is None else f'{x:.1%}'
parts=['<!doctype html><html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Emerald — covered singles results</title><style>body{font:15px/1.55 system-ui,sans-serif;margin:0;background:#f4f5f0;color:#172c28}main{max-width:1180px;margin:auto;padding:40px 28px}h1{font-size:30px;letter-spacing:-1px;margin:8px 0}h2{font-size:21px;margin-top:40px}p{max-width:900px}small,.muted{color:#54665f}.scope{padding:16px 20px;border-left:4px solid #237455;background:#e3eee6}.stats{display:flex;gap:36px;flex-wrap:wrap;margin:28px 0}.stats strong{display:block;font-size:26px}.scroll{overflow:auto}table{border-collapse:collapse;width:100%;font-variant-numeric:tabular-nums;background:white}th,td{padding:10px 12px;border-bottom:1px solid #d7dfd8;text-align:left;white-space:nowrap}th{font-size:12px;text-transform:uppercase;letter-spacing:.04em}tbody tr:hover{background:#e9f1eb}code{overflow-wrap:anywhere;font-size:12px}details{margin:20px 0}summary{cursor:pointer}a{color:#166247}input{padding:10px;font:inherit;border:1px solid #9cad9f;width:300px;max-width:90%}</style></head><body><main>']
parts += ['<small>POKÉMON EMERALD · REAL ARM ENGINE · COMPLETE CONFIGURED LEAGUE</small><h1>Covered singles tournament</h1><p class="scope">Eight qualified trainer entries. All 855 source entries were evaluated; 847 are explicitly excluded by the current mechanics policy. These results do not identify the strongest trainer across all Emerald.</p>',f'<div class="stats"><div><strong>{len(records)}</strong>engine runs</div><div><strong>{len(matchups)}</strong>unique pairings</div><div><strong>{counts["timeout"]}</strong>censored timeouts</div><div><strong>{failures}</strong>failed attempts</div></div>', '<p>Two seeds per pair, both orientations; 36,000 frames per battle. Source teams and levels are unchanged. Timeouts are excluded from W/L/D, win rates and Elo. Elo starts at 1500 with K = 32 in pinned schedule order.</p><h2>Standings</h2>']
parts += [table(['Trainer entry','Level','Elo','W','L','D','Timeout','Games','Win rate'],[[name(r['trainer_id']),r['level'],f"{r['elo']:.1f}",r['wins'],r['losses'],r['draws'],r['timeouts'],r['games_played'],pct(r['win_rate'])] for r in ranked])]
parts += ['<h2>Level-stratified outcomes</h2><p>Rates are grouped by actual opponent level. This is a descriptive comparison, not a causal estimate or a level-normalized battle simulation. A dash means there were no completed games in that stratum.</p>',table(['Trainer','Vs lower level','Vs equal level','Vs higher level','Elo-change SD','Matchup rate spread'],[[name(r['trainer_id'])]+[pct(r['level_strata'][g]['win_rate'])+f" ({r['level_strata'][g]['games']} games)" for g in ('lower','equal','higher')]+[f"{r['elo_change_sd']:.2f}",pct(r['matchup_win_rate_spread'])] for r in ranked])]
parts += ['<h2>Matchups</h2><p>Four games scheduled per unordered pair. A and B below refer to the displayed trainer entries, not controller orientation. Mean turns includes censored runs and is descriptive.</p><input id="filter" placeholder="Filter matchup by trainer or ID" aria-label="Filter matchups"><div id="matchups">',table(['Entry A','Entry B','A wins','B wins','Draws','Timeouts','Mean turns'],[[name(r['trainer_a']),name(r['trainer_b']),r['a_wins'],r['b_wins'],r['draws'],r['timeouts'],f"{r['mean_turns']:.1f}"] for r in matchups.values()]),'</div>']
if upsets:parts += ['<h2>Largest Elo upsets</h2><p>Sorted by the winner’s lowest pre-match Elo expectation. Expectations are model scores, not calibrated probabilities.</p>',table(['Winner','Loser','Pre-match expectation','Seed','Match lookup'],[[name(r['winner']),name(r['loser']),pct(r['prematch_win_probability']),r['seed'],r['match_id'][:16]] for r in analysis['upsets'][:10]])]
if lower_wins:parts += ['<h2>Lower-level wins</h2>',table(['Winner','Level','Loser','Level','Seed','Match lookup'],[[name(r['winner']),r['winner_level'],name(r['loser']),r['loser_level'],r['seed'],r['match_id'][:16]] for r in analysis['lower_level_wins'][:10]])]
parts += ['<h2>Provenance & replay</h2><p>Source: this run’s immutable <a href="results.sqlite">SQLite ledger</a>, <a href="preflight.json">preflight</a> and <a href="analysis.json">complete derived analysis</a>. All matches use the exact pinned ROM, checkpoint, runtime and source hashes.</p><p>Run ID: <code>'+esc(preflight['run_id'])+'</code></p><p>Replay from the project directory:</p><code>.venv/bin/python -m emerald_tournament.replay --run '+esc(str(run.relative_to(ROOT)))+' --match MATCH_ID --output build/reports/replay-new</code><details><summary>Exact executable provenance</summary><pre>'+esc(json.dumps(preflight['provenance'],indent=2))+'</pre></details><script>document.getElementById("filter").addEventListener("input",e=>{let q=e.target.value.toLowerCase();document.querySelectorAll("#matchups tbody tr").forEach(r=>r.hidden=!r.textContent.toLowerCase().includes(q))})</script></main></body></html>']
(run/'report.html').write_text(''.join(parts))
strong=ranked[0];weak=ranked[-1];volatile=max(ranked,key=lambda r:r['elo_change_sd']);spread=max(ranked,key=lambda r:r['matchup_win_rate_sd'])
md=f'''# Configured Emerald singles tournament — completed

The evidence-authorized eight-entry league completed all {len(records)} battles: {counts['a_win']+counts['b_win']} wins/losses, {counts['draw']} natural draws and {counts['timeout']} censored timeouts; {failures} failed attempts. This is the covered subset of 855 extracted entries, not a ranking of all Emerald trainers. The other 847 entries retain explicit exclusions in the population manifest.

[Open the full standings, W/L/D/timeout table, matchup table, upsets and level-stratified analysis]({run/'report.html'}). [All derived data]({run/'analysis.json'}), [immutable raw results]({run/'results.sqlite'}), [exact preflight]({run/'preflight.json'}).

Final Elo ranks **{name(strong['trainer_id'])}** highest ({strong['elo']:.1f}; {strong['wins']}–{strong['losses']}–{strong['draws']}) and **{name(weak['trainer_id'])}** lowest ({weak['elo']:.1f}; {weak['wins']}–{weak['losses']}–{weak['draws']}). These conclusions apply only to the admitted population and actual source levels.

The largest per-game Elo-change standard deviation belongs to {name(volatile['trainer_id'])} ({volatile['elo_change_sd']:.2f}). The widest matchup variation by win-rate standard deviation belongs to {name(spread['trainer_id'])} ({spread['matchup_win_rate_sd']:.3f}). The HTML report lists individual low-expectation upsets and lower-level wins with their exact replay identities. These descriptive outliers are not evidence of engine errors or calibrated predictions.

Level analysis groups completed games against lower-, equal- and higher-level opponents. It does not change team levels or claim a causal level adjustment. Timeouts remain separate and never contribute to W/L/D, win-rate denominators or Elo. Both orientations and two deterministic seeds are present for every unordered pair. Elo starts at 1500, K=32, in sorted pair/repetition/orientation order.

Run identity: `{preflight['run_id']}`. Source commit: `{preflight['provenance']['pokeemerald_commit']}`. All executable, checkpoint, adapter, host and runtime hashes are in the preflight. Release authorization: [authorization.json]({ROOT/'docs/evidence/release-v2/authorization.json'}).

Replay any listed match, retaining the pinned artifacts and using a fresh output directory:

```sh
.venv/bin/python -m emerald_tournament.replay --run {run.relative_to(ROOT)} --match MATCH_ID --output build/reports/replay-new
```

Resume verification (a complete run executes zero additional battles):

```sh
.venv/bin/python -m emerald_tournament.tournament --config config/tournament_singles.yaml --output {run.relative_to(ROOT)}
```
'''
md += '\nFinal validation evidence: `docs/evidence/completed-league-v2/` contains the regression log, all-capture completion audit, no-op resume and selected detailed replay. Broader trainer coverage remains outside this authorization.\n'
(ROOT/'docs/final_tournament_report.md').write_text(md)
print(json.dumps({'complete':True,'counts':counts,'highest_elo':name(strong['trainer_id']),'lowest_elo':name(weak['trainer_id']),'report':str(run/'report.html')}))
