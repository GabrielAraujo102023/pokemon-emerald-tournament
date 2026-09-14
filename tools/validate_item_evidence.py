"""Assert real captured item selections, inventory ownership and healing effects."""
from collections import Counter
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_protocol import elf_symbol,digest
ROOT=Path(__file__).resolve().parents[1]
ITEMS={'ITEM_NONE':0,'ITEM_POTION':13,'ITEM_FULL_RESTORE':19,'ITEM_HYPER_POTION':21,'ITEM_SUPER_POTION':22}

def inventory_transition_valid(before, after, choices):
    ok=bool(choices)
    for side in [0,1]:
        want=Counter(before[side]);want.pop(0,None)
        for choice in choices:
            if choice['battler']==side:want[choice['value0']]-=1
        actual=Counter(after[side]);actual.pop(0,None)
        ok &= all(n>=0 for n in want.values()) and +want==actual
    return bool(ok)

def validate(path, trainers, elf):
    events=[json.loads(x) for x in (path/'events.jsonl').read_text().splitlines()]
    observations=[json.loads(x) for x in (path/'engine_observations.jsonl').read_text().splitlines()]
    result=json.loads((path/'battle_result.json').read_text())
    if result["provenance"]["elf_sha256"] != digest(elf): raise ValueError("Capture ELF hash mismatch")
    ids=[result['trainer_a'],result['trainer_b']]
    expected=[[ITEMS[name] for name in trainers[i]['battle_items']] for i in ids]
    selected=[e for e in events if e['event']=='trainer_item_selected']
    # Skip the phase-5 host observation before TournamentStart initializes inventories.
    start=next(e['sequence'] for e in events if e['event']=='battle_start')
    observations=[o for o in observations if o['event_count']>start]
    checks={'initial_inventories_match':observations[0]['inventory']==expected,
            'selected_from_owner_inventory':bool(selected) and all(e['value0'] in expected[e['battler']] for e in selected)}
    mutations=[]
    for before,after in zip(observations,observations[1:]):
        if before['inventory']==after['inventory']: continue
        choices=[e for e in selected if before['event_count']<=e['sequence']<after['event_count']]
        ok=inventory_transition_valid(before['inventory'],after['inventory'],choices)
        mutations.append(dict(frame=after['frame'],choices=choices,valid=bool(ok)))
    checks['isolated_inventory_consumption']=bool(mutations) and all(m['valid'] for m in mutations)
    checks['every_selection_consumed_once']=sum(len(m['choices']) for m in mutations)==len(selected)
    lo=elf_symbol(elf,'BattleScript_OpponentUsesHealItem');hi=elf_symbol(elf,'BattleScript_OpponentUsesStatusCureItem')
    heals=[];cures=[]
    for before,after in zip(observations,observations[1:]):
        side=after['attacker']
        if side not in (0,1) or before['slots']!=after['slots'] or not lo<=after['script']<hi:continue
        if after['item']!=19:continue
        other=1-side
        if after['hp'][side]>before['hp'][side]>0:
            heals.append(dict(side=side,before=before,after=after,valid=after['hp'][side]==after['max_hp'][side] and before['hp'][other]==after['hp'][other] and before['status1'][other]==after['status1'][other] and before['stages'][other]==after['stages'][other]))
        if before['status1'][side] & 0xFF and after['status1'][side]==0:
            cures.append(dict(side=side,before=before,after=after,valid=before['status1'][other]==after['status1'][other]))
    checks['fullrestore_healing_correct']=bool(heals) and all(h['valid'] for h in heals)
    checks['both_sides_healed']={h['side'] for h in heals}=={0,1}
    return dict(result=result,checks=checks,inventory_mutations=mutations,heals=heals,cures=cures,
                status_cure_observed=bool(cures) and all(c['valid'] for c in cures))

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--capture',type=Path,required=True);p.add_argument('--output',type=Path,required=True);args=p.parse_args()
    trainers={t['id']:t for t in json.loads((ROOT/'data/generated/trainers.json').read_text())['trainers']}
    report=validate(args.capture,trainers,ROOT/'build/pokeemerald/pokeemerald_modern.elf')
    with args.output.open('x') as f:f.write(json.dumps(report,indent=2)+'\n')
    print(report['checks'],'status cure',report['status_cure_observed'])
    assert all(report['checks'].values()),report['checks']
if __name__=='__main__':main()
