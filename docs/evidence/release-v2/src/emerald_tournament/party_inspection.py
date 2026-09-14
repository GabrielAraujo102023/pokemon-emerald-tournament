"""Read encrypted Pokemon data for validation; never executes battle mechanics."""
import re,struct
from pathlib import Path

def decode_growth(raw: bytes, pokemon_source: Path):
    if len(raw)%100:raise ValueError('Expected complete ARM Pokemon records')
    rows=re.findall(r'SUBSTRUCT_CASE\(\s*(\d+),\s*(\d+),\s*(\d+),\s*(\d+),\s*(\d+)\)',pokemon_source.read_text())
    order={int(row[0]):tuple(map(int,row[1:])) for row in rows}
    if set(order)!=set(range(24)) or any(set(v)!={0,1,2,3} for v in order.values()):raise ValueError('Unrecognized upstream substructure ordering')
    records=[]
    for pos in range(0,len(raw),100):
        mon=raw[pos:pos+100];personality,ot=struct.unpack_from('<II',mon)
        decrypted=b''.join(struct.pack('<I',word^personality^ot) for word in struct.unpack_from('<12I',mon,32))
        if sum(struct.unpack('<24H',decrypted))&65535!=struct.unpack_from('<H',mon,28)[0]:raise ValueError('Pokemon checksum mismatch')
        growth=decrypted[order[personality%24][0]*12:][:12]
        records.append(dict(species=struct.unpack_from('<H',growth)[0],experience=struct.unpack_from('<I',growth,4)[0],friendship=growth[9],personality=personality,ot_id=ot,level=mon[84],hp=struct.unpack_from('<H',mon,86)[0]))
    return records
