#include "global.h"
#include "graphics.h"
#include "palette.h"
#include "util.h"
#include "battle_transition.h"
#include "task.h"
#include "battle_transition.h"
#include "fieldmap.h"

static EWRAM_DATA struct {
    const u16 *src;
    u16 *dest;
    u16 size;
} sTilesetDMA3TransferBuffer[20] = {0};

static u8 sTilesetDMA3TransferBufferSize;
static u16 sPrimaryTilesetAnimCounter;
static u16 sPrimaryTilesetAnimCounterMax;
static u16 sSecondaryTilesetAnimCounter;
static u16 sSecondaryTilesetAnimCounterMax;
static void (*sPrimaryTilesetAnimCallback)(u16);
static void (*sSecondaryTilesetAnimCallback)(u16);

static void _InitPrimaryTilesetAnimation(void);
static void _InitSecondaryTilesetAnimation(void);
static void TilesetAnim_General(u16);
static void TilesetAnim_Building(u16);
static void TilesetAnim_Rustboro(u16);
static void TilesetAnim_Slateport(u16);
static void TilesetAnim_Mauville(u16);
static void TilesetAnim_BlackthornGym(u16);
static void TilesetAnim_PokemonLeague(u16);
static void TilesetAnim_DragonsDen_Shrine(u16);
static void TilesetAnim_EverGrande(u16);
static void TilesetAnim_Pacifidlog(u16);
static void TilesetAnim_Sootopolis(u16);
static void TilesetAnim_BattleFrontierOutsideWest(u16);
static void TilesetAnim_BattleFrontierOutsideEast(u16);
static void TilesetAnim_Underwater(u16);
static void TilesetAnim_SootopolisGym(u16);
static void TilesetAnim_EliteFour(u16);
static void TilesetAnim_AzaleaGym(u16);
static void TilesetAnim_GoldenrodGym(u16);
static void TilesetAnim_MauvilleGym(u16);
static void TilesetAnim_PagodaTower(u16);
static void TilesetAnim_PokemonDayCare(u16);
static void TilesetAnim_BattlePyramid(u16);
static void TilesetAnim_BattleDome(u16);
static void TilesetAnim_NationalPark(u16);
static void QueueAnimTiles_General_WaterFast(u16);
static void QueueAnimTiles_General_Water(u16);
static void QueueAnimTiles_General_Flower(u16);
static void QueueAnimTiles_General_Whirlpool(u16);
static void QueueAnimTiles_Building_TVTurnedOn(u16);
static void QueueAnimTiles_Rustboro_WindyWater(u16, u8);
static void QueueAnimTiles_Rustboro_Fountain(u16);
static void QueueAnimTiles_Dewford_Flag(u16);
static void QueueAnimTiles_Slateport_Balloons(u16);
static void QueueAnimTiles_Mauville_Flowers(u16, u8);
static void QueueAnimTiles_PagodaTower_SproutTowerPillar(u16);
static void QueueAnimTiles_PokemonDayCare_RedFlower(u16);
static void QueueAnimTiles_PokemonDayCare_YellowFlower(u16);
static void QueueAnimTiles_BattlePyramid_Torch(u16);
static void QueueAnimTiles_DragonsDen_Shrine_Torch(u16 timer);
static void QueueAnimTiles_DragonsDen_Shrine_TorchShadow(u16 timer);
static void QueueAnimTiles_BattlePyramid_StatueShadow(u16);
static void BlendAnimPalette_BattleDome_FloorLights(u16);
static void BlendAnimPalette_BattleDome_FloorLightsNoBlend(u16);
static void QueueAnimTiles_Lavaridge_Steam(u8);
static void QueueAnimTiles_BlackthornGym_Lava(u16);
static void QueueAnimTiles_PokemonLeague_Lava(u16);
static void QueueAnimTiles_EverGrande_Flowers(u16, u8);
static void QueueAnimTiles_Pacifidlog_LogBridges(u8);
static void QueueAnimTiles_Pacifidlog_WaterCurrents(u8);
static void QueueAnimTiles_Sootopolis_StormyWater(u16);
static void QueueAnimTiles_Underwater_Seaweed(u8);
static void QueueAnimTiles_BattleFrontierOutsideWest_Flower(u16);
static void QueueAnimTiles_BattleFrontierOutsideEast_Flower(u16);
static void QueueAnimTiles_BattleFrontierOutsideWest_Flag(u16);
static void QueueAnimTiles_BattleFrontierOutsideEast_Flag(u16);
static void QueueAnimTiles_AzaleaGym_Flowers(u16);
static void QueueAnimTiles_GoldenrodGym_Flowers(u16);
static void QueueAnimTiles_MauvilleGym_ElectricGates(u16);
static void QueueAnimTiles_SootopolisGym_Waterfalls(u16);
static void QueueAnimTiles_EliteFour_GroundLights(u16);
static void QueueAnimTiles_EliteFour_WallLights(u16);
static void QueueAnimTiles_NationalPark_LargeFountain(u16);
static void QueueAnimTiles_NationalPark_SmallFountain(u16);
static void QueueAnimTiles_NationalPark_RedFlower(u16);
static void QueueAnimTiles_NationalPark_YellowFlower(u16);

const u16 gTilesetAnims_General_WaterFast_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/0.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/1.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/2.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/3.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/4.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/5.4bpp");
const u16 gTilesetAnims_General_WaterFast_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/water_fast/6.4bpp");

const u16 *const gTilesetAnims_General_WaterFast[] = {
    gTilesetAnims_General_WaterFast_Frame0,
    gTilesetAnims_General_WaterFast_Frame1,
    gTilesetAnims_General_WaterFast_Frame2,
    gTilesetAnims_General_WaterFast_Frame3,
    gTilesetAnims_General_WaterFast_Frame4,
    gTilesetAnims_General_WaterFast_Frame5,
    gTilesetAnims_General_WaterFast_Frame6,
    gTilesetAnims_General_WaterFast_Frame0
};

const u16 gTilesetAnims_General_Water_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/water/0.4bpp");
const u16 gTilesetAnims_General_Water_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/water/1.4bpp");
const u16 gTilesetAnims_General_Water_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/water/2.4bpp");
const u16 gTilesetAnims_General_Water_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/water/3.4bpp");
const u16 gTilesetAnims_General_Water_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/water/4.4bpp");
const u16 gTilesetAnims_General_Water_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/water/5.4bpp");
const u16 gTilesetAnims_General_Water_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/water/6.4bpp");
const u16 gTilesetAnims_General_Water_Frame7[] = INCBIN_U16("data/tilesets/primary/general/anim/water/7.4bpp");

const u16 *const gTilesetAnims_General_Water[] = {
    gTilesetAnims_General_Water_Frame0,
    gTilesetAnims_General_Water_Frame1,
    gTilesetAnims_General_Water_Frame2,
    gTilesetAnims_General_Water_Frame3,
    gTilesetAnims_General_Water_Frame4,
    gTilesetAnims_General_Water_Frame5,
    gTilesetAnims_General_Water_Frame6,
    gTilesetAnims_General_Water_Frame7
};

