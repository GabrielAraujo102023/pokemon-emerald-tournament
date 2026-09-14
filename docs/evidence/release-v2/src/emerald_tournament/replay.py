"""Lookup an immutable match and rerun its one authoritative Emerald instance."""
import argparse,json,sqlite3
from pathlib import Path
from .result_store import rows
from .emu_battle import run_battle
from .admission import sha
ROOT=Path(__file__).resolve().parents[2]
def replay(run_dir,match_prefix,output):
    db=sqlite3.connect(f'file:{run_dir/"results.sqlite"}?mode=ro',uri=True)
    try:
        matches=[x for x in rows(db) if x['match_id'].startswith(match_prefix)]
        if len(matches)!=1:raise ValueError('Replay identity must resolve to exactly one stored match')
        selected=matches[0];pinned=json.loads(db.execute('SELECT preflight FROM metadata').fetchone()[0])
    finally:db.close()
    for p in ('src/emerald_tournament/emu_battle.py','src/emerald_tournament/emu_protocol.py'):
        if sha(ROOT/p)!=pinned['source_hashes'][p]:raise ValueError('Replay execution source differs from pinned run')
    for path,expected in pinned.get('runtime_hashes',{}).items():
        if sha(ROOT/path)!=expected:raise ValueError('Replay runtime library/compiler provenance changed')
    record=selected['record'];build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports'
    if json.loads((reports/'battle-manifest.json').read_text())!=record['provenance']:raise ValueError('Restore the pinned executable/checkpoint manifest before replay')
    actual=run_battle(**{k:record[k] for k in ('trainer_a','trainer_b','seed','max_frames')},rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=reports/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=output,observe_engine=True)
    original=run_dir/selected['artifact']
    names=['events.bin','initial_parties.bin','stopped_parties.bin']+(['final_parties.bin'] if record['terminal_from_engine'] else [])
    checks={name:(output/name).read_bytes()==(original/name).read_bytes() for name in names}
    report=dict(match_id=selected['match_id'],passed=actual==record and all(checks.values()),compact_result_equal=actual==record,byte_comparisons=checks)
    (output/'replay_validation.json').write_text(json.dumps(report,indent=2)+'\n')
    if not report['passed']:raise ValueError('Replay diverged from immutable original; evidence retained')
    return report

def main():
    p=argparse.ArgumentParser();p.add_argument('--run',type=Path,required=True);p.add_argument('--match',required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
    print(json.dumps(replay(a.run.resolve(),a.match,a.output.resolve()),indent=2))
if __name__=='__main__':main()
