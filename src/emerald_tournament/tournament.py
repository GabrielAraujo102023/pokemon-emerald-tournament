"""Resumable, fail-closed single-core Emerald tournament execution."""
import argparse,fcntl,itertools,json,uuid
from pathlib import Path
from .admission import build_population,check_runtime,sha
from .emu_battle import run_battle,check_manifest
from .result_store import connect,identity,canonical,append_result,rows
from .ranking import standings
import platform
ROOT=Path(__file__).resolve().parents[2]

def preflight(config_path):
    config=json.loads(config_path.read_text())
    population=json.loads((ROOT/config['population_manifest']).read_text())
    if population!=build_population(ROOT):raise ValueError('Stale population manifest; re-audit inputs')
    ids=population['supported_ids']
    if len(set(ids))!=len(ids) or len(ids)<2:raise ValueError('Invalid admitted population')
    if config['mode']=='smoke':
        if not 8<=len(ids)<=16 or config['pairing']!='ring':raise ValueError('Smoke must be a bounded 8–16 trainer ring')
    elif config['mode']=='full':
        if 'Tournament authorized: yes' not in (ROOT/'docs/tournament_readiness_gate.md').read_text().splitlines():raise ValueError('Full tournament not authorized')
        if config['pairing']!='all_pairs':raise ValueError('Full run must use all admitted pairs')
        authorization=json.loads((ROOT/'docs/evidence/release-v2/authorization.json').read_text())
        if not config.get('tournament_authorized') or authorization['config_sha256']!=sha(config_path) or authorization['population_sha256']!=sha(ROOT/config['population_manifest']):raise ValueError('Configuration not authorized by release audit')
    else:raise ValueError('Unknown run mode')
    if config['seed_version']!='sha256-canonical-pair-repetition-orientation-v1':raise ValueError('Unknown seed derivation')
    if config['repetitions']!=len(config['max_frames_by_repetition']) or any(not isinstance(x,int) or x<1 for x in config['max_frames_by_repetition']):raise ValueError('Invalid frame budgets')
    build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports'
    inputs=dict(rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=reports/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge')
    manifest=json.loads(inputs['manifest_path'].read_text());check_manifest(manifest,**{k:v for k,v in inputs.items() if k!='manifest_path'})
    ranking=json.loads((ROOT/config['ranking_config']).read_text())
    pinned=['src/emerald_tournament/emu_battle.py','src/emerald_tournament/emu_protocol.py','src/emerald_tournament/admission.py','src/emerald_tournament/teams.py','src/emerald_tournament/tournament.py','src/emerald_tournament/result_store.py','src/emerald_tournament/ranking.py','src/emerald_tournament/replay.py','adapter/tournament_adapter.c','adapter/tournament_protocol.h','adapter/tournament_battle.h','tools/apply_battle_adapter.py','tools/apply_constructor_adapter.py']
    runtime_paths=['build/mgba-prefix/lib/libmgba.0.10.5.dylib','/opt/homebrew/opt/libpng/lib/libpng16.16.dylib','/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc']
    runtime_hashes={p:sha(ROOT/p) for p in runtime_paths}
    base=dict(runtime_hashes=runtime_hashes,host_platform=platform.platform(),config=config,population_sha256=sha(ROOT/config['population_manifest']),supported_ids=ids,provenance=manifest,source_hashes={p:sha(ROOT/p) for p in pinned},ranking=ranking)
    if config['mode']=='full' and authorization['execution_identity']!=identity({k:v for k,v in base.items() if k not in ('config','population_sha256')}):raise ValueError('Release execution artifacts changed')
    run_id=identity(base)
    pairs=list(itertools.combinations(ids,2)) if config['pairing']=='all_pairs' else sorted({tuple(sorted((a,ids[(i+1)%len(ids)]))) for i,a in enumerate(ids)})
    schedule=[]
    for a,b in pairs:
        for repetition in range(config['repetitions']):
            for orientation in (0,1):
                seed=int(identity([config['seed_version'],config['master_seed'],a,b,repetition,orientation])[:8],16)
                x=dict(ordinal=len(schedule),trainer_a=b if orientation else a,trainer_b=a if orientation else b,repetition=repetition,orientation=orientation,seed=seed,max_frames=config['max_frames_by_repetition'][repetition])
                x['match_id']=identity([run_id,x]);schedule.append(x)
    return dict(**base,run_id=run_id,unique_pairs=len(pairs),expected_battles=len(schedule),schedule=schedule),inputs,population

def verify_capture(folder,match,report,population):
    result=check_runtime(folder,population['policy'])
    if result['provenance']!=report['provenance'] or result['max_frames']!=match['max_frames']:raise ValueError('Capture provenance/frame-budget mismatch')
    for filename,key in [('events.bin','trace_sha256'),('initial_parties.bin','initial_party_sha256'),('stopped_parties.bin','stopped_party_sha256')]:
        if sha(folder/filename)!=result[key]:raise ValueError('Capture digest mismatch: '+filename)
    entries={t['id']:t for t in population['entries']}
    for side in 'ab':
        expected=entries[match['trainer_'+side]]
        if not expected['supported']:raise ValueError('Unsupported trainer')
        actual=json.loads((folder/f'party_{side}.json').read_text())
        if len(actual)!=len(expected['party']):raise ValueError('Source/ARM party size mismatch')
        for a,b in zip(actual,expected['party']):
            if (a['species'],a['level'],a['ability'],a['personality'])!=(b['species_id'],b['level'],b['ability_id'],b['personality']):raise ValueError('Source/ARM admission-field mismatch')
    return result

def run(config_path,output,limit=None):
    report,inputs,population=preflight(config_path)
    output.mkdir(parents=True,exist_ok=True)
    with (output/'runner.lock').open('a') as lock:
        fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
        pf=output/'preflight.json'
        if pf.exists() and json.loads(pf.read_text())!=report:raise ValueError('Preflight changed; refusing resume')
        if not pf.exists():pf.write_text(json.dumps(report,indent=2)+'\n')
        db=connect(output/'results.sqlite',report)
        try:
            done={x['match_id'] for x in rows(db)};completed_now=0
            for match in report['schedule']:
                if match['match_id'] in done:continue
                if limit is not None and completed_now>=limit:break
                attempt=uuid.uuid4().hex;folder=output/'battles'/f'{match["ordinal"]:05d}-{attempt}'
                try:
                    run_battle(**{k:match[k] for k in ('trainer_a','trainer_b','seed','max_frames')},**inputs,output=folder)
                    result=verify_capture(folder,match,report,population)
                    append_result(db,match,result,folder.relative_to(output))
                    print(f'{match["ordinal"]+1}/{report["expected_battles"]} {match["trainer_a"]} vs {match["trainer_b"]}: {result["outcome"]}',flush=True)
                except Exception as e:
                    with db:db.execute('INSERT INTO failures VALUES (?,?,?,?)',(attempt,match['match_id'],str(e),str(folder.relative_to(output))))
                    raise
                completed_now+=1
            records=rows(db)
            # Derived view may be regenerated; raw SQLite records never change.
            (output/'standings.json').write_text(json.dumps(standings(records,report['supported_ids'],report['ranking']),indent=2)+'\n')
            summary=dict(run_id=report['run_id'],completed=len(records),expected=report['expected_battles'],newly_completed=completed_now,complete=len(records)==report['expected_battles'])
            print(json.dumps(summary));return summary
        finally:db.close()

def main():
    p=argparse.ArgumentParser();p.add_argument('--config',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--limit',type=int);args=p.parse_args()
    if args.limit is not None and args.limit<0:p.error('limit must be nonnegative')
    run(args.config.resolve(),args.output.resolve(),args.limit)
if __name__=='__main__':main()
