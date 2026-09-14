"""Real ARM party construction validation. No battle result is synthesized."""
from pathlib import Path
import hashlib,json,subprocess,sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.emu_protocol import elf_symbol,control,FIELDS,MON_FIELDS,EVENT_FIELDS,words,digest
from emerald_tournament.emu_battle import Bridge
ROOT=Path(__file__).resolve().parents[1]


def main():
    binary=ROOT/'build/emulator/emerald-mgba-bridge';rom=ROOT/'build/pokeemerald/pokeemerald_modern.gba';elf=rom.with_suffix('.elf');out=ROOT/'build/reports'
    address=elf_symbol(elf,'gTournamentControl');checkpoint=out/'constructor-ready.ss'
    with (out/'constructor-ready.trace').open('w') as trace,(out/'constructor-ready.stderr').open('w') as err:
        subprocess.run([str(binary),'--capture-ready',str(rom),'1200',hex(address),str(checkpoint)],stdout=trace,stderr=err,check=True,timeout=60)
    records=[]
    for name,seed in [('constructor-a',12345),('constructor-b',12345),('constructor-c',12346)]:
        with (out/(name+'.stderr')).open('wb') as err:
            client=Bridge(binary,rom,checkpoint,err)
            try:
                state=control(client.read(address,92));assert state['phase']==2
                for field,value in [('trainer_a',1),('trainer_b',335),('seed',seed),('rules_version',1),('phase',1)]:
                    client.write(address+FIELDS.index(field)*4,value)
                for frame in range(120):
                    client.frame();state=control(client.read(address,92))
                    if state['phase'] in (4,8):break
                assert state['phase']==4,state
                assert not state['event_overflow']
                if '--uninstrumented' not in sys.argv: assert state['event_count']>0
                trace=client.read(state['event_address'],state['event_count']*32) if state['event_count'] else b''
                events=[words(trace[i:i+32],EVENT_FIELDS) for i in range(0,len(trace),32)]
                previous=seed
                for event in events:
                    assert event['value0']==previous
                    assert event['value1']==(1103515245*previous+24691)&0xFFFFFFFF
                    previous=event['value1']
                if events: assert state['rng_after_party_init'] in [e['value1'] for e in events]
                # Snapshot decoding can cross additional VBlanks before phase 4.
                # Preserve the entire trace and distinguish the constructor boundary.
                (out/(name+'.events.json')).write_text(json.dumps(events,indent=2)+'\n')
                raw=client.read(state['initial_party_address'],state['initial_party_size'])
                decoded=client.read(state['decoded_address'],state['decoded_count']*112)
                mons=[words(decoded[i:i+112],MON_FIELDS) for i in range(0,len(decoded),112)]
                (out/(name+'.bin')).write_bytes(raw)
                (out/(name+'.json')).write_text(json.dumps(dict(control=state,party=mons),indent=2)+'\n')
                records.append((raw,decoded,state,trace))
            finally:client.close()
    report=dict(kind='actual ARM constructor validation; no battle execution',instrumented='--uninstrumented' not in sys.argv,emulator=subprocess.check_output([str(binary),'--version'],text=True).strip(),compiler=json.loads((out/'build-modern.json').read_text())['compiler'],adapter_sha256=digest(ROOT/'adapter/tournament_adapter.c'),rules_version=1,rom_sha256=digest(rom),elf_sha256=digest(elf),checkpoint_sha256=digest(checkpoint),bridge_sha256=digest(binary),
                same_seed_rng_trace_equal=records[0][3]==records[1][3],rng_calls=[r[2]['event_count'] for r in records],same_seed_raw_equal=records[0][0]==records[1][0],same_seed_decoded_equal=records[0][1]==records[1][1],same_seed_post_rng_equal=records[0][2]['rng_after_party_init']==records[1][2]['rng_after_party_init'],
                different_seed_raw_differs=records[0][0]!=records[2][0],different_seed_post_rng_differs=records[0][2]['rng_after_party_init']!=records[2][2]['rng_after_party_init'],
                post_rng=[r[2]['rng_after_party_init'] for r in records],party_count=records[0][2]['decoded_count'])
    (out/'constructor-validation.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
    assert all(report[k] for k in ['same_seed_rng_trace_equal','same_seed_raw_equal','same_seed_decoded_equal','same_seed_post_rng_equal','different_seed_raw_differs','different_seed_post_rng_differs'])

if __name__=='__main__':main()
