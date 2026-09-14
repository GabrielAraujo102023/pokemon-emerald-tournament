#ifndef TOURNAMENT_BATTLE_H
#define TOURNAMENT_BATTLE_H
#include "tournament_protocol.h"
bool8 TournamentActive(void);
u16 TournamentTrainer(u8 battler);
u8 TournamentItemIndex(u8 battler);
void TournamentAIAction(void);
u8 TournamentAIMove(void);
u8 TournamentReplacement(void);
void TournamentLog(u32 kind,u32 battler,u32 a,u32 b);
bool8 TournamentTick(void);
void TournamentClearHistory(u8 battler);
#endif
