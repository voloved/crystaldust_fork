Std_RegisteredInMatchCall::
	waitse
	playfanfare MUS_REGISTER_PHONE
	textcolor MSG_COLOR_SYS
	msgbox EventScript_Text_Trainer_Registered
	waitfanfare
	closemessage
	textcolor MSG_COLOR_PREV
	return

EventScript_TryGetTrainerScript::
	goto_if_set FLAG_RAN_FROM_TRAINER, EventScript_TryGetTrainerScript_Cont
	special ShouldTryGetTrainerScript
	compare VAR_RESULT, 1
	goto_if_eq EventScript_GotoTrainerScript
EventScript_TryGetTrainerScript_Cont:
	releaseall
	end

EventScript_GotoTrainerScript::
	gotobeatenscript
	releaseall
	end

EventScript_Text_Trainer_Registered:
	.string "{PLAYER} registered\n"
	.string "{STR_VAR_1}'s phone number!$"
