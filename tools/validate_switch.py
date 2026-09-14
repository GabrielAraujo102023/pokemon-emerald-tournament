"""Validate a voluntary switch from AI selection to loaded slot in real ARM execution.
This is a bounded path probe, not a terminal battle validation.
"""
import argparse
import json
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import run_battle
ROOT=Path(__file__).resolve().parents[1]

def verify(events, observations, party, side):
    proofs=[]
    for event in events:
        if event['event']!='switch_selected' or event['battler']!=side: continue
        seq=event['sequence'];slot=event['value0']
        before=[o for o in observations if o['event_count']<=seq]
        after=[o for o in observations if o['event_count']>seq]
        if not before: continue
        old=before[-1]
        mon=next((m for m in party if m['slot']==slot),None)
        if not mon or old['hp'][side]<=0 or old['slots'][side]==slot: continue
        loaded=next((o for o in after if o['slots'][side]==slot and o['species'][side]==mon['species'] and o['hp'][side]>0),None)
        if not loaded: continue
        # Require the newly loaded battler to reach its next AI move selection.
        next_move=next((e for e in events if e['sequence']>=loaded['event_count']-1 and e['event']=='move_selected' and e['battler']==side),None)
        if not next_move: continue
        until=[e for e in events if seq<e['sequence']<next_move['sequence'] and e['battler']==side]
        if any(e['event'] in ('faint','switch_selected') for e in until): continue
        acting = next((o for o in after if o['event_count']>next_move['sequence']),None)
        if not acting or acting['slots'][side]!=slot or acting['species'][side]!=mon['species'] or acting['hp'][side]<=0: continue
        proofs.append(dict(selection=event,before=old,loaded=loaded,next_move=next_move,acting=acting))
    return proofs

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--output',type=Path,required=True)
    p.add_argument('--pair',type=int,nargs=2,default=[100,210])
    p.add_argument('--seed',type=int,default=12345)
    p.add_argument('--max-frames',type=int,default=6000)
    p.add_argument('--side-seeds',type=int,nargs=2,help='Pinned seed for each orientation')
    args=p.parse_args();args.output.mkdir(parents=True,exist_ok=False)
    build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports'
    report=dict(scope='bounded voluntary-switch path only; terminal outcome not required',passed=False,runs=[])
    try:
        for side in [0,1]:
            a,b=args.pair if side==0 else args.pair[::-1]
            out=args.output/f'side-{side}'
            result=run_battle(trainer_a=a,trainer_b=b,seed=args.side_seeds[side] if args.side_seeds else args.seed,rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',manifest_path=reports/'battle-manifest.json',bridge=ROOT/'build/emulator/emerald-mgba-bridge',output=out,max_frames=args.max_frames,observe_engine=True)
            events=[json.loads(x) for x in (out/'events.jsonl').read_text().splitlines()]
            observations=[json.loads(x) for x in (out/'engine_observations.jsonl').read_text().splitlines()]
            party=json.loads((out/f"party_{'a' if side==0 else 'b'}.json").read_text())
            proofs=verify(events,observations,party,side)
            report['runs'].append(dict(side=side,battle_result=result,proofs=proofs))
            print('side',side,'validated voluntary switches',len(proofs),flush=True)
            if not proofs: raise RuntimeError(f'No validated voluntary switch on side {side} within {args.max_frames} frames')
        report['passed']=True
    except Exception as error:
        report['error']=str(error);raise
    finally:
        (args.output/'validation.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__': main()
