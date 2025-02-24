#ifndef GUARD_MENU_H
#define GUARD_MENU_H

#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/pokemon.h"

#define MENU_NOTHING_CHOSEN -2
#define MENU_B_PRESSED -1

#define DLG_WINDOW_PALETTE_NUM 15
#define DLG_WINDOW_BASE_TILE_NUM 0x200
#define STD_WINDOW_PALETTE_NUM 14
#define STD_WINDOW_BASE_TILE_NUM 0x214

#define MENU_CURSOR_DELTA_NONE   0
#define MENU_CURSOR_DELTA_UP    -1
#define MENU_CURSOR_DELTA_DOWN   1
#define MENU_CURSOR_DELTA_LEFT  -1
#define MENU_CURSOR_DELTA_RIGHT  1

#define MENU_INFO_ICON_TYPE      (NUMBER_OF_MON_TYPES + 1)
#define MENU_INFO_ICON_POWER     (NUMBER_OF_MON_TYPES + 2)
#define MENU_INFO_ICON_ACCURACY  (NUMBER_OF_MON_TYPES + 3)
#define MENU_INFO_ICON_PP        (NUMBER_OF_MON_TYPES + 4)
#define MENU_INFO_ICON_EFFECT    (NUMBER_OF_MON_TYPES + 5)
#define MENU_INFO_ICON_BALL_RED  (NUMBER_OF_MON_TYPES + 6)
#define MENU_INFO_ICON_BALL_BLUE (NUMBER_OF_MON_TYPES + 7)
#define MENU_INFO_ICON_PHYSICAL  (NUMBER_OF_MON_TYPES + 8)
#define MENU_INFO_ICON_SPECIAL   (NUMBER_OF_MON_TYPES + 9)
#define MENU_INFO_ICON_STATUS    (NUMBER_OF_MON_TYPES + 10)  // Unused
#define MENU_INFO_ICON_PSS_PHYS  (NUMBER_OF_MON_TYPES + 11)
#define MENU_INFO_ICON_PSS_SPEC  (NUMBER_OF_MON_TYPES + 12)
#define MENU_INFO_ICON_PSS_STAT  (NUMBER_OF_MON_TYPES + 13)

enum
{
    SAVE_MENU_NAME,
    SAVE_MENU_CAUGHT,
    SAVE_MENU_PLAY_TIME,
    SAVE_MENU_LOCATION,
    SAVE_MENU_BADGES,
};

struct MenuAction
{
    const u8 *text;
    union {
        void (*void_u8)(u8);
        u8 (*u8_void)(void);
    } func;
};

enum
{
	YESNO_STANDARD,
	YESNO_PHONE_OVERWORLD,
	YESNO_PHONE_POKEGEAR,
};

extern const u16 gUnknown_0860F074[];

