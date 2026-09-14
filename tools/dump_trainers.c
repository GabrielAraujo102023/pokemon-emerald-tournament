/* Host-only extraction: actual upstream declarations/initializers, no ROM ABI claims. */
#include <stdio.h>
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t bool8;
#define TRUE 1
#define FALSE 0
#define _(s) s
#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))
#include "constants/global.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/trainers.h"
#include "constants/battle_ai.h"
#include "trainer_declarations.h"
#include "src/data/trainer_parties.h"
#include "src/data/trainers.h"
int main(void) {
    for (unsigned i = 0; i < ARRAY_COUNT(gTrainers); i++) {
        const struct Trainer *t = &gTrainers[i];
        printf("T\t%u\t%s\t%u\t%u\t%u\t%u\t%u\t%u", i, t->trainerName,
            t->trainerClass, t->encounterMusic_gender, t->doubleBattle, t->aiFlags, t->partyFlags, t->partySize);
        for (unsigned j = 0; j < MAX_TRAINER_ITEMS; j++) printf("\t%u", t->items[j]);
        puts("");
        for (unsigned j = 0; j < t->partySize; j++) {
            unsigned iv, level, species, item = 0; const u16 *moves = NULL;
            switch(t->partyFlags) {
            case 0: { const struct TrainerMonNoItemDefaultMoves *p = &t->party.NoItemDefaultMoves[j]; iv=p->iv; level=p->lvl; species=p->species; break; }
            case 1: { const struct TrainerMonNoItemCustomMoves *p = &t->party.NoItemCustomMoves[j]; iv=p->iv; level=p->lvl; species=p->species; moves=p->moves; break; }
            case 2: { const struct TrainerMonItemDefaultMoves *p = &t->party.ItemDefaultMoves[j]; iv=p->iv; level=p->lvl; species=p->species; item=p->heldItem; break; }
            case 3: { const struct TrainerMonItemCustomMoves *p = &t->party.ItemCustomMoves[j]; iv=p->iv; level=p->lvl; species=p->species; item=p->heldItem; moves=p->moves; break; }
            default: return 2;
            }
            printf("P\t%u\t%u\t%u\t%u\t%u", j, iv, level, species, item);
            if (moves) for (unsigned k=0; k<MAX_MON_MOVES; k++) printf("\t%u", moves[k]);
            puts("");
        }
    }
}
