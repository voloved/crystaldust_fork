#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tv.h"
#include "bg.h"
#include "data.h"
#include "item.h"
#include "item_menu.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "party_menu.h"
#include "pokeball.h"
#include "pokemon.h"
#include "random.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/battle_string_ids.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/rgb.h"

// this file's functions
static void WallyHandleGetMonData(void);
static void WallyHandleGetRawMonData(void);
static void WallyHandleSetMonData(void);
static void WallyHandleSetRawMonData(void);
static void WallyHandleLoadMonSprite(void);
static void WallyHandleSwitchInAnim(void);
static void WallyHandleReturnMonToBall(void);
static void WallyHandleDrawTrainerPic(void);
static void WallyHandleTrainerSlide(void);
static void WallyHandleTrainerSlideBack(void);
static void WallyHandleFaintAnimation(void);
static void WallyHandlePaletteFade(void);
static void WallyHandleSuccessBallThrowAnim(void);
static void WallyHandleBallThrowAnim(void);
static void WallyHandlePause(void);
static void WallyHandleMoveAnimation(void);
static void WallyHandlePrintString(void);
static void WallyHandlePrintSelectionString(void);
static void WallyHandleChooseAction(void);
static void WallyHandleYesNoBox(void);
static void WallyHandleChooseMove(void);
static void WallyHandleChooseItem(void);
static void WallyHandleChoosePokemon(void);
static void WallyHandleCmd23(void);
static void WallyHandleHealthBarUpdate(void);
static void WallyHandleExpUpdate(void);
static void WallyHandleStatusIconUpdate(void);
static void WallyHandleStatusAnimation(void);
static void WallyHandleStatusXor(void);
static void WallyHandleDataTransfer(void);
static void WallyHandleDMA3Transfer(void);
static void WallyHandlePlayBGM(void);
static void WallyHandleCmd32(void);
static void WallyHandleTwoReturnValues(void);
static void WallyHandleChosenMonReturnValue(void);
static void WallyHandleOneReturnValue(void);
static void WallyHandleOneReturnValue_Duplicate(void);
static void WallyHandleClearUnkVar(void);
static void WallyHandleSetUnkVar(void);
static void WallyHandleClearUnkFlag(void);
static void WallyHandleToggleUnkFlag(void);
static void WallyHandleHitAnimation(void);
static void WallyHandleCantSwitch(void);
static void WallyHandlePlaySE(void);
static void WallyHandlePlayFanfareOrBGM(void);
static void WallyHandleFaintingCry(void);
static void WallyHandleIntroSlide(void);
static void WallyHandleIntroTrainerBallThrow(void);
static void WallyHandleDrawPartyStatusSummary(void);
static void WallyHandleHidePartyStatusSummary(void);
static void WallyHandleEndBounceEffect(void);
static void WallyHandleSpriteInvisibility(void);
static void WallyHandleBattleAnimation(void);
static void WallyHandleLinkStandbyMsg(void);
static void WallyHandleResetActionMoveSelection(void);
static void WallyHandleEndLinkBattle(void);
static void WallyCmdEnd(void);

static void WallyBufferRunCommand(void);
static void WallyBufferExecCompleted(void);
static void CompleteOnChosenItem(void);
static void Intro_WaitForShinyAnimAndHealthbox(void);
static u32 CopyWallyMonData(u8 monId, u8 *dst);
static void SetWallyMonData(u8 monId);
static void WallyDoMoveAnimation(void);
static void Task_StartSendOutAnim(u8 taskId);

