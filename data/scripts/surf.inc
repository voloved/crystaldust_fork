EventScript_UseSurf::
	checkpartymove MOVE_SURF
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_EndUseSurf
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_ReleaseUseSurf
	setflag FLAG_SURF_SKIP_INTRO
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end
EventScript_UseSurfNoIntro::
	goto_if_unset FLAG_SURF_SKIP_INTRO, EventScript_EndUseSurf
	checkpartymove MOVE_SURF
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_EndUseSurf
	dofieldeffect FLDEFF_USE_SURF_NO_INTRO