const u16 gTilesetAnims_General_Flower_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/0.4bpp");
const u16 gTilesetAnims_General_Flower_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/1.4bpp");
const u16 gTilesetAnims_General_Flower_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/2.4bpp");
const u16 gTilesetAnims_General_Flower_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/3.4bpp");
const u16 gTilesetAnims_General_Flower_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/4.4bpp");

const u16 *const gTilesetAnims_General_Flower[] = {
    gTilesetAnims_General_Flower_Frame0,
    gTilesetAnims_General_Flower_Frame1,
    gTilesetAnims_General_Flower_Frame2,
    gTilesetAnims_General_Flower_Frame3,
    gTilesetAnims_General_Flower_Frame4
};

const u16 gTilesetAnims_General_Whirlpool_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/whirlpool/0.4bpp");
const u16 gTilesetAnims_General_Whirlpool_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/whirlpool/1.4bpp");
const u16 gTilesetAnims_General_Whirlpool_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/whirlpool/2.4bpp");
const u16 gTilesetAnims_General_Whirlpool_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/whirlpool/3.4bpp");

const u16 *const gTilesetAnims_General_Whirlpool[] = {
    gTilesetAnims_General_Whirlpool_Frame0,
    gTilesetAnims_General_Whirlpool_Frame1,
    gTilesetAnims_General_Whirlpool_Frame2,
    gTilesetAnims_General_Whirlpool_Frame3
};

const u16 gTilesetAnims_Lavaridge_Steam_Frame0[] = INCBIN_U16("data/tilesets/secondary/azalea/anim/steam/0.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame1[] = INCBIN_U16("data/tilesets/secondary/azalea/anim/steam/1.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame2[] = INCBIN_U16("data/tilesets/secondary/azalea/anim/steam/2.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame3[] = INCBIN_U16("data/tilesets/secondary/azalea/anim/steam/3.4bpp");

const u16 *const gTilesetAnims_Lavaridge_Steam[] = {
    gTilesetAnims_Lavaridge_Steam_Frame0,
    gTilesetAnims_Lavaridge_Steam_Frame1,
    gTilesetAnims_Lavaridge_Steam_Frame2,
    gTilesetAnims_Lavaridge_Steam_Frame3
};

const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/0.4bpp");
const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/1.4bpp");
const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/2.4bpp");

const u16 *const gTilesetAnims_Pacifidlog_LogBridges[] = {
    gTilesetAnims_Pacifidlog_LogBridges_Frame0,
    gTilesetAnims_Pacifidlog_LogBridges_Frame1,
    gTilesetAnims_Pacifidlog_LogBridges_Frame2,
    gTilesetAnims_Pacifidlog_LogBridges_Frame1
};

const u16 gTilesetAnims_Underwater_Seaweed_Frame0[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/0.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame1[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/1.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame2[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/2.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame3[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/3.4bpp");

const u16 *const gTilesetAnims_Underwater_Seaweed[] = {
    gTilesetAnims_Underwater_Seaweed_Frame0,
    gTilesetAnims_Underwater_Seaweed_Frame1,
    gTilesetAnims_Underwater_Seaweed_Frame2,
    gTilesetAnims_Underwater_Seaweed_Frame3
};

const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/0.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/1.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/2.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame3[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/3.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame4[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/4.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame5[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/5.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame6[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/6.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame7[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/7.4bpp");

const u16 *const gTilesetAnims_Pacifidlog_WaterCurrents[] = {
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame0,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame1,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame2,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame3,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame4,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame5,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame6,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame7
};

const u16 gTilesetAnims_Mauville_Flower1_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/0.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/1.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/2.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/3.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame4[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/4.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/0.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/1.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/2.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/3.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame4[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/4.4bpp");
const u16 tileset_anims_space_1[16] = {};

u16 *const gTilesetAnims_Mauville_Flower1_VDests[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 96)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 100)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 104)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 108)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 112)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 116)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 120)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 124))
};

u16 *const gTilesetAnims_Mauville_Flower2_VDests[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 128)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 132)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 136)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 140)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 148)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 152)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 156))
};

const u16 *const gTilesetAnims_Mauville_Flower1[] = {
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame1,
    gTilesetAnims_Mauville_Flower1_Frame2,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame2,
    gTilesetAnims_Mauville_Flower1_Frame1
};

const u16 *const gTilesetAnims_Mauville_Flower2[] = {
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame1,
    gTilesetAnims_Mauville_Flower2_Frame2,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame2,
    gTilesetAnims_Mauville_Flower2_Frame1
};

const u16 *const gTilesetAnims_Mauville_Flower1_B[] = {
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame4,
    gTilesetAnims_Mauville_Flower1_Frame4
};

const u16 *const gTilesetAnims_Mauville_Flower2_B[] = {
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame4,
    gTilesetAnims_Mauville_Flower2_Frame4
};

const u16 gTilesetAnims_Rustboro_WindyWater_Frame0[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/0.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame1[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/1.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame2[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/2.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame3[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/3.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame4[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/4.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame5[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/5.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame6[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/6.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame7[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/windy_water/7.4bpp");

u16 *const gTilesetAnims_Rustboro_WindyWater_VDests[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 128)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 132)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 136)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 140)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 148)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 152)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 156))
};

const u16 *const gTilesetAnims_Rustboro_WindyWater[] = {
    gTilesetAnims_Rustboro_WindyWater_Frame0,
    gTilesetAnims_Rustboro_WindyWater_Frame1,
    gTilesetAnims_Rustboro_WindyWater_Frame2,
    gTilesetAnims_Rustboro_WindyWater_Frame3,
    gTilesetAnims_Rustboro_WindyWater_Frame4,
    gTilesetAnims_Rustboro_WindyWater_Frame5,
    gTilesetAnims_Rustboro_WindyWater_Frame6,
    gTilesetAnims_Rustboro_WindyWater_Frame7
};

const u16 gTilesetAnims_Rustboro_Fountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/fountain/0.4bpp");
const u16 gTilesetAnims_Rustboro_Fountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/goldenrod/anim/fountain/1.4bpp");
const u16 tileset_anims_space_2[16] = {};

const u16 *const gTilesetAnims_Rustboro_Fountain[] = {
    gTilesetAnims_Rustboro_Fountain_Frame0,
    gTilesetAnims_Rustboro_Fountain_Frame1
};

