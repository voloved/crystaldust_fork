BattleFrontier_Lounge1_MapScripts::
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder::
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	compare VAR_0x8004, 255
	goto_if_eq BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	compare VAR_0x8005, 90   @ Average of 15
	goto_if_le BattleFrontier_Lounge1_EventScript_AverageTotalIVs
	compare VAR_0x8005, 120  @ Average of 20
	goto_if_le BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs
	compare VAR_0x8005, 150  @ Average of 25
	goto_if_le BattleFrontier_Lounge1_EventScript_HighTotalIVs
	compare VAR_0x8005, 151  @ Average of > 25
	goto_if_ge BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat::
	compare VAR_0x8006, STAT_HP
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVHP
	compare VAR_0x8006, STAT_ATK
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVAtk
	compare VAR_0x8006, STAT_DEF
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVDef
	compare VAR_0x8006, STAT_SPEED
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	compare VAR_0x8006, STAT_SPATK
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	compare VAR_0x8006, STAT_SPDEF
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	compare VAR_0x8007, 15
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVLow
	compare VAR_0x8007, 25
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVMid
	compare VAR_0x8007, 30
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVHigh
	compare VAR_0x8007, 31
	goto_if_ge BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro:
	.string "For 70 years I have raised {POKEMON}!\n"
	.string "I am the man they revere as\l"
	.string "the legendary top {POKEMON} BREEDER!\p"
	.string "If you ever become as seasoned as me,\n"
	.string "you'll see the abilities of {POKEMON}\l"
	.string "at a glance.\p"
	.string "You're a TRAINER. Doesn't it interest\n"
	.string "you to know your own {POKEMON}'s\l"
	.string "abilities?\p"
	.string "Here!\n"
	.string "Let's have a look at your {POKEMON}!$"

BattleFrontier_Lounge1_Text_AverageAbility:
	.string "…Hmm…\p"
	.string "This one, overall, I would describe\n"
	.string "as being of average ability.$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility:
	.string "…Hmm…\p"
	.string "This one, overall, I would describe as\n"
	.string "having better-than-average ability.$"

BattleFrontier_Lounge1_Text_ImpressiveAbility:
	.string "…Hmm…\p"
	.string "This one, overall, I would say is\n"
	.string "quite impressive in ability!$"

BattleFrontier_Lounge1_Text_OutstandingAbility:
	.string "…Hmm…\p"
	.string "This one, overall, I would say is\n"
	.string "wonderfully outstanding in ability!$"

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its HP…$"

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its ATTACK…$"

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its DEFENSE…$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its SPECIAL ATTACK…$"

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its SPECIAL DEFENSE…$"

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its SPEED…$"

BattleFrontier_Lounge1_Text_StatRelativelyGood:
	.string "That stat is relatively good.\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatImpressive:
	.string "That stat is quite impressive.\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatOutstanding:
	.string "That stat is outstanding!\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatFlawless:
	.string "It's flawless! A thing of perfection!\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice:
	.string "What?\n"
	.string "You have no time for my advice?\p"
	.string "You should always be eager to learn\n"
	.string "from the experiences of your elders!$"

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending:
	.string "Yes, what is it now?\p"
	.string "I have business that needs tending!\n"
	.string "Save it for next time!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon:
	.string "Ah, youngster! Do your {POKEMON}'s\n"
	.string "abilities intrigue you?\p"
	.string "Here, here!\n"
	.string "Let's have a look at your {POKEMON}!$"

BattleFrontier_Lounge1_Text_EvenICantTell:
	.string "An expert I am, but even I can't tell\n"
	.string "anything about an unhatched {POKEMON}!\p"
	.string "Show me a {POKEMON}!\n"
	.string "A {POKEMON} is what I need to see!$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding:
	.string "He said my {POKEMON} is outstanding!\n"
	.string "I'm glad I raised it carefully!$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt:
	.string "He said my {POKEMON} is outstanding!\n"
	.string "But I didn't do anything special\l"
	.string "raising it…$"

