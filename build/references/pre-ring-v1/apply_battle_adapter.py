"""Guarded battle overlay applied only to disposable build sources."""
import shutil
from apply_constructor_adapter import ROOT,DEST,replace,main as constructor

def main():
    constructor()
    shutil.copyfile(ROOT/'adapter/tournament_battle.h',DEST/'include/tournament_battle.h')
    names=['battle_main','battle_controller_player','battle_controller_opponent','battle_ai_script_commands','battle_ai_switch_items','battle_util','pokemon','battle_script_commands','battle_message']
    for name in names:
        p=DEST/f'src/{name}.c'
        replace(p,'#include "global.h"','#include "global.h"\n#ifdef TOURNAMENT_MODE\n#include "tournament_battle.h"\n#endif')
    def patch(name,old,new):replace(DEST/f'src/{name}.c',old,new)
    def entry(name,sig,code):patch(name,sig+'\n{',sig+'\n{\n#ifdef TOURNAMENT_MODE\n'+code+'\n#endif')
    entry('battle_main','void BattleMainCB2(void)','    if (TournamentTick()) return;')
    patch('battle_main','    if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)))\n    {','    if (\n#ifdef TOURNAMENT_MODE\n        !TournamentActive() &&\n#endif\n        !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)))\n    {')
    patch('battle_main','        AdjustFriendship(&gPlayerParty[i], FRIENDSHIP_EVENT_LEAGUE_BATTLE);','#ifdef TOURNAMENT_MODE\n        if (!TournamentActive())\n#endif\n        AdjustFriendship(&gPlayerParty[i], FRIENDSHIP_EVENT_LEAGUE_BATTLE);')
    p=DEST/'src/battle_main.c';s=p.read_text();s=s.replace('        && FlagGet(FLAG_BADGE03_GET)\n','        && FlagGet(FLAG_BADGE03_GET)\n#ifdef TOURNAMENT_MODE\n        && !TournamentActive()\n#endif\n') if '&& !TournamentActive()' not in s else s;p.write_text(s)
    for who in ['Player','Opponent']:
        name='battle_controller_'+who.lower();done=who+'BufferExecCompleted(); return;'
        entry(name,f'static void {who}HandleChooseAction(void)',f'    if (TournamentActive()) {{ TournamentAIAction(); {done} }}')
        entry(name,f'static void {who}HandleChooseMove(void)',f'    if (TournamentActive()) {{ u8 move=TournamentAIMove(); BtlController_EmitTwoReturnValues(B_COMM_TO_ENGINE, B_ACTION_EXEC_SCRIPT, move | (gBattlerTarget << 8)); {done} }}')
        entry(name,f'static void {who}HandleChoosePokemon(void)',f'    if (TournamentActive()) {{ u8 mon=TournamentReplacement(); gBattleStruct->monToSwitchIntoId[gActiveBattler]=mon; BtlController_EmitChosenMonReturnValue(B_COMM_TO_ENGINE, mon, NULL); {done} }}')
        entry(name,f'static void {who}HandleChooseItem(void)',f'    if (TournamentActive()) {{ BtlController_EmitOneReturnValue(B_COMM_TO_ENGINE, gBattleStruct->chosenItem[TournamentItemIndex(gActiveBattler)*2]); {done} }}')
    patch('battle_ai_script_commands','        AI_THINKING_STRUCT->aiFlags |= AI_SCRIPT_DOUBLE_BATTLE; // act smart in doubles and don\'t attack your partner','        AI_THINKING_STRUCT->aiFlags |= AI_SCRIPT_DOUBLE_BATTLE; // act smart in doubles and don\'t attack your partner\n#ifdef TOURNAMENT_MODE\n    if (TournamentActive()) AI_THINKING_STRUCT->aiFlags=gTrainers[TournamentTrainer(gActiveBattler)].aiFlags;\n#endif')
    entry('battle_ai_script_commands','void ClearBattlerMoveHistory(u8 battler)','    if (TournamentActive()) TournamentClearHistory(battler);')
    for name in ['battle_ai_switch_items','battle_util']:
        p=DEST/f'src/{name}.c';s=p.read_text()
        if 'TournamentItemIndex(' in s: continue
        lines=s.splitlines(True)
        for i,line in enumerate(lines):
            if 'gBattleStruct->AI_item' in line or 'gBattleStruct->chosenItem' in line:
                new=line.replace('gActiveBattler / 2','TournamentItemIndex(gActiveBattler)').replace('(gBattlerAttacker >> 1)','TournamentItemIndex(gBattlerAttacker)').replace('gBattlerAttacker / 2','TournamentItemIndex(gBattlerAttacker)')
                if new!=line:lines[i]='#ifdef TOURNAMENT_MODE\n'+new+'#else\n'+line+'#endif\n'
        p.write_text(''.join(lines))
    patch('battle_util','    else if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)\n    {','    else if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER\n#ifdef TOURNAMENT_MODE\n        && !TournamentActive()\n#endif\n    )\n    {')
    entry('battle_util','u8 IsMonDisobedient(void)','    if (TournamentActive()) return 0;')
    entry('pokemon','static bool8 ShouldGetStatBadgeBoost(u16 badgeFlag, u8 battler)','    if (TournamentActive()) return FALSE;')
    entry('pokemon','void AdjustFriendship(struct Pokemon *mon, u8 event)','    if (TournamentActive()) return;')
    patch('battle_script_commands','        if (GetBattlerSide(gBattlerFainted) != B_SIDE_OPPONENT || (gBattleTypeFlags &','        if (\n#ifdef TOURNAMENT_MODE\n            TournamentActive() ||\n#endif\n            GetBattlerSide(gBattlerFainted) != B_SIDE_OPPONENT || (gBattleTypeFlags &')
    patch('battle_script_commands', '    PokemonUseItemEffects(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]], gLastUsedItem, gBattlerPartyIndexes[gBattlerAttacker], 0, TRUE);', '#ifdef TOURNAMENT_MODE\n    if (TournamentActive() && GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)\n        PokemonUseItemEffects(&gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]], gLastUsedItem, gBattlerPartyIndexes[gBattlerAttacker], 0, TRUE);\n    else\n#endif\n    PokemonUseItemEffects(&gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]], gLastUsedItem, gBattlerPartyIndexes[gBattlerAttacker], 0, TRUE);')
    entry('battle_script_commands','static void Cmd_attackstring(void)','    if (TournamentActive()) TournamentLog(7,gBattlerAttacker,gCurrentMove,gBattlerTarget);')
    patch('battle_message','        gTextFlags.autoScroll = FALSE;','        gTextFlags.autoScroll = FALSE;\n#ifdef TOURNAMENT_MODE\n    if (TournamentActive()) gTextFlags.autoScroll = TRUE;\n#endif')

if __name__=='__main__':main()