const u16 gTilesetAnims_BlackthornCity_Gym_Lava_Frame0[] = INCBIN_U16("data/tilesets/secondary/blackthorngym/anim/lava/0.4bpp");
const u16 gTilesetAnims_BlackthornCity_Gym_Lava_Frame1[] = INCBIN_U16("data/tilesets/secondary/blackthorngym/anim/lava/1.4bpp");
const u16 gTilesetAnims_BlackthornCity_Gym_Lava_Frame2[] = INCBIN_U16("data/tilesets/secondary/blackthorngym/anim/lava/2.4bpp");
const u16 gTilesetAnims_BlackthornCity_Gym_Lava_Frame3[] = INCBIN_U16("data/tilesets/secondary/blackthorngym/anim/lava/3.4bpp");

const u16 *const gTilesetAnims_BlackthornCity_Gym_Lava[] = {
    gTilesetAnims_BlackthornCity_Gym_Lava_Frame0,
    gTilesetAnims_BlackthornCity_Gym_Lava_Frame1,
    gTilesetAnims_BlackthornCity_Gym_Lava_Frame2,
    gTilesetAnims_BlackthornCity_Gym_Lava_Frame3
};

const u16 gTilesetAnims_PokemonLeague_Lava_Frame0[] = INCBIN_U16("data/tilesets/secondary/pokemonleague/anim/lava/0.4bpp");
const u16 gTilesetAnims_PokemonLeague_Lava_Frame1[] = INCBIN_U16("data/tilesets/secondary/pokemonleague/anim/lava/1.4bpp");
const u16 gTilesetAnims_PokemonLeague_Lava_Frame2[] = INCBIN_U16("data/tilesets/secondary/pokemonleague/anim/lava/2.4bpp");
const u16 gTilesetAnims_PokemonLeague_Lava_Frame3[] = INCBIN_U16("data/tilesets/secondary/pokemonleague/anim/lava/3.4bpp");

const u16 *const gTilesetAnims_PokemonLeague_Lava[] = {
    gTilesetAnims_PokemonLeague_Lava_Frame0,
    gTilesetAnims_PokemonLeague_Lava_Frame1,
    gTilesetAnims_PokemonLeague_Lava_Frame2,
    gTilesetAnims_PokemonLeague_Lava_Frame3
};

const u16 gTilesetAnims_EverGrande_Flowers_Frame0[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/0.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame1[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/1.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame2[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/2.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame3[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/3.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame4[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/4.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame5[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/5.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame6[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/6.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame7[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/7.4bpp");
const u16 tileset_anims_space_4[16] = {};

u16 *const gTilesetAnims_EverGrande_VDests[] = {
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 224)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 228)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 232)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 236)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 240)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 244)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 248)),
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 252))
};

const u16 *const gTilesetAnims_EverGrande_Flowers[] = {
    gTilesetAnims_EverGrande_Flowers_Frame0,
    gTilesetAnims_EverGrande_Flowers_Frame1,
    gTilesetAnims_EverGrande_Flowers_Frame2,
    gTilesetAnims_EverGrande_Flowers_Frame3,
    gTilesetAnims_EverGrande_Flowers_Frame4,
    gTilesetAnims_EverGrande_Flowers_Frame5,
    gTilesetAnims_EverGrande_Flowers_Frame6,
    gTilesetAnims_EverGrande_Flowers_Frame7
};

