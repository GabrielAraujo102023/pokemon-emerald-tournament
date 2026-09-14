"""Actual mGBA ring wrap, repeatability and deliberately undrained overflow."""
from pathlib import Path
import argparse,json,sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_battle import Bridge,run_battle
from emerald_tournament.emu_protocol import control,elf_symbol,FIELDS
ROOT=Path(__file__).resolve().parents[1]

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--output',type=Path,required=True);args=parser.parse_args()
    out=args.output;out.mkdir(parents=True,exist_ok=False)
    build=ROOT/'build/pokeemerald';reports=ROOT/'build/reports'
    inputs=dict(rom=build/'pokeemerald_modern.gba',elf=build/'pokeemerald_modern.elf',checkpoint=reports/'constructor-ready.ss',bridge=ROOT/'build/emulator/emerald-mgba-bridge')
    result={'passed':False,'checks':{}}
    try:
        trials=[]
        for name in ['a','b']:
            trials.append(run_battle(trainer_a=100,trainer_b=98,seed=12345,manifest_path=reports/'battle-manifest.json',output=out/name,max_frames=24000,**inputs))
            print(name,trials[-1]['trace_event_count'],trials[-1]['outcome'],flush=True)
        result['trials']=trials
        result['checks']['wrapped']=all(t['trace_event_count']>128 for t in trials)
        result['checks']['same_result']=trials[0]==trials[1]
        for filename in ['events.bin','initial_parties.bin','stopped_parties.bin']:
            result['checks']['repeat_'+filename]=(out/'a'/filename).read_bytes()==(out/'b'/filename).read_bytes()
        # Deliberately withhold acknowledgments; test the actual producer's fail-closed behavior.
        address=elf_symbol(inputs['elf'],'gTournamentControl')
        with (out/'undrained.stderr').open('wb') as stderr:
            client=Bridge(inputs['bridge'],inputs['rom'],inputs['checkpoint'],stderr)
            try:
                for field,value in [('trainer_a',100),('trainer_b',98),('seed',12345),('rules_version',1),('phase',1)]:client.write(address+FIELDS.index(field)*4,value)
                for frame in range(24000):
                    client.frame();state=control(client.read(address,92))
                    if state['phase']==4:client.write(address+FIELDS.index('phase')*4,5)
                    if state['event_overflow'] or state['phase'] in (7,8):break
                result['undrained']=dict(frame=frame+1,control=state)
                result['checks']['overflow_rejected']=state['event_overflow']==1 and state['event_count']==128 and state['phase']==8 and state['error_code']==2
                (out/'undrained-events.bin').write_bytes(client.read(state['event_address'],128*32))
            finally:client.close()
        assert all(result['checks'].values()),result['checks']
        result['passed']=True
    finally:(out/'validation.json').write_text(json.dumps(result,indent=2)+'\n')
if __name__=='__main__':main()
