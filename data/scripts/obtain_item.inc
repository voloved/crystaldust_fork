Std_ObtainItem::
	setvar VAR_0x8007, 0
	textcolor MSG_COLOR_SYS
	additem VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	compare VAR_0x8007, 0
	call_if_eq EventScript_TryAddItemToPCObtain
	call EventScript_ObtainItemMessage
	return

EventScript_TryAddItemToPCObtain::
	checkitemtype VAR_0x8000 @ Don't add if it's a key item
	compare VAR_RESULT, POCKET_KEY_ITEMS
	goto_if_eq EventScript_TryAddItemToPCObtainContinue
	addpcitem VAR_0x8000, VAR_0x8001
	compare VAR_RESULT, 0
	call_if_eq EventScript_TryAddItemToPCObtainContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC) 
EventScript_TryAddItemToPCObtainContinue::
	return

EventScript_ObtainItemMessage::
	bufferitemnameplural 1, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_BufferPocketNameAndTryFanfare
	compare VAR_0x8007, 0
	call_if_ne EventScript_ObtainedItem
	compare VAR_0x8007, 0
	call_if_eq EventScript_NoRoomForItem
	return

EventScript_BufferPocketNameAndTryFanfare::
	switch VAR_RESULT
	case POCKET_ITEMS,        EventScript_BufferItemsPocket
	case POCKET_MEDICINE,     EventScript_BufferMedicinePocket
	case POCKET_POKE_BALLS,   EventScript_BufferPokeballsPocket
	case POCKET_BATTLE_ITEMS, EventScript_BufferBattleItemsPocket
	case POCKET_BERRIES,      EventScript_BufferBerriesPocket
	case POCKET_TREASURES,    EventScript_BufferTreasuresPocket
	case POCKET_TM_HM,        EventScript_BufferTMHMsPocket
	case POCKET_KEY_ITEMS,    EventScript_BufferKeyItemsPocket
	end

EventScript_BufferItemsPocket::
	bufferstdstring 2, STDSTRING_ITEMS
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferKeyItemsPocket::
	bufferstdstring 2, STDSTRING_KEYITEMS
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferPokeballsPocket::
	bufferstdstring 2, STDSTRING_POKEBALLS
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferTMHMsPocket::
	bufferstdstring 2, STDSTRING_TMHMS
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedTMHM
	return

EventScript_BufferBerriesPocket::
	bufferstdstring 2, STDSTRING_BERRIES
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferMedicinePocket::
	bufferstdstring 2, STDSTRING_MEDICINE
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferBattleItemsPocket::
	bufferstdstring 2, STDSTRING_BATTLEITEMS
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferTreasuresPocket::
	bufferstdstring 2, STDSTRING_TREASURES
	compare VAR_0x8007, 0
	call_if_ne EventScript_PlayFanfareObtainedItem
	return

EventScript_ObtainedItem::
	message gText_ObtainedTheItem
	waitfanfare
	call EventScript_PutItemMsg
	setvar VAR_RESULT, 1
	return

EventScript_NoRoomForItem::
	setvar VAR_RESULT, 0
	return

EventScript_PlayFanfareObtainedItem::
	playfanfare MUS_OBTAIN_ITEM
	return

EventScript_PlayFanfareObtainedTMHM::
	playfanfare MUS_OBTAIN_TMHM
	return

Std_ObtainDecoration::
	adddecoration VAR_0x8000
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_ObtainDecorationMessage
	return

EventScript_ObtainDecorationMessage::
	bufferdecorationname 1, VAR_0x8000
	compare VAR_0x8007, 1
	call_if_eq EventScript_ObtainedDecor
	compare VAR_0x8007, 0
	call_if_eq EventScript_NoRoomForDecor
	return

EventScript_ObtainedDecor::
	playfanfare MUS_OBTAIN_ITEM
	message gText_ObtainedTheDecor
	waitfanfare
	msgbox gText_TheDecorWasTransferredToThePC, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

EventScript_NoRoomForDecor::
	setvar VAR_RESULT, 0
	return

Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8001
	checkitemspace VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	compare VAR_0x8007, 0
	call_if_eq EventScript_CheckPCSpace
	bufferitemnameplural 1, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_BufferPocketNameAndTryFanfare
	compare VAR_0x8007, 0
	call_if_ne EventScript_PickUpItem
	compare VAR_0x8007, 0
	call_if_eq EventScript_NoRoomToPickUpItem
	release
	return

EventScript_CheckPCSpace::
	checkitemtype VAR_0x8004 @ Don't add if it's a key item
	compare VAR_RESULT, POCKET_KEY_ITEMS
	goto_if_eq EventScript_CheckPCSpaceContinue
	checkpcspace VAR_0x8004, VAR_0x8005
	compare VAR_RESULT, FALSE
	call_if_eq EventScript_CheckPCSpaceContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC) 
EventScript_CheckPCSpaceContinue::
	return

EventScript_PickUpItem::
	removeobject VAR_LAST_TALKED
	compare VAR_0x8007, 2
	goto_if_eq EventScript_PickUpItemPCAdd
	additem VAR_0x8004, VAR_0x8005
	goto EventScript_PickUpItemContinueAdd
EventScript_PickUpItemPCAdd::
	addpcitem VAR_0x8004, VAR_0x8005
