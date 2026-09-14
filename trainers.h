#include "opponents.h"
#include "items.h"
#include <map>
#include <string>
#include "trainer_types.h"
#include "trainer_parties.cpp"
#include "battle_ai.h"

struct Trainer
{
    /*0x01*/ int trainerClass;
    /*0x04*/ std::string trainerName[20 + 1];
    /*0x10*/ int items[10];
    /*0x18*/ bool doubleBattle;
    /*0x1C*/ int aiFlags;
    /*0x24*/ Party_Member party[6];
};


const struct Trainer gTrainers[] = {
    [TRAINER_SAWYER_1] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "SAWYER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sawyer1,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout1,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout2,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout3,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout4,
    },

    [TRAINER_GRUNT_SEAFLOOR_CAVERN_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSeafloorCavern1,
    },

    [TRAINER_GRUNT_SEAFLOOR_CAVERN_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSeafloorCavern2,
    },

    [TRAINER_GRUNT_SEAFLOOR_CAVERN_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSeafloorCavern3,
    },

    [TRAINER_GABRIELLE_1] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "GABRIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gabrielle1,
    },

    [TRAINER_GRUNT_PETALBURG_WOODS] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntPetalburgWoods,
    },

    [TRAINER_MARCEL] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "MARCEL",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Marcel,
    },

    [TRAINER_ALBERTO] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ALBERTO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alberto,
    },

    [TRAINER_ED] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "ED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ed,
    },

    [TRAINER_GRUNT_SEAFLOOR_CAVERN_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSeafloorCavern4,
    },

    [TRAINER_DECLAN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DECLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Declan,
    },

    [TRAINER_GRUNT_RUSTURF_TUNNEL] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntRusturfTunnel,
    },

    [TRAINER_GRUNT_WEATHER_INST_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntWeatherInst1,
    },

    [TRAINER_GRUNT_WEATHER_INST_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntWeatherInst2,
    },

    [TRAINER_GRUNT_WEATHER_INST_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntWeatherInst3,
    },

    [TRAINER_GRUNT_MUSEUM_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMuseum1,
    },

    [TRAINER_GRUNT_MUSEUM_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMuseum2,
    },

    [TRAINER_GRUNT_SPACE_CENTER_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter1,
    },

    [TRAINER_GRUNT_MT_PYRE_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtPyre1,
    },

    [TRAINER_GRUNT_MT_PYRE_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtPyre2,
    },

    [TRAINER_GRUNT_MT_PYRE_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtPyre3,
    },

    [TRAINER_GRUNT_WEATHER_INST_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntWeatherInst4,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_5] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout5,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_6] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout6,
    },

    [TRAINER_FREDRICK] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "FREDRICK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Fredrick,
    },

    [TRAINER_MATT] =
    {
        .trainerClass = TRAINER_CLASS_AQUA_ADMIN,
        
        
        .trainerName = "MATT",
        .items = {ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Matt,
    },

    [TRAINER_ZANDER] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "ZANDER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Zander,
    },

    [TRAINER_SHELLY_WEATHER_INSTITUTE] =
    {
        .trainerClass = TRAINER_CLASS_AQUA_ADMIN,
        
        
        .trainerName = "SHELLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_ShellyWeatherInstitute,
    },

    [TRAINER_SHELLY_SEAFLOOR_CAVERN] =
    {
        .trainerClass = TRAINER_CLASS_AQUA_ADMIN,
        
        
        .trainerName = "SHELLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_ShellySeafloorCavern,
    },

    [TRAINER_ARCHIE] =
    {
        .trainerClass = TRAINER_CLASS_AQUA_LEADER,
        
        
        .trainerName = "ARCHIE",
        .items = {ITEM_SUPER_POTION, ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Archie,
    },

    [TRAINER_LEAH] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "LEAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Leah,
    },

    [TRAINER_DAISY] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "DAISY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Daisy,
    },

    [TRAINER_ROSE_1] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "ROSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rose1,
    },

    [TRAINER_FELIX] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "FELIX",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Felix,
    },

    [TRAINER_VIOLET] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "VIOLET",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Violet,
    },

    [TRAINER_ROSE_2] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "ROSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rose2,
    },

    [TRAINER_ROSE_3] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "ROSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rose3,
    },

    [TRAINER_ROSE_4] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "ROSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rose4,
    },

    [TRAINER_ROSE_5] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "ROSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rose5,
    },

    [TRAINER_DUSTY_1] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "DUSTY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dusty1,
    },

    [TRAINER_CHIP] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "CHIP",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chip,
    },

    [TRAINER_FOSTER] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "FOSTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Foster,
    },

    [TRAINER_DUSTY_2] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "DUSTY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dusty2,
    },

    [TRAINER_DUSTY_3] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "DUSTY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dusty3,
    },

    [TRAINER_DUSTY_4] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "DUSTY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dusty4,
    },

    [TRAINER_DUSTY_5] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "DUSTY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dusty5,
    },

    [TRAINER_GABBY_AND_TY_1] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy1,
    },

    [TRAINER_GABBY_AND_TY_2] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy2,
    },

    [TRAINER_GABBY_AND_TY_3] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy3,
    },

    [TRAINER_GABBY_AND_TY_4] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy4,
    },

    [TRAINER_GABBY_AND_TY_5] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy5,
    },

    [TRAINER_GABBY_AND_TY_6] =
    {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        
        
        .trainerName = "GABBY & TY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GabbyAndTy6,
    },

    [TRAINER_LOLA_1] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "LOLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lola1,
    },

    [TRAINER_AUSTINA] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "AUSTINA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Austina,
    },

    [TRAINER_GWEN] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "GWEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gwen,
    },

    [TRAINER_LOLA_2] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "LOLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lola2,
    },

    [TRAINER_LOLA_3] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "LOLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lola3,
    },

    [TRAINER_LOLA_4] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "LOLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lola4,
    },

    [TRAINER_LOLA_5] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "LOLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lola5,
    },

    [TRAINER_RICKY_1] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "RICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ricky1,
    },

    [TRAINER_SIMON] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "SIMON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Simon,
    },

    [TRAINER_CHARLIE] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "CHARLIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Charlie,
    },

    [TRAINER_RICKY_2] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "RICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ricky2,
    },

    [TRAINER_RICKY_3] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "RICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ricky3,
    },

    [TRAINER_RICKY_4] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "RICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ricky4,
    },

    [TRAINER_RICKY_5] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "RICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ricky5,
    },

    [TRAINER_RANDALL] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "RANDALL",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Randall,
    },

    [TRAINER_PARKER] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "PARKER",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Parker,
    },

    [TRAINER_GEORGE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "GEORGE",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_George,
    },

    [TRAINER_BERKE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BERKE",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Berke,
    },

    [TRAINER_BRAXTON] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BRAXTON",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Braxton,
    },

    [TRAINER_VINCENT] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "VINCENT",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Vincent,
    },

    [TRAINER_LEROY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "LEROY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Leroy,
    },

    [TRAINER_WILTON_1] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WILTON",
        .items = {ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wilton1,
    },

    [TRAINER_EDGAR] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "EDGAR",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Edgar,
    },

    [TRAINER_ALBERT] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "ALBERT",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Albert,
    },

    [TRAINER_SAMUEL] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "SAMUEL",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Samuel,
    },

    [TRAINER_VITO] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "VITO",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Vito,
    },

    [TRAINER_OWEN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "OWEN",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Owen,
    },

    [TRAINER_WILTON_2] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WILTON",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wilton2,
    },

    [TRAINER_WILTON_3] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WILTON",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wilton3,
    },

    [TRAINER_WILTON_4] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WILTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wilton4,
    },

    [TRAINER_WILTON_5] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WILTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wilton5,
    },

    [TRAINER_WARREN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WARREN",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Warren,
    },

    [TRAINER_MARY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "MARY",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Mary,
    },

    [TRAINER_ALEXIA] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "ALEXIA",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Alexia,
    },

    [TRAINER_JODY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "JODY",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Jody,
    },

    [TRAINER_WENDY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "WENDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Wendy,
    },

    [TRAINER_KEIRA] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "KEIRA",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Keira,
    },

    [TRAINER_BROOKE_1] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BROOKE",
        .items = {ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brooke1,
    },

    [TRAINER_JENNIFER] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "JENNIFER",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jennifer,
    },

    [TRAINER_HOPE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "HOPE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Hope,
    },

    [TRAINER_SHANNON] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "SHANNON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shannon,
    },

    [TRAINER_MICHELLE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "MICHELLE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Michelle,
    },

    [TRAINER_CAROLINE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CAROLINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Caroline,
    },

    [TRAINER_JULIE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "JULIE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Julie,
    },

    [TRAINER_BROOKE_2] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BROOKE",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brooke2,
    },

    [TRAINER_BROOKE_3] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BROOKE",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brooke3,
    },

    [TRAINER_BROOKE_4] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BROOKE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brooke4,
    },

    [TRAINER_BROOKE_5] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "BROOKE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brooke5,
    },

    [TRAINER_PATRICIA] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "PATRICIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Patricia,
    },

    [TRAINER_KINDRA] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "KINDRA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kindra,
    },

    [TRAINER_TAMMY] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "TAMMY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tammy,
    },

    [TRAINER_VALERIE_1] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "VALERIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Valerie1,
    },

    [TRAINER_TASHA] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "TASHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tasha,
    },

    [TRAINER_VALERIE_2] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "VALERIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Valerie2,
    },

    [TRAINER_VALERIE_3] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "VALERIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Valerie3,
    },

    [TRAINER_VALERIE_4] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "VALERIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Valerie4,
    },

    [TRAINER_VALERIE_5] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "VALERIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Valerie5,
    },

    [TRAINER_CINDY_1] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy1,
    },

    [TRAINER_DAPHNE] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "DAPHNE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Daphne,
    },

    [TRAINER_GRUNT_SPACE_CENTER_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter2,
    },

    [TRAINER_CINDY_2] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy2,
    },

    [TRAINER_BRIANNA] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "BRIANNA",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brianna,
    },

    [TRAINER_NAOMI] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "NAOMI",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Naomi,
    },

    [TRAINER_CINDY_3] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy3,
    },

    [TRAINER_CINDY_4] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy4,
    },

    [TRAINER_CINDY_5] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy5,
    },

    [TRAINER_CINDY_6] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "CINDY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cindy6,
    },

    [TRAINER_MELISSA] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "MELISSA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Melissa,
    },

    [TRAINER_SHEILA] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "SHEILA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sheila,
    },

    [TRAINER_SHIRLEY] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "SHIRLEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Shirley,
    },

    [TRAINER_JESSICA_1] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JESSICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jessica1,
    },

    [TRAINER_CONNIE] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "CONNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Connie,
    },

    [TRAINER_BRIDGET] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "BRIDGET",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bridget,
    },

    [TRAINER_OLIVIA] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "OLIVIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Olivia,
    },

    [TRAINER_TIFFANY] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "TIFFANY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tiffany,
    },

    [TRAINER_JESSICA_2] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JESSICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jessica2,
    },

    [TRAINER_JESSICA_3] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JESSICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jessica3,
    },

    [TRAINER_JESSICA_4] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JESSICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jessica4,
    },

    [TRAINER_JESSICA_5] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JESSICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jessica5,
    },

    [TRAINER_WINSTON_1] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "WINSTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Winston1,
    },

    [TRAINER_MOLLIE] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "MOLLIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Mollie,
    },

    [TRAINER_GARRET] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "GARRET",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Garret,
    },

    [TRAINER_WINSTON_2] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "WINSTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Winston2,
    },

    [TRAINER_WINSTON_3] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "WINSTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Winston3,
    },

    [TRAINER_WINSTON_4] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "WINSTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Winston4,
    },

    [TRAINER_WINSTON_5] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "WINSTON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Winston5,
    },

    [TRAINER_STEVE_1] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "STEVE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Steve1,
    },

    [TRAINER_THALIA_1] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "THALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thalia1,
    },

    [TRAINER_MARK] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "MARK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Mark,
    },

    [TRAINER_GRUNT_MT_CHIMNEY_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtChimney1,
    },

    [TRAINER_STEVE_2] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "STEVE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Steve2,
    },

    [TRAINER_STEVE_3] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "STEVE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Steve3,
    },

    [TRAINER_STEVE_4] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "STEVE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Steve4,
    },

    [TRAINER_STEVE_5] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "STEVE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Steve5,
    },

    [TRAINER_LUIS] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "LUIS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Luis,
    },

    [TRAINER_DOMINIK] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DOMINIK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dominik,
    },

    [TRAINER_DOUGLAS] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DOUGLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Douglas,
    },

    [TRAINER_DARRIN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DARRIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Darrin,
    },

    [TRAINER_TONY_1] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "TONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tony1,
    },

    [TRAINER_JEROME] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "JEROME",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerome,
    },

    [TRAINER_MATTHEW] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "MATTHEW",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Matthew,
    },

    [TRAINER_DAVID] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DAVID",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_David,
    },

    [TRAINER_SPENCER] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "SPENCER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Spencer,
    },

    [TRAINER_ROLAND] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "ROLAND",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Roland,
    },

    [TRAINER_NOLEN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "NOLEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nolen,
    },

    [TRAINER_STAN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "STAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Stan,
    },

    [TRAINER_BARRY] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "BARRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Barry,
    },

    [TRAINER_DEAN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DEAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dean,
    },

    [TRAINER_RODNEY] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "RODNEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rodney,
    },

    [TRAINER_RICHARD] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "RICHARD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Richard,
    },

    [TRAINER_HERMAN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "HERMAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Herman,
    },

    [TRAINER_SANTIAGO] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "SANTIAGO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Santiago,
    },

    [TRAINER_GILBERT] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "GILBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gilbert,
    },

    [TRAINER_FRANKLIN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "FRANKLIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Franklin,
    },

    [TRAINER_KEVIN] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "KEVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kevin,
    },

    [TRAINER_JACK] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "JACK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jack,
    },

    [TRAINER_DUDLEY] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "DUDLEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dudley,
    },

    [TRAINER_CHAD] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "CHAD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chad,
    },

    [TRAINER_TONY_2] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "TONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tony2,
    },

    [TRAINER_TONY_3] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "TONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tony3,
    },

    [TRAINER_TONY_4] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "TONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tony4,
    },

    [TRAINER_TONY_5] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "TONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tony5,
    },

    [TRAINER_TAKAO] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "TAKAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Takao,
    },

    [TRAINER_HITOSHI] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "HITOSHI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hitoshi,
    },

    [TRAINER_KIYO] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KIYO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kiyo,
    },

    [TRAINER_KOICHI] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOICHI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koichi,
    },

    [TRAINER_NOB_1] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "NOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nob1,
    },

    [TRAINER_NOB_2] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "NOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nob2,
    },

    [TRAINER_NOB_3] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "NOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nob3,
    },

    [TRAINER_NOB_4] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "NOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nob4,
    },

    [TRAINER_NOB_5] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "NOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nob5,
    },

    [TRAINER_YUJI] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "YUJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Yuji,
    },

    [TRAINER_DAISUKE] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "DAISUKE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Daisuke,
    },

    [TRAINER_ATSUSHI] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "ATSUSHI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Atsushi,
    },

    [TRAINER_KIRK] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "KIRK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kirk,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_7] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout7,
    },

    [TRAINER_GRUNT_AQUA_HIDEOUT_8] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntAquaHideout8,
    },

    [TRAINER_SHAWN] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "SHAWN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Shawn,
    },

    [TRAINER_FERNANDO_1] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FERNANDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fernando1,
    },

    [TRAINER_DALTON_1] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "DALTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dalton1,
    },

    [TRAINER_DALTON_2] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "DALTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dalton2,
    },

    [TRAINER_DALTON_3] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "DALTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dalton3,
    },

    [TRAINER_DALTON_4] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "DALTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dalton4,
    },

    [TRAINER_DALTON_5] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "DALTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dalton5,
    },

    [TRAINER_COLE] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "COLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cole,
    },

    [TRAINER_JEFF] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "JEFF",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeff,
    },

    [TRAINER_AXLE] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "AXLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Axle,
    },

    [TRAINER_JACE] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "JACE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jace,
    },

    [TRAINER_KEEGAN] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "KEEGAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Keegan,
    },

    [TRAINER_BERNIE_1] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BERNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bernie1,
    },

    [TRAINER_BERNIE_2] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BERNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bernie2,
    },

    [TRAINER_BERNIE_3] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BERNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bernie3,
    },

    [TRAINER_BERNIE_4] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BERNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bernie4,
    },

    [TRAINER_BERNIE_5] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BERNIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bernie5,
    },

    [TRAINER_DREW] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "DREW",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Drew,
    },

    [TRAINER_BEAU] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "BEAU",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Beau,
    },

    [TRAINER_LARRY] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "LARRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Larry,
    },

    [TRAINER_SHANE] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "SHANE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Shane,
    },

    [TRAINER_JUSTIN] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "JUSTIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Justin,
    },

    [TRAINER_ETHAN_1] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "ETHAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ethan1,
    },

    [TRAINER_AUTUMN] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "AUTUMN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Autumn,
    },

    [TRAINER_TRAVIS] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "TRAVIS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Travis,
    },

    [TRAINER_ETHAN_2] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "ETHAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ethan2,
    },

    [TRAINER_ETHAN_3] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "ETHAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ethan3,
    },

    [TRAINER_ETHAN_4] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "ETHAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ethan4,
    },

    [TRAINER_ETHAN_5] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "ETHAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ethan5,
    },

    [TRAINER_BRENT] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "BRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brent,
    },

    [TRAINER_DONALD] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "DONALD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Donald,
    },

    [TRAINER_TAYLOR] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "TAYLOR",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Taylor,
    },

    [TRAINER_JEFFREY_1] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "JEFFREY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeffrey1,
    },

    [TRAINER_DEREK] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "DEREK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Derek,
    },

    [TRAINER_JEFFREY_2] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "JEFFREY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeffrey2,
    },

    [TRAINER_JEFFREY_3] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "JEFFREY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeffrey3,
    },

    [TRAINER_JEFFREY_4] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "JEFFREY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeffrey4,
    },

    [TRAINER_JEFFREY_5] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "JEFFREY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jeffrey5,
    },

    [TRAINER_EDWARD] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "EDWARD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edward,
    },

    [TRAINER_PRESTON] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "PRESTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Preston,
    },

    [TRAINER_VIRGIL] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "VIRGIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Virgil,
    },

    [TRAINER_BLAKE] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "BLAKE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Blake,
    },

    [TRAINER_WILLIAM] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "WILLIAM",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_William,
    },

    [TRAINER_JOSHUA] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JOSHUA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Joshua,
    },

    [TRAINER_CAMERON_1] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CAMERON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cameron1,
    },

    [TRAINER_CAMERON_2] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CAMERON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cameron2,
    },

    [TRAINER_CAMERON_3] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CAMERON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cameron3,
    },

    [TRAINER_CAMERON_4] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CAMERON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cameron4,
    },

    [TRAINER_CAMERON_5] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CAMERON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cameron5,
    },

    [TRAINER_JACLYN] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACLYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jaclyn,
    },

    [TRAINER_HANNAH] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "HANNAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hannah,
    },

    [TRAINER_SAMANTHA] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "SAMANTHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Samantha,
    },

    [TRAINER_MAURA] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "MAURA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maura,
    },

    [TRAINER_KAYLA] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "KAYLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kayla,
    },

    [TRAINER_ALEXIS] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "ALEXIS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alexis,
    },

    [TRAINER_JACKI_1] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacki1,
    },

    [TRAINER_JACKI_2] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacki2,
    },

    [TRAINER_JACKI_3] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacki3,
    },

    [TRAINER_JACKI_4] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacki4,
    },

    [TRAINER_JACKI_5] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "JACKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacki5,
    },

    [TRAINER_WALTER_1] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "WALTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Walter1,
    },

    [TRAINER_MICAH] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "MICAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Micah,
    },

    [TRAINER_THOMAS] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "THOMAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thomas,
    },

    [TRAINER_WALTER_2] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "WALTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Walter2,
    },

    [TRAINER_WALTER_3] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "WALTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Walter3,
    },

    [TRAINER_WALTER_4] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "WALTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Walter4,
    },

    [TRAINER_WALTER_5] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "WALTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Walter5,
    },

    [TRAINER_SIDNEY] =
    {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        
        
        .trainerName = "SIDNEY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Sidney,
    },

    [TRAINER_PHOEBE] =
    {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        
        
        .trainerName = "PHOEBE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Phoebe,
    },

    [TRAINER_GLACIA] =
    {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        
        
        .trainerName = "GLACIA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Glacia,
    },

    [TRAINER_DRAKE] =
    {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        
        
        .trainerName = "DRAKE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Drake,
    },

    [TRAINER_ROXANNE_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "ROXANNE",
        .items = {ITEM_POTION, ITEM_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Roxanne1,
    },

    [TRAINER_BRAWLY_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "BRAWLY",
        .items = {ITEM_SUPER_POTION, ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brawly1,
    },

    [TRAINER_WATTSON_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WATTSON",
        .items = {ITEM_SUPER_POTION, ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wattson1,
    },

    [TRAINER_FLANNERY_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "FLANNERY",
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Flannery1,
    },

    [TRAINER_NORMAN_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "NORMAN",
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Norman1,
    },

    [TRAINER_WINONA_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WINONA",
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .party = sParty_Winona1,
    },

    [TRAINER_TATE_AND_LIZA_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "TATE&LIZA",
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_HYPER_POTION},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TateAndLiza1,
    },

    [TRAINER_JUAN_1] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "JUAN",
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Juan1,
    },

    [TRAINER_JERRY_1] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "JERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerry1,
    },

    [TRAINER_TED] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "TED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ted,
    },

    [TRAINER_PAUL] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "PAUL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Paul,
    },

    [TRAINER_JERRY_2] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "JERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerry2,
    },

    [TRAINER_JERRY_3] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "JERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerry3,
    },

    [TRAINER_JERRY_4] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "JERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerry4,
    },

    [TRAINER_JERRY_5] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "JERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jerry5,
    },

    [TRAINER_KAREN_1] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "KAREN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Karen1,
    },

    [TRAINER_GEORGIA] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "GEORGIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Georgia,
    },

    [TRAINER_KAREN_2] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "KAREN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Karen2,
    },

    [TRAINER_KAREN_3] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "KAREN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Karen3,
    },

    [TRAINER_KAREN_4] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "KAREN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Karen4,
    },

    [TRAINER_KAREN_5] =
    {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        
        
        .trainerName = "KAREN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Karen5,
    },

    [TRAINER_KATE_AND_JOY] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "KATE & JOY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KateAndJoy,
    },

    [TRAINER_ANNA_AND_MEG_1] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "ANNA & MEG",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AnnaAndMeg1,
    },

    [TRAINER_ANNA_AND_MEG_2] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "ANNA & MEG",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AnnaAndMeg2,
    },

    [TRAINER_ANNA_AND_MEG_3] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "ANNA & MEG",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AnnaAndMeg3,
    },

    [TRAINER_ANNA_AND_MEG_4] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "ANNA & MEG",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AnnaAndMeg4,
    },

    [TRAINER_ANNA_AND_MEG_5] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "ANNA & MEG",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AnnaAndMeg5,
    },

    [TRAINER_VICTOR] =
    {
        .trainerClass = TRAINER_CLASS_WINSTRATE,
        
        
        .trainerName = "VICTOR",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Victor,
    },

    [TRAINER_MIGUEL_1] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "MIGUEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Miguel1,
    },

    [TRAINER_COLTON] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "COLTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Colton,
    },

    [TRAINER_MIGUEL_2] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "MIGUEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Miguel2,
    },

    [TRAINER_MIGUEL_3] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "MIGUEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Miguel3,
    },

    [TRAINER_MIGUEL_4] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "MIGUEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Miguel4,
    },

    [TRAINER_MIGUEL_5] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "MIGUEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Miguel5,
    },

    [TRAINER_VICTORIA] =
    {
        .trainerClass = TRAINER_CLASS_WINSTRATE,
        
        
        .trainerName = "VICTORIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Victoria,
    },

    [TRAINER_VANESSA] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "VANESSA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Vanessa,
    },

    [TRAINER_BETHANY] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "BETHANY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bethany,
    },

    [TRAINER_ISABEL_1] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ISABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabel1,
    },

    [TRAINER_ISABEL_2] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ISABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabel2,
    },

    [TRAINER_ISABEL_3] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ISABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabel3,
    },

    [TRAINER_ISABEL_4] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ISABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabel4,
    },

    [TRAINER_ISABEL_5] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ISABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabel5,
    },

    [TRAINER_TIMOTHY_1] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "TIMOTHY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Timothy1,
    },

    [TRAINER_TIMOTHY_2] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "TIMOTHY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Timothy2,
    },

    [TRAINER_TIMOTHY_3] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "TIMOTHY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Timothy3,
    },

    [TRAINER_TIMOTHY_4] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "TIMOTHY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Timothy4,
    },

    [TRAINER_TIMOTHY_5] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "TIMOTHY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Timothy5,
    },

    [TRAINER_VICKY] =
    {
        .trainerClass = TRAINER_CLASS_WINSTRATE,
        
        
        .trainerName = "VICKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Vicky,
    },

    [TRAINER_SHELBY_1] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "SHELBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shelby1,
    },

    [TRAINER_SHELBY_2] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "SHELBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shelby2,
    },

    [TRAINER_SHELBY_3] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "SHELBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shelby3,
    },

    [TRAINER_SHELBY_4] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "SHELBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shelby4,
    },

    [TRAINER_SHELBY_5] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "SHELBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Shelby5,
    },

    [TRAINER_CALVIN_1] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "CALVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Calvin1,
    },

    [TRAINER_BILLY] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "BILLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Billy,
    },

    [TRAINER_JOSH] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "JOSH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Josh,
    },

    [TRAINER_TOMMY] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "TOMMY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tommy,
    },

    [TRAINER_JOEY] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "JOEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Joey,
    },

    [TRAINER_BEN] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "BEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ben,
    },

    [TRAINER_QUINCY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "QUINCY",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Quincy,
    },

    [TRAINER_KATELYNN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "KATELYNN",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Katelynn,
    },

    [TRAINER_JAYLEN] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "JAYLEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jaylen,
    },

    [TRAINER_DILLON] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "DILLON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dillon,
    },

    [TRAINER_CALVIN_2] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "CALVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Calvin2,
    },

    [TRAINER_CALVIN_3] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "CALVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Calvin3,
    },

    [TRAINER_CALVIN_4] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "CALVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Calvin4,
    },

    [TRAINER_CALVIN_5] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "CALVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Calvin5,
    },

    [TRAINER_EDDIE] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "EDDIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Eddie,
    },

    [TRAINER_ALLEN] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "ALLEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Allen,
    },

    [TRAINER_TIMMY] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "TIMMY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Timmy,
    },

    [TRAINER_WALLACE] =
    {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        
        
        .trainerName = "WALLACE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wallace,
    },

    [TRAINER_ANDREW] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ANDREW",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andrew,
    },

    [TRAINER_IVAN] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "IVAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ivan,
    },

    [TRAINER_CLAUDE] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "CLAUDE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Claude,
    },

    [TRAINER_ELLIOT_1] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ELLIOT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Elliot1,
    },

    [TRAINER_NED] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "NED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ned,
    },

    [TRAINER_DALE] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "DALE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dale,
    },

    [TRAINER_NOLAN] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "NOLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nolan,
    },

    [TRAINER_BARNY] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "BARNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Barny,
    },

    [TRAINER_WADE] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "WADE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Wade,
    },

    [TRAINER_CARTER] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "CARTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Carter,
    },

    [TRAINER_ELLIOT_2] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ELLIOT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Elliot2,
    },

    [TRAINER_ELLIOT_3] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ELLIOT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Elliot3,
    },

    [TRAINER_ELLIOT_4] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ELLIOT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Elliot4,
    },

    [TRAINER_ELLIOT_5] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ELLIOT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Elliot5,
    },

    [TRAINER_RONALD] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "RONALD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ronald,
    },

    [TRAINER_JACOB] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "JACOB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jacob,
    },

    [TRAINER_ANTHONY] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ANTHONY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Anthony,
    },

    [TRAINER_BENJAMIN_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "BENJAMIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benjamin1,
    },

    [TRAINER_BENJAMIN_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "BENJAMIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benjamin2,
    },

    [TRAINER_BENJAMIN_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "BENJAMIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benjamin3,
    },

    [TRAINER_BENJAMIN_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "BENJAMIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benjamin4,
    },

    [TRAINER_BENJAMIN_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "BENJAMIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benjamin5,
    },

    [TRAINER_ABIGAIL_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ABIGAIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Abigail1,
    },

    [TRAINER_JASMINE] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "JASMINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jasmine,
    },

    [TRAINER_ABIGAIL_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ABIGAIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Abigail2,
    },

    [TRAINER_ABIGAIL_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ABIGAIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Abigail3,
    },

    [TRAINER_ABIGAIL_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ABIGAIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Abigail4,
    },

    [TRAINER_ABIGAIL_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ABIGAIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Abigail5,
    },

    [TRAINER_DYLAN_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DYLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dylan1,
    },

    [TRAINER_DYLAN_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DYLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dylan2,
    },

    [TRAINER_DYLAN_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DYLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dylan3,
    },

    [TRAINER_DYLAN_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DYLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dylan4,
    },

    [TRAINER_DYLAN_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DYLAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dylan5,
    },

    [TRAINER_MARIA_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MARIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maria1,
    },

    [TRAINER_MARIA_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MARIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maria2,
    },

    [TRAINER_MARIA_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MARIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maria3,
    },

    [TRAINER_MARIA_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MARIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maria4,
    },

    [TRAINER_MARIA_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MARIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Maria5,
    },

    [TRAINER_CAMDEN] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "CAMDEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Camden,
    },

    [TRAINER_DEMETRIUS] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "DEMETRIUS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Demetrius,
    },

    [TRAINER_ISAIAH_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISAIAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaiah1,
    },

    [TRAINER_PABLO_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "PABLO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pablo1,
    },

    [TRAINER_CHASE] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "CHASE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chase,
    },

    [TRAINER_ISAIAH_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISAIAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaiah2,
    },

    [TRAINER_ISAIAH_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISAIAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaiah3,
    },

    [TRAINER_ISAIAH_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISAIAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaiah4,
    },

    [TRAINER_ISAIAH_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISAIAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaiah5,
    },

    [TRAINER_ISOBEL] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISOBEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isobel,
    },

    [TRAINER_DONNY] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "DONNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Donny,
    },

    [TRAINER_TALIA] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "TALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Talia,
    },

    [TRAINER_KATELYN_1] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KATELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katelyn1,
    },

    [TRAINER_ALLISON] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ALLISON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Allison,
    },

    [TRAINER_KATELYN_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KATELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katelyn2,
    },

    [TRAINER_KATELYN_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KATELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katelyn3,
    },

    [TRAINER_KATELYN_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KATELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katelyn4,
    },

    [TRAINER_KATELYN_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KATELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katelyn5,
    },

    [TRAINER_NICOLAS_1] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "NICOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicolas1,
    },

    [TRAINER_NICOLAS_2] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "NICOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicolas2,
    },

    [TRAINER_NICOLAS_3] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "NICOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicolas3,
    },

    [TRAINER_NICOLAS_4] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "NICOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicolas4,
    },

    [TRAINER_NICOLAS_5] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "NICOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicolas5,
    },

    [TRAINER_AARON] =
    {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        
        
        .trainerName = "AARON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Aaron,
    },

    [TRAINER_PERRY] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "PERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Perry,
    },

    [TRAINER_HUGH] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "HUGH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hugh,
    },

    [TRAINER_PHIL] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "PHIL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Phil,
    },

    [TRAINER_JARED] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "JARED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jared,
    },

    [TRAINER_HUMBERTO] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "HUMBERTO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Humberto,
    },

    [TRAINER_PRESLEY] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "PRESLEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Presley,
    },

    [TRAINER_EDWARDO] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "EDWARDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwardo,
    },

    [TRAINER_COLIN] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "COLIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Colin,
    },

    [TRAINER_ROBERT_1] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ROBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robert1,
    },

    [TRAINER_BENNY] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "BENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Benny,
    },

    [TRAINER_CHESTER] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "CHESTER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chester,
    },

    [TRAINER_ROBERT_2] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ROBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robert2,
    },

    [TRAINER_ROBERT_3] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ROBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robert3,
    },

    [TRAINER_ROBERT_4] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ROBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robert4,
    },

    [TRAINER_ROBERT_5] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ROBERT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robert5,
    },

    [TRAINER_ALEX] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ALEX",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alex,
    },

    [TRAINER_BECK] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "BECK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Beck,
    },

    [TRAINER_YASU] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "YASU",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Yasu,
    },

    [TRAINER_TAKASHI] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "TAKASHI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Takashi,
    },

    [TRAINER_DIANNE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "DIANNE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Dianne,
    },

    [TRAINER_JANI] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "JANI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Jani,
    },

    [TRAINER_LAO_1] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lao1,
    },

    [TRAINER_LUNG] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LUNG",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lung,
    },

    [TRAINER_LAO_2] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lao2,
    },

    [TRAINER_LAO_3] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lao3,
    },

    [TRAINER_LAO_4] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lao4,
    },

    [TRAINER_LAO_5] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "LAO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Lao5,
    },

    [TRAINER_JOCELYN] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "JOCELYN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jocelyn,
    },

    [TRAINER_LAURA] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "LAURA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Laura,
    },

    [TRAINER_CYNDY_1] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CYNDY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cyndy1,
    },

    [TRAINER_CORA] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CORA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cora,
    },

    [TRAINER_PAULA] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "PAULA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Paula,
    },

    [TRAINER_CYNDY_2] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CYNDY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cyndy2,
    },

    [TRAINER_CYNDY_3] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CYNDY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cyndy3,
    },

    [TRAINER_CYNDY_4] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CYNDY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cyndy4,
    },

    [TRAINER_CYNDY_5] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CYNDY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cyndy5,
    },

    [TRAINER_MADELINE_1] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "MADELINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Madeline1,
    },

    [TRAINER_CLARISSA] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "CLARISSA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Clarissa,
    },

    [TRAINER_ANGELICA] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "ANGELICA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Angelica,
    },

    [TRAINER_MADELINE_2] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "MADELINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Madeline2,
    },

    [TRAINER_MADELINE_3] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "MADELINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Madeline3,
    },

    [TRAINER_MADELINE_4] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "MADELINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Madeline4,
    },

    [TRAINER_MADELINE_5] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "MADELINE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Madeline5,
    },

    [TRAINER_BEVERLY] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "BEVERLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Beverly,
    },

    [TRAINER_IMANI] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "IMANI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Imani,
    },

    [TRAINER_KYLA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "KYLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kyla,
    },

    [TRAINER_DENISE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "DENISE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Denise,
    },

    [TRAINER_BETH] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "BETH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Beth,
    },

    [TRAINER_TARA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "TARA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tara,
    },

    [TRAINER_MISSY] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "MISSY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Missy,
    },

    [TRAINER_ALICE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "ALICE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alice,
    },

    [TRAINER_JENNY_1] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "JENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jenny1,
    },

    [TRAINER_GRACE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "GRACE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Grace,
    },

    [TRAINER_TANYA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "TANYA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tanya,
    },

    [TRAINER_SHARON] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "SHARON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sharon,
    },

    [TRAINER_NIKKI] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "NIKKI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nikki,
    },

    [TRAINER_BRENDA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "BRENDA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brenda,
    },

    [TRAINER_KATIE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "KATIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Katie,
    },

    [TRAINER_SUSIE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "SUSIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Susie,
    },

    [TRAINER_KARA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "KARA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kara,
    },

    [TRAINER_DANA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "DANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dana,
    },

    [TRAINER_SIENNA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "SIENNA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sienna,
    },

    [TRAINER_DEBRA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "DEBRA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Debra,
    },

    [TRAINER_LINDA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "LINDA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Linda,
    },

    [TRAINER_KAYLEE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "KAYLEE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kaylee,
    },

    [TRAINER_LAUREL] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "LAUREL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Laurel,
    },

    [TRAINER_CARLEE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "CARLEE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Carlee,
    },

    [TRAINER_JENNY_2] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "JENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jenny2,
    },

    [TRAINER_JENNY_3] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "JENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jenny3,
    },

    [TRAINER_JENNY_4] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "JENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jenny4,
    },

    [TRAINER_JENNY_5] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "JENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jenny5,
    },

    [TRAINER_HEIDI] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "HEIDI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Heidi,
    },

    [TRAINER_BECKY] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "BECKY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Becky,
    },

    [TRAINER_CAROL] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "CAROL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Carol,
    },

    [TRAINER_NANCY] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "NANCY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nancy,
    },

    [TRAINER_MARTHA] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "MARTHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Martha,
    },

    [TRAINER_DIANA_1] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "DIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Diana1,
    },

    [TRAINER_CEDRIC] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "CEDRIC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cedric,
    },

    [TRAINER_IRENE] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "IRENE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Irene,
    },

    [TRAINER_DIANA_2] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "DIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Diana2,
    },

    [TRAINER_DIANA_3] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "DIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Diana3,
    },

    [TRAINER_DIANA_4] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "DIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Diana4,
    },

    [TRAINER_DIANA_5] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "DIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Diana5,
    },

    [TRAINER_AMY_AND_LIV_1] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv1,
    },

    [TRAINER_AMY_AND_LIV_2] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv2,
    },

    [TRAINER_GINA_AND_MIA_1] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "GINA & MIA",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GinaAndMia1,
    },

    [TRAINER_MIU_AND_YUKI] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "MIU & YUKI",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_MiuAndYuki,
    },

    [TRAINER_AMY_AND_LIV_3] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv3,
    },

    [TRAINER_GINA_AND_MIA_2] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "GINA & MIA",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GinaAndMia2,
    },

    [TRAINER_AMY_AND_LIV_4] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv4,
    },

    [TRAINER_AMY_AND_LIV_5] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv5,
    },

    [TRAINER_AMY_AND_LIV_6] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "AMY & LIV",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_AmyAndLiv6,
    },

    [TRAINER_HUEY] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "HUEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Huey,
    },

    [TRAINER_EDMOND] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "EDMOND",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edmond,
    },

    [TRAINER_ERNEST_1] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "ERNEST",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ernest1,
    },

    [TRAINER_DWAYNE] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "DWAYNE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dwayne,
    },

    [TRAINER_PHILLIP] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "PHILLIP",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Phillip,
    },

    [TRAINER_LEONARD] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "LEONARD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Leonard,
    },

    [TRAINER_DUNCAN] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "DUNCAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Duncan,
    },

    [TRAINER_ERNEST_2] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "ERNEST",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ernest2,
    },

    [TRAINER_ERNEST_3] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "ERNEST",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ernest3,
    },

    [TRAINER_ERNEST_4] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "ERNEST",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ernest4,
    },

    [TRAINER_ERNEST_5] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "ERNEST",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ernest5,
    },

    [TRAINER_ELI] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "ELI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Eli,
    },

    [TRAINER_ANNIKA] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "ANNIKA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Annika,
    },

    [TRAINER_JAZMYN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER_2,
        
        
        .trainerName = "JAZMYN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jazmyn,
    },

    [TRAINER_JONAS] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "JONAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jonas,
    },

    [TRAINER_KAYLEY] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "KAYLEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kayley,
    },

    [TRAINER_AURON] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "AURON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Auron,
    },

    [TRAINER_KELVIN] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "KELVIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kelvin,
    },

    [TRAINER_MARLEY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "MARLEY",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Marley,
    },

    [TRAINER_REYNA] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "REYNA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Reyna,
    },

    [TRAINER_HUDSON] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "HUDSON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hudson,
    },

    [TRAINER_CONOR] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "CONOR",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Conor,
    },

    [TRAINER_EDWIN_1] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "EDWIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwin1,
    },

    [TRAINER_HECTOR] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "HECTOR",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hector,
    },

    [TRAINER_TABITHA_MOSSDEEP] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_ADMIN,
        
        
        .trainerName = "TABITHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_TabithaMossdeep,
    },

    [TRAINER_EDWIN_2] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "EDWIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwin2,
    },

    [TRAINER_EDWIN_3] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "EDWIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwin3,
    },

    [TRAINER_EDWIN_4] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "EDWIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwin4,
    },

    [TRAINER_EDWIN_5] =
    {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        
        
        .trainerName = "EDWIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Edwin5,
    },

    [TRAINER_WALLY_VR_1] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyVR1,
    },

    [TRAINER_BRENDAN_ROUTE_103_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute103Mudkip,
    },

    [TRAINER_BRENDAN_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute110Mudkip,
    },

    [TRAINER_BRENDAN_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute119Mudkip,
    },

    [TRAINER_BRENDAN_ROUTE_103_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_BrendanRoute103Treecko,
    },

    [TRAINER_BRENDAN_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute110Treecko,
    },

    [TRAINER_BRENDAN_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute119Treecko,
    },

    [TRAINER_BRENDAN_ROUTE_103_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute103Torchic,
    },

    [TRAINER_BRENDAN_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute110Torchic,
    },

    [TRAINER_BRENDAN_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRoute119Torchic,
    },

    [TRAINER_MAY_ROUTE_103_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute103Mudkip,
    },

    [TRAINER_MAY_ROUTE_110_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute110Mudkip,
    },

    [TRAINER_MAY_ROUTE_119_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute119Mudkip,
    },

    [TRAINER_MAY_ROUTE_103_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute103Treecko,
    },

    [TRAINER_MAY_ROUTE_110_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute110Treecko,
    },

    [TRAINER_MAY_ROUTE_119_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute119Treecko,
    },

    [TRAINER_MAY_ROUTE_103_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute103Torchic,
    },

    [TRAINER_MAY_ROUTE_110_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute110Torchic,
    },

    [TRAINER_MAY_ROUTE_119_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRoute119Torchic,
    },

    [TRAINER_ISAAC_1] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "ISAAC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaac1,
    },

    [TRAINER_DAVIS] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "DAVIS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Davis,
    },

    [TRAINER_MITCHELL] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "MITCHELL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Mitchell,
    },

    [TRAINER_ISAAC_2] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "ISAAC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaac2,
    },

    [TRAINER_ISAAC_3] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "ISAAC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaac3,
    },

    [TRAINER_ISAAC_4] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "ISAAC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaac4,
    },

    [TRAINER_ISAAC_5] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "ISAAC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isaac5,
    },

    [TRAINER_LYDIA_1] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "LYDIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lydia1,
    },

    [TRAINER_HALLE] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "HALLE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Halle,
    },

    [TRAINER_GARRISON] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "GARRISON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Garrison,
    },

    [TRAINER_LYDIA_2] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "LYDIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lydia2,
    },

    [TRAINER_LYDIA_3] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "LYDIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lydia3,
    },

    [TRAINER_LYDIA_4] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "LYDIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lydia4,
    },

    [TRAINER_LYDIA_5] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "LYDIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lydia5,
    },

    [TRAINER_JACKSON_1] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JACKSON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jackson1,
    },

    [TRAINER_LORENZO] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "LORENZO",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Lorenzo,
    },

    [TRAINER_SEBASTIAN] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "SEBASTIAN",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sebastian,
    },

    [TRAINER_JACKSON_2] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JACKSON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Jackson2,
    },

    [TRAINER_JACKSON_3] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JACKSON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jackson3,
    },

    [TRAINER_JACKSON_4] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JACKSON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Jackson4,
    },

    [TRAINER_JACKSON_5] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JACKSON",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Jackson5,
    },

    [TRAINER_CATHERINE_1] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "CATHERINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Catherine1,
    },

    [TRAINER_JENNA] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "JENNA",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Jenna,
    },

    [TRAINER_SOPHIA] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "SOPHIA",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sophia,
    },

    [TRAINER_CATHERINE_2] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "CATHERINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Catherine2,
    },

    [TRAINER_CATHERINE_3] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "CATHERINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Catherine3,
    },

    [TRAINER_CATHERINE_4] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "CATHERINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Catherine4,
    },

    [TRAINER_CATHERINE_5] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        
        
        .trainerName = "CATHERINE",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Catherine5,
    },

    [TRAINER_JULIO] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "JULIO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Julio,
    },

    [TRAINER_GRUNT_SEAFLOOR_CAVERN_5] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSeafloorCavern5,
    },

    [TRAINER_GRUNT_UNUSED] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntUnused,
    },

    [TRAINER_GRUNT_MT_PYRE_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtPyre4,
    },

    [TRAINER_GRUNT_JAGGED_PASS] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntJaggedPass,
    },

    [TRAINER_MARC] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "MARC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Marc,
    },

    [TRAINER_BRENDEN] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "BRENDEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brenden,
    },

    [TRAINER_LILITH] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "LILITH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lilith,
    },

    [TRAINER_CRISTIAN] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "CRISTIAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cristian,
    },

    [TRAINER_SYLVIA] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "SYLVIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sylvia,
    },

    [TRAINER_LEONARDO] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "LEONARDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Leonardo,
    },

    [TRAINER_ATHENA] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "ATHENA",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Athena,
    },

    [TRAINER_HARRISON] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "HARRISON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Harrison,
    },

    [TRAINER_GRUNT_MT_CHIMNEY_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMtChimney2,
    },

    [TRAINER_CLARENCE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "CLARENCE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Clarence,
    },

    [TRAINER_TERRY] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "TERRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Terry,
    },

    [TRAINER_NATE] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "NATE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nate,
    },

    [TRAINER_KATHLEEN] =
    {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        
        
        .trainerName = "KATHLEEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kathleen,
    },

    [TRAINER_CLIFFORD] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "CLIFFORD",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Clifford,
    },

    [TRAINER_NICHOLAS] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "NICHOLAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Nicholas,
    },

    [TRAINER_GRUNT_SPACE_CENTER_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter3,
    },

    [TRAINER_GRUNT_SPACE_CENTER_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter4,
    },

    [TRAINER_GRUNT_SPACE_CENTER_5] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter5,
    },

    [TRAINER_GRUNT_SPACE_CENTER_6] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter6,
    },

    [TRAINER_GRUNT_SPACE_CENTER_7] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntSpaceCenter7,
    },

    [TRAINER_MACEY] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "MACEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Macey,
    },

    [TRAINER_BRENDAN_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_BrendanRustboroTreecko,
    },

    [TRAINER_BRENDAN_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_BrendanRustboroMudkip,
    },

    [TRAINER_PAXTON] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "PAXTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Paxton,
    },

    [TRAINER_ISABELLA] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ISABELLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabella,
    },

    [TRAINER_GRUNT_WEATHER_INST_5] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntWeatherInst5,
    },

    [TRAINER_TABITHA_MT_CHIMNEY] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_ADMIN,
        
        
        .trainerName = "TABITHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TabithaMtChimney,
    },

    [TRAINER_JONATHAN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "JONATHAN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_Jonathan,
    },

    [TRAINER_BRENDAN_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanRustboroTorchic,
    },

    [TRAINER_MAY_RUSTBORO_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_MayRustboroMudkip,
    },

    [TRAINER_MAXIE_MAGMA_HIDEOUT] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_LEADER,
        
        
        .trainerName = "MAXIE",
        .items = {ITEM_SUPER_POTION, ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MaxieMagmaHideout,
    },

    [TRAINER_MAXIE_MT_CHIMNEY] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_LEADER,
        
        
        .trainerName = "MAXIE",
        .items = {ITEM_SUPER_POTION, ITEM_SUPER_POTION, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MaxieMtChimney,
    },

    [TRAINER_TIANA] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "TIANA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tiana,
    },

    [TRAINER_HALEY_1] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "HALEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Haley1,
    },

    [TRAINER_JANICE] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "JANICE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Janice,
    },

    [TRAINER_VIVI] =
    {
        .trainerClass = TRAINER_CLASS_WINSTRATE,
        
        
        .trainerName = "VIVI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Vivi,
    },

    [TRAINER_HALEY_2] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "HALEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Haley2,
    },

    [TRAINER_HALEY_3] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "HALEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Haley3,
    },

    [TRAINER_HALEY_4] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "HALEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Haley4,
    },

    [TRAINER_HALEY_5] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "HALEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Haley5,
    },

    [TRAINER_SALLY] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "SALLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sally,
    },

    [TRAINER_ROBIN] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "ROBIN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Robin,
    },

    [TRAINER_ANDREA] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "ANDREA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andrea,
    },

    [TRAINER_CRISSY] =
    {
        .trainerClass = TRAINER_CLASS_LASS,
        
        
        .trainerName = "CRISSY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Crissy,
    },

    [TRAINER_RICK] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "RICK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rick,
    },

    [TRAINER_LYLE] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "LYLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lyle,
    },

    [TRAINER_JOSE] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JOSE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jose,
    },

    [TRAINER_DOUG] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "DOUG",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Doug,
    },

    [TRAINER_GREG] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "GREG",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Greg,
    },

    [TRAINER_KENT] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "KENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kent,
    },

    [TRAINER_JAMES_1] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JAMES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_James1,
    },

    [TRAINER_JAMES_2] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JAMES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_James2,
    },

    [TRAINER_JAMES_3] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JAMES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_James3,
    },

    [TRAINER_JAMES_4] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JAMES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_James4,
    },

    [TRAINER_JAMES_5] =
    {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        
        
        .trainerName = "JAMES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_James5,
    },

    [TRAINER_BRICE] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "BRICE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brice,
    },

    [TRAINER_TRENT_1] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "TRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Trent1,
    },

    [TRAINER_LENNY] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "LENNY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lenny,
    },

    [TRAINER_LUCAS_1] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "LUCAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lucas1,
    },

    [TRAINER_ALAN] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "ALAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alan,
    },

    [TRAINER_CLARK] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "CLARK",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Clark,
    },

    [TRAINER_ERIC] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "ERIC",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Eric,
    },

    [TRAINER_LUCAS_2] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "LUCAS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lucas2,
    },

    [TRAINER_MIKE_1] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "MIKE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Mike1,
    },

    [TRAINER_MIKE_2] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "MIKE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Mike2,
    },

    [TRAINER_TRENT_2] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "TRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Trent2,
    },

    [TRAINER_TRENT_3] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "TRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Trent3,
    },

    [TRAINER_TRENT_4] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "TRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Trent4,
    },

    [TRAINER_TRENT_5] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "TRENT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Trent5,
    },

    [TRAINER_DEZ_AND_LUKE] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "DEZ & LUKE",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_DezAndLuke,
    },

    [TRAINER_LEA_AND_JED] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "LEA & JED",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LeaAndJed,
    },

    [TRAINER_KIRA_AND_DAN_1] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "KIRA & DAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KiraAndDan1,
    },

    [TRAINER_KIRA_AND_DAN_2] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "KIRA & DAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KiraAndDan2,
    },

    [TRAINER_KIRA_AND_DAN_3] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "KIRA & DAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KiraAndDan3,
    },

    [TRAINER_KIRA_AND_DAN_4] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "KIRA & DAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KiraAndDan4,
    },

    [TRAINER_KIRA_AND_DAN_5] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "KIRA & DAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KiraAndDan5,
    },

    [TRAINER_JOHANNA] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "JOHANNA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Johanna,
    },

    [TRAINER_GERALD] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "GERALD",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Gerald,
    },

    [TRAINER_VIVIAN] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "VIVIAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Vivian,
    },

    [TRAINER_DANIELLE] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "DANIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Danielle,
    },

    [TRAINER_HIDEO] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "HIDEO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Hideo,
    },

    [TRAINER_KEIGO] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "KEIGO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Keigo,
    },

    [TRAINER_RILEY] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "RILEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT,
        .party = sParty_Riley,
    },

    [TRAINER_FLINT] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "FLINT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Flint,
    },

    [TRAINER_ASHLEY] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "ASHLEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Ashley,
    },

    [TRAINER_WALLY_MAUVILLE] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyMauville,
    },

    [TRAINER_WALLY_VR_2] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyVR2,
    },

    [TRAINER_WALLY_VR_3] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyVR3,
    },

    [TRAINER_WALLY_VR_4] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyVR4,
    },

    [TRAINER_WALLY_VR_5] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "WALLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_WallyVR5,
    },

    [TRAINER_BRENDAN_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanLilycoveMudkip,
    },

    [TRAINER_BRENDAN_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanLilycoveTreecko,
    },

    [TRAINER_BRENDAN_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_BrendanLilycoveTorchic,
    },

    [TRAINER_MAY_LILYCOVE_MUDKIP] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayLilycoveMudkip,
    },

    [TRAINER_MAY_LILYCOVE_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayLilycoveTreecko,
    },

    [TRAINER_MAY_LILYCOVE_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayLilycoveTorchic,
    },

    [TRAINER_JONAH] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "JONAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jonah,
    },

    [TRAINER_HENRY] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "HENRY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Henry,
    },

    [TRAINER_ROGER] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "ROGER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Roger,
    },

    [TRAINER_ALEXA] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "ALEXA",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Alexa,
    },

    [TRAINER_RUBEN] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "RUBEN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Ruben,
    },

    [TRAINER_KOJI_1] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koji1,
    },

    [TRAINER_WAYNE] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "WAYNE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Wayne,
    },

    [TRAINER_AIDAN] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "AIDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Aidan,
    },

    [TRAINER_REED] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "REED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Reed,
    },

    [TRAINER_TISHA] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "TISHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tisha,
    },

    [TRAINER_TORI_AND_TIA] =
    {
        .trainerClass = TRAINER_CLASS_TWINS,
        
        
        .trainerName = "TORI & TIA",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_ToriAndTia,
    },

    [TRAINER_KIM_AND_IRIS] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "KIM & IRIS",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_KimAndIris,
    },

    [TRAINER_TYRA_AND_IVY] =
    {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        
        
        .trainerName = "TYRA & IVY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_TyraAndIvy,
    },

    [TRAINER_MEL_AND_PAUL] =
    {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        
        
        .trainerName = "MEL & PAUL",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_MelAndPaul,
    },

    [TRAINER_JOHN_AND_JAY_1] =
    {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        
        
        .trainerName = "JOHN & JAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_JohnAndJay1,
    },

    [TRAINER_JOHN_AND_JAY_2] =
    {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        
        
        .trainerName = "JOHN & JAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_JohnAndJay2,
    },

    [TRAINER_JOHN_AND_JAY_3] =
    {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        
        
        .trainerName = "JOHN & JAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_JohnAndJay3,
    },

    [TRAINER_JOHN_AND_JAY_4] =
    {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        
        
        .trainerName = "JOHN & JAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_SETUP_FIRST_TURN,
        .party = sParty_JohnAndJay4,
    },

    [TRAINER_JOHN_AND_JAY_5] =
    {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        
        
        .trainerName = "JOHN & JAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_JohnAndJay5,
    },

    [TRAINER_RELI_AND_IAN] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "RELI & IAN",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_ReliAndIan,
    },

    [TRAINER_LILA_AND_ROY_1] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LILA & ROY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LilaAndRoy1,
    },

    [TRAINER_LILA_AND_ROY_2] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LILA & ROY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LilaAndRoy2,
    },

    [TRAINER_LILA_AND_ROY_3] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LILA & ROY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LilaAndRoy3,
    },

    [TRAINER_LILA_AND_ROY_4] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LILA & ROY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LilaAndRoy4,
    },

    [TRAINER_LILA_AND_ROY_5] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LILA & ROY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LilaAndRoy5,
    },

    [TRAINER_LISA_AND_RAY] =
    {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        
        
        .trainerName = "LISA & RAY",
        .items = {},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_LisaAndRay,
    },

    [TRAINER_CHRIS] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "CHRIS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chris,
    },

    [TRAINER_DAWSON] =
    {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        
        
        .trainerName = "DAWSON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dawson,
    },

    [TRAINER_SARAH] =
    {
        .trainerClass = TRAINER_CLASS_LADY,
        
        
        .trainerName = "SARAH",
        .items = {ITEM_FULL_RESTORE, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sarah,
    },

    [TRAINER_DARIAN] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "DARIAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Darian,
    },

    [TRAINER_HAILEY] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_F,
        
        
        .trainerName = "HAILEY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hailey,
    },

    [TRAINER_CHANDLER] =
    {
        .trainerClass = TRAINER_CLASS_TUBER_M,
        
        
        .trainerName = "CHANDLER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Chandler,
    },

    [TRAINER_KALEB] =
    {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        
        
        .trainerName = "KALEB",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kaleb,
    },

    [TRAINER_JOSEPH] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "JOSEPH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Joseph,
    },

    [TRAINER_ALYSSA] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "ALYSSA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alyssa,
    },

    [TRAINER_MARCOS] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "MARCOS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Marcos,
    },

    [TRAINER_RHETT] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "RHETT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rhett,
    },

    [TRAINER_TYRON] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "TYRON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Tyron,
    },

    [TRAINER_CELINA] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "CELINA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Celina,
    },

    [TRAINER_BIANCA] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "BIANCA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bianca,
    },

    [TRAINER_HAYDEN] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "HAYDEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Hayden,
    },

    [TRAINER_SOPHIE] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "SOPHIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Sophie,
    },

    [TRAINER_COBY] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "COBY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Coby,
    },

    [TRAINER_LAWRENCE] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "LAWRENCE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Lawrence,
    },

    [TRAINER_WYATT] =
    {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        
        
        .trainerName = "WYATT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Wyatt,
    },

    [TRAINER_ANGELINA] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "ANGELINA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Angelina,
    },

    [TRAINER_KAI] =
    {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        
        
        .trainerName = "KAI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kai,
    },

    [TRAINER_CHARLOTTE] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "CHARLOTTE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Charlotte,
    },

    [TRAINER_DEANDRE] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "DEANDRE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Deandre,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_1] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout1,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_2] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout2,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_3] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout3,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_4] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout4,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_5] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout5,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_6] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout6,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_7] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout7,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_8] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout8,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_9] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout9,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_10] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout10,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_11] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout11,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_12] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout12,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_13] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout13,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_14] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout14,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_15] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout15,
    },

    [TRAINER_GRUNT_MAGMA_HIDEOUT_16] =
    {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        
        
        .trainerName = "GRUNT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_GruntMagmaHideout16,
    },

    [TRAINER_TABITHA_MAGMA_HIDEOUT] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_ADMIN,
        
        
        .trainerName = "TABITHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_TabithaMagmaHideout,
    },

    [TRAINER_DARCY] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "DARCY",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Darcy,
    },

    [TRAINER_MAXIE_MOSSDEEP] =
    {
        .trainerClass = TRAINER_CLASS_MAGMA_LEADER,
        
        
        .trainerName = "MAXIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MaxieMossdeep,
    },

    [TRAINER_PETE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        
        
        .trainerName = "PETE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pete,
    },

    [TRAINER_ISABELLE] =
    {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        
        
        .trainerName = "ISABELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Isabelle,
    },

    [TRAINER_ANDRES_1] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "ANDRES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andres1,
    },

    [TRAINER_JOSUE] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "JOSUE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Josue,
    },

    [TRAINER_CAMRON] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "CAMRON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Camron,
    },

    [TRAINER_CORY_1] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "CORY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cory1,
    },

    [TRAINER_CAROLINA] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CAROLINA",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Carolina,
    },

    [TRAINER_ELIJAH] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "ELIJAH",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Elijah,
    },

    [TRAINER_CELIA] =
    {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        
        
        .trainerName = "CELIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Celia,
    },

    [TRAINER_BRYAN] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "BRYAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bryan,
    },

    [TRAINER_BRANDEN] =
    {
        .trainerClass = TRAINER_CLASS_CAMPER,
        
        
        .trainerName = "BRANDEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Branden,
    },

    [TRAINER_BRYANT] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "BRYANT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Bryant,
    },

    [TRAINER_SHAYLA] =
    {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        
        
        .trainerName = "SHAYLA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Shayla,
    },

    [TRAINER_KYRA] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "KYRA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Kyra,
    },

    [TRAINER_JAIDEN] =
    {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        
        
        .trainerName = "JAIDEN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Jaiden,
    },

    [TRAINER_ALIX] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "ALIX",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Alix,
    },

    [TRAINER_HELENE] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "HELENE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Helene,
    },

    [TRAINER_MARLENE] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "MARLENE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Marlene,
    },

    [TRAINER_DEVAN] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "DEVAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Devan,
    },

    [TRAINER_JOHNSON] =
    {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        
        
        .trainerName = "JOHNSON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Johnson,
    },

    [TRAINER_MELINA] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "MELINA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Melina,
    },

    [TRAINER_BRANDI] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "BRANDI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Brandi,
    },

    [TRAINER_AISHA] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "AISHA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Aisha,
    },

    [TRAINER_MAKAYLA] =
    {
        .trainerClass = TRAINER_CLASS_EXPERT,
        
        
        .trainerName = "MAKAYLA",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Makayla,
    },

    [TRAINER_FABIAN] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FABIAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fabian,
    },

    [TRAINER_DAYTON] =
    {
        .trainerClass = TRAINER_CLASS_KINDLER,
        
        
        .trainerName = "DAYTON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Dayton,
    },

    [TRAINER_RACHEL] =
    {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        
        
        .trainerName = "RACHEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Rachel,
    },

    [TRAINER_LEONEL] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "LEONEL",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Leonel,
    },

    [TRAINER_CALLIE] =
    {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        
        
        .trainerName = "CALLIE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Callie,
    },

    [TRAINER_CALE] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "CALE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cale,
    },

    [TRAINER_MYLES] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "MYLES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Myles,
    },

    [TRAINER_PAT] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "PAT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pat,
    },

    [TRAINER_CRISTIN_1] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CRISTIN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Cristin1,
    },

    [TRAINER_MAY_RUSTBORO_TREECKO] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRustboroTreecko,
    },

    [TRAINER_MAY_RUSTBORO_TORCHIC] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_MayRustboroTorchic,
    },

    [TRAINER_ROXANNE_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "ROXANNE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Roxanne2,
    },

    [TRAINER_ROXANNE_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "ROXANNE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Roxanne3,
    },

    [TRAINER_ROXANNE_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "ROXANNE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Roxanne4,
    },

    [TRAINER_ROXANNE_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "ROXANNE",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Roxanne5,
    },

    [TRAINER_BRAWLY_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "BRAWLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brawly2,
    },

    [TRAINER_BRAWLY_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "BRAWLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brawly3,
    },

    [TRAINER_BRAWLY_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "BRAWLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brawly4,
    },

    [TRAINER_BRAWLY_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "BRAWLY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brawly5,
    },

    [TRAINER_WATTSON_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WATTSON",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wattson2,
    },

    [TRAINER_WATTSON_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WATTSON",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wattson3,
    },

    [TRAINER_WATTSON_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WATTSON",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wattson4,
    },

    [TRAINER_WATTSON_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WATTSON",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Wattson5,
    },

    [TRAINER_FLANNERY_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "FLANNERY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Flannery2,
    },

    [TRAINER_FLANNERY_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "FLANNERY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Flannery3,
    },

    [TRAINER_FLANNERY_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "FLANNERY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Flannery4,
    },

    [TRAINER_FLANNERY_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "FLANNERY",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Flannery5,
    },

    [TRAINER_NORMAN_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "NORMAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Norman2,
    },

    [TRAINER_NORMAN_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "NORMAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Norman3,
    },

    [TRAINER_NORMAN_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "NORMAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Norman4,
    },

    [TRAINER_NORMAN_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "NORMAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Norman5,
    },

    [TRAINER_WINONA_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WINONA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .party = sParty_Winona2,
    },

    [TRAINER_WINONA_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WINONA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .party = sParty_Winona3,
    },

    [TRAINER_WINONA_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WINONA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .party = sParty_Winona4,
    },

    [TRAINER_WINONA_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "WINONA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_RISKY,
        .party = sParty_Winona5,
    },

    [TRAINER_TATE_AND_LIZA_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "TATE&LIZA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TateAndLiza2,
    },

    [TRAINER_TATE_AND_LIZA_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "TATE&LIZA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TateAndLiza3,
    },

    [TRAINER_TATE_AND_LIZA_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "TATE&LIZA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TateAndLiza4,
    },

    [TRAINER_TATE_AND_LIZA_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "TATE&LIZA",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_TateAndLiza5,
    },

    [TRAINER_JUAN_2] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "JUAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Juan2,
    },

    [TRAINER_JUAN_3] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "JUAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Juan3,
    },

    [TRAINER_JUAN_4] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "JUAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Juan4,
    },

    [TRAINER_JUAN_5] =
    {
        .trainerClass = TRAINER_CLASS_LEADER,
        
        
        .trainerName = "JUAN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_NONE},
        .doubleBattle = true,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Juan5,
    },

    [TRAINER_ANGELO] =
    {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        
        
        .trainerName = "ANGELO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Angelo,
    },

    [TRAINER_DARIUS] =
    {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        
        
        .trainerName = "DARIUS",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Darius,
    },

    [TRAINER_STEVEN] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "STEVEN",
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Steven,
    },

    [TRAINER_ANABEL] =
    {
        .trainerClass = TRAINER_CLASS_SALON_MAIDEN,
        
        
        .trainerName = "ANABEL",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Anabel,
    },

    [TRAINER_TUCKER] =
    {
        .trainerClass = TRAINER_CLASS_DOME_ACE,
        
        
        .trainerName = "TUCKER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Tucker,
    },

    [TRAINER_SPENSER] =
    {
        .trainerClass = TRAINER_CLASS_PALACE_MAVEN,
        
        
        .trainerName = "SPENSER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Spenser,
    },

    [TRAINER_GRETA] =
    {
        .trainerClass = TRAINER_CLASS_ARENA_TYCOON,
        
        
        .trainerName = "GRETA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Greta,
    },

    [TRAINER_NOLAND] =
    {
        .trainerClass = TRAINER_CLASS_FACTORY_HEAD,
        
        
        .trainerName = "NOLAND",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Noland,
    },

    [TRAINER_LUCY] =
    {
        .trainerClass = TRAINER_CLASS_PIKE_QUEEN,
        
        
        .trainerName = "LUCY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Lucy,
    },

    [TRAINER_BRANDON] =
    {
        .trainerClass = TRAINER_CLASS_PYRAMID_KING,
        
        
        .trainerName = "BRANDON",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Brandon,
    },

    [TRAINER_ANDRES_2] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "ANDRES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andres2,
    },

    [TRAINER_ANDRES_3] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "ANDRES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andres3,
    },

    [TRAINER_ANDRES_4] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "ANDRES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andres4,
    },

    [TRAINER_ANDRES_5] =
    {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        
        
        .trainerName = "ANDRES",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Andres5,
    },

    [TRAINER_CORY_2] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "CORY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cory2,
    },

    [TRAINER_CORY_3] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "CORY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cory3,
    },

    [TRAINER_CORY_4] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "CORY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cory4,
    },

    [TRAINER_CORY_5] =
    {
        .trainerClass = TRAINER_CLASS_SAILOR,
        
        
        .trainerName = "CORY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Cory5,
    },

    [TRAINER_PABLO_2] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "PABLO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pablo2,
    },

    [TRAINER_PABLO_3] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "PABLO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pablo3,
    },

    [TRAINER_PABLO_4] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "PABLO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pablo4,
    },

    [TRAINER_PABLO_5] =
    {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        
        
        .trainerName = "PABLO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Pablo5,
    },

    [TRAINER_KOJI_2] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koji2,
    },

    [TRAINER_KOJI_3] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koji3,
    },

    [TRAINER_KOJI_4] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koji4,
    },

    [TRAINER_KOJI_5] =
    {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        
        
        .trainerName = "KOJI",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Koji5,
    },

    [TRAINER_CRISTIN_2] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CRISTIN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Cristin2,
    },

    [TRAINER_CRISTIN_3] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CRISTIN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Cristin3,
    },

    [TRAINER_CRISTIN_4] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CRISTIN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Cristin4,
    },

    [TRAINER_CRISTIN_5] =
    {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        
        
        .trainerName = "CRISTIN",
        .items = {ITEM_HYPER_POTION, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Cristin5,
    },

    [TRAINER_FERNANDO_2] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FERNANDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fernando2,
    },

    [TRAINER_FERNANDO_3] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FERNANDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fernando3,
    },

    [TRAINER_FERNANDO_4] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FERNANDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fernando4,
    },

    [TRAINER_FERNANDO_5] =
    {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        
        
        .trainerName = "FERNANDO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Fernando5,
    },

    [TRAINER_SAWYER_2] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "SAWYER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sawyer2,
    },

    [TRAINER_SAWYER_3] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "SAWYER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sawyer3,
    },

    [TRAINER_SAWYER_4] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "SAWYER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sawyer4,
    },

    [TRAINER_SAWYER_5] =
    {
        .trainerClass = TRAINER_CLASS_HIKER,
        
        
        .trainerName = "SAWYER",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = sParty_Sawyer5,
    },

    [TRAINER_GABRIELLE_2] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "GABRIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gabrielle2,
    },

    [TRAINER_GABRIELLE_3] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "GABRIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gabrielle3,
    },

    [TRAINER_GABRIELLE_4] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "GABRIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gabrielle4,
    },

    [TRAINER_GABRIELLE_5] =
    {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        
        
        .trainerName = "GABRIELLE",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Gabrielle5,
    },

    [TRAINER_THALIA_2] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "THALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thalia2,
    },

    [TRAINER_THALIA_3] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "THALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thalia3,
    },

    [TRAINER_THALIA_4] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "THALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thalia4,
    },

    [TRAINER_THALIA_5] =
    {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        
        
        .trainerName = "THALIA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = sParty_Thalia5,
    },

    [TRAINER_MARIELA] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "MARIELA",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Mariela,
    },

    [TRAINER_ALVARO] =
    {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        
        
        .trainerName = "ALVARO",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Alvaro,
    },

    [TRAINER_EVERETT] =
    {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        
        
        .trainerName = "EVERETT",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Everett,
    },

    [TRAINER_RED] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "RED",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Red,
    },

    [TRAINER_LEAF] =
    {
        .trainerClass = TRAINER_CLASS_RIVAL,
        
        
        .trainerName = "LEAF",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_Leaf,
    },

    [TRAINER_BRENDAN_PLACEHOLDER] =
    {
        .trainerClass = TRAINER_CLASS_RS_PROTAG,
        
        
        .trainerName = "BRENDAN",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_BrendanLinkPlaceholder,
    },

    [TRAINER_MAY_PLACEHOLDER] =
    {
        .trainerClass = TRAINER_CLASS_RS_PROTAG,
        
        
        .trainerName = "MAY",
        .items = {},
        .doubleBattle = false,
        .aiFlags = 0,
        .party = sParty_MayLinkPlaceholder,
    },
};
