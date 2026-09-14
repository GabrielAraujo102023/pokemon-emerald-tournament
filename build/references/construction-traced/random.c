#include "global.h"
#include "random.h"

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
COMMON_DATA u32 gRngValue = 0;
COMMON_DATA u32 gRng2Value = 0;

u16 Random(void)
{
#ifdef TOURNAMENT_MODE
    u32 before = gRngValue;
    extern void TournamentRecordRandom(u32 before, u32 after);
#endif
    gRngValue = ISO_RANDOMIZE1(gRngValue);
#ifdef TOURNAMENT_MODE
    TournamentRecordRandom(before, gRngValue);
#endif
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}
