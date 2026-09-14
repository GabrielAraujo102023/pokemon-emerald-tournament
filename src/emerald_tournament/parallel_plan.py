"""Validate configuration once, pin semantic inputs, and keep host paths out of IDs."""
import json
from pathlib import Path
from .admission import build_population,sha
from .emu_battle import check_manifest
from .result_store import identity
from .parallel_tasks import SEED_VERSION,count_tasks
ROOT=Path(__file__).resolve().parents[2]

def prepare(config_path, *, enforce=True):
    cfg=json.loads(Path(config_path).read_text())
    if cfg.get('version')!=1:raise ValueError('Unsupported parallel configuration version')
    source=json.loads((ROOT/'data/generated/trainers.json').read_text())
    population=build_population(ROOT)
    singles={t['id']:t for t in source['trainers'] if t['party'] and not t['double_battle']}
    admitted=set(population['supported_ids'])
    scope=cfg.get('scope','admitted_singles')
    if scope=='all_singles':ids=sorted(singles)
    elif scope=='admitted_singles':ids=sorted(admitted)
    elif scope=='fixture':ids=sorted(cfg['trainer_ids'])
    else:raise ValueError('Unknown population scope')
    if len(set(ids))!=len(ids) or len(ids)<2 or any(i not in singles for i in ids):raise ValueError('Population contains doubles, empty, duplicate or unknown trainers')
    budgets=cfg.get('frame_budgets',[36000,36000])
    if not budgets or any(type(v)!=int or not 1<=v<=1000000 for v in budgets):raise ValueError('Invalid frame budgets')
    if cfg.get('pairing') not in ('ring','all_pairs'):raise ValueError('Invalid pairing rule')
    if type(cfg.get('master_seed'))!=int:raise ValueError('master_seed must be an integer')
    total=count_tasks(ids,cfg['pairing'],len(budgets))
    mode=cfg.get('mode');unsupported=sorted(set(ids)-admitted)
    if mode not in ('validation','benchmark','tournament'):raise ValueError('Unknown execution mode')
    if mode in ('validation','benchmark') and (len(ids)>16 or total>128):raise ValueError('Validation/benchmark must be bounded to 16 trainers and 128 battles')
    if mode!='benchmark' and unsupported and enforce:
        raise ValueError(f'{len(unsupported)} singles entries lack mechanics admission; no tournament execution authorized. Use plan to inspect the 777-entry schedule.')
    if mode=='benchmark' and scope!='fixture':raise ValueError('Benchmarks require an explicit unranked fixture population')
    defaults=dict(rom='build/pokeemerald/pokeemerald_modern.gba',elf='build/pokeemerald/pokeemerald_modern.elf',
                  checkpoint='build/reports/constructor-ready.ss',manifest_path='build/reports/battle-manifest.json',
                  bridge='build/emulator/emerald-mgba-bridge')
    defaults.update(cfg.get('backend_paths',{}))
    if set(defaults)!={'rom','elf','checkpoint','manifest_path','bridge'}:raise ValueError('Unknown backend path key')
    paths={k:(ROOT/v).resolve() for k,v in defaults.items()}
    manifest=json.loads(paths['manifest_path'].read_text())
    check_manifest(manifest,**{k:v for k,v in paths.items() if k!='manifest_path'})
    runtime={k:(ROOT/v).resolve() for k,v in cfg.get('runtime_files',{}).items()}
    if not runtime:raise ValueError('Pin runtime_files (mGBA and non-system dynamic dependencies, or static binary)')
    execution_files=['emu_battle.py','emu_protocol.py','admission.py','teams.py','parallel_worker.py','parallel_tasks.py','parallel_store.py','parallel_plan.py','parallel_runner.py']
    semantic=dict(schema_version=1,mode=mode,scope=scope,trainer_ids=ids,pairing=cfg['pairing'],master_seed=cfg['master_seed'],
                  seed_version=SEED_VERSION,frame_budgets=budgets,total_battles=total,
                  unsupported_ids=unsupported,admission_policy=population['policy'],
                  trainer_data_sha256=sha(ROOT/'data/generated/trainers.json'),generation_sha256=sha(ROOT/'data/generated/generation.json'),
                  provenance=manifest,runtime_hashes={k:sha(v) for k,v in runtime.items()},
                  execution_hashes={n:sha(ROOT/'src/emerald_tournament'/n) for n in execution_files},
                  archive_format='zip-deflate-v1',classification='unranked diagnostic fixtures' if mode=='benchmark' else 'admitted singles')
    semantic['plan_id']=identity(semantic)
    if mode=='tournament' and enforce:
        gate=(ROOT/'docs/tournament_readiness_gate.md').read_text().splitlines()
        auth_path=cfg.get('authorization')
        if not auth_path or 'Tournament authorized: yes' not in gate:raise ValueError('Concurrent tournament requires exact release authorization; legacy authorization does not cover this scheduler')
        auth=json.loads((ROOT/auth_path).read_text())
        if auth.get('authorized') is not True or auth.get('plan_id')!=semantic['plan_id']:raise ValueError('Concurrent tournament authorization mismatch')
    worker=dict(paths=paths,runtime_paths=runtime,plan=semantic,population=population)
    return semantic,worker