static void (*const sWallyBufferCommands[CONTROLLER_CMDS_COUNT])(void) =
{
    [CONTROLLER_GETMONDATA]               = WallyHandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = WallyHandleGetRawMonData,
    [CONTROLLER_SETMONDATA]               = WallyHandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = WallyHandleSetRawMonData,
    [CONTROLLER_LOADMONSPRITE]            = WallyHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = WallyHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = WallyHandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = WallyHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = WallyHandleTrainerSlide,
    [CONTROLLER_TRAINERSLIDEBACK]         = WallyHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = WallyHandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = WallyHandlePaletteFade,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = WallyHandleSuccessBallThrowAnim,
    [CONTROLLER_BALLTHROWANIM]            = WallyHandleBallThrowAnim,
    [CONTROLLER_PAUSE]                    = WallyHandlePause,
    [CONTROLLER_MOVEANIMATION]            = WallyHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = WallyHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = WallyHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = WallyHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = WallyHandleYesNoBox,
    [CONTROLLER_CHOOSEMOVE]               = WallyHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = WallyHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = WallyHandleChoosePokemon,
    [CONTROLLER_23]                       = WallyHandleCmd23,
    [CONTROLLER_HEALTHBARUPDATE]          = WallyHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = WallyHandleExpUpdate,
    [CONTROLLER_STATUSICONUPDATE]         = WallyHandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = WallyHandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = WallyHandleStatusXor,
    [CONTROLLER_DATATRANSFER]             = WallyHandleDataTransfer,
    [CONTROLLER_DMA3TRANSFER]             = WallyHandleDMA3Transfer,
    [CONTROLLER_PLAYBGM]                  = WallyHandlePlayBGM,
    [CONTROLLER_32]                       = WallyHandleCmd32,
    [CONTROLLER_TWORETURNVALUES]          = WallyHandleTwoReturnValues,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = WallyHandleChosenMonReturnValue,
    [CONTROLLER_ONERETURNVALUE]           = WallyHandleOneReturnValue,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = WallyHandleOneReturnValue_Duplicate,
    [CONTROLLER_CLEARUNKVAR]              = WallyHandleClearUnkVar,
    [CONTROLLER_SETUNKVAR]                = WallyHandleSetUnkVar,
    [CONTROLLER_CLEARUNKFLAG]             = WallyHandleClearUnkFlag,
    [CONTROLLER_TOGGLEUNKFLAG]            = WallyHandleToggleUnkFlag,
    [CONTROLLER_HITANIMATION]             = WallyHandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = WallyHandleCantSwitch,
    [CONTROLLER_PLAYSE]                   = WallyHandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = WallyHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = WallyHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = WallyHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = WallyHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = WallyHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = WallyHandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = WallyHandleEndBounceEffect,
    [CONTROLLER_SPRITEINVISIBILITY]       = WallyHandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = WallyHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = WallyHandleLinkStandbyMsg,
    [CONTROLLER_RESETACTIONMOVESELECTION] = WallyHandleResetActionMoveSelection,
    [CONTROLLER_ENDLINKBATTLE]            = WallyHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = WallyCmdEnd
};

static void SpriteCB_Null7(void)
{
}

void SetControllerToWally(void)
{
    gBattlerControllerFuncs[gActiveBattler] = WallyBufferRunCommand;
    gBattleStruct->wallyBattleState = 0;
    gBattleStruct->wallyMovesState = 0;
    gBattleStruct->wallyWaitFrames = 0;
    gBattleStruct->wallyMoveFrames = 0;
}

static void WallyBufferRunCommand(void)
{
    if (gBattleControllerExecFlags & gBitTable[gActiveBattler])
    {
        if (gBattleBufferA[gActiveBattler][0] < ARRAY_COUNT(sWallyBufferCommands))
            sWallyBufferCommands[gBattleBufferA[gActiveBattler][0]]();
        else
            WallyBufferExecCompleted();
    }
}

static void WallyHandleActions(void)
{
    switch (gBattleStruct->wallyBattleState)
    {
    case 0:
        gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
        gBattleStruct->wallyBattleState++;
    case 1:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(0);
            ActionSelectionCreateCursorAt(1, 0);
            gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
            gBattleStruct->wallyBattleState++;
        }
        break;
    case 2:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(1, B_ACTION_USE_ITEM, 0);
            WallyBufferExecCompleted();
        }
        break;
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(void)
{
    if (gSprites[gBattlerSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        WallyBufferExecCompleted();
}

static void CompleteOnInactiveTextPrinter(void)
{
    if (!IsTextPrinterActive(0))
        WallyBufferExecCompleted();
}

static void CompleteOnFinishedAnimation(void)
{
    if (!gDoingBattleAnim)
        WallyBufferExecCompleted();
}

static void OpenBagAfterPaletteFade(void)
{
    if (!gPaletteFade.active)
    {
        gBattlerControllerFuncs[gActiveBattler] = CompleteOnChosenItem;
        ReshowBattleScreenDummy();
        FreeAllWindowBuffers();
        DoWallyTutorialBagMenu();
    }
}

static void CompleteOnChosenItem(void)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(1, gSpecialVar_ItemId);
        WallyBufferExecCompleted();
    }
}

