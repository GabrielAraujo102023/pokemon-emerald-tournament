/* Separate construction barrier and narrow single-battle tournament adapter. */
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
EWRAM_DATA volatile u32 gTournamentEventRead = 0;
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
    if(gTournamentEventRead>count || count-gTournamentEventRead>=128) { gTournamentControl.event_overflow=1; return; }
    event=&sEvents[count % 128];
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
static void TournamentStart(void);
static void TournamentPoll(void)
{
    u32 i,n=0;
    u16 a=gTournamentControl.trainer_a,b=gTournamentControl.trainer_b;
    if(gTournamentControl.phase==TOURNAMENT_RUNNING) {
        TournamentStart(); return;
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
    gTournamentEventRead=0;
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

/* Battle slice: one engine, side-local decision history and item inventories. */
#include "battle_main.h"
#include "battle_anim.h"
#include "battle_setup.h"
#include "battle_ai_script_commands.h"
#include "battle_ai_switch_items.h"
#include "battle_controllers.h"
static EWRAM_DATA struct BattleHistory sHistory[2] = {0};
static EWRAM_DATA struct Pokemon sFinal[PARTY_SIZE * 2] = {0};
static u16 sLastHp[2], sLastSpecies[2];
static u32 sLastTurn;
bool8 TournamentActive(void) { return gTournamentControl.magic==TOURNAMENT_MAGIC && gTournamentControl.phase==TOURNAMENT_RUNNING; }
u16 TournamentTrainer(u8 battler) { return GetBattlerSide(battler)==B_SIDE_PLAYER ? gTournamentControl.trainer_a : gTournamentControl.trainer_b; }
u8 TournamentItemIndex(u8 battler) { return TournamentActive() ? GetBattlerSide(battler) : battler/2; }
void TournamentLog(u32 kind,u32 battler,u32 a,u32 b)
{
    u32 n=gTournamentControl.event_count;
    struct TournamentEvent *e;
    if(gTournamentEventRead>n || n-gTournamentEventRead>=128) { gTournamentControl.event_overflow=1; return; }
    e=&sEvents[n % 128]; e->sequence=n; e->kind=kind; e->turn=gBattleResults.battleTurnCounter;
    e->battler=battler; e->value0=a; e->value1=b; e->rng=gRngValue; e->phase=gTournamentControl.phase;
    gTournamentControl.event_count=n+1;
}
static struct BattleHistory *SelectHistory(void)
{
    struct BattleHistory *old=gBattleResources->battleHistory;
    struct BattleHistory *selected=&sHistory[GetBattlerSide(gActiveBattler)];
    /* Observed effects are public engine records; move discovery stays side-local. */
    memcpy(selected->abilities,old->abilities,sizeof(selected->abilities));
    memcpy(selected->itemEffects,old->itemEffects,sizeof(selected->itemEffects));
    gBattleResources->battleHistory=selected;
    return old;
}
void TournamentAIAction(void)
{
    struct BattleHistory *old=SelectHistory();
    AI_TrySwitchOrUseItem();
    gBattleResources->battleHistory=old;
    if (gBattleBufferB[gActiveBattler][1]==B_ACTION_SWITCH) TournamentLog(5,gActiveBattler,gBattleStruct->monToSwitchIntoId[gActiveBattler],0);
    else if (gBattleBufferB[gActiveBattler][1]==B_ACTION_USE_ITEM) TournamentLog(6,gActiveBattler,gBattleStruct->chosenItem[TournamentItemIndex(gActiveBattler)*2],0);
}
u8 TournamentAIMove(void)
{
    u8 move;
    struct BattleHistory *old=SelectHistory();
    BattleAI_SetupAIData(ALL_MOVES_MASK);
    move=BattleAI_ChooseMoveOrAction();
    gBattleResources->battleHistory=old;
    if(move>=MAX_MON_MOVES) { gTournamentControl.error_code=101; gTournamentControl.phase=TOURNAMENT_ERROR; return 0; }
    if (gBattleMoves[gBattleMons[gActiveBattler].moves[move]].target & (MOVE_TARGET_USER_OR_SELECTED | MOVE_TARGET_USER)) gBattlerTarget=gActiveBattler;
    TournamentLog(4,gActiveBattler,gBattleMons[gActiveBattler].moves[move],gBattlerTarget);
    return move;
}
u8 TournamentReplacement(void)
{
    u8 i;
    struct Pokemon *party=GetBattlerSide(gActiveBattler)==B_SIDE_PLAYER ? gPlayerParty:gEnemyParty;
    struct BattleHistory *old=SelectHistory();
    u8 chosen=gBattleStruct->AI_monToSwitchIntoId[gActiveBattler];
    if (chosen==PARTY_SIZE) chosen=GetMostSuitableMonToSwitchInto();
    else gBattleStruct->AI_monToSwitchIntoId[gActiveBattler]=PARTY_SIZE;
    gBattleResources->battleHistory=old;
    if(chosen==PARTY_SIZE) {
        for(i=0;i<PARTY_SIZE;i++) if(i!=gBattlerPartyIndexes[gActiveBattler] && GetMonData(&party[i],MON_DATA_HP)) { chosen=i; break; }
    }
    TournamentLog(20,gActiveBattler,chosen,0);
    return chosen;
}
static void TournamentStart(void)
{
    u32 side,i;
    memset(sHistory,0,sizeof(sHistory));
    memset(sLastHp,0,sizeof(sLastHp));memset(sLastSpecies,0,sizeof(sLastSpecies));sLastTurn=0xFFFFFFFF;
    for(side=0;side<2;side++) {
        u16 trainer=side ? gTournamentControl.trainer_b:gTournamentControl.trainer_a;
        for(i=0;i<MAX_TRAINER_ITEMS;i++) if(gTrainers[trainer].items[i]) sHistory[side].trainerItems[sHistory[side].itemsNo++]=gTrainers[trainer].items[i];
    }
    gTrainerBattleOpponent_A=gTournamentControl.trainer_b;
    gBattleTypeFlags=BATTLE_TYPE_TRAINER;
    gBattleOutcome=0;
    gSaveBlock2Ptr->optionsBattleStyle=1; /* SET: no player-only shift prompt. */
    TournamentLog(1,0xFFFFFFFF,gTournamentControl.trainer_a,gTournamentControl.trainer_b);
    SetMainCallback1(NULL);
    SetMainCallback2(CB2_InitBattle);
}
bool8 TournamentTick(void)
{
    u32 side;
    if(!TournamentActive()) return FALSE;
    gTournamentControl.turns=gBattleResults.battleTurnCounter;
    if(sLastTurn!=gBattleResults.battleTurnCounter) { sLastTurn=gBattleResults.battleTurnCounter;TournamentLog(3,0xFFFFFFFF,sLastTurn,0); }
    for(side=0;side<2;side++) {
        if(sLastSpecies[side]!=gBattleMons[side].species && gBattleMons[side].species) { sLastSpecies[side]=gBattleMons[side].species;TournamentLog(2,side,sLastSpecies[side],gBattlerPartyIndexes[side]); }
        if(sLastHp[side] && !gBattleMons[side].hp) TournamentLog(19,side,gBattleMons[side].species,0);
        sLastHp[side]=gBattleMons[side].hp;
    }
    if(gTournamentControl.event_overflow) { gTournamentControl.error_code=2;gTournamentControl.phase=TOURNAMENT_ERROR;SetMainCallback1(NULL);SetMainCallback2(TournamentPoll);return TRUE; }
    if(!gBattleOutcome) return FALSE;
    gTournamentControl.outcome=gBattleOutcome==B_OUTCOME_WON ? 1 : gBattleOutcome==B_OUTCOME_LOST ? 2 : gBattleOutcome==B_OUTCOME_DREW ? 3 : 5;
    gTournamentControl.rng_final=gRngValue;
    memcpy(sFinal,gPlayerParty,sizeof(gPlayerParty));memcpy(sFinal+PARTY_SIZE,gEnemyParty,sizeof(gEnemyParty));
    gTournamentControl.final_party_address=(u32)sFinal;gTournamentControl.final_party_size=sizeof(sFinal);
    TournamentLog(21,0xFFFFFFFF,gBattleOutcome,gBattleResults.battleTurnCounter);
    gTournamentControl.phase=TOURNAMENT_RESULT_READY;
    SetMainCallback1(NULL);SetMainCallback2(TournamentPoll);return TRUE;
}

void TournamentClearHistory(u8 battler)
{
    memset(&sHistory[0].usedMoves[battler],0,sizeof(sHistory[0].usedMoves[battler]));
    memset(&sHistory[1].usedMoves[battler],0,sizeof(sHistory[1].usedMoves[battler]));
}