const u16 gTilesetAnims_Dewford_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/violet/anim/flag/0.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/violet/anim/flag/1.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/violet/anim/flag/2.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/violet/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_Dewford_Flag[] = {
    gTilesetAnims_Dewford_Flag_Frame0,
    gTilesetAnims_Dewford_Flag_Frame1,
    gTilesetAnims_Dewford_Flag_Frame2,
    gTilesetAnims_Dewford_Flag_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/2.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideWest_Flag[] = {
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame0,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame1,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame2,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/2.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideEast_Flag[] = {
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame0,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame1,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame2,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flower/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flower/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flower/2.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideWest_Flower[] = {
    gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame0,
    gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame1,
    gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame0,
    gTilesetAnims_BattleFrontierOutsideWest_Flower_Frame2
};

const u16 gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flower/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flower/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flower/2.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideEast_Flower[] = {
    gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame0,
    gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame1,
    gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame0,
    gTilesetAnims_BattleFrontierOutsideEast_Flower_Frame2
};

const u16 gTilesetAnims_Slateport_Balloons_Frame0[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/0.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame1[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/1.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame2[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/2.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame3[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/3.4bpp");

const u16 *const gTilesetAnims_Slateport_Balloons[] = {
    gTilesetAnims_Slateport_Balloons_Frame0,
    gTilesetAnims_Slateport_Balloons_Frame1,
    gTilesetAnims_Slateport_Balloons_Frame2,
    gTilesetAnims_Slateport_Balloons_Frame3
};

const u16 gTilesetAnims_Building_TvTurnedOn_Frame0[] = INCBIN_U16("data/tilesets/primary/building/anim/tv_turned_on/0.4bpp");
const u16 gTilesetAnims_Building_TvTurnedOn_Frame1[] = INCBIN_U16("data/tilesets/primary/building/anim/tv_turned_on/1.4bpp");

const u16 *const gTilesetAnims_Building_TvTurnedOn[] = {
    gTilesetAnims_Building_TvTurnedOn_Frame0,
    gTilesetAnims_Building_TvTurnedOn_Frame1
};

const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/0.4bpp");
const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/1.4bpp");
const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/2.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/0.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/1.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/2.4bpp");

const u16 *const gTilesetAnims_SootopolisGym_SideWaterfall[] = {
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame0,
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame1,
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame2
};

const u16 *const gTilesetAnims_SootopolisGym_FrontWaterfall[] = {
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame0,
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame1,
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame2
};

const u16 gTilesetAnims_EliteFour_FloorLight_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/floor_light/0.4bpp");
const u16 gTilesetAnims_EliteFour_FloorLight_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/floor_light/1.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/0.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/1.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame2[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/2.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame3[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/3.4bpp");
const u16 tileset_anims_space_5[16] = {};

const u16 *const gTilesetAnims_EliteFour_WallLights[] = {
    gTilesetAnims_EliteFour_WallLights_Frame0,
    gTilesetAnims_EliteFour_WallLights_Frame1,
    gTilesetAnims_EliteFour_WallLights_Frame2,
    gTilesetAnims_EliteFour_WallLights_Frame3
};

const u16 *const gTilesetAnims_EliteFour_FloorLight[] = {
    gTilesetAnims_EliteFour_FloorLight_Frame0,
    gTilesetAnims_EliteFour_FloorLight_Frame1
};

const u16 gTilesetAnims_AzaleaGym_Flowers_Frame0[] = INCBIN_U16("data/tilesets/secondary/azalea_gym/anim/flowers/0.4bpp");
const u16 gTilesetAnims_AzaleaGym_Flowers_Frame1[] = INCBIN_U16("data/tilesets/secondary/azalea_gym/anim/flowers/1.4bpp");
const u16 gTilesetAnims_AzaleaGym_Flowers_Frame2[] = INCBIN_U16("data/tilesets/secondary/azalea_gym/anim/flowers/2.4bpp");

const u16 *const gTilesetAnims_AzaleaGym_Flowers[] = {
    gTilesetAnims_AzaleaGym_Flowers_Frame0,
    gTilesetAnims_AzaleaGym_Flowers_Frame1,
    gTilesetAnims_AzaleaGym_Flowers_Frame2,
    gTilesetAnims_AzaleaGym_Flowers_Frame1,
};

const u16 gTilesetAnims_GoldenrodGym_Flowers_Frame0[] = INCBIN_U16("data/tilesets/secondary/goldenrod_gym/anim/flowers/0.4bpp");
const u16 gTilesetAnims_GoldenrodGym_Flowers_Frame1[] = INCBIN_U16("data/tilesets/secondary/goldenrod_gym/anim/flowers/1.4bpp");
const u16 gTilesetAnims_GoldenrodGym_Flowers_Frame2[] = INCBIN_U16("data/tilesets/secondary/goldenrod_gym/anim/flowers/2.4bpp");

const u16 *const gTilesetAnims_GoldenrodGym_Flowers[] = {
    gTilesetAnims_GoldenrodGym_Flowers_Frame0,
    gTilesetAnims_GoldenrodGym_Flowers_Frame1,
    gTilesetAnims_GoldenrodGym_Flowers_Frame2,
    gTilesetAnims_GoldenrodGym_Flowers_Frame1,
};

const u16 gTilesetAnims_MauvilleGym_ElectricGates_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/electric_gates/0.4bpp");
const u16 gTilesetAnims_MauvilleGym_ElectricGates_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/electric_gates/1.4bpp");

const u16 *const gTilesetAnims_MauvilleGym_ElectricGates[] = {
    gTilesetAnims_MauvilleGym_ElectricGates_Frame0,
    gTilesetAnims_MauvilleGym_ElectricGates_Frame1
};

const u16 gTilesetAnims_PagodaTower_SproutTowerPillar_Frame0[] = INCBIN_U16("data/tilesets/secondary/pagoda_tower/anim/sprout_tower_pillar/0.4bpp");
const u16 gTilesetAnims_PagodaTower_SproutTowerPillar_Frame1[] = INCBIN_U16("data/tilesets/secondary/pagoda_tower/anim/sprout_tower_pillar/1.4bpp");
const u16 gTilesetAnims_PagodaTower_SproutTowerPillar_Frame2[] = INCBIN_U16("data/tilesets/secondary/pagoda_tower/anim/sprout_tower_pillar/2.4bpp");
const u16 gTilesetAnims_PagodaTower_SproutTowerPillar_Frame3[] = INCBIN_U16("data/tilesets/secondary/pagoda_tower/anim/sprout_tower_pillar/3.4bpp");
const u16 gTilesetAnims_PagodaTower_SproutTowerPillar_Frame7[] = INCBIN_U16("data/tilesets/secondary/pagoda_tower/anim/sprout_tower_pillar/7.4bpp");

const u16 *const gTilesetAnims_PagodaTower_SproutTowerPillar[] = {
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame0,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame1,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame2,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame3,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame2,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame1,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame0,
    gTilesetAnims_PagodaTower_SproutTowerPillar_Frame7,
};

const u16 gTilesetAnims_PokemonDayCare_RedFlower_Frame0[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/red_flower/0.4bpp");
const u16 gTilesetAnims_PokemonDayCare_RedFlower_Frame1[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/red_flower/1.4bpp");
const u16 gTilesetAnims_PokemonDayCare_RedFlower_Frame2[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/red_flower/2.4bpp");

const u16 *const gTilesetAnims_PokemonDayCare_RedFlower[] = {
    gTilesetAnims_PokemonDayCare_RedFlower_Frame0,
    gTilesetAnims_PokemonDayCare_RedFlower_Frame1,
    gTilesetAnims_PokemonDayCare_RedFlower_Frame2,
    gTilesetAnims_PokemonDayCare_RedFlower_Frame1
};

const u16 gTilesetAnims_PokemonDayCare_YellowFlower_Frame0[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/yellow_flower/0.4bpp");
const u16 gTilesetAnims_PokemonDayCare_YellowFlower_Frame1[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/yellow_flower/1.4bpp");
const u16 gTilesetAnims_PokemonDayCare_YellowFlower_Frame2[] = INCBIN_U16("data/tilesets/secondary/pokemon_day_care/anim/yellow_flower/2.4bpp");

const u16 *const gTilesetAnims_PokemonDayCare_YellowFlower[] = {
    gTilesetAnims_PokemonDayCare_YellowFlower_Frame0,
    gTilesetAnims_PokemonDayCare_YellowFlower_Frame1,
    gTilesetAnims_PokemonDayCare_YellowFlower_Frame2,
    gTilesetAnims_PokemonDayCare_YellowFlower_Frame1
};

const u16 gTilesetAnims_Sootopolis_StormyWater_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/0.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/1.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/2.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame3[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/3.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame4[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/4.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame5[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/5.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame6[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/6.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame7[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/7.4bpp");

const u16 *const gTilesetAnims_Sootopolis_StormyWater[] = {
    gTilesetAnims_Sootopolis_StormyWater_Frame0,
    gTilesetAnims_Sootopolis_StormyWater_Frame1,
    gTilesetAnims_Sootopolis_StormyWater_Frame2,
    gTilesetAnims_Sootopolis_StormyWater_Frame3,
    gTilesetAnims_Sootopolis_StormyWater_Frame4,
    gTilesetAnims_Sootopolis_StormyWater_Frame5,
    gTilesetAnims_Sootopolis_StormyWater_Frame6,
    gTilesetAnims_Sootopolis_StormyWater_Frame7
};

const u16 gTilesetAnims_DragonsDen_Shrine_Torch_Frame0[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch/0.4bpp");
const u16 gTilesetAnims_DragonsDen_Shrine_Torch_Frame1[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch/1.4bpp");
const u16 gTilesetAnims_DragonsDen_Shrine_Torch_Frame2[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch/2.4bpp");

const u16 *const gTilesetAnims_DragonsDen_Shrine_Torch[] = {
    gTilesetAnims_DragonsDen_Shrine_Torch_Frame0,
    gTilesetAnims_DragonsDen_Shrine_Torch_Frame1,
    gTilesetAnims_DragonsDen_Shrine_Torch_Frame2
};

const u16 gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame0[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch_shadow/0.4bpp");
const u16 gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame1[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch_shadow/1.4bpp");
const u16 gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame2[] = INCBIN_U16("data/tilesets/secondary/dragonsden_shrine/anim/torch_shadow/2.4bpp");

const u16 *const gTilesetAnims_DragonsDen_Shrine_TorchShadow[] = {
    gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame0,
    gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame1,
    gTilesetAnims_DragonsDen_Shrine_TorchShadow_Frame2
};

const u16 gTilesetAnims_BattlePyramid_Torch_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/0.4bpp");
const u16 gTilesetAnims_BattlePyramid_Torch_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/1.4bpp");
const u16 gTilesetAnims_BattlePyramid_Torch_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/2.4bpp");
const u16 tileset_anims_space_9[16] = {};

const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/0.4bpp");
const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/1.4bpp");
const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/2.4bpp");

const u16 *const gTilesetAnims_BattlePyramid_Torch[] = {
    gTilesetAnims_BattlePyramid_Torch_Frame0,
    gTilesetAnims_BattlePyramid_Torch_Frame1,
    gTilesetAnims_BattlePyramid_Torch_Frame2
};

const u16 *const gTilesetAnims_BattlePyramid_StatueShadow[] = {
    gTilesetAnims_BattlePyramid_StatueShadow_Frame0,
    gTilesetAnims_BattlePyramid_StatueShadow_Frame1,
    gTilesetAnims_BattlePyramid_StatueShadow_Frame2
};

static const u16 *const gTilesetAnims_BattleDomeFloorLightPals[] = {
    gTilesetAnims_BattleDomePals0_0,
    gTilesetAnims_BattleDomePals0_1,
    gTilesetAnims_BattleDomePals0_2,
    gTilesetAnims_BattleDomePals0_3,
};

const u16 gTilesetAnims_NationalPark_LargeFountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/large_fountain/0.4bpp");
const u16 gTilesetAnims_NationalPark_LargeFountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/large_fountain/1.4bpp");
const u16 gTilesetAnims_NationalPark_LargeFountain_Frame2[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/large_fountain/2.4bpp");
const u16 gTilesetAnims_NationalPark_LargeFountain_Frame3[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/large_fountain/3.4bpp");

const u16 *const gTilesetAnims_NationalPark_LargeFountain[] = {
    gTilesetAnims_NationalPark_LargeFountain_Frame0,
    gTilesetAnims_NationalPark_LargeFountain_Frame1,
    gTilesetAnims_NationalPark_LargeFountain_Frame2,
    gTilesetAnims_NationalPark_LargeFountain_Frame3
};

const u16 gTilesetAnims_NationalPark_SmallFountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/small_fountain/0.4bpp");
const u16 gTilesetAnims_NationalPark_SmallFountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/small_fountain/1.4bpp");
const u16 gTilesetAnims_NationalPark_SmallFountain_Frame2[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/small_fountain/2.4bpp");
const u16 gTilesetAnims_NationalPark_SmallFountain_Frame3[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/small_fountain/3.4bpp");
const u16 gTilesetAnims_NationalPark_SmallFountain_Frame4[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/small_fountain/4.4bpp");

const u16 *const gTilesetAnims_NationalPark_SmallFountain[] = {
    gTilesetAnims_NationalPark_SmallFountain_Frame0,
    gTilesetAnims_NationalPark_SmallFountain_Frame1,
    gTilesetAnims_NationalPark_SmallFountain_Frame2,
    gTilesetAnims_NationalPark_SmallFountain_Frame3,
    gTilesetAnims_NationalPark_SmallFountain_Frame4
};

const u16 gTilesetAnims_NationalPark_RedFlower_Frame0[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/red_flower/0.4bpp");
const u16 gTilesetAnims_NationalPark_RedFlower_Frame1[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/red_flower/1.4bpp");
const u16 gTilesetAnims_NationalPark_RedFlower_Frame2[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/red_flower/2.4bpp");

const u16 *const gTilesetAnims_NationalPark_RedFlower[] = {
    gTilesetAnims_NationalPark_RedFlower_Frame0,
    gTilesetAnims_NationalPark_RedFlower_Frame1,
    gTilesetAnims_NationalPark_RedFlower_Frame2,
    gTilesetAnims_NationalPark_RedFlower_Frame1
};

const u16 gTilesetAnims_NationalPark_YellowFlower_Frame0[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/yellow_flower/0.4bpp");
const u16 gTilesetAnims_NationalPark_YellowFlower_Frame1[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/yellow_flower/1.4bpp");
const u16 gTilesetAnims_NationalPark_YellowFlower_Frame2[] = INCBIN_U16("data/tilesets/secondary/national_park/anim/yellow_flower/2.4bpp");

const u16 *const gTilesetAnims_NationalPark_YellowFlower[] = {
    gTilesetAnims_NationalPark_YellowFlower_Frame2,
    gTilesetAnims_NationalPark_YellowFlower_Frame1,
    gTilesetAnims_NationalPark_YellowFlower_Frame0,
    gTilesetAnims_NationalPark_YellowFlower_Frame1
};

static const u16 sTilesetAnims_SilphCo_Fountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/silphco/anim/fountain/0.4bpp");
static const u16 sTilesetAnims_SilphCo_Fountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/silphco/anim/fountain/1.4bpp");
static const u16 sTilesetAnims_SilphCo_Fountain_Frame2[] = INCBIN_U16("data/tilesets/secondary/silphco/anim/fountain/2.4bpp");
static const u16 sTilesetAnims_SilphCo_Fountain_Frame3[] = INCBIN_U16("data/tilesets/secondary/silphco/anim/fountain/3.4bpp");

static const u16 *const sTilesetAnims_SilphCo_Fountain[] = {
    sTilesetAnims_SilphCo_Fountain_Frame0,
    sTilesetAnims_SilphCo_Fountain_Frame1,
    sTilesetAnims_SilphCo_Fountain_Frame2,
    sTilesetAnims_SilphCo_Fountain_Frame3
};

static const u16 sTilesetAnims_CeladonCity_Fountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/celadoncity/anim/fountain/0.4bpp");
static const u16 sTilesetAnims_CeladonCity_Fountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/celadoncity/anim/fountain/1.4bpp");
static const u16 sTilesetAnims_CeladonCity_Fountain_Frame2[] = INCBIN_U16("data/tilesets/secondary/celadoncity/anim/fountain/2.4bpp");
static const u16 sTilesetAnims_CeladonCity_Fountain_Frame3[] = INCBIN_U16("data/tilesets/secondary/celadoncity/anim/fountain/3.4bpp");
static const u16 sTilesetAnims_CeladonCity_Fountain_Frame4[] = INCBIN_U16("data/tilesets/secondary/celadoncity/anim/fountain/4.4bpp");

static const u16 *const sTilesetAnims_CeladonCity_Fountain[] = {
    sTilesetAnims_CeladonCity_Fountain_Frame0,
    sTilesetAnims_CeladonCity_Fountain_Frame1,
    sTilesetAnims_CeladonCity_Fountain_Frame2,
    sTilesetAnims_CeladonCity_Fountain_Frame3,
    sTilesetAnims_CeladonCity_Fountain_Frame4
};

static void ResetTilesetAnimBuffer(void)
{
    sTilesetDMA3TransferBufferSize = 0;
    CpuFill32(0, sTilesetDMA3TransferBuffer, sizeof sTilesetDMA3TransferBuffer);
}

static void AppendTilesetAnimToBuffer(const u16 *src, u16 *dest, u16 size)
{
    if (sTilesetDMA3TransferBufferSize < 20)
    {
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].src = src;
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].dest = dest;
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].size = size;
        sTilesetDMA3TransferBufferSize ++;
    }
}

void TransferTilesetAnimsBuffer(void)
{
    int i;

    for (i = 0; i < sTilesetDMA3TransferBufferSize; i ++)
        DmaCopy16(3, sTilesetDMA3TransferBuffer[i].src, sTilesetDMA3TransferBuffer[i].dest, sTilesetDMA3TransferBuffer[i].size);

    sTilesetDMA3TransferBufferSize = 0;
}

void InitTilesetAnimations(void)
{
    ResetTilesetAnimBuffer();
    _InitPrimaryTilesetAnimation();
    _InitSecondaryTilesetAnimation();
}

void InitSecondaryTilesetAnimation(void)
{
    _InitSecondaryTilesetAnimation();
}

void UpdateTilesetAnimations(void)
{
    ResetTilesetAnimBuffer();
    if (++sPrimaryTilesetAnimCounter >= sPrimaryTilesetAnimCounterMax)
        sPrimaryTilesetAnimCounter = 0;
    if (++sSecondaryTilesetAnimCounter >= sSecondaryTilesetAnimCounterMax)
        sSecondaryTilesetAnimCounter = 0;

    if (sPrimaryTilesetAnimCallback)
        sPrimaryTilesetAnimCallback(sPrimaryTilesetAnimCounter);
    if (sSecondaryTilesetAnimCallback)
        sSecondaryTilesetAnimCallback(sSecondaryTilesetAnimCounter);
}

static void _InitPrimaryTilesetAnimation(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 0;
    sPrimaryTilesetAnimCallback = NULL;
    if (gMapHeader.mapLayout->primaryTileset && gMapHeader.mapLayout->primaryTileset->callback)
        gMapHeader.mapLayout->primaryTileset->callback();
}

static void _InitSecondaryTilesetAnimation(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 0;
    sSecondaryTilesetAnimCallback = NULL;
    if (gMapHeader.mapLayout->secondaryTileset && gMapHeader.mapLayout->secondaryTileset->callback)
        gMapHeader.mapLayout->secondaryTileset->callback();
}

void InitTilesetAnim_General(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 640;
    sPrimaryTilesetAnimCallback = TilesetAnim_General;
}

void InitTilesetAnim_Building(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 256;
    sPrimaryTilesetAnimCallback = TilesetAnim_Building;
}

static void TilesetAnim_General(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_General_WaterFast(timer >> 3);
    if (timer % 16 == 1)
        QueueAnimTiles_General_Water(timer >> 4);
    if (timer % 16 == 2)
        QueueAnimTiles_General_Flower(timer >> 4);
    if (timer % 16 == 4)
        QueueAnimTiles_General_Whirlpool(timer >> 4);
}

static void TilesetAnim_Building(u16 timer)
{
    //if (timer % 8 == 0)
        //QueueAnimTiles_Building_TVTurnedOn(timer >> 3);
}

static void QueueAnimTiles_General_WaterFast(u16 timer)
{
    u32 i = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_General_WaterFast[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(464)), 0x240);
}

static void QueueAnimTiles_General_Water(u16 timer)
{
    u32 i = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Water[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(416)), 0x600);
}

static void QueueAnimTiles_General_Flower(u16 timer)
{
    u32 i = timer % 5;
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Flower[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(508)), 0x80);
}

static void QueueAnimTiles_General_Whirlpool(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Whirlpool[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(488)), 0x80);
}

void InitTilesetAnim_NewBark(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Goldenrod(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Rustboro;
}

void InitTilesetAnim_Violet(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Slateport(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Slateport;
}

void InitTilesetAnim_Mauville(void)
{
    sSecondaryTilesetAnimCounter = sPrimaryTilesetAnimCounter;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Mauville;
}

void InitTilesetAnim_Azalea(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Fallarbor(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Fortree(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Lilycove(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Mossdeep(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_EverGrande(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_EverGrande;
}

void InitTilesetAnim_Pacifidlog(void)
{
    sSecondaryTilesetAnimCounter = sPrimaryTilesetAnimCounter;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Pacifidlog;
}

void InitTilesetAnim_Sootopolis(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Sootopolis;
}

void InitTilesetAnim_BattleFrontierOutsideWest(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 256;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleFrontierOutsideWest;
}

void InitTilesetAnim_BattleFrontierOutsideEast(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 256;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleFrontierOutsideEast;
}

void InitTilesetAnim_Underwater(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 128;
    sSecondaryTilesetAnimCallback = TilesetAnim_Underwater;
}

void InitTilesetAnim_SootopolisGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 240;
    sSecondaryTilesetAnimCallback = TilesetAnim_SootopolisGym;
}

void InitTilesetAnim_EliteFour(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 128;
    sSecondaryTilesetAnimCallback = TilesetAnim_EliteFour;
}

void InitTilesetAnim_AzaleaGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 256;
    sSecondaryTilesetAnimCallback = TilesetAnim_AzaleaGym;
}

void InitTilesetAnim_GoldenrodGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 256;
    sSecondaryTilesetAnimCallback = TilesetAnim_GoldenrodGym;
}

void InitTilesetAnim_MauvilleGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_MauvilleGym;
}

void InitTilesetAnim_PagodaTower(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_PagodaTower;
}

void InitTilesetAnim_PokemonDayCare(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 256;
    sSecondaryTilesetAnimCallback = TilesetAnim_PokemonDayCare;
}

void InitTilesetAnim_BattlePyramid(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattlePyramid;
}

void InitTilesetAnim_BattleDome(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleDome;
}

void InitTilesetAnim_NationalPark(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 960;
    sSecondaryTilesetAnimCallback = TilesetAnim_NationalPark;
}

void InitTilesetAnim_BlackthornGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BlackthornGym;
}

void InitTilesetAnim_PokemonLeague(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_PokemonLeague;
}

void InitTilesetAnim_DragonsDen_Shrine(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_DragonsDen_Shrine;
}

static void TilesetAnim_Rustboro(u16 timer)
{
    /*if (timer % 8 == 0)
    {
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 0);
        QueueAnimTiles_Rustboro_Fountain(timer >> 3);
    }
    if (timer % 8 == 1)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_Rustboro_WindyWater(timer >> 3, 7);*/
}

static void TilesetAnim_Slateport(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Slateport_Balloons(timer >> 4);
}

static void TilesetAnim_Mauville(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 0);
    if (timer % 8 == 1)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_Mauville_Flowers(timer >> 3, 7);
}

static void TilesetAnim_BlackthornGym(u16 timer)
{
    if (timer % 16 == 1)
        QueueAnimTiles_BlackthornGym_Lava(timer >> 4);
}

static void TilesetAnim_PokemonLeague(u16 timer)
{
    if (timer % 16 == 1)
        QueueAnimTiles_PokemonLeague_Lava(timer >> 4);
}

static void TilesetAnim_EverGrande(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 0);
    if (timer % 8 == 1)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_EverGrande_Flowers(timer >> 3, 7);
}

static void TilesetAnim_Pacifidlog(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Pacifidlog_LogBridges(timer >> 4);
    if (timer % 16 == 1)
        QueueAnimTiles_Pacifidlog_WaterCurrents(timer >> 4);
}

static void TilesetAnim_Sootopolis(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Sootopolis_StormyWater(timer >> 4);
}

static void TilesetAnim_Underwater(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Underwater_Seaweed(timer >> 4);
}

static void TilesetAnim_BattleFrontierOutsideWest(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_BattleFrontierOutsideWest_Flower(timer >> 4);
    if (timer % 8 == 0)
        QueueAnimTiles_BattleFrontierOutsideWest_Flag(timer >> 3);
}

static void TilesetAnim_BattleFrontierOutsideEast(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_BattleFrontierOutsideEast_Flower(timer >> 4);
    if (timer % 8 == 0)
        QueueAnimTiles_BattleFrontierOutsideEast_Flag(timer >> 3);
}

static void QueueAnimTiles_Lavaridge_Steam(u8 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Steam[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 288)), 0x80);

    i = (timer + 2) % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Steam[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 292)), 0x80);
}

static void QueueAnimTiles_Pacifidlog_LogBridges(u8 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog_LogBridges[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 464)), 0x3C0);
}

static void QueueAnimTiles_Underwater_Seaweed(u8 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Underwater_Seaweed[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x80);
}

static void QueueAnimTiles_Pacifidlog_WaterCurrents(u8 timer)
{
    u32 i = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog_WaterCurrents[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x100);
}

static void QueueAnimTiles_Mauville_Flowers(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    if (timer_div < 12) // almost certainly a typo
    {
        timer_div %= 12;
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower1[timer_div], gTilesetAnims_Mauville_Flower1_VDests[timer_mod], 0x80);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower2[timer_div], gTilesetAnims_Mauville_Flower2_VDests[timer_mod], 0x80);
    }
    else
    {
        timer_div %= 4;
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower1_B[timer_div], gTilesetAnims_Mauville_Flower1_VDests[timer_mod], 0x80);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower2_B[timer_div], gTilesetAnims_Mauville_Flower2_VDests[timer_mod], 0x80);
    }
}

static void QueueAnimTiles_Rustboro_WindyWater(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= 8;
    if (gTilesetAnims_Rustboro_WindyWater[timer_div])
        AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro_WindyWater[timer_div], gTilesetAnims_Rustboro_WindyWater_VDests[timer_mod], 0x80);
}

static void QueueAnimTiles_Rustboro_Fountain(u16 timer)
{
    u32 i = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro_Fountain[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 448)), 0x80);
}

static void QueueAnimTiles_BlackthornGym_Lava(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BlackthornCity_Gym_Lava[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 16)), 0x80);
}

static void QueueAnimTiles_PokemonLeague_Lava(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_PokemonLeague_Lava[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 352)), 0x80);
}

static void QueueAnimTiles_EverGrande_Flowers(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= 8;

    AppendTilesetAnimToBuffer(gTilesetAnims_EverGrande_Flowers[timer_div], gTilesetAnims_EverGrande_VDests[timer_mod], 0x80);
}

static void QueueAnimTiles_Dewford_Flag(u16 timer)
{
    u16 id = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Dewford_Flag[id], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 170)), 0xC0);
}

static void QueueAnimTiles_BattleFrontierOutsideWest_Flag(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideWest_Flag[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(0x300)), 0xC0);
}

static void QueueAnimTiles_BattleFrontierOutsideEast_Flag(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideEast_Flag[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(0x300)), 0xC0);
}

static void QueueAnimTiles_BattleFrontierOutsideWest_Flower(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideWest_Flower[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(0x312)), 0x80);
}

static void QueueAnimTiles_BattleFrontierOutsideEast_Flower(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideEast_Flower[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(0x312)), 0x80);
}

static void QueueAnimTiles_Slateport_Balloons(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_Slateport_Balloons[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 224)), 0x80);
}

static void TilesetAnim_AzaleaGym(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_AzaleaGym_Flowers(timer >> 4);
}

static void TilesetAnim_GoldenrodGym(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_GoldenrodGym_Flowers(timer >> 4);
}

static void TilesetAnim_MauvilleGym(u16 timer)
{
    if (timer % 2 == 0)
        QueueAnimTiles_MauvilleGym_ElectricGates(timer >> 1);
}

static void TilesetAnim_SootopolisGym(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_SootopolisGym_Waterfalls(timer >> 3);
}

static void TilesetAnim_EliteFour(u16 timer)
{
    if (timer % 64 == 1)
        QueueAnimTiles_EliteFour_GroundLights(timer >> 6);
    if (timer % 8 == 1)
        QueueAnimTiles_EliteFour_WallLights(timer >> 3);
}

static void TilesetAnim_PagodaTower(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_PagodaTower_SproutTowerPillar(timer >> 4);
}

static void TilesetAnim_PokemonDayCare(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_PokemonDayCare_RedFlower(timer / 16);
    if (timer % 16 == 0)
        QueueAnimTiles_PokemonDayCare_YellowFlower(timer / 16);
}

static void TilesetAnim_BattlePyramid(u16 timer)
{
    if (timer % 8 == 0)
    {
        QueueAnimTiles_BattlePyramid_Torch(timer >> 3);
        QueueAnimTiles_BattlePyramid_StatueShadow(timer >> 3);
    }
}

static void TilesetAnim_DragonsDen_Shrine(u16 timer)
{
    if (timer % 8 == 0)
    {
        QueueAnimTiles_DragonsDen_Shrine_Torch(timer >> 3);
        QueueAnimTiles_DragonsDen_Shrine_TorchShadow(timer >> 3);
    }
}

static void TilesetAnim_BattleDome(u16 timer)
{
    if (timer % 4 == 0)
        BlendAnimPalette_BattleDome_FloorLights(timer >> 2);
}

static void TilesetAnim_BattleDome2(u16 timer)
{
    if (timer % 4 == 0)
        BlendAnimPalette_BattleDome_FloorLightsNoBlend(timer >> 2);
}

static void TilesetAnim_NationalPark(u16 timer)
{
    if (timer % 10 == 0)
        QueueAnimTiles_NationalPark_LargeFountain(timer / 10);
    if (timer % 12 == 1)
        QueueAnimTiles_NationalPark_SmallFountain(timer / 12);
    if (timer % 16 == 2)
        QueueAnimTiles_NationalPark_RedFlower(timer / 16);
    if (timer % 16 == 12)
        QueueAnimTiles_NationalPark_YellowFlower(timer / 16);
}

static void QueueAnimTiles_SilphCo_Fountain(u16 timer)
{
    AppendTilesetAnimToBuffer(sTilesetAnims_SilphCo_Fountain[timer % NELEMS(sTilesetAnims_SilphCo_Fountain)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(976)), 8 * TILE_SIZE_4BPP);
}

static void TilesetAnim_SilphCo(u16 timer)
{
    if (timer % 10 == 0)
        QueueAnimTiles_SilphCo_Fountain(timer / 10);
}

void InitTilesetAnim_SilphCo(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 160;
    sSecondaryTilesetAnimCallback = TilesetAnim_SilphCo;
}

static void QueueAnimTiles_CeladonCity_Fountain(u16 timer)
{
    AppendTilesetAnimToBuffer(sTilesetAnims_CeladonCity_Fountain[timer % NELEMS(sTilesetAnims_CeladonCity_Fountain)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(744)), 8 * TILE_SIZE_4BPP);
}

static void TilesetAnim_CeladonCity(u16 timer)
{
    if (timer % 12 == 0)
        QueueAnimTiles_CeladonCity_Fountain(timer / 12);
}

void InitTilesetAnim_CeladonCity(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 120;
    sSecondaryTilesetAnimCallback = TilesetAnim_CeladonCity;
}

static void QueueAnimTiles_Building_TVTurnedOn(u16 timer)
{
    u32 i = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_Building_TvTurnedOn[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(496)), 0x80);
}

