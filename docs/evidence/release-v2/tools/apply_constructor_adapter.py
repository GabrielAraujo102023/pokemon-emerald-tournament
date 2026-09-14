"""Apply the construction-only adapter to the disposable build copy, never upstream."""
from pathlib import Path
import shutil
ROOT=Path(__file__).resolve().parents[1]
DEST=ROOT/'build/pokeemerald'


def replace(path, old, new):
    text=path.read_text()
    if new in text:return
    if text.count(old)!=1:raise RuntimeError(f'Patch anchor not unique: {path}')
    path.write_text(text.replace(old,new))


def main():
    shutil.copyfile(ROOT/'adapter/tournament_protocol.h',DEST/'include/tournament_protocol.h')
    shutil.copyfile(ROOT/'adapter/tournament_adapter.c',DEST/'src/tournament_adapter.c')
    replace(DEST/'src/intro.c','        InitHeap(gHeap, HEAP_SIZE);\n    }\n}\n\nvoid CB2_InitCopyrightScreenAfterTitleScreen', '        InitHeap(gHeap, HEAP_SIZE);\n#ifdef TOURNAMENT_MODE\n        { extern void CB2_NewGame(void); SetMainCallback2(CB2_NewGame); }\n#endif\n    }\n}\n\nvoid CB2_InitCopyrightScreenAfterTitleScreen')
    replace(DEST/'src/overworld.c','    SetMainCallback2(CB2_Overworld);\n}\n\nvoid CB2_WhiteOut', '    SetMainCallback2(CB2_Overworld);\n#ifdef TOURNAMENT_MODE\n    { extern void TournamentReady(void); TournamentReady(); }\n#endif\n}\n\nvoid CB2_WhiteOut')
    replace(DEST/'src/battle_main.c','        if (firstTrainer == TRUE)\n            ZeroEnemyPartyMons();', '        if (firstTrainer == TRUE)\n        {\n#ifdef TOURNAMENT_MODE\n            memset(party, 0, sizeof(struct Pokemon) * PARTY_SIZE);\n#else\n            ZeroEnemyPartyMons();\n#endif\n        }')
    replace(DEST/'src/battle_main.c','static void UNUSED HBlankCB_Battle(void)', '#ifdef TOURNAMENT_MODE\nu8 TournamentCreateParty(struct Pokemon *party, u16 trainer) { return CreateNPCTrainerParty(party, trainer, TRUE); }\n#endif\n\nstatic void UNUSED HBlankCB_Battle(void)')
    replace(DEST/'src/random.c', '    gRngValue = ISO_RANDOMIZE1(gRngValue);\n    sRandCount++;', '#ifdef TOURNAMENT_MODE\n    u32 before = gRngValue;\n    extern void TournamentRecordRandom(u32 before, u32 after);\n#endif\n    gRngValue = ISO_RANDOMIZE1(gRngValue);\n#ifdef TOURNAMENT_MODE\n    TournamentRecordRandom(before, gRngValue);\n#endif\n    sRandCount++;')
    config=DEST/'include/config.h'
    if '#define TOURNAMENT_MODE 1' not in config.read_text():config.write_text('#define TOURNAMENT_MODE 1\n'+config.read_text())
    print('Construction adapter applied to',DEST)

if __name__=='__main__':main()
