#include "global.h"
#include "berry.h"
#include "bike.h"
#include "field_camera.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "event_object_movement.h"
#include "gpu_regs.h"
#include "menu.h"
#include "overworld.h"
#include "rotating_gate.h"
#include "sprite.h"
#include "text.h"

EWRAM_DATA bool8 gUnusedBikeCameraAheadPanback = FALSE;

// Static type declarations
struct FieldCameraOffset
{
    u8 xPixelOffset;
    u8 yPixelOffset;
    u8 xTileOffset;
    u8 yTileOffset;
    bool8 copyBGToVRAM;
};

// static functions
static void RedrawMapSliceNorth(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout);
static void RedrawMapSliceSouth(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout);
static void RedrawMapSliceEast(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout);
static void RedrawMapSliceWest(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout);
static s32 MapPosToBgTilemapOffset(struct FieldCameraOffset *a, s32 x, s32 y);
static void DrawWholeMapViewInternal(int x, int y, const struct MapLayout *mapLayout);
static void DrawMetatileAt(const struct MapLayout *mapLayout, u32, int, int);
static void DrawMetatile(s32 a, u16 *b, u32 c);
static void CameraPanningCB_PanAhead(void);

// IWRAM bss vars
static struct FieldCameraOffset sFieldCameraOffset;
static s16 sHorizontalCameraPan;
static s16 sVerticalCameraPan;
static bool8 sBikeCameraPanFlag;
static void (*sFieldCameraPanningCallback)(void);

struct CameraObject gFieldCamera;
u16 gTotalCameraPixelOffsetY;
u16 gTotalCameraPixelOffsetX;

// text
static void ResetCameraOffset(struct FieldCameraOffset *cameraOffset)
{
    cameraOffset->xTileOffset = 0;
    cameraOffset->yTileOffset = 0;
    cameraOffset->xPixelOffset = 0;
    cameraOffset->yPixelOffset = 0;
    cameraOffset->copyBGToVRAM = TRUE;
}

static void AddCameraTileOffset(struct FieldCameraOffset *cameraOffset, u32 xOffset, u32 yOffset)
{
    cameraOffset->xTileOffset += xOffset;
    cameraOffset->xTileOffset %= 32;
    cameraOffset->yTileOffset += yOffset;
    cameraOffset->yTileOffset %= 32;
}

static void AddCameraPixelOffset(struct FieldCameraOffset *cameraOffset, u32 xOffset, u32 yOffset)
{
    cameraOffset->xPixelOffset += xOffset;
    cameraOffset->yPixelOffset += yOffset;
}

void ResetFieldCamera(void)
{
    ResetCameraOffset(&sFieldCameraOffset);
}

void FieldUpdateBgTilemapScroll(void)
{
    u32 r4, r5;
    r5 = sFieldCameraOffset.xPixelOffset + sHorizontalCameraPan;
    r4 = sVerticalCameraPan + sFieldCameraOffset.yPixelOffset + 8;

    SetGpuReg(REG_OFFSET_BG1HOFS, r5);
    SetGpuReg(REG_OFFSET_BG1VOFS, r4);
    SetGpuReg(REG_OFFSET_BG2HOFS, r5);
    SetGpuReg(REG_OFFSET_BG2VOFS, r4);
    SetGpuReg(REG_OFFSET_BG3HOFS, r5);
    SetGpuReg(REG_OFFSET_BG3VOFS, r4);
}

void GetCameraOffsetWithPan(s16 *x, s16 *y)
{
    *x = sFieldCameraOffset.xPixelOffset + sHorizontalCameraPan;
    *y = sFieldCameraOffset.yPixelOffset + sVerticalCameraPan + 8;
}

void DrawWholeMapView(void)
{
    DrawWholeMapViewInternal(gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y, gMapHeader.mapLayout);
    sFieldCameraOffset.copyBGToVRAM = TRUE;
}

static void DrawWholeMapViewInternal(int x, int y, const struct MapLayout *mapLayout)
{
    for (u32 i = 0; i < 32; i += 2)
    {
        u32 yOffset = ((sFieldCameraOffset.yTileOffset + i) & 31) * 32;

        for (u32 j = 0; j < 32; j += 2)
        {
            u32 xOffset = (sFieldCameraOffset.xTileOffset + j) & 31;
            DrawMetatileAt(mapLayout, yOffset + xOffset, x + (j >> 1), y + (i >> 1));
        }
    }
}