static void Intro_TryShinyAnimShowHealthbox(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].triedShinyMonAnim 
     && !gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].ballAnimActive)
        TryShinyAnimation(gActiveBattler, &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].triedShinyMonAnim 
     && !gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].ballAnimActive)
        TryShinyAnimation(gActiveBattler ^ BIT_FLANK, &gPlayerParty[gBattlerPartyIndexes[gActiveBattler ^ BIT_FLANK]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].ballAnimActive
        && !gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].ballAnimActive
        && gSprites[gBattleControllerData[gActiveBattler]].callback == SpriteCallbackDummy
        && gSprites[gBattlerSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
    {
        if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            DestroySprite(&gSprites[gBattleControllerData[gActiveBattler ^ BIT_FLANK]]);
            UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler ^ BIT_FLANK], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler ^ BIT_FLANK]], HEALTHBOX_ALL);
            StartHealthboxSlideIn(gActiveBattler ^ BIT_FLANK);
            SetHealthboxSpriteVisible(gHealthboxSpriteIds[gActiveBattler ^ BIT_FLANK]);
        }
        DestroySprite(&gSprites[gBattleControllerData[gActiveBattler]]);
        UpdateHealthboxAttribute(gHealthboxSpriteIds[gActiveBattler], &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], HEALTHBOX_ALL);
        StartHealthboxSlideIn(gActiveBattler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[gActiveBattler]);

        gBattleSpritesDataPtr->animationData->introAnimActive = FALSE;
        gBattlerControllerFuncs[gActiveBattler] = Intro_WaitForShinyAnimAndHealthbox;
    }

}

static void Intro_WaitForShinyAnimAndHealthbox(void)
{
    bool32 healthboxAnimDone = FALSE;

    if (gSprites[gHealthboxSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        healthboxAnimDone = TRUE;

    if (healthboxAnimDone && gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].finishedShinyMonAnim
        && gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].finishedShinyMonAnim)
    {
        gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].finishedShinyMonAnim = FALSE;

        gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[gActiveBattler ^ BIT_FLANK].finishedShinyMonAnim = FALSE;

        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        CreateTask(Task_PlayerController_RestoreBgmAfterCry, 10);
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], gActiveBattler);

        WallyBufferExecCompleted();
    }
}

static void CompleteOnHealthbarDone(void)
{
    s16 hpValue = MoveBattleBar(gActiveBattler, gHealthboxSpriteIds[gActiveBattler], HEALTH_BAR, 0);

    SetHealthboxSpriteVisible(gHealthboxSpriteIds[gActiveBattler]);

    if (hpValue != -1)
    {
        UpdateHpTextInHealthbox(gHealthboxSpriteIds[gActiveBattler], hpValue, HP_CURRENT);
    }
    else
    {
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], gActiveBattler);
        WallyBufferExecCompleted();
    }
}

static void DoHitAnimBlinkSpriteEffect(void)
{
    u8 spriteId = gBattlerSpriteIds[gActiveBattler];

    if (gSprites[spriteId].data[1] == 32)
    {
        gSprites[spriteId].data[1] = 0;
        gSprites[spriteId].invisible = FALSE;
        gDoingBattleAnim = FALSE;
        WallyBufferExecCompleted();
    }
    else
    {
        if ((gSprites[spriteId].data[1] % 4) == 0)
            gSprites[spriteId].invisible ^= 1;
        gSprites[spriteId].data[1]++;
    }
}

static void DoSwitchOutAnimation(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].specialAnimActive)
    {
        FreeSpriteOamMatrix(&gSprites[gBattlerSpriteIds[gActiveBattler]]);
        DestroySprite(&gSprites[gBattlerSpriteIds[gActiveBattler]]);
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[gActiveBattler]);
        WallyBufferExecCompleted();
    }
}

static void CompleteOnBankSpriteCallbackDummy2(void)
{
    if (gSprites[gBattlerSpriteIds[gActiveBattler]].callback == SpriteCallbackDummy)
        WallyBufferExecCompleted();
}

static void CompleteOnFinishedBattleAnimation(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].animFromTableActive)
        WallyBufferExecCompleted();
}

