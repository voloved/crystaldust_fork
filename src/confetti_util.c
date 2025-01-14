#include "global.h"
#include "confetti_util.h"
#include "malloc.h"
#include "main.h"
#include "digit_obj_util.h"

static EWRAM_DATA struct
{
    u8 count;
    struct ConfettiUtil *array;
} *sWork = NULL;

static void sub_81520A8(void *dest, u16 value, u8 left, u8 top, u8 width, u8 height) // Unused.
{
    u32 i;
    u32 j;
    u8 x;
    u8 y;

    for (i = 0, y = top; i < height; i++)
    {
        for (x = left, j = 0; j < width; j++)
        {
            *(u16 *)((dest) + (y * 64 + x * 2)) = value;
            x = (x + 1) % 32;
        }
        y = (y + 1) % 32;
    }
}

static void sub_8152134(void *dest, const u16 *src, u8 left, u8 top, u8 width, u8 height) // Unused.
{
    u32 i;
    u32 j;
    u8 x;
    u8 y;
    const u16 *_src;

    for (i = 0, _src = src, y = top; i < height; i++)
    {
        for (x = left, j = 0; j < width; j++)
        {
            *(u16 *)((dest) + (y * 64 + x * 2)) = *(_src++);
            x = (x + 1) % 32;
        }
        y = (y + 1) % 32;
    }
}

bool32 ConfettiUtil_Init(u8 count)
{
    u32 i = 0;

    if (count == 0)
        return FALSE;
    if (count > 64)
        count = 64;

    sWork = AllocZeroed(sizeof(*sWork));
    if (sWork == NULL)
        return FALSE;
    sWork->array = AllocZeroed(count * sizeof(struct ConfettiUtil));
    if (sWork->array == NULL)
    {
        FREE_AND_SET_NULL(sWork);
        return FALSE;
    }

    sWork->count = count;
    for (i = 0; i < count; i++)
    {
        memcpy(&sWork->array[i].oam, &gDummyOamData, sizeof(struct OamData));
        sWork->array[i].dummied = TRUE;
    }

    return TRUE;
}

bool32 ConfettiUtil_Free(void)
{
    u32 i = 0;

    if (sWork == NULL)
        return FALSE;

    for (i = 0; i < sWork->count; i++)
        memcpy(&gMain.oamBuffer[i + 64], &gDummyOamData, sizeof(struct OamData));

    memset(sWork->array, 0, sWork->count * sizeof(struct ConfettiUtil));
    FREE_AND_SET_NULL(sWork->array);
    memset(sWork, 0, sizeof(*sWork));
    FREE_AND_SET_NULL(sWork);

    return TRUE;
}

bool32 ConfettiUtil_Update(void)
{
    u32 i = 0;

    if (sWork == NULL || sWork->array == NULL)
        return FALSE;

    for (i = 0; i < sWork->count; i++)
    {
        if (sWork->array[i].active && sWork->array[i].allowUpdates)
        {
            if (sWork->array[i].callback != NULL)
                sWork->array[i].callback(&sWork->array[i]);

            if (sWork->array[i].dummied)
            {
                memcpy(&gMain.oamBuffer[i + 64], &gDummyOamData, sizeof(struct OamData));
            }
            else
            {
                sWork->array[i].oam.y = sWork->array[i].y + sWork->array[i].yDelta;
                sWork->array[i].oam.x = sWork->array[i].x + sWork->array[i].xDelta;
                sWork->array[i].oam.priority = sWork->array[i].priority;
                sWork->array[i].oam.tileNum = sWork->array[i].tileNum;
                memcpy(&gMain.oamBuffer[i + 64], &sWork->array[i], sizeof(struct OamData));
            }
        }
    }

    return TRUE;
}

static bool32 SetAnimAndTileNum(struct ConfettiUtil *structPtr, u8 animNum)
{
    u16 tileStart;

    if (structPtr == NULL)
        return FALSE;

    tileStart = GetSpriteTileStartByTag(structPtr->tileTag);
    if (tileStart == 0xFFFF)
        return FALSE;

    structPtr->animNum = animNum;
    structPtr->tileNum = (GetTilesPerImage(structPtr->oam.shape, structPtr->oam.size) * animNum) + tileStart;
    return TRUE;
}

u8 ConfettiUtil_SetCallback(u8 id, void (*func)(struct ConfettiUtil *))
{
    if (sWork == NULL || id >= sWork->count)
        return 0xFF;
    else if (!sWork->array[id].active)
        return 0xFF;

    sWork->array[id].callback = func;
    return id;
}

u8 ConfettiUtil_SetData(u8 id, u8 dataArrayId, s16 dataValue)
{
    if (sWork == NULL || id >= sWork->count)
        return 0xFF;
    else if (!sWork->array[id].active || dataArrayId > ARRAY_COUNT(sWork->array[id].data) - 1) // - 1 b/c last slot is reserved for taskId
        return 0xFF;

    sWork->array[id].data[dataArrayId] = dataValue;
    return id;
}

u8 ConfettiUtil_AddNew(const struct OamData *oam, u16 tileTag, u16 palTag, s16 x, s16 y, u8 animNum, u8 priority)
{
    struct ConfettiUtil *structPtr = NULL;
    u32 i;

    if (sWork == NULL || oam == NULL)
        return 0xFF;

    for (i = 0; i < sWork->count; i++)
    {
        if (!sWork->array[i].active)
        {
            structPtr = &sWork->array[i];
            memset(structPtr, 0, sizeof(*structPtr));
            structPtr->id = i;
            structPtr->active = TRUE;
            structPtr->allowUpdates = TRUE;
            break;
        }
    }

    if (structPtr == NULL)
        return 0xFF;

    memcpy(&structPtr->oam, oam, sizeof(*oam));
    structPtr->tileTag = tileTag;
    structPtr->palTag = palTag;
    structPtr->x = x;
    structPtr->y = y;
    structPtr->oam.paletteNum = IndexOfSpritePaletteTag(palTag);
    if (priority < 4)
    {
        structPtr->priority = priority;
        structPtr->oam.priority = priority;
    }
    SetAnimAndTileNum(structPtr, animNum);

    return structPtr->id;
}

u8 ConfettiUtil_Remove(u8 id)
{
    if (sWork == NULL || !sWork->array[id].active)
        return 0xFF;

    memset(&sWork->array[id], 0, sizeof(struct ConfettiUtil));
    sWork->array[id].oam.y = DISPLAY_HEIGHT;
    sWork->array[id].oam.x = DISPLAY_WIDTH;
    sWork->array[id].dummied = TRUE;
    memcpy(&gMain.oamBuffer[id + 64], &gDummyOamData, sizeof(struct OamData));
    return id;
}
