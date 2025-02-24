#include "gba/io_reg.h"

EventScript_StartTrainerApproach::
	selectapproachingtrainer
	lockfortrainer
EventScript_TrainerApproach::
	special PlayTrainerEncounterMusic
	special DoTrainerApproach
	waitstate
	goto EventScript_ShowTrainerIntroMsg

EventScript_TryDoNormalTrainerBattle::
	lock
	faceplayer
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	specialvar VAR_RESULT, GetTrainerFlag
	compare VAR_RESULT, FALSE
	goto_if_ne EventScript_NoNormalTrainerBattleCheckRematch
EventScript_TryDoNormalTrainerBattleRematch::
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto EventScript_ShowTrainerIntroMsg

EventScript_NoNormalTrainerBattleCheckRematch::
	callnative IsRematchAllowed
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_NoRematchTrainerBattle
	checkbuttonheld B_BUTTON
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_NoRematchTrainerBattle
	msgbox TrainerBattle_Text_WouldYouLikeToRematch, MSGBOX_YESNO
	compare VAR_RESULT, YES
	setflag FLAG_TEMP_16
	goto_if_eq EventScript_TryDoNormalTrainerBattleRematch
	gotopostbattlescript

EventScript_TryDoDoubleTrainerBattle::
	lock
	faceplayer
	call EventScript_RevealTrainer
	specialvar VAR_RESULT, GetTrainerFlag
	compare VAR_RESULT, FALSE
	goto_if_ne EventScript_NoDoubleTrainerBattleCheckRematch
EventScript_TryDoDoubleTrainerBattleRematch::
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne EventScript_NotEnoughMonsForDoubleBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto EventScript_ShowTrainerIntroMsg

EventScript_NotEnoughMonsForDoubleBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

EventScript_NoDoubleTrainerBattleCheckRematch::
	callnative IsRematchAllowed
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_NoDoubleRematchTrainerBattle
	checkbuttonheld B_BUTTON
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_NoDoubleRematchTrainerBattle
	msgbox TrainerBattle_Text_WouldYouLikeToRematchUs, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq EventScript_TryDoDoubleTrainerBattleRematch
	gotopostbattlescript

TrainerBattle_Text_WouldYouLikeToRematch:
	.string "Would you like to have a\n"
	.string "rematch with me?$"

TrainerBattle_Text_WouldYouLikeToRematchUs:
	.string "Would you like to have a\n"
	.string "rematch with us?$"

EventScript_DoNoIntroTrainerBattle::
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	special PlayTrainerEncounterMusic
	trainerbattlebegin
	gotopostbattlescript

EventScript_TryDoRematchBattle::
	call EventScript_RevealTrainer
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_NoRematchTrainerBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

EventScript_NoRematchTrainerBattle::
	gotopostbattlescript

EventScript_TryDoDoubleRematchBattle::
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_NoDoubleRematchTrainerBattle
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne EventScript_NotEnoughMonsForDoubleRematchBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

EventScript_NoDoubleRematchTrainerBattle::
	gotopostbattlescript

EventScript_NotEnoughMonsForDoubleRematchBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

EventScript_RevealTrainer::
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	return

Movement_RevealTrainer:
	reveal_trainer
	step_end

EventScript_ShowTrainerIntroMsg::
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special TryPrepareSecondApproachingTrainer
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_TrainerApproach
	goto EventScript_DoTrainerBattle

EventScript_DoTrainerBattle::
	trainerbattlebegin
	@ Below battle mode check only needed in FRLG
	specialvar VAR_RESULT, GetTrainerBattleMode
	compare VAR_RESULT, TRAINER_BATTLE_SINGLE
	goto_if_eq EventScript_EndTrainerBattle
	compare VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT
	goto_if_eq EventScript_EndTrainerBattle
	compare VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC
	goto_if_eq EventScript_EndTrainerBattle
	compare VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE
	goto_if_eq EventScript_EndTrainerBattle
	compare VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC
	goto_if_eq EventScript_EndTrainerBattle
EventScript_EndTrainerBattle::
	gotobeatenscript
	releaseall
	end

Std_MsgboxAutoclose::
	message 0x0
	waitmessage
	waitbuttonpress
	release
	return
