#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "pokedex.h"

#define NUM_SPECIAL_FLAGS (SPECIAL_FLAGS_END - SPECIAL_FLAGS_START + 1)
#define NUM_TEMP_FLAGS    (TEMP_FLAGS_END - TEMP_FLAGS_START + 1)
#define NUM_DAILY_FLAGS   (DAILY_FLAGS_END - DAILY_FLAGS_START + 1)
#define NUM_TEMP_VARS     (TEMP_VARS_END - TEMP_VARS_START + 1)

#define SPECIAL_FLAGS_SIZE  (NUM_SPECIAL_FLAGS / 8)  // 8 flags per byte
#define TEMP_FLAGS_SIZE     (NUM_TEMP_FLAGS / 8)
#define DAILY_FLAGS_SIZE    (NUM_DAILY_FLAGS / 8)
#define TEMP_VARS_SIZE      (NUM_TEMP_VARS * 2)      // 1/2 var per byte

EWRAM_DATA u16 gSpecialVar_0x8000 = 0;
EWRAM_DATA u16 gSpecialVar_0x8001 = 0;
EWRAM_DATA u16 gSpecialVar_0x8002 = 0;
EWRAM_DATA u16 gSpecialVar_0x8003 = 0;
EWRAM_DATA u16 gSpecialVar_0x8004 = 0;
EWRAM_DATA u16 gSpecialVar_0x8005 = 0;
EWRAM_DATA u16 gSpecialVar_0x8006 = 0;
EWRAM_DATA u16 gSpecialVar_0x8007 = 0;
EWRAM_DATA u16 gSpecialVar_0x8008 = 0;
EWRAM_DATA u16 gSpecialVar_0x8009 = 0;
EWRAM_DATA u16 gSpecialVar_0x800A = 0;
EWRAM_DATA u16 gSpecialVar_0x800B = 0;
EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;
EWRAM_DATA u16 gSpecialVar_TextColor = 0;
EWRAM_DATA u16 gSpecialVar_TextColorBackup = 0;
EWRAM_DATA u16 gSpecialVar_Unused_0x8014 = 0;
EWRAM_DATA static u8 gSpecialFlags[SPECIAL_FLAGS_SIZE] = {0};

extern u16 *const gSpecialVars[];

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, sizeof(gSaveBlock1Ptr->flags));
    memset(gSaveBlock1Ptr->vars, 0, sizeof(gSaveBlock1Ptr->vars));
    memset(gSpecialFlags, 0, sizeof(gSpecialFlags));
}

void ClearTempFieldEventData(void)
{
    memset(gSaveBlock1Ptr->flags + (TEMP_FLAGS_START / 8), 0, TEMP_FLAGS_SIZE);
    memset(gSaveBlock1Ptr->vars + ((TEMP_VARS_START - VARS_START) * 2), 0, TEMP_VARS_SIZE);
    FlagClear(FLAG_RAN_FROM_TRAINER);
    FlagClear(FLAG_SYS_ENC_UP_ITEM);
    FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_CTRL_OBJ_DELETE);
    FlagClear(FLAG_NURSE_UNION_ROOM_REMINDER);
}

void ClearDailyFlags(void)
{
    u32 i;
    memset(gSaveBlock1Ptr->flags + (DAILY_FLAGS_START / 8), 0, DAILY_FLAGS_SIZE);
    FlagClear(FLAG_GOT_SHUCKIE_TODAY);
    ClearTrainerFlag(TRAINER_RIVAL_REMATCH_CHIKORITA);
    ClearTrainerFlag(TRAINER_RIVAL_REMATCH_CYNDAQUIL);
    ClearTrainerFlag(TRAINER_RIVAL_REMATCH_TOTODILE);
    for(i = FLAG_HIDDEN_ITEM_MT_MOON_B2F_TINY_MUSHROOM_1; i <= FLAG_HIDDEN_ITEM_MT_MOON_B2F_BIG_MUSHROOM_3; i++)
    {   // clear the six Mt. Moon hidden mushroom flags
        FlagClear(i);
    }
    ClearAllTrainerWantRematchStates();
}

void DisableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0;
    *nationalDexVar = 0;
    FlagClear(FLAG_SYS_NATIONAL_DEX);
}

void EnableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0xDA;
    *nationalDexVar = 0x302;
    FlagSet(FLAG_SYS_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.mode = DEX_MODE_NATIONAL;
    gSaveBlock2Ptr->pokedex.order = 0;
    ResetPokedexScrollPositions();
}

bool32 IsNationalPokedexEnabled(void)
{
    if (gSaveBlock2Ptr->pokedex.nationalMagic == 0xDA && VarGet(VAR_NATIONAL_DEX) == 0x302 && FlagGet(FLAG_SYS_NATIONAL_DEX))
        return TRUE;
    else
        return FALSE;
}

void DisableMysteryEvent(void)
{
    FlagClear(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void EnableMysteryEvent(void)
{
    FlagSet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

bool32 IsMysteryEventEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void DisableMysteryGift(void)
{
    FlagClear(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void EnableMysteryGift(void)
{
    FlagSet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

bool32 IsMysteryGiftEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void ClearMysteryEventFlags(void)
{
    FlagClear(FLAG_MYSTERY_EVENT_DONE);
    FlagClear(FLAG_MYSTERY_EVENT_1);
    FlagClear(FLAG_MYSTERY_EVENT_2);
    FlagClear(FLAG_MYSTERY_EVENT_3);
    FlagClear(FLAG_MYSTERY_EVENT_4);
    FlagClear(FLAG_MYSTERY_EVENT_5);
    FlagClear(FLAG_MYSTERY_EVENT_6);
    FlagClear(FLAG_MYSTERY_EVENT_7);
    FlagClear(FLAG_MYSTERY_EVENT_8);
    FlagClear(FLAG_MYSTERY_EVENT_9);
    FlagClear(FLAG_MYSTERY_EVENT_10);
    FlagClear(FLAG_MYSTERY_EVENT_11);
    FlagClear(FLAG_MYSTERY_EVENT_12);
    FlagClear(FLAG_MYSTERY_EVENT_13);
    FlagClear(FLAG_MYSTERY_EVENT_14);
    FlagClear(FLAG_MYSTERY_EVENT_15);
}

void ClearMysteryEventVars(void)
{
    VarSet(VAR_EVENT_PICHU_SLOT, 0);
    VarSet(VAR_NEVER_READ_0x40DE, 0);
    VarSet(VAR_NEVER_READ_0x40DF, 0);
    VarSet(VAR_NEVER_READ_0x40E0, 0);
    VarSet(VAR_NEVER_READ_0x40E1, 0);
    VarSet(VAR_NEVER_READ_0x40E2, 0);
    VarSet(VAR_NEVER_READ_0x40E3, 0);
    VarSet(VAR_NEVER_READ_0x40E4, 0);
}

void DisableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0);
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);
}

void EnableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0x920);
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);
}

bool32 CanResetRTC(void)
{
    if (FlagGet(FLAG_SYS_RESET_RTC_ENABLE) && VarGet(VAR_RESET_RTC_ENABLE) == 0x920)
        return TRUE;
    else
        return FALSE;
}

u16 *GetVarPointer(u16 id)
{
    if (id < VARS_START)
        return NULL;
    else if (id < SPECIAL_VARS_START)
        return &gSaveBlock1Ptr->vars[id - VARS_START];
    else
        return gSpecialVars[id - SPECIAL_VARS_START];
}

u16 VarGet(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return id;
    return *ptr;
}

bool8 VarSet(u16 id, u16 value)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return FALSE;
    *ptr = value;
    return TRUE;
}

u16 VarGetObjectEventGraphicsId(u8 id)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + id);
}

u8 *GetFlagPointer(u16 id)
{
    if (id == 0)
        return NULL;
    else if (id < SPECIAL_FLAGS_START)
        return &gSaveBlock1Ptr->flags[id / 8];
    else
        return &gSpecialFlags[(id - SPECIAL_FLAGS_START) / 8];
}

u8 FlagSet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 FlagClear(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 FlagGet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}
