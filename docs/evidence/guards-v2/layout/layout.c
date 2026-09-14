#include "global.h"
#include "battle.h"
#include "constants/flags.h"
#include <stddef.h>
const unsigned int layout[] = {sizeof(struct BattlePokemon),offsetof(struct BattlePokemon,hp),offsetof(struct BattlePokemon,status1),sizeof(struct BattleHistory),offsetof(struct BattleHistory,trainerItems),offsetof(struct BattleHistory,itemsNo),sizeof(struct Pokemon),offsetof(struct Pokemon,hp),offsetof(struct SaveBlock1,flags),FLAG_BADGE01_GET,FLAG_BADGE08_GET};