static void RedrawMapSlicesForCameraUpdate(struct FieldCameraOffset *cameraOffset, int x, int y)
{
    const struct MapLayout *mapLayout = gMapHeader.mapLayout;

    if (x > 0)
        RedrawMapSliceWest(cameraOffset, mapLayout);
    if (x < 0)
        RedrawMapSliceEast(cameraOffset, mapLayout);
    if (y > 0)
        RedrawMapSliceNorth(cameraOffset, mapLayout);
    if (y < 0)
        RedrawMapSliceSouth(cameraOffset, mapLayout);
    cameraOffset->copyBGToVRAM = TRUE;
}

static void RedrawMapSliceNorth(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout)
{
    u32 i;
    u32 temp;
    u32 r7;

    temp = cameraOffset->yTileOffset + 28;
    if (temp >= 32)
        temp -= 32;
    r7 = temp * 32;
    for (i = 0; i < 32; i += 2)
    {
        temp = cameraOffset->xTileOffset + i;
        if (temp >= 32)
            temp -= 32;
        DrawMetatileAt(mapLayout, r7 + temp, gSaveBlock1Ptr->pos.x + i / 2, gSaveBlock1Ptr->pos.y + 14);
    }
}

static void RedrawMapSliceSouth(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout)
{
    u32 i;
    u32 temp;
    u32 r7 = cameraOffset->yTileOffset * 32;

    for (i = 0; i < 32; i += 2)
    {
        temp = cameraOffset->xTileOffset + i;
        if (temp >= 32)
            temp -= 32;
        DrawMetatileAt(mapLayout, r7 + temp, gSaveBlock1Ptr->pos.x + i / 2, gSaveBlock1Ptr->pos.y);
    }
}

static void RedrawMapSliceEast(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout)
{
    u32 i;
    u32 temp;
    u32 r6 = cameraOffset->xTileOffset;

    for (i = 0; i < 32; i += 2)
    {
        temp = cameraOffset->yTileOffset + i;
        if (temp >= 32)
            temp -= 32;
        DrawMetatileAt(mapLayout, temp * 32 + r6, gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y + i / 2);
    }
}

static void RedrawMapSliceWest(struct FieldCameraOffset *cameraOffset, const struct MapLayout *mapLayout)
{
    u32 i;
    u32 temp;
    u32 r5 = cameraOffset->xTileOffset + 28;

    if (r5 >= 32)
        r5 -= 32;
    for (i = 0; i < 32; i += 2)
    {
        temp = cameraOffset->yTileOffset + i;
        if (temp >= 32)
            temp -= 32;
        DrawMetatileAt(mapLayout, temp * 32 + r5, gSaveBlock1Ptr->pos.x + 14, gSaveBlock1Ptr->pos.y + i / 2);
    }
}

void CurrentMapDrawMetatileAt(int x, int y)
{
    int offset = MapPosToBgTilemapOffset(&sFieldCameraOffset, x, y);

    if (offset >= 0)
    {
        DrawMetatileAt(gMapHeader.mapLayout, offset, x, y);
        sFieldCameraOffset.copyBGToVRAM = TRUE;
    }
}

void DrawDoorMetatileAt(int x, int y, u16 *arr)
{
    int offset = MapPosToBgTilemapOffset(&sFieldCameraOffset, x, y);

    if (offset >= 0)
    {
        DrawMetatile(1, arr, offset);
        sFieldCameraOffset.copyBGToVRAM = TRUE;
    }
}

static void DrawMetatileAt(const struct MapLayout *mapLayout, u32 offset, int x, int y)
{
    u32 metatileId = MapGridGetMetatileIdAt(x, y);
    u16 *metatiles;

    if (metatileId > NUM_METATILES_TOTAL)
        metatileId = 0;
    if (metatileId < NUM_METATILES_IN_PRIMARY)
        metatiles = mapLayout->primaryTileset->metatiles;
    else
    {
        metatiles = mapLayout->secondaryTileset->metatiles;
        metatileId -= NUM_METATILES_IN_PRIMARY;
    }
    DrawMetatile(MapGridGetMetatileLayerTypeAt(x, y), metatiles + metatileId * 8, offset);
}

