/* Data only. Upstream preproc supplies Emerald-encoded strings. */
#include <stdio.h>
#include <stdint.h>
typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t bool8;
#define TRUE 1
#define FALSE 0
#define ARRAY_COUNT(a) (sizeof(a)/sizeof((a)[0]))
#define min(a,b) ((a)<(b)?(a):(b))
#include "constants/global.h"
#include "constants/characters.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "constants/trainers.h"
#include "constants/battle_ai.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "declarations.h"
#include "src/data/trainer_parties.h"
#include "encoded_trainers.h"
#include "encoded_species.h"
#include "src/data/pokemon/species_info.h"
#include "src/data/pokemon/level_up_learnsets.h"
#include "src/data/pokemon/level_up_learnset_pointers.h"
#include "src/data/pokemon/experience_tables.h"
#include "src/data/battle_moves.h"
#include "nature.h"
/* Constructor oracle: original function, captured calls, no fake battle engine. */
typedef int32_t s32;
struct Pokemon { u8 unused; };
static u32 gBattleTypeFlags;
static unsigned oracleTrainer;
static void ZeroEnemyPartyMons(void) {}
static void CreateMon(struct Pokemon *p, u16 species, u8 level, u8 iv, u8 fixed, u32 personality, u8 otType, u32 ot) {
    (void)p; (void)fixed; (void)otType; (void)ot;
    printf("C\t%u\t%u\t%u\t%u\t%u\n",oracleTrainer,species,level,iv,personality);
}
static void SetMonData(struct Pokemon *p, int field, const void *value) { (void)p; (void)field; (void)value; }
#include "constructor.h"
static void bytes(const u8 *s) { for (; *s != 255; s++) printf("\t%u", *s); puts(""); }
int main(void) {
    struct Pokemon party[PARTY_SIZE];
    for(oracleTrainer=1;oracleTrainer<ARRAY_COUNT(gTrainers);oracleTrainer++) { gBattleTypeFlags=BATTLE_TYPE_TRAINER; CreateNPCTrainerParty(party,oracleTrainer,TRUE); }
    for(unsigned i=0;i<ARRAY_COUNT(gTrainers);i++) { printf("T\t%u",i); bytes(gTrainers[i].trainerName); }
    for(unsigned i=0;i<ARRAY_COUNT(gSpeciesInfo);i++) {
        const struct SpeciesInfo *s=&gSpeciesInfo[i];
        printf("S\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u",i,s->baseHP,s->baseAttack,s->baseDefense,s->baseSpeed,s->baseSpAttack,s->baseSpDefense,s->genderRatio,s->friendship,s->growthRate,s->abilities[0],s->abilities[1],s->types[0],s->types[1]); puts("");
        printf("N\t%u",i); bytes(gSpeciesNames[i]);
        printf("L\t%u",i);
        if (i<ARRAY_COUNT(gLevelUpLearnsets) && gLevelUpLearnsets[i])
            for(const u16 *m=gLevelUpLearnsets[i];*m!=LEVEL_UP_END;m++) printf("\t%u",*m);
        puts("");
    }
    for(unsigned i=0;i<ARRAY_COUNT(gBattleMoves);i++) {
        const struct BattleMove *m=&gBattleMoves[i];
        printf("M\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%d\t%u\n",i,m->pp,m->power,m->type,m->accuracy,m->effect,m->secondaryEffectChance,m->target,m->priority,m->flags);
    }
    for(unsigned i=0;i<NUM_NATURES;i++) { printf("A\t%u",i); for(unsigned j=0;j<NUM_NATURE_STATS;j++) printf("\t%d",gNatureStatTable[i][j]); puts(""); }
    for(unsigned i=0;i<ARRAY_COUNT(gExperienceTables);i++) { printf("E\t%u",i); for(unsigned j=0;j<=MAX_LEVEL;j++) printf("\t%u",gExperienceTables[i][j]); puts(""); }
}