void FreeAllOverworldWindowBuffers(void);
void InitStandardTextBoxWindows(void);
void InitTextBoxGfxAndPrinters(void);
u16 RunTextPrintersAndIsPrinter0Active(void);
void LoadMessageBoxAndBorderGfx(void);
void LoadSignAndUserWindowBorderGfx(void);
void DrawDialogueFrame(u32 windowId, bool8 copyToVram);
void ClearStdWindowAndFrame(u32 windowId, bool8 copyToVram);
u16 AddTextPrinterParameterized2(u32 windowId, u8 fontId, const u8 *str, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16), u8 fgColor, u8 bgColor, u8 shadowColor);
void PrintPlayerNameOnWindow(u32, const u8*, u16, u16);
void ClearDialogWindowAndFrame(u32 windowId, bool8 copyToVram);
void SetStandardWindowBorderStyle(u32 windowId, bool8 copyToVram);
void DisplayYesNoMenuDefaultYes(void);
u32 GetPlayerTextSpeed(void);
u8 GetPlayerTextSpeedDelay(void);
void Menu_LoadStdPalAt(u16 arg0);
void AddTextPrinterWithCallbackForMessage(bool8 a1, void (*callback)(struct TextPrinterTemplate *, u16));
void sub_8199DF0(u32 bg, u8 a1, int a2, int a3);
void AddTextPrinterParameterized3(u32 windowId, u8 fontId, u8 left, u8 top, const u8 *color, s8 speed, const u8 *str);
void ClearStdWindowAndFrameToTransparent(u32 windowId, bool8 copyToVram);
void SetWindowTemplateFields(struct WindowTemplate* template, u8 priority, u8 tilemapLeft, u8 tilemapTop, u8 width, u8 height, u8 palNum, u16 baseBlock);
void DrawStdFrameWithCustomTileAndPalette(u32 windowId, bool8 copyToVram, u16 tileStart, u8 palette);
void ScheduleBgCopyTilemapToVram(u8 bgNum);
void PrintMenuTable(u32 windowId, u8 itemCount, const struct MenuAction *strs);
void MultichoiceList_PrintItems(u32 windowId, u8 fontId, u8 left, u8 top, u8 lineHeight, u8 itemCount, const struct MenuAction *strs, u8 letterSpacing, u8 lineSpacing);
u8 InitMenuInUpperLeftCornerPlaySoundWhenAPressed(u32 windowId, u8 fontId, u8 left, u8 top, u8 cursorHeight, u8 itemCount, u8 initialCursorPos);
u8 Menu_GetCursorPos(void);
s8 Menu_ProcessInput(void);
s8 Menu_ProcessInputNoWrap(void);
void BlitMenuInfoIcon(u32 windowId, u8 a2, u16 x, u16 y);
void ResetTempTileDataBuffers(void);
void *DecompressAndCopyTileDataToVram(u8 bgId, const void *src, u32 size, u16 offset, u8 mode);
bool8 FreeTempTileDataBuffersIfPossible(void);
struct WindowTemplate CreateWindowTemplate(u8 bg, u8 left, u8 top, u8 width, u8 height, u8 paletteNum, u16 baseBlock);
void CreateYesNoMenu(const struct WindowTemplate *windowTemplate, u8 fontId, u8 left, u8 top, u16 borderFirstTileNum, u8 borderPalette, u8 initialCursorPos);
void CreatePhoneYesNoMenu(const struct WindowTemplate *windowTemplate, u8 fontId, u8 left, u8 top, u16 borderFirstTileNum, u8 borderPalette, u8 initialCursorPos, bool8 fromOverworld);
void DecompressAndLoadBgGfxUsingHeap(u8 bgId, const void *src, u32 size, u16 offset, u8 mode);
s8 Menu_ProcessInputNoWrapClearOnChoose(void);
s8 ProcessMenuInput_other(void);
void DoScheduledBgTilemapCopiesToVram(void);
void ClearScheduledBgCopiesToVram(void);
void AddTextPrinterParameterized4(u32 windowId, u8 fontId, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, const u8 *color, s8 speed, const u8 *str);
void DrawDialogFrameWithCustomTileAndPalette(u32 windowId, bool8 copyToVram, u16 a2, u8 a3);
void sub_81995E4(u32 windowId, u8 optionsNo, const struct MenuAction *actions, const u8 *actionIds);
void ClearDialogWindowAndFrameToTransparent(u32 windowId, bool8 copyToVram);
u16 AddWindowParameterized(u8, u8, u8, u8, u8, u8, u16);
void *malloc_and_decompress(const void *src, u32 *sizeOut);
u16 copy_decompressed_tile_data_to_vram(u8 bgId, const void *src, u16 size, u16 offset, u8 mode);
void AddTextPrinterForMessage(bool8 allowSkippingDelayWithButtonPress);
void AddItemMenuActionTextPrinters(u32 windowId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineHeight, u8 itemCount, const struct MenuAction *strs, const u8 *a8);
void PrintMenuActionGrid(u32 windowId, u8 fontId, u8 left, u8 top, u8 a4, u8 itemCount, u8 itemCount2, const struct MenuAction *strs, const u8 *a8);
u8 InitMenuActionGrid(u32 windowId, u8 optionWidth, u8 columns, u8 rows, u8 initialCursorPos);
u8 ChangeListMenuCursorPosition(s8 deltaX, s8 deltaY);
u8 GetStartMenuWindowId(void);
void ListMenuLoadStdPalAt(u8, u8);
u8 Menu_MoveCursor(s32 cursorDelta);
u8 Menu_MoveCursorNoWrapAround(s8 cursorDelta);
void DrawStdWindowFrame(u32 windowId, bool8 CopyToVram);
u8 AddStartMenuWindow(u8 numActions);
u8 InitMenuNormal(u32 windowId, u8 fontId, u8 left, u8 top, u8 cursorHeight, u8 numChoices, u8 initialCursorPos);
void sub_819786C(u32 windowId, bool8 copyToVram);
void AddTextPrinterForMessage_IgnoreTextColor(bool8 allowSkippingDelayWithButtonPress);
void RemoveStartMenuWindow(void);
void DisplayYesNoMenuWithDefault(u8 initialCursorPos);
void BufferSaveMenuText(u8 textId, u8 *dest, u8 color);
void RemoveMapNamePopUpWindow(void);
u8 GetMapNamePopUpWindowId(void);
u8 AddMapNamePopUpWindow(void);
void AddTextPrinterParameterized5(u32 windowId, u8 fontId, const u8 *str, u8 left, u8 top, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16), u8 letterSpacing, u8 lineSpacing);
void SetBgTilemapPalette(u8 bgId, u8 left, u8 top, u8 width, u8 height, u8 palette);
void sub_8199D3C(void *ptr, int delta, int width, int height, bool32 is8BPP);
void sub_8198204(const u8 *string, const u8 *string2, u8 a3, u8 a4, bool8 copyToVram);
void sub_8197AE8(bool8 copyToVram);
void PrintMenuGridTable(u32 windowId, u8 optionWidth, u8 columns, u8 rows, const struct MenuAction *strs);
s8 Menu_ProcessInputGridLayout(void);
u8 InitMenuInUpperLeftCorner(u32 windowId, u8 fontId, u8 left, u8 top, u8 cursorHeight, u8 itemCount, u8 initialCursorPos, bool8 APressMuted);
s8 Menu_ProcessInputNoWrapAround_other(void);
void CopyToBufferFromBgTilemap(u8 bgId, u16 *dest, u8 left, u8 top, u8 width, u8 height);
u8 sub_81980F0(u8 bg, u8 xPos, u8 yPos, u8 palette, u16 baseTile);
void sub_8198314(void);
void sub_8198180(const u8 *string, u8 a2, bool8 copyToVram);
void ResetBgPositions(void);
void AddTextPrinterWithCustomSpeedForMessage(bool8 allowSkippingDelayWithButtonPress, u8 speed);
void sub_8198C78(void);
void PrintTextArray(u32 windowId, u8 fontId, u8 left, u8 top, u8 lineHeight, u8 itemCount, const struct MenuAction *strs);
u8 sub_81983EC(u32 windowId, u8 fontId, u8 left, u8 top, u8 numChoices, u8 initialCursorPos);

#endif // GUARD_MENU_H
