"""Small natural-team ARM fixtures; never substitutes parties or engine outcomes."""
import argparse
import json
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'src'))
from emerald_tournament.emu_battle import run_battle
from emerald_tournament.emu_protocol import elf_symbol
ROOT = Path(__file__).resolve().parents[1]
FIXTURES = [
    ('swapped-baseline', 335, 1, None),
    ('replacement-side-a', 265, 335, 0),
    ('replacement-side-b', 335, 265, 1),
]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--items', action='store_true', help='Probe Roxanne/Brawly in both orientations')
    parser.add_argument('--pair', nargs=2, type=int, metavar=('TRAINER_A', 'TRAINER_B'))
    parser.add_argument('--seed', type=int, default=12345)
    parser.add_argument('--require-potions', action='store_true')
    parser.add_argument('--max-frames',type=int,default=12000)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=False)
    report = {'scope': 'natural-team single-battle fixtures', 'fixtures': [], 'passed': False}
    build, reports = ROOT/'build/pokeemerald', ROOT/'build/reports'
    try:
        fixtures = [('items-a', 265, 266, None), ('items-b', 266, 265, None)] if args.items else FIXTURES
        if args.pair:
            a,b=args.pair
            fixtures=[('pair-a',a,b,None),('pair-b',b,a,None)]
        for name, a, b, replacement_side in fixtures:
            out = args.output/name
            record = {'name': name, 'trainer_a': a, 'trainer_b': b, 'seed': args.seed}
            report['fixtures'].append(record)
            result = run_battle(trainer_a=a, trainer_b=b, seed=args.seed,
                rom=build/'pokeemerald_modern.gba', elf=build/'pokeemerald_modern.elf',
                checkpoint=reports/'constructor-ready.ss', manifest_path=reports/'battle-manifest.json',
                bridge=ROOT/'build/emulator/emerald-mgba-bridge', output=out, max_frames=args.max_frames, observe_engine=True)
            events = [json.loads(line) for line in (out/'events.jsonl').read_text().splitlines()]
            record['result'] = result
            record['checks'] = {
                'terminal': result['terminal_from_engine'],
                'both_ai': {e['battler'] for e in events if e['event']=='move_selected'} == {0, 1},
            }
            if 335 in (a,b):
                record['checks']['wallace_wins'] = result['outcome'] == ('a_win' if a==335 else 'b_win')
            record['observed_items'] = [e for e in events if e['event']=='trainer_item_selected']
            record['observed_self_targets'] = [e for e in events if e['event']=='move_selected' and e['battler']==e['value1']]
            if replacement_side is not None:
                record['checks']['replacement_observed'] = any(e['event']=='replacement' and e['battler']==replacement_side for e in events)
            observations = [json.loads(line) for line in (out/'engine_observations.jsonl').read_text().splitlines()]
            heal_start = elf_symbol(build/'pokeemerald_modern.elf', 'BattleScript_OpponentUsesHealItem')
            heal_end = elf_symbol(build/'pokeemerald_modern.elf', 'BattleScript_OpponentUsesStatusCureItem')
            heals = []
            for before, after in zip(observations, observations[1:]):
                side = after['attacker']
                if side not in (0, 1) or before['slots'] != after['slots']:
                    continue
                if heal_start <= after['script'] < heal_end and after['item']==13 and after['hp'][side]>before['hp'][side]:
                    heals.append({'side': side, 'before': before, 'after': after})
            record['potion_heals'] = heals
            if args.require_potions:
                side = 0 if a==265 else 1
                selections = [e for e in record['observed_items'] if e['battler']==side and e['value0']==13]
                actual = [h for h in heals if h['side']==side]
                record['checks']['potions_executed'] = bool(selections) and len(actual)==len(selections)
                record['checks']['correct_hp_delta'] = bool(actual) and all(
                    h['after']['hp'][side] == min(h['before']['hp'][side]+20,h['after']['max_hp'][side])
                    and h['after']['hp'][1-side] == h['before']['hp'][1-side] for h in actual)
            print(name, record['checks'], flush=True)
            if not all(record['checks'].values()):
                raise RuntimeError(f'Fixture failed: {name}; inspect saved engine events')
        report['passed'] = True
    except Exception as error:
        report['error'] = str(error)
        raise
    finally:
        (args.output/'validation.json').write_text(json.dumps(report, indent=2)+'\n')

if __name__ == '__main__':
    main()
