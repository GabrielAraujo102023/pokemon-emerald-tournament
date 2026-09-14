"""Actual ROM boot/restore smoke test. Explicitly NOT a tournament checkpoint test."""
from pathlib import Path
import hashlib
import json
import subprocess
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/"src"))
from emerald_tournament.emu_protocol import elf_symbol, digest
from emerald_tournament.emu_battle import Bridge

ROOT=Path(__file__).resolve().parents[1]

def main():
    binary=ROOT/'build/emulator/emerald-mgba-bridge'
    rom=ROOT/'build/pokeemerald/pokeemerald_modern.gba'
    elf=rom.with_suffix('.elf')
    out=ROOT/'build/reports'
    rng=elf_symbol(elf,'gRngValue')
    report=dict(kind='boot/restore only; not party or battle validation',frames=600,rtc='fixed Unix epoch 0',rom_sha256=digest(rom),elf_sha256=digest(elf),bridge_sha256=digest(binary),emulator=subprocess.check_output([str(binary),'--version'],text=True).strip())
    for name in ('boot-a','boot-b'):
        with (out/(name+'.trace')).open('w') as trace,(out/(name+'.stderr')).open('w') as log:
            subprocess.run([str(binary),'--boot-probe',str(rom),'600',hex(rng),str(out/(name+'.ss'))],stdout=trace,stderr=log,check=True,timeout=60)
    report['trace_identical']=(out/'boot-a.trace').read_bytes()==(out/'boot-b.trace').read_bytes()
    report['state_identical']=(out/'boot-a.ss').read_bytes()==(out/'boot-b.ss').read_bytes()
    traces=[]
    for name in ('restore-a','restore-b'):
        with (out/(name+'.stderr')).open('wb') as log:
            client=Bridge(binary,rom,out/'boot-a.ss',log)
            try:
                values=[]
                for _ in range(120):
                    client.frame();values.append(int.from_bytes(client.read(rng,4),'little'))
                traces.append(values)
            finally:client.close()
    report['restored_trace_identical']=traces[0]==traces[1]
    report['trace_sha256']=digest(out/'boot-a.trace')
    report['checkpoint_sha256']=digest(out/'boot-a.ss')
    (out/'boot-validation.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))
    if not all(report[k] for k in ('trace_identical','state_identical','restored_trace_identical')):raise SystemExit(1)

if __name__=='__main__':main()
