"""Small actual-engine probe. Stops at the first unsuccessful battle."""
from pathlib import Path
import argparse,json,sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
ROOT=Path(__file__).resolve().parents[1]
def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--output',type=Path,default=ROOT/'build/reports')
    args=parser.parse_args()
    reports=ROOT/'build/reports';build=ROOT/'build/pokeemerald'
    output=args.output;output.mkdir(parents=True,exist_ok=True)
    evidence=json.loads((reports/'constructor-validation.json').read_text())
    manifest={k:evidence[k] for k in ['rom_sha256','elf_sha256','checkpoint_sha256','bridge_sha256','rules_version']}
    manifest.update(abi_version=2,compiler_version=evidence['compiler'],emulator_version=evidence['emulator'],adapter_version=evidence['adapter_sha256'],pokeemerald_commit=json.loads((reports/'build-modern.json').read_text())['source_commit'],checkpoint_entry='TournamentReady after normal new-game initialization',validation_evidence='build/reports/constructor-validation.json; construction only')
    path=reports/'battle-manifest.json';path.write_text(json.dumps(manifest,indent=2)+'\n')
    results=[]
    for name,seed in [('battle-entry-a',12345),('battle-entry-b',12345),('battle-entry-c',12346)]:
        result=run_battle(trainer_a=1,trainer_b=335,seed=seed,rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=path,bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=output/name,max_frames=12000)
        results.append(result)
        print(name,result['outcome'],result['terminal_from_engine'],result['frames'],flush=True)
        if not result['terminal_from_engine']: break
    checks={}
    if len(results)==3:
        a,b,c=results
        checks['same_seed_result_equal']=a==b
        for filename in ['initial_parties.bin','final_parties.bin','events.bin','party_a.json','party_b.json']:
            checks['same_seed_'+filename]=(output/'battle-entry-a'/filename).read_bytes()==(output/'battle-entry-b'/filename).read_bytes()
        checks['different_seed_trace_differs']=a['trace_sha256']!=c['trace_sha256']
        checks['different_seed_final_rng_differs']=a['rng_final']!=c['rng_final']
        checks['all_terminal']=all(r['terminal_from_engine'] for r in results)
        for name in ['battle-entry-a','battle-entry-b','battle-entry-c']:
            events=[json.loads(line) for line in (output/name/'events.jsonl').read_text().splitlines()]
            checks[name+'_both_ai']={e['battler'] for e in events if e['event']=='move_selected'}=={0,1}
    (output/'battle-entry-validation.json').write_text(json.dumps(dict(results=results,checks=checks),indent=2)+'\n')
    assert checks and all(checks.values()), checks
if __name__=='__main__':main()