static void QueueAnimTiles_SootopolisGym_Waterfalls(u16 timer)
{
    u32 i = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym_SideWaterfall[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 496)), 0x180);
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym_FrontWaterfall[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 464)), 0x280);
}

static void QueueAnimTiles_EliteFour_WallLights(u16 timer)
{
    u32 i = timer % 4;
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour_WallLights[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 504)), 0x20);
}

static void QueueAnimTiles_EliteFour_GroundLights(u16 timer)
{
    u32 i = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour_FloorLight[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 480)), 0x80);
}

static void QueueAnimTiles_AzaleaGym_Flowers(u16 timer)
{
    u32 i = timer % NELEMS(gTilesetAnims_AzaleaGym_Flowers);
    AppendTilesetAnimToBuffer(gTilesetAnims_AzaleaGym_Flowers[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 99)), 0x80);
}

static void QueueAnimTiles_GoldenrodGym_Flowers(u16 timer)
{
    u32 i = timer % NELEMS(gTilesetAnims_GoldenrodGym_Flowers);
    AppendTilesetAnimToBuffer(gTilesetAnims_GoldenrodGym_Flowers[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 90)), 0x80);
}

static void QueueAnimTiles_MauvilleGym_ElectricGates(u16 timer)
{
    u32 i = timer % 2;
    AppendTilesetAnimToBuffer(gTilesetAnims_MauvilleGym_ElectricGates[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 144)), 0x200);
}

static void QueueAnimTiles_PagodaTower_SproutTowerPillar(u16 timer)
{
    u32 i = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_PagodaTower_SproutTowerPillar[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 89)), 0x300);
}

static void QueueAnimTiles_PokemonDayCare_RedFlower(u16 timer)
{
    u32 i = timer % NELEMS(gTilesetAnims_PokemonDayCare_RedFlower);
    AppendTilesetAnimToBuffer(gTilesetAnims_PokemonDayCare_RedFlower[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 88)), 0x80);
}

static void QueueAnimTiles_PokemonDayCare_YellowFlower(u16 timer)
{
    u32 i = timer % NELEMS(gTilesetAnims_PokemonDayCare_YellowFlower);
    AppendTilesetAnimToBuffer(gTilesetAnims_PokemonDayCare_YellowFlower[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 92)), 0x80);
}

static void QueueAnimTiles_Sootopolis_StormyWater(u16 timer)
{
    u32 i = timer % 8;
    AppendTilesetAnimToBuffer(gTilesetAnims_Sootopolis_StormyWater[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 240)), 0xc00);
}

static void QueueAnimTiles_BattlePyramid_Torch(u16 timer)
{
    u32 i = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid_Torch[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 151)), 0x100);
}

static void QueueAnimTiles_DragonsDen_Shrine_Torch(u16 timer)
{
    u32 i = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_DragonsDen_Shrine_Torch[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 74)), 0xC0);
}

