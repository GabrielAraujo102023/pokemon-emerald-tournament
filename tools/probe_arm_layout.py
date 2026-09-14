"""Compile actual ARM struct offsets for host read-only observations."""
from pathlib import Path
import json,struct,subprocess
ROOT=Path(__file__).resolve().parents[1]
FIELDS={'battle_mon_size':'sizeof(struct BattlePokemon)','battle_hp':'offsetof(struct BattlePokemon,hp)','battle_status1':'offsetof(struct BattlePokemon,status1)','history_size':'sizeof(struct BattleHistory)','history_items':'offsetof(struct BattleHistory,trainerItems)','history_items_no':'offsetof(struct BattleHistory,itemsNo)','party_mon_size':'sizeof(struct Pokemon)','party_hp':'offsetof(struct Pokemon,hp)','save_flags':'offsetof(struct SaveBlock1,flags)','badge_first':'FLAG_BADGE01_GET','badge_last':'FLAG_BADGE08_GET'}
def main():
 out=ROOT/'build/layout';out.mkdir(exist_ok=True)
 src=out/'layout.c';src.write_text('#include "global.h"\n#include "battle.h"\n#include "constants/flags.h"\n#include <stddef.h>\nconst unsigned int layout[] = {'+','.join(FIELDS.values())+'};\n')
 subprocess.run(['/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc','-mthumb','-mcpu=arm7tdmi','-fmax-errors=3','-DMODERN=1','-mabi=apcs-gnu','-iquote',str(ROOT/'build/pokeemerald/include'),'-c',str(src),'-o',str(out/'layout.o')],check=True)
 subprocess.run(['/opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy','--dump-section',f'.rodata={out/"layout.bin"}',str(out/'layout.o')],check=True)
 values=struct.unpack('<'+'I'*len(FIELDS),(out/'layout.bin').read_bytes())
 data=dict(zip(FIELDS,values));(out/'layout.json').write_text(json.dumps(data,indent=2)+'\n');print(data)
if __name__=='__main__':main()
