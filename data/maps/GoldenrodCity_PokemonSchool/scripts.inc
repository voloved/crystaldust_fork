GoldenrodCity_PokemonSchool_MapScripts:: @ 8213EA8
	.byte 0

GoldenrodCity_PokemonSchool_EventScript_Blackboard:: @ 8213EA9
	lockall
	msgbox GoldenrodCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic:: @ 8213EB8
	message GoldenrodCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, 0
	switch VAR_RESULT
	case 0, GoldenrodCity_PokemonSchool_EventScript_Poison
	case 1, GoldenrodCity_PokemonSchool_EventScript_Paralysis
	case 2, GoldenrodCity_PokemonSchool_EventScript_Sleep
	case 3, GoldenrodCity_PokemonSchool_EventScript_Burn
	case 4, GoldenrodCity_PokemonSchool_EventScript_Freeze
	case 5, GoldenrodCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, GoldenrodCity_PokemonSchool_EventScript_ExitTopicSelect
	end

GoldenrodCity_PokemonSchool_EventScript_Poison:: @ 8213F17
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_Paralysis:: @ 8213F25
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_Sleep:: @ 8213F33
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_Burn:: @ 8213F41
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_Freeze:: @ 8213F4F
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

GoldenrodCity_PokemonSchool_EventScript_ExitTopicSelect:: @ 8213F5D
	releaseall
	end

GoldenrodCity_PokemonSchool_EventScript_GameboyKid1:: @ 8213F5F
	msgbox GoldenrodCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

GoldenrodCity_PokemonSchool_EventScript_GameboyKid2:: @ 8213F68
	msgbox GoldenrodCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

GoldenrodCity_PokemonSchool_EventScript_RichBoy:: @ 8213F71
	msgbox GoldenrodCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

GoldenrodCity_PokemonSchool_EventScript_Lass:: @ 8213F7A
	msgbox GoldenrodCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

GoldenrodCity_PokemonSchool_EventScript_SchoolKidM:: @ 8213F83
	msgbox GoldenrodCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

GoldenrodCity_PokemonSchool_EventScript_StudentNotebook:: @ 8213F8C
	msgbox GoldenrodCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

GoldenrodCity_PokemonSchool_EventScript_Teacher:: @ 8213F95
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, GoldenrodCity_PokemonSchool_EventScript_GaveQuickClaw
	compare VAR_FACING, DIR_EAST
	call_if_eq GoldenrodCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	compare VAR_FACING, DIR_WEST
	call_if_eq GoldenrodCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox GoldenrodCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

GoldenrodCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast:: @ 8213FE5
	applymovement VAR_LAST_TALKED, GoldenrodCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

GoldenrodCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest:: @ 8213FF0
	applymovement VAR_LAST_TALKED, GoldenrodCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

GoldenrodCity_PokemonSchool_EventScript_GaveQuickClaw:: @ 8213FFB
	msgbox GoldenrodCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	release
	end

GoldenrodCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest: @ 8214010
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_fastest_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

GoldenrodCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast: @ 8214027
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_fastest_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_fastest_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

GoldenrodCity_PokemonSchool_EventScript_Scott:: @ 8214040
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, GoldenrodCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, GoldenrodCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, GoldenrodCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox GoldenrodCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

GoldenrodCity_PokemonSchool_EventScript_ScottSpokeAlready:: @ 821406F
	goto_if_set FLAG_BADGE01_GET, GoldenrodCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox GoldenrodCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_PokemonSchool_EventScript_ScottGreetHasBadge:: @ 8214082
	msgbox GoldenrodCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

GoldenrodCity_PokemonSchool_EventScript_ScottNoticeBadge:: @ 8214090
	msgbox GoldenrodCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto GoldenrodCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

GoldenrodCity_PokemonSchool_EventScript_MetScottAfterBadge:: @ 821409E
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

GoldenrodCity_PokemonSchool_EventScript_ScottWatchStudents:: @ 82140A8
	msgbox GoldenrodCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_PokemonSchool_Text_BlackboardListsStatusChanges: @ 82140B2
	.string "The blackboard lists status changes\n"
	.string "that may affect {POKEMON} in battle.$"

GoldenrodCity_PokemonSchool_Text_ReadWhichTopic: @ 82140F9
	.string "Which topic do you want to read?$"

GoldenrodCity_PokemonSchool_Text_ExplainPoison: @ 821411A
	.string "If a {POKEMON} is poisoned, it will\n"
	.string "steadily lose HP.\p"
	.string "The effects of poison remain after\n"
	.string "a battle.\p"
	.string "A poisoned {POKEMON}'s HP will drop\n"
	.string "while it is traveling.\p"
	.string "Heal a poisoning using an ANTIDOTE.$"

GoldenrodCity_PokemonSchool_Text_ExplainParalysis: @ 82141D8
	.string "If a {POKEMON} becomes paralyzed,\n"
	.string "its SPEED drops.\p"
	.string "It may also not be able to move while\n"
	.string "it is in battle.\p"
	.string "Paralysis remains after battle.\n"
	.string "Cure it using a PARLYZ HEAL.$"

