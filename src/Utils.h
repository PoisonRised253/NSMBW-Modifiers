#ifndef __H_UTILS
#define __H_UTILS
#include "common.h"
#include "game.h"
#include "scStage.h"
#include "defines.h"
#include "math.h"

extern bool Modifiers[MOD_SIZE];
extern dAc_Py_c *Players[4];
extern int GlobalFrameTimer;
extern int currentMoveMod;

inline bool GetPlayers();
inline void getLevelInfo(u32 *, u32 *, u8 *, u32 *, u32 *);
inline void SetLives();
ext void ToggleMods();
inline bool CallSpacer(int callsPerSecond);
inline dEn_c *GetNextOfType(Actors actorID, bool fromPlayer);
inline void ClearObjVel(dEn_c *obj, u8 mode);
inline void DeleteUnwanted();
inline int GetPowerupType(u32 settings);

volatile void LivePatch(u32 newInstr, u32 *addr);
ext void ModifyMovement(int mode);
ext void NahFuckThat(bool); // Stops dAc_Py_c from existing
inline bool ObjectBoundCheck(Vec boundsMin, Vec boundsMax, Vec pos);
inline u32* GetMemberFromOffset(void* object, u32 offset);
volatile inline int *GetPlayerPowerState(dAc_Py_c *player);
volatile inline int *checkGrounded(dAc_Py_c *player);
volatile inline int *checkAllowedMoves(dAc_Py_c *player);
volatile inline bool isPause();
volatile inline int *GetPlayerState(dAc_Py_c *player);
ext void DisablePropeller(u32 replaceWithItemID);
ext void SetUpper(u32* variable, u16 value);
ext void SetLower(u32* variable, u16 value);
inline u32 NoJumping(u32 value);
ext void DumpPlayer(int which);
ext void HandleHotkeys();

template <typename T>
inline int GetNextFreeArrayEntry(T* arr[], int size);

#endif