#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

extern EWRAM_DATA struct ItemSlot gMartPurchaseHistory[3];
extern const u8 *const gMoveDescriptionPointers[];

enum
{
    MART_TYPE_NORMAL, // normal mart
    MART_TYPE_TMHM,
    MART_TYPE_HERB,
    MART_TYPE_BARGAIN,
    MART_TYPE_ROOFTOP_SALE,
    MART_TYPE_DECOR,
    MART_TYPE_DECOR2
};

// shop view window NPC info enum
enum
{
    OBJ_EVENT_ID,
    X_COORD,
    Y_COORD,
    ANIM_NUM
};

struct MartInfo
{
    /*0x0*/ void (*callback)(void);
    /*0x4*/ const struct MenuAction *menuActions;
    /*0x8*/ const u16 *itemList;
    /*0x8*/ const u16 *customItemPrices;
    /*0xC*/ u16 itemCount;
    /*0xE*/ u8 windowId;
    /*0xF*/ u8 martType;
};

struct ShopData
{
    /*0x0000*/ u16 tilemapBuffers[4][0x400];
    /*0x2000*/ u32 totalCost;
    /*0x2004*/ u16 itemsShowed;
    /*0x2006*/ u16 selectedRow;
    /*0x2008*/ u16 scrollOffset;
    /*0x2008*/ u16 buyMenuArrowScrollOffset;
    /*0x200A*/ u16 maxQuantity;
    /*0x200C*/ u8 scrollIndicatorsTaskId;
    /*0x200D*/ u8 iconSlot;
    /*0x200E*/ u8 itemSpriteIds[2];
    /*0x200G*/ u8 bargainShopPurchasedItems;
    /*0x2011*/ s16 viewportObjects[OBJECT_EVENTS_COUNT][4];
};

void CreatePokemartMenu(const u16 *);
void CreateBargainShopMenu(const u16 *, const u16 *);
void CreateHerbShopMenu(const u16 *);
void CreateRooftopSaleShopMenu(const u16 *, const u16 *);
void CreateDecorationShop1Menu(const u16 *);
void CreateDecorationShop2Menu(const u16 *);
void CB2_ExitSellMenu(void);

#endif // GUARD_SHOP_H
