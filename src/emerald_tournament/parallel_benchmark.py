"""Measure actual throughput and deterministic equivalence across worker counts."""
import json,sqlite3
from .parallel_plan import prepare
from .parallel_platform import hardware
from .parallel_runner import run

def logical_hashes(path):
    db=sqlite3.connect(path)
    try:return list(db.execute('SELECT match_id,record_sha256 FROM results ORDER BY ordinal'))
    finally:db.close()

def benchmark(config,output,counts=None):
    plan,context=prepare(config)
    if plan['mode']!='benchmark':raise ValueError('Use an explicit unranked benchmark fixture configuration')
    hw=hardware()
    if counts is None:counts=sorted({1,min(4,hw['logical_cpus']),min(8,hw['logical_cpus']),hw['auto_workers']})
    if not counts or any(n<1 for n in counts) or len(set(counts))!=len(counts):raise ValueError('Invalid benchmark worker counts')
    if 1 not in counts:raise ValueError('Include one worker for the sequential baseline')
    counts=sorted(counts);output.mkdir(parents=True,exist_ok=False)
    samples=[];baseline=None
    try:
        for n in counts:
            directory=output/f'workers-{n}'
            sample=run(plan,context,directory,workers=n,new=True)
            hashes=logical_hashes(directory/'results.sqlite')
            if baseline is None:baseline=hashes
            sample['logical_results_equal']=hashes==baseline
            samples.append(sample)
            (output/'partial-benchmark.json').write_text(json.dumps(samples,indent=2)+'\n')
            if not sample['complete'] or not sample['logical_results_equal']:raise RuntimeError('Incomplete or divergent benchmark; retained database and evidence')
        fastest=max(x['battles_per_second'] for x in samples)
        recommended=min(x['workers'] for x in samples if x['battles_per_second']>=fastest*.95)
        base=samples[0]['battles_per_second']
        for x in samples:
            x['speedup']=x['battles_per_second']/base
            x['projected_1205904_days']=1205904/x['battles_per_second']/86400
        report=dict(passed=True,hardware=hw,fixture_plan=plan,samples=samples,recommended_workers=recommended,
                    recommendation_rule='smallest measured count reaching 95% of maximum throughput',
                    limitations='Unranked natural fixtures, not all 777 trainers. Includes spawn, bridge startup, verification, compression and durable commits. RAM is a peak estimate; source/OS/CPU differences require a fresh benchmark.')
        (output/'benchmark.json').write_text(json.dumps(report,indent=2)+'\n')
        print('\nWorkers | Battles | Seconds | Battles/s | Mean task s | Speedup | Approx pool MiB | 1,205,904 days')
        for x in samples:
            mem=f"{x['approx_peak_pool_bytes']/1024**2:.0f}" if x['approx_peak_pool_bytes'] else 'unavailable'
            print(f"{x['workers']:7} | {x['completed']:7} | {x['elapsed_seconds']:7.2f} | {x['battles_per_second']:9.3f} | {x['mean_battle_runtime_seconds']:11.2f} | {x['speedup']:7.2f} | {mem:15} | {x['projected_1205904_days']:.1f}")
        print(f'Recommended measured worker count: {recommended}')
        return report
    except BaseException:
        (output/'interrupted-benchmark.json').write_text(json.dumps({'completed_samples':samples},indent=2)+'\n')
        raise
