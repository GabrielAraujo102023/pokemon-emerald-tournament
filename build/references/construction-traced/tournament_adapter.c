/* Construction milestone only: no battle execution is implemented here. */
#include "global.h"
#include "main.h"
#include "overworld.h"
#include "pokemon.h"
#include "random.h"
#include "battle.h"
#include "data.h"
#include "tournament_protocol.h"
#include "constants/trainers.h"
#include "constants/opponents.h"
EWRAM_DATA volatile struct TournamentControl gTournamentControl = {0};
static EWRAM_DATA struct TournamentEvent sEvents[128] = {0};
static EWRAM_DATA struct Pokemon sInitial[PARTY_SIZE * 2] = {0};
static EWRAM_DATA struct TournamentMonSnapshot sDecoded[PARTY_SIZE * 2] = {0};
extern u8 TournamentCreateParty(struct Pokemon *party, u16 trainer);
void TournamentRecordRandom(u32 before, u32 after)
{
    u32 count;
    struct TournamentEvent *event;
    if(gTournamentControl.phase!=TOURNAMENT_RNG_SEEDED) return;
    count=gTournamentControl.event_count;
    if(count>=128) { gTournamentControl.event_overflow=1; return; }
    event=&sEvents[count];
    event->sequence=count; event->kind=22; event->battler=0xFFFFFFFF;
    event->value0=before; event->value1=after; event->rng=after;
    event->phase=TOURNAMENT_RNG_SEEDED;
    gTournamentControl.event_count=count+1;
}
static void Snapshot(struct Pokemon *mon, u32 side, u32 slot, struct TournamentMonSnapshot *d)
{
    d->side=side; d->slot=slot;
    d->species=GetMonData(mon,MON_DATA_SPECIES);
    d->level=GetMonData(mon,MON_DATA_LEVEL);
    d->personality=GetMonData(mon,MON_DATA_PERSONALITY);
    d->ot_id=GetMonData(mon,MON_DATA_OT_ID);
    d->nature=GetNature(mon);
    d->ability=GetMonAbility(mon);
    d->gender=GetMonGender(mon);
    d->hp=GetMonData(mon,MON_DATA_HP); d->max_hp=GetMonData(mon,MON_DATA_MAX_HP);
    d->attack=GetMonData(mon,MON_DATA_ATK); d->defense=GetMonData(mon,MON_DATA_DEF);
    d->speed=GetMonData(mon,MON_DATA_SPEED); d->sp_attack=GetMonData(mon,MON_DATA_SPATK); d->sp_defense=GetMonData(mon,MON_DATA_SPDEF);
    d->status=GetMonData(mon,MON_DATA_STATUS); d->held_item=GetMonData(mon,MON_DATA_HELD_ITEM);
    d->move0=GetMonData(mon,MON_DATA_MOVE1); d->move1=GetMonData(mon,MON_DATA_MOVE2); d->move2=GetMonData(mon,MON_DATA_MOVE3); d->move3=GetMonData(mon,MON_DATA_MOVE4);
    d->pp0=GetMonData(mon,MON_DATA_PP1); d->pp1=GetMonData(mon,MON_DATA_PP2); d->pp2=GetMonData(mon,MON_DATA_PP3); d->pp3=GetMonData(mon,MON_DATA_PP4);
    d->friendship=GetMonData(mon,MON_DATA_FRIENDSHIP); d->experience=GetMonData(mon,MON_DATA_EXP);
}
static void TournamentPoll(void)
{
    u32 i,n=0;
    u16 a=gTournamentControl.trainer_a,b=gTournamentControl.trainer_b;
    if(gTournamentControl.phase==TOURNAMENT_RUNNING) {
        gTournamentControl.error_code=100; /* Both-side AI not implemented. */
        gTournamentControl.phase=TOURNAMENT_ERROR;
    }
    if(gTournamentControl.phase!=TOURNAMENT_REQUEST_LOADED) return;
    if(gTournamentControl.rules_version!=1 || !a || !b || a>=TRAINERS_COUNT || b>=TRAINERS_COUNT || !gTrainers[a].partySize || !gTrainers[b].partySize || gTrainers[a].doubleBattle || gTrainers[b].doubleBattle) {
        gTournamentControl.error_code=1; gTournamentControl.phase=TOURNAMENT_ERROR; return;
    }
    gRngValue=gTournamentControl.seed;
    gTournamentControl.rng_start=gRngValue;
    gTournamentControl.phase=TOURNAMENT_RNG_SEEDED;
    gBattleTypeFlags=BATTLE_TYPE_TRAINER;
    TournamentCreateParty(gPlayerParty,a);
    TournamentCreateParty(gEnemyParty,b);
    gPlayerPartyCount=gTrainers[a].partySize;
    gEnemyPartyCount=gTrainers[b].partySize;
    gTournamentControl.rng_after_party_init=gRngValue;
    memcpy(sInitial,gPlayerParty,sizeof(gPlayerParty));
    memcpy(sInitial+PARTY_SIZE,gEnemyParty,sizeof(gEnemyParty));
    for(i=0;i<gPlayerPartyCount;i++) Snapshot(&gPlayerParty[i],0,i,&sDecoded[n++]);
    for(i=0;i<gEnemyPartyCount;i++) Snapshot(&gEnemyParty[i],1,i,&sDecoded[n++]);
    gTournamentControl.decoded_count=n;
    if(gTournamentControl.event_overflow) { gTournamentControl.error_code=2; gTournamentControl.phase=TOURNAMENT_ERROR; }
    else gTournamentControl.phase=TOURNAMENT_PARTIES_CONSTRUCTED;
}
void TournamentReady(void)
{
    STATIC_ASSERT(sizeof(struct TournamentControl)==92,control_size);
    STATIC_ASSERT(sizeof(struct TournamentMonSnapshot)==112,decoded_size);
    memset((void *)&gTournamentControl,0,sizeof(gTournamentControl));
    gTournamentControl.magic=TOURNAMENT_MAGIC;
    gTournamentControl.abi=TOURNAMENT_ABI;
    gTournamentControl.event_address=(u32)sEvents;
    gTournamentControl.event_capacity=128;
    gTournamentControl.initial_party_address=(u32)sInitial;
    gTournamentControl.initial_party_size=sizeof(sInitial);
    gTournamentControl.decoded_address=(u32)sDecoded;
    gTournamentControl.phase=TOURNAMENT_CHECKPOINT_READY;
    SetMainCallback1(NULL);
    SetMainCallback2(TournamentPoll);
}