static void QueueAnimTiles_DragonsDen_Shrine_TorchShadow(u16 timer)
{
    u32 i = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_DragonsDen_Shrine_TorchShadow[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 128)), 0x200);
}

static void QueueAnimTiles_BattlePyramid_StatueShadow(u16 timer)
{
    u32 i = timer % 3;
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid_StatueShadow[i], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 135)), 0x100);
}

static void BlendAnimPalette_BattleDome_FloorLights(u16 timer)
{
    CpuCopy16(gTilesetAnims_BattleDomeFloorLightPals[timer % 4], gPlttBufferUnfaded + 0x80, 32);
    BlendPalette(0x80, 16, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
    if ((u8)FindTaskIdByFunc(TransitionPhase1_Task_RunFuncs) != TASK_NONE)
    {
        sSecondaryTilesetAnimCallback = TilesetAnim_BattleDome2;
        sSecondaryTilesetAnimCounterMax = 32;
    }
}

static void BlendAnimPalette_BattleDome_FloorLightsNoBlend(u16 timer)
{
    CpuCopy16(gTilesetAnims_BattleDomeFloorLightPals[timer % 4], gPlttBufferUnfaded + 0x80, 32);
    if ((u8)FindTaskIdByFunc(TransitionPhase1_Task_RunFuncs) == TASK_NONE)
    {
        BlendPalette(0x80, 16, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
        if (!--sSecondaryTilesetAnimCounterMax)
            sSecondaryTilesetAnimCallback = NULL;
    }
}

static void QueueAnimTiles_NationalPark_LargeFountain(u16 timer)
{
    AppendTilesetAnimToBuffer(gTilesetAnims_NationalPark_LargeFountain[timer % ARRAY_COUNT(gTilesetAnims_NationalPark_LargeFountain)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 88)), 0x100);
}

static void QueueAnimTiles_NationalPark_SmallFountain(u16 timer)
{
    AppendTilesetAnimToBuffer(gTilesetAnims_NationalPark_SmallFountain[timer % ARRAY_COUNT(gTilesetAnims_NationalPark_SmallFountain)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 104)), 0x100);
}

static void QueueAnimTiles_NationalPark_RedFlower(u16 timer)
{
    AppendTilesetAnimToBuffer(gTilesetAnims_NationalPark_RedFlower[timer % ARRAY_COUNT(gTilesetAnims_NationalPark_RedFlower)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 96)), 0x80);
}

static void QueueAnimTiles_NationalPark_YellowFlower(u16 timer)
{
    AppendTilesetAnimToBuffer(gTilesetAnims_NationalPark_YellowFlower[timer % ARRAY_COUNT(gTilesetAnims_NationalPark_YellowFlower)], (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 100)), 0x80);
}
