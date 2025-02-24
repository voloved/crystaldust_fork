#ifndef GUARD_BATTLE_SETUP_H
#define GUARD_BATTLE_SETUP_H

#include "gym_leader_rematch.h"

#define REMATCHES_COUNT 5

struct RematchTrainer
{
    u16 trainerIds[REMATCHES_COUNT];
    u16 mapGroup;
    u16 mapNum;
    u8 phoneContactId;
};

extern const struct RematchTrainer gRematchTable[REMATCH_TABLE_ENTRIES];

extern u16 gTrainerBattleOpponent_A;
extern u16 gTrainerBattleOpponent_B;
extern u16 gPartnerTrainerId;

void BattleSetup_StartWildBattle(u32 flags);
void BattleSetup_StartBattlePikeWildBattle(void);
void BattleSetup_StartRoamerBattle(void);
void StartDudeTutorialBattle(void);
void BattleSetup_StartScriptedWildBattle(void);
void BattleSetup_StartLatiBattle(void);
void BattleSetup_StartLegendaryBattle(void);
void StartRegiBattle(void);
u8 BattleSetup_GetTerrainId(void);
u8 GetSpecialBattleTransition(s32 arg0);
void ChooseStarter(void);
void ResetTrainerOpponentIds(void);
void SetMapVarsToTrainer(void);
const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data);
void ConfigureAndSetUpOneTrainerBattle(u8 trainerObjEventId, const u8 *trainerScript);
void ConfigureTwoTrainersBattle(u8 trainerObjEventId, const u8 *trainerScript);
void SetUpTwoTrainersBattle(void);
bool32 GetTrainerFlagFromScriptPointer(const u8 *data);
void SetTrainerFacingDirection(void);
u8 GetTrainerBattleMode(void);
u8 GetFirstBattleTutorialMode(void);
bool8 GetTrainerFlag(void);
bool8 HasTrainerBeenFought(u16 trainerId);
void SetTrainerFlag(u16 trainerId);
void ClearTrainerFlag(u16 trainerId);
void BattleSetup_StartTrainerBattle(void);
void BattleSetup_StartRematchBattle(void);
void ShowTrainerIntroSpeech(void);
u8 GetScaledLevel(u8 lvl);
const u8 *BattleSetup_GetScriptAddrAfterBattle(void);
const u8 *BattleSetup_GetTrainerPostBattleScript(void);
void ShowTrainerCantBattleSpeech(void);
void PlayTrainerEncounterMusic(void);
const u8 *GetTrainerALoseText(void);
const u8 *GetTrainerBLoseText(void);
const u8 *GetTrainerWonSpeech(void);
void UpdateRematchIfDefeated(s32 rematchTableId);
void IncrementRematchStepCounter(void);
bool32 IsRematchTrainerIn(u16 mapGroup, u16 mapNum);
u16 GetLastBeatenRematchTrainerId(u16 trainerId);
bool8 ShouldTryRematchBattle(void);
bool8 IsTrainerReadyForRematch(void);
void ShouldTryGetTrainerScript(void);
u16 CountBattledRematchTeams(u16 trainerId);
bool32 IsPlayerDefeated(u32 battleOutcome);
void ClearAllTrainerWantRematchStates(void);
bool32 CheckRematchTrainerFlag(u16 flag);
void SetRematchTrainerFlag(u16 flag);
void ClearRematchTrainerFlag(u16 flag);
bool8 IsFirstTrainerIdReadyForRematch(const struct RematchTrainer *table, u16 firstBattleTrainerId);

#endif // GUARD_BATTLE_SETUP_H
