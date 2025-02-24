#include "global.h"
#include "constants/decorations.h"
#include "constants/mauville_old_man.h"
#include "decoration.h"
#include "decoration_inventory.h"
#include "event_data.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "script.h"
#include "constants/songs.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "script_menu.h"

static const u8 * const sDefaultTraderNames[] =
{
    gText_Tristan,
    gText_Philip,
    gText_Dennis,
    gText_Roberto,
};

static const u8 sDefaultTraderDecorations[] =
{
    DECOR_DUSKULL_DOLL,
    DECOR_BALL_CUSHION,
    DECOR_TIRE,
    DECOR_PRETTY_FLOWERS,
};

void TraderSetup(void)
{
    u32 i;
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;

    trader->id = MAUVILLE_MAN_TRADER;
    trader->alreadyTraded = FALSE;

    for (i = 0; i < 4; i++)
    {
        StringCopy(trader->playerNames[i], sDefaultTraderNames[i]);
        trader->decorations[i] = sDefaultTraderDecorations[i];
        trader->language[i] = GAME_LANGUAGE;
    }
}

void Trader_ResetFlag(void)
{
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;
    trader->alreadyTraded = FALSE;
}

void CreateAvailableDecorationsMenu(u8 taskId)
{
    u32 i;
    s16 * data = gTasks[taskId].data;
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;
    struct WindowTemplate windowTemplate = {0, 1, 1, 10, 10, 15, 1};
    s32 windowWidth = GetStringWidth(2, gText_Exit, 0);
    s32 fiveMarksWidth = GetStringWidth(2, gText_FiveMarks, 0);
    for (i = 0; i < 4; i++)
    {
        s32 curWidth;
        if (trader->decorations[i] > NUM_DECORATIONS)
            curWidth = fiveMarksWidth;
        else
            curWidth = GetStringWidth(2, gDecorations[trader->decorations[i]].name, 0);
        if (curWidth > windowWidth)
            windowWidth = curWidth;
    }
    windowTemplate.width = ConvertPixelWidthToTileWidth(windowWidth);
    data[3] = AddWindow(&windowTemplate);
    DrawStdFrameWithCustomTileAndPalette(data[3], FALSE, 0x214, 14);
    for (i = 0; i < 4; i++)
    {
        if (trader->decorations[i] > NUM_DECORATIONS)
            AddTextPrinterParameterized(data[3], 2, gText_FiveMarks, 8, 16 * i + 1, 255, NULL);
        else
            AddTextPrinterParameterized(data[3], 2, gDecorations[trader->decorations[i]].name, 8, 16 * i + 1, 255, NULL);
    }
    AddTextPrinterParameterized(data[3], 2, gText_Exit, 8, 16 * i + 1, 255, NULL);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(data[3], 2, 0, 1, 16, 5, 0);
    ScheduleBgCopyTilemapToVram(0);
}

void Task_BufferDecorSelectionAndCloseWindow(u8 taskId, u8 decorationId)
{
    s16 * data = gTasks[taskId].data;
    if (decorationId > NUM_DECORATIONS)
    {
        gSpecialVar_0x8004 = 0xFFFF;
    }
    else
    {
        gSpecialVar_0x8004 = decorationId;
    }

    ClearStdWindowAndFrameToTransparent(data[3], FALSE);
    ClearWindowTilemap(data[3]);
    RemoveWindow(data[3]);
    ScheduleBgCopyTilemapToVram(0);
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

void Task_HandleGetDecorationMenuInput(u8 taskId)
{
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;
    s8 input = Menu_ProcessInput();

    switch (input)
    {
        case MENU_NOTHING_CHOSEN:
            break;
        case MENU_B_PRESSED:
        case 4:
            PlaySE(SE_SELECT);
            Task_BufferDecorSelectionAndCloseWindow(taskId, 0);
            break;
        default:
            PlaySE(SE_SELECT);
            gSpecialVar_0x8005 = input;
            StringCopy(gStringVar1, trader->playerNames[input]);
            ConvertInternationalString(gStringVar1, trader->language[input]);
            Task_BufferDecorSelectionAndCloseWindow(taskId, trader->decorations[input]);
            break;
    }
}

void ScrSpecial_GetTraderTradedFlag(void)
{
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;
    gSpecialVar_Result = trader->alreadyTraded;
}

void ScrSpecial_DoesPlayerHaveNoDecorations(void)
{
    u32 i;

    for (i = 0; i < 8; i++)
    {
        if (GetNumOwnedDecorationsInCategory(i))
        {
            gSpecialVar_Result = FALSE;
            return;
        }
    }
    gSpecialVar_Result = TRUE;
}

void ScrSpecial_IsDecorationFull(void)
{
    gSpecialVar_Result = FALSE;
    if (gDecorations[gSpecialVar_0x8004].category != gDecorations[gSpecialVar_0x8006].category
        && GetFirstEmptyDecorSlot(gDecorations[gSpecialVar_0x8004].category) == -1)
    {
        CopyDecorationCategoryName(gStringVar2, gDecorations[gSpecialVar_0x8004].category);
        gSpecialVar_Result = TRUE;
    }
}

void ScrSpecial_TraderMenuGiveDecoration(void)
{
    CreateTask(ShowDecorationCategoriesWindow, 0);
}

void DecorationItemsMenuAction_Trade(u8 taskId)
{
    if (IsSelectedDecorInThePC() == TRUE)
    {
        gSpecialVar_0x8006 = gCurDecorationItems[gCurDecorationIndex];
        StringCopy(gStringVar3, gDecorations[gSpecialVar_0x8004].name);
        StringCopy(gStringVar2, gDecorations[gSpecialVar_0x8006].name);
    }
    else
    {
        gSpecialVar_0x8006 = 0xFFFF;
    }
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

void ExitTraderMenu(u8 taskId)
{
    gSpecialVar_0x8006 = 0;
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

void ScrSpecial_TraderDoDecorationTrade(void)
{
    struct MauvilleOldManTrader *trader = &gSaveBlock1Ptr->oldMan.trader;

    DecorationRemove(gSpecialVar_0x8006);
    DecorationAdd(gSpecialVar_0x8004);
    StringCopy(trader->playerNames[gSpecialVar_0x8005], gSaveBlock2Ptr->playerName);
    trader->decorations[gSpecialVar_0x8005] = gSpecialVar_0x8006;
    trader->language[gSpecialVar_0x8005] = GAME_LANGUAGE;
    trader->alreadyTraded = TRUE;
}

void ScrSpecial_TraderMenuGetDecoration(void)
{
    u8 taskId = CreateTask(Task_HandleGetDecorationMenuInput, 0);
    CreateAvailableDecorationsMenu(taskId);
}