EventScript_PickUpItemContinueAdd::
	specialvar VAR_RESULT, BufferTMHMMoveName
	copyvar VAR_0x8008, VAR_RESULT
	compare VAR_0x8008, 1
	call_if_eq EventScript_FoundTMHM
	compare VAR_0x8008, 0
	call_if_eq EventScript_FoundItem
	waitfanfare
	waitmessage
	bufferitemnameplural 1, VAR_0x8004, VAR_0x8005
	pyramid_inchallenge
	compare VAR_RESULT, 1
	goto_if_eq EventScript_PutBattlePyramidItemInBag
	call EventScript_PutItemMsg
	return

EventScript_PutBattlePyramidItemInBag::
	msgbox gText_PlayerPutItemInBag, MSGBOX_DEFAULT
	return

EventScript_FoundTMHM::
	bufferitemnameplural 0, VAR_0x8004, VAR_0x8005
	message gText_PlayerFoundOneTMHM
	return

EventScript_FoundItem::
	message gText_PlayerFoundOneItem
	return

EventScript_NoRoomToPickUpItem::
	msgbox gText_ObtainedTheItem, MSGBOX_DEFAULT
	msgbox gText_TooBadBagAndPCAreFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

EventScript_FruitTree::
	lockall
	special GetFruitTreeItem
	compare VAR_RESULT, 0
	goto_if_eq FruitTree_EventScript_NothingHere
	copyvar VAR_0x8000, VAR_RESULT
	bufferitemnameplural 1, VAR_0x8000, 1
	msgbox gText_FruitBearingTree

@ Done so the fruit only disappears from the tree if it can be put in the bag,
@ but before the actual giveitem text appears.

	checkitemspace VAR_0x8000, 1
	compare VAR_RESULT, 1
	goto_if_eq EventScript_FruitTree_HaveSpace
	checkpcspace VAR_0x8000, 1
	compare VAR_RESULT, 1
	goto_if_eq EventScript_FruitTree_HaveSpace
	goto EventScript_FruitTree_NoSpace
EventScript_FruitTree_HaveSpace::	
	call FruitTree_TakeItemFromTree
	giveitem VAR_0x8000
	compare VAR_0x8007, 0
	goto_if_eq EventScript_FruitTree_NoSpace
	goto EventScript_FruitTree_ContSpace
EventScript_FruitTree_NoSpace::
	call FruitTree_NotEnoughSpace
	goto EventScript_FruitTree_Cont
EventScript_FruitTree_ContSpace::
	addvar VAR_0x8004, FLAG_FRUIT_TREES_START - 1
	special SetHiddenItemFlag
EventScript_FruitTree_Cont::
	releaseall
	return

FruitTree_NotEnoughSpace:
	msgbox gText_FruitBearingTreeBagAndPCFull
	releaseall
	return

FruitTree_TakeItemFromTree:
	special SetFruitTreeMetatileTakenFromId
	return

FruitTree_EventScript_NothingHere:
	msgbox gText_FruitBearingTreeNothingHere
	releaseall
	return

EventScript_HiddenItemScript::
	lockall
	waitse
	additem VAR_0x8005
	copyvar VAR_0x8007, VAR_RESULT
	compare VAR_0x8007, FALSE
	call_if_eq EventScript_TryAddItemToPCHidden
	bufferitemnameplural 1, VAR_0x8005, 1
	checkitemtype VAR_0x8005
	call EventScript_BufferPocketNameAndTryFanfare
	compare VAR_0x8007, 0
	goto_if_ne EventScript_PickUpHiddenItem
	goto EventScript_NoRoomForHiddenItem
	end

EventScript_TryAddItemToPCHidden::
	checkitemtype VAR_0x8005 @ Don't add if it's a key item
	compare VAR_RESULT, POCKET_KEY_ITEMS
	goto_if_eq EventScript_TryAddHiddenItemToPCContinue
	addpcitem VAR_0x8004, VAR_0x8005
	compare VAR_RESULT, FALSE
	call_if_eq EventScript_TryAddHiddenItemToPCContinue
	setvar VAR_0x8007, 2  @ (0= full, 1= in pocket, 2=in PC) 
EventScript_TryAddHiddenItemToPCContinue::
	return

EventScript_PickUpHiddenItem::
	copyvar VAR_0x8008, VAR_0x8004
	copyvar VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, BufferTMHMMoveName
	compare VAR_RESULT, 1
	goto_if_eq EventScript_FoundHiddenTMHM
	compare VAR_RESULT, 0
	goto_if_eq EventScript_FoundHiddenItem
	end

EventScript_FoundHiddenTMHM::
	bufferitemnameplural 0, VAR_0x8004, 1
	message gText_PlayerFoundOneTMHM
	goto EventScript_PutHiddenItemInPocket
	end

EventScript_FoundHiddenItem::
	message gText_PlayerFoundOneItem
	goto EventScript_PutHiddenItemInPocket
	end

EventScript_PutHiddenItemInPocket::
	waitmessage
	waitfanfare
	bufferitemnameplural 1, VAR_0x8004, 1
	copyvar VAR_0x8004, VAR_0x8008
	call EventScript_PutItemMsg
	special TryPutTreasureInvestigatorsOnAir
	special SetHiddenItemFlag
	releaseall
	end

EventScript_PutItemMsg::
	compare VAR_0x8007, 2
	goto_if_eq EventScript_PutItemPCMsg
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto EventScript_PutItemContinueMsg
EventScript_PutItemPCMsg::
	msgbox gText_PutItemInPC, MSGBOX_DEFAULT
EventScript_PutItemContinueMsg::
	return

EventScript_NoRoomForHiddenItem::
	msgbox gText_PlayerFoundOneItem, MSGBOX_DEFAULT
	msgbox gText_TooBadBagAndPCAreFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end