static void DrawMetatile(s32 metatileLayerType, u16 *metatiles, u32 offset)
{
    switch (metatileLayerType)
    {
    case 2: // LAYER_TYPE_
        // Draw metatile's bottom layer to the bottom background layer.
        gBGTilemapBuffers3[offset] = metatiles[0];
        gBGTilemapBuffers3[offset + 1] = metatiles[1];
        gBGTilemapBuffers3[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers3[offset + 0x21] = metatiles[3];

        // Draw transparent tiles to the middle background layer.
        gBGTilemapBuffers1[offset] = 0;
        gBGTilemapBuffers1[offset + 1] = 0;
        gBGTilemapBuffers1[offset + 0x20] = 0;
        gBGTilemapBuffers1[offset + 0x21] = 0;

        // Draw metatile's top layer to the top background layer.
        gBGTilemapBuffers2[offset] = metatiles[4];
        gBGTilemapBuffers2[offset + 1] = metatiles[5];
        gBGTilemapBuffers2[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers2[offset + 0x21] = metatiles[7];
        break;
    case 1:  // LAYER_TYPE_COVERED_BY_OBJECTS
        // Draw metatile's bottom layer to the bottom background layer.
        gBGTilemapBuffers3[offset] = metatiles[0];
        gBGTilemapBuffers3[offset + 1] = metatiles[1];
        gBGTilemapBuffers3[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers3[offset + 0x21] = metatiles[3];

        // Draw metatile's top layer to the middle background layer.
        gBGTilemapBuffers1[offset] = metatiles[4];
        gBGTilemapBuffers1[offset + 1] = metatiles[5];
        gBGTilemapBuffers1[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers1[offset + 0x21] = metatiles[7];

        // Draw transparent tiles to the top background layer.
        gBGTilemapBuffers2[offset] = 0;
        gBGTilemapBuffers2[offset + 1] = 0;
        gBGTilemapBuffers2[offset + 0x20] = 0;
        gBGTilemapBuffers2[offset + 0x21] = 0;
        break;
    case 0: // LAYER_TYPE_NORMAL
        // Draw garbage to the bottom background layer.
        gBGTilemapBuffers3[offset] = 0x3014;
        gBGTilemapBuffers3[offset + 1] = 0x3014;
        gBGTilemapBuffers3[offset + 0x20] = 0x3014;
        gBGTilemapBuffers3[offset + 0x21] = 0x3014;

        // Draw metatile's bottom layer to the middle background layer.
        gBGTilemapBuffers1[offset] = metatiles[0];
        gBGTilemapBuffers1[offset + 1] = metatiles[1];
        gBGTilemapBuffers1[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers1[offset + 0x21] = metatiles[3];

        // Draw metatile's top layer to the top background layer, which covers object event sprites.
        gBGTilemapBuffers2[offset] = metatiles[4];
        gBGTilemapBuffers2[offset + 1] = metatiles[5];
        gBGTilemapBuffers2[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers2[offset + 0x21] = metatiles[7];
        break;
    }
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);
    ScheduleBgCopyTilemapToVram(3);
}

static s32 MapPosToBgTilemapOffset(struct FieldCameraOffset *cameraOffset, s32 x, s32 y)
{
    x -= gSaveBlock1Ptr->pos.x;
    x <<= 1;
    if (x >= 32 || x < 0)
        return -1;
    x += cameraOffset->xTileOffset;
    x &= 31;

    y = (y - gSaveBlock1Ptr->pos.y) << 1;
    if (y >= 32 || y < 0)
        return -1;
    y += cameraOffset->yTileOffset;
    y &= 31;

    return (y << 5) + x;
}

static void CameraUpdateCallback(struct CameraObject *fieldCamera)
{
    if (fieldCamera->spriteId != 0)
    {
        fieldCamera->movementSpeedX = gSprites[fieldCamera->spriteId].data[2];
        fieldCamera->movementSpeedY = gSprites[fieldCamera->spriteId].data[3];
    }
}

void ResetCameraUpdateInfo(void)
{
    gFieldCamera.movementSpeedX = 0;
    gFieldCamera.movementSpeedY = 0;
    gFieldCamera.x = 0;
    gFieldCamera.y = 0;
    gFieldCamera.spriteId = 0;
    gFieldCamera.callback = NULL;
}

u32 InitCameraUpdateCallback(u8 trackedSpriteId)
{
    if (gFieldCamera.spriteId != 0)
        DestroySprite(&gSprites[gFieldCamera.spriteId]);
    gFieldCamera.spriteId = AddCameraObject(trackedSpriteId);
    gFieldCamera.callback = CameraUpdateCallback;
    return 0;
}

void CameraUpdate(void)
{
    int deltaX;
    int deltaY;
    int curMovementOffsetY;
    int curMovementOffsetX;
    int movementSpeedX;
    int movementSpeedY;

    if (gFieldCamera.callback != NULL)
        gFieldCamera.callback(&gFieldCamera);
    movementSpeedX = gFieldCamera.movementSpeedX;
    movementSpeedY = gFieldCamera.movementSpeedY;
    deltaX = 0;
    deltaY = 0;
    curMovementOffsetX = gFieldCamera.x;
    curMovementOffsetY = gFieldCamera.y;


    if (curMovementOffsetX == 0 && movementSpeedX != 0)
    {
        if (movementSpeedX > 0)
            deltaX = 1;
        else
            deltaX = -1;
    }
    if (curMovementOffsetY == 0 && movementSpeedY != 0)
    {
        if (movementSpeedY > 0)
            deltaY = 1;
        else
            deltaY = -1;
    }
    if (curMovementOffsetX != 0 && curMovementOffsetX == -movementSpeedX)
    {
        if (movementSpeedX > 0)
            deltaX = 1;
        else
            deltaX = -1;
    }
    if (curMovementOffsetY != 0 && curMovementOffsetY == -movementSpeedY)
    {
        if (movementSpeedY > 0)
            deltaX = 1;
        else
            deltaX = -1;
    }

    gFieldCamera.x += movementSpeedX;
    gFieldCamera.x = gFieldCamera.x - 16 * (gFieldCamera.x / 16);
    gFieldCamera.y += movementSpeedY;
    gFieldCamera.y = gFieldCamera.y - 16 * (gFieldCamera.y / 16);

    if (deltaX != 0 || deltaY != 0)
    {
        CameraMove(deltaX, deltaY);
        UpdateObjectEventsForCameraUpdate(deltaX, deltaY);
        RotatingGatePuzzleCameraUpdate(deltaX, deltaY);
        SetBerryTreesSeen();
        AddCameraTileOffset(&sFieldCameraOffset, deltaX * 2, deltaY * 2);
        RedrawMapSlicesForCameraUpdate(&sFieldCameraOffset, deltaX * 2, deltaY * 2);
    }

    AddCameraPixelOffset(&sFieldCameraOffset, movementSpeedX, movementSpeedY);
    gTotalCameraPixelOffsetX -= movementSpeedX;
    gTotalCameraPixelOffsetY -= movementSpeedY;
}

void MoveCameraAndRedrawMap(int deltaX, int deltaY) //unused
{
    CameraMove(deltaX, deltaY);
    UpdateObjectEventsForCameraUpdate(deltaX, deltaY);
    DrawWholeMapView();
    gTotalCameraPixelOffsetX -= deltaX * 16;
    gTotalCameraPixelOffsetY -= deltaY * 16;
}

void SetCameraPanningCallback(void (*callback)(void))
{
    sFieldCameraPanningCallback = callback;
}

void SetCameraPanning(s16 a, s16 b)
{
    sHorizontalCameraPan = a;
    sVerticalCameraPan = b + 32;
}

void InstallCameraPanAheadCallback(void)
{
    sFieldCameraPanningCallback = CameraPanningCB_PanAhead;
    sBikeCameraPanFlag = FALSE;
    sHorizontalCameraPan = 0;
    sVerticalCameraPan = 32;
}

void UpdateCameraPanning(void)
{
    if (sFieldCameraPanningCallback != NULL)
        sFieldCameraPanningCallback();
    //Update sprite offset of overworld objects
    gSpriteCoordOffsetX = gTotalCameraPixelOffsetX - sHorizontalCameraPan;
    gSpriteCoordOffsetY = gTotalCameraPixelOffsetY - sVerticalCameraPan - 8;
}

static void CameraPanningCB_PanAhead(void)
{
    u32 var;

    if (gUnusedBikeCameraAheadPanback == FALSE)
    {
        InstallCameraPanAheadCallback();
    }
    else
    {
        // this code is never reached
        if (gPlayerAvatar.tileTransitionState == T_TILE_TRANSITION)
        {
            sBikeCameraPanFlag ^= 1;
            if (sBikeCameraPanFlag == FALSE)
                return;
        }
        else
        {
            sBikeCameraPanFlag = FALSE;
        }

        var = GetPlayerMovementDirection();
        if (var == 2)
        {
            if (sVerticalCameraPan > -8)
                sVerticalCameraPan -= 2;
        }
        else if (var == 1)
        {
            if (sVerticalCameraPan < 72)
                sVerticalCameraPan += 2;
        }
        else if (sVerticalCameraPan < 32)
        {
            sVerticalCameraPan += 2;
        }
        else if (sVerticalCameraPan > 32)
        {
            sVerticalCameraPan -= 2;
        }
    }
}