GoldenrodCity_PokemonSchool_Text_ExplainSleep: @ 821427D
	.string "If a {POKEMON} falls asleep, it will be\n"
	.string "unable to attack.\p"
	.string "A {POKEMON} may wake up on its own,\n"
	.string "but if a battle ends while it is\l"
	.string "sleeping, it will stay asleep.\p"
	.string "Wake it up using an AWAKENING.$"

GoldenrodCity_PokemonSchool_Text_ExplainBurn: @ 8214336
	.string "A burn reduces ATTACK power, and it\n"
	.string "steadily reduces the victim's HP.\p"
	.string "A burn lingers after battle.\n"
	.string "Cure a burn using a BURN HEAL.$"

GoldenrodCity_PokemonSchool_Text_ExplainFreeze: @ 82143B8
	.string "If a {POKEMON} is frozen, it becomes\n"
	.string "completely helpless.\p"
	.string "It will remain frozen after battle.\n"
	.string "Thaw it out using an ICE HEAL.$"

GoldenrodCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw: @ 8214433
	.string "Students who don't study get a little\n"
	.string "taste of my QUICK CLAW.\p"
	.string "Whether or not you are a good student \n"
	.string "will be evident from the way you use\l"
	.string "this item.$"

GoldenrodCity_PokemonSchool_Text_ExplainQuickClaw: @ 82144C8
	.string "A {POKEMON} holding the QUICK CLAW will\n"
	.string "occasionally speed up and get to move\l"
	.string "before its opponent.\p"
	.string "There are many other items that are\n"
	.string "meant to be held by {POKEMON}.\p"
	.string "Just those alone will give you many\n"
	.string "topics to study!$"

GoldenrodCity_PokemonSchool_Text_TradingRightNow: @ 821459F
	.string "I'm trading {POKEMON} with my friend\n"
	.string "right now.$"

GoldenrodCity_PokemonSchool_Text_AlwaysWantedSeedot: @ 82145CD
	.string "I always wanted a SEEDOT, and\n"
	.string "I'm finally getting one!$"

GoldenrodCity_PokemonSchool_Text_PokemontCantUseManMadeItems: @ 8214604
	.string "{POKEMON} can hold items, but they\n"
	.string "don't know what to do with man-made\l"
	.string "items like POTION and ANTIDOTE.$"

GoldenrodCity_PokemonSchool_Text_ConfusedPokemonAttacksItself: @ 8214669
	.string "You know how some {POKEMON} moves can\n"
	.string "confuse a {POKEMON}?\p"
	.string "A confused {POKEMON} will sometimes\n"
	.string "attack itself without meaning to.\p"
	.string "But once it leaves battle, it will\n"
	.string "return to normal.$"

GoldenrodCity_PokemonSchool_Text_PokemonHealItselfWithBerry: @ 8214719
	.string "A {POKEMON} holding a BERRY will heal\n"
	.string "itself…\p"
	.string "There are many kinds of items that\n"
	.string "{POKEMON} can hold…\p"
	.string "Boy, it sure is hard taking notes\n"
	.string "down…$"

GoldenrodCity_PokemonSchool_Text_StudentsNotes: @ 82147A2
	.string "It's this student's notebook…\p"
	.string "{POKEMON} are to be caught using\n"
	.string "{POKE} BALLS.\p"
	.string "Up to six {POKEMON} can accompany\n"
	.string "a TRAINER.\p"
	.string "A TRAINER is someone who catches\n"
	.string "{POKEMON}, raises them, and battles\l"
	.string "with them.\p"
	.string "A TRAINER's mission is to defeat\n"
	.string "the strong TRAINERS who await\l"
	.string "challengers in {POKEMON} GYMS.$"

GoldenrodCity_PokemonSchool_Text_ScottMetAlreadyCut: @ 82148C0
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "{POKEMON} battle experts.\p"
	.string "So, what brings you to this SCHOOL?\n"
	.string "Are you a TRAINER, too?\p"
	.string "The first thing you should do is to\n"
	.string "have a {POKEMON} learn the move CUT.\p"
	.string "If I remember correctly, someone in\n"
	.string "this town has CUT.$"

GoldenrodCity_PokemonSchool_Text_StudentTalentLevelUnknown: @ 8214A5F
	.string "SCOTT: Hmm…\p"
	.string "The talent levels of the students here\n"
	.string "are unknown. The potential's there.$"

GoldenrodCity_PokemonSchool_Text_ScottStoneBadge: @ 8214AB6
	.string "SCOTT: Oh, what's that?\p"
	.string "It's a STONE BADGE, isn't it?\n"
	.string "That's pretty impressive, I'd say.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"

GoldenrodCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge: @ 8214B8A
	.string "Hello? Didn't we meet before?\n"
	.string "I think back in PETALBURG CITY.\p"
	.string "Let me introduce myself.\n"
	.string "My name's SCOTT.\p"
	.string "I've been traveling everywhere in\n"
	.string "search of outstanding TRAINERS.\p"
	.string "More specifically, I'm looking for\n"
	.string "{POKEMON} battle experts.\p"
	.string "Oh, what's that?\n"
	.string "It's a STONE BADGE, isn't it?\p"
	.string "That's pretty impressive, I'd say, for\n"
	.string "a starting TRAINER like yourself.\p"
	.string "But, you know, I would've loved to see\n"
	.string "you in battle.\p"
	.string "It's hard to tell what you're like as\n"
	.string "a TRAINER from a LEAGUE BADGE.$"