static void WallyBufferExecCompleted(void)
{
    gBattlerControllerFuncs[gActiveBattler] = WallyBufferRunCommand;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        u8 playerId = GetMultiplayerId();

        PrepareBufferDataTransferLink(2, 4, &playerId);
        gBattleBufferA[gActiveBattler][0] = CONTROLLER_TERMINATOR_NOP;
    }
    else
    {
        gBattleControllerExecFlags &= ~gBitTable[gActiveBattler];
    }
}

static void CompleteOnFinishedStatusAnimation(void)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].statusAnimActive)
        WallyBufferExecCompleted();
}

static void WallyHandleGetMonData(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleGetRawMonData(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSetMonData(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSetRawMonData(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleLoadMonSprite(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSwitchInAnim(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleReturnMonToBall(void)
{
    WallyBufferExecCompleted();
}

#define sSpeedX data[0]

static void WallyHandleDrawTrainerPic(void)
{
    DecompressTrainerBackPic(TRAINER_BACK_PIC_DUDE, gActiveBattler);
    SetMultiuseSpriteTemplateToTrainerBack(TRAINER_BACK_PIC_DUDE, GetBattlerPosition(gActiveBattler));
    gBattlerSpriteIds[gActiveBattler] = CreateSprite(&gMultiuseSpriteTemplate,
                                               80,
                                               80 + 4 * (8 - gTrainerBackPicCoords[TRAINER_BACK_PIC_DUDE].size),
                                               30);
    gSprites[gBattlerSpriteIds[gActiveBattler]].oam.paletteNum = gActiveBattler;
    gSprites[gBattlerSpriteIds[gActiveBattler]].x2 = DISPLAY_WIDTH;
    gSprites[gBattlerSpriteIds[gActiveBattler]].sSpeedX = -2;
    gSprites[gBattlerSpriteIds[gActiveBattler]].callback = SpriteCB_TrainerSpawn;
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnBattlerSpriteCallbackDummy;
}

static void WallyHandleTrainerSlide(void)
{
    DecompressTrainerBackPic(TRAINER_BACK_PIC_DUDE, gActiveBattler);
    SetMultiuseSpriteTemplateToTrainerBack(TRAINER_BACK_PIC_DUDE, GetBattlerPosition(gActiveBattler));
    gBattlerSpriteIds[gActiveBattler] = CreateSprite(&gMultiuseSpriteTemplate,
                                               80,
                                               80 + 4 * (8 - gTrainerBackPicCoords[TRAINER_BACK_PIC_DUDE].size),
                                               30);
    gSprites[gBattlerSpriteIds[gActiveBattler]].oam.paletteNum = gActiveBattler;
    gSprites[gBattlerSpriteIds[gActiveBattler]].x2 = -96;
    gSprites[gBattlerSpriteIds[gActiveBattler]].sSpeedX = 2;
    gSprites[gBattlerSpriteIds[gActiveBattler]].callback = SpriteCB_TrainerSpawn;
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnBankSpriteCallbackDummy2;
}

#undef sSpeedX

static void WallyHandleTrainerSlideBack(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleFaintAnimation(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandlePaletteFade(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSuccessBallThrowAnim(void)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = BALL_3_SHAKES_SUCCESS;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnFinishedAnimation;
}

static void WallyHandleBallThrowAnim(void)
{
    u8 ballThrowCaseId = gBattleBufferA[gActiveBattler][1];

    gBattleSpritesDataPtr->animationData->ballThrowCaseId = ballThrowCaseId;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(gActiveBattler, gActiveBattler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[gActiveBattler] = CompleteOnFinishedAnimation;
}

static void WallyHandlePause(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleMoveAnimation(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandlePrintString(void)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16*)(&gBattleBufferA[gActiveBattler][2]);
    if (*stringId == STRINGID_INTROSENDOUT)
    {
        WallyBufferExecCompleted();
    }
    else
    {
        BufferStringBattle(*stringId);
        BattlePutTextOnWindow(gDisplayedStringBattle, 0);
        gBattlerControllerFuncs[gActiveBattler] = CompleteOnInactiveTextPrinter;
    }
}

static void WallyHandlePrintSelectionString(void)
{
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        WallyHandlePrintString();
    else
        WallyBufferExecCompleted();
}

static void HandleChooseActionAfterDma3(void)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = DISPLAY_HEIGHT;
        gBattlerControllerFuncs[gActiveBattler] = WallyHandleActions;
    }
}

static void WallyHandleChooseAction(void)
{
    s32 i;

    gBattlerControllerFuncs[gActiveBattler] = HandleChooseActionAfterDma3;
    BattlePutTextOnWindow(gText_BattleMenu, 2);

    for (i = 0; i < 4; i++)
        ActionSelectionDestroyCursorAt(i);

    ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(gText_WhatWillTheDudeDo);
    BattlePutTextOnWindow(gDisplayedStringBattle, 1);
}

static void WallyHandleYesNoBox(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleChooseMove(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleChooseItem(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[gActiveBattler] = OpenBagAfterPaletteFade;
    gBattlerInMenuId = gActiveBattler;
}

static void WallyHandleChoosePokemon(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleCmd23(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleHealthBarUpdate(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleExpUpdate(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleStatusIconUpdate(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleStatusAnimation(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleStatusXor(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleDataTransfer(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleDMA3Transfer(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandlePlayBGM(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleCmd32(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleTwoReturnValues(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleChosenMonReturnValue(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleOneReturnValue(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleOneReturnValue_Duplicate(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleClearUnkVar(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSetUnkVar(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleClearUnkFlag(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleToggleUnkFlag(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleHitAnimation(void)
{
    if (gSprites[gBattlerSpriteIds[gActiveBattler]].invisible == TRUE)
    {
        WallyBufferExecCompleted();
    }
    else
    {
        gDoingBattleAnim = TRUE;
        gSprites[gBattlerSpriteIds[gActiveBattler]].data[1] = 0;
        DoHitAnimHealthboxEffect(gActiveBattler);
        gBattlerControllerFuncs[gActiveBattler] = DoHitAnimBlinkSpriteEffect;
    }
}

static void WallyHandleCantSwitch(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandlePlaySE(void)
{
    PlaySE(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    WallyBufferExecCompleted();
}

static void WallyHandlePlayFanfareOrBGM(void)
{
    if (gBattleBufferA[gActiveBattler][3])
    {
        BattleStopLowHpSound();
        PlayBGM(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }
    else
    {
        PlayFanfare(gBattleBufferA[gActiveBattler][1] | (gBattleBufferA[gActiveBattler][2] << 8));
    }

    WallyBufferExecCompleted();
}

static void WallyHandleFaintingCry(void)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gActiveBattler]], MON_DATA_SPECIES);

    PlayCry1(species, 25);
    WallyBufferExecCompleted();
}

static void WallyHandleIntroSlide(void)
{
    HandleIntroSlide(gBattleBufferA[gActiveBattler][1]);
    gIntroSlideFlags |= 1;
    WallyBufferExecCompleted();
}

static void WallyHandleIntroTrainerBallThrow(void)
{
    if (gBattleSpritesDataPtr->healthBoxesData[gActiveBattler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[gActiveBattler]].func = Task_HidePartyStatusSummary;

    WallyBufferExecCompleted();
}

static void WallyHandleDrawPartyStatusSummary(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleHidePartyStatusSummary(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleEndBounceEffect(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleSpriteInvisibility(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleBattleAnimation(void)
{
    u8 animationId = gBattleBufferA[gActiveBattler][1];
    u16 argument = gBattleBufferA[gActiveBattler][2] | (gBattleBufferA[gActiveBattler][3] << 8);

    if (TryHandleLaunchBattleTableAnimation(gActiveBattler, gActiveBattler, gActiveBattler, animationId, argument))
        WallyBufferExecCompleted();
    else
        gBattlerControllerFuncs[gActiveBattler] = CompleteOnFinishedBattleAnimation;
}

static void WallyHandleLinkStandbyMsg(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleResetActionMoveSelection(void)
{
    WallyBufferExecCompleted();
}

static void WallyHandleEndLinkBattle(void)
{
    gBattleOutcome = gBattleBufferA[gActiveBattler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    WallyBufferExecCompleted();

    if (!(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER) && gBattleTypeFlags & BATTLE_TYPE_LINK)
        gBattlerControllerFuncs[gActiveBattler] = SetBattleEndCallbacks;
}

static void WallyCmdEnd(void)
{
}
