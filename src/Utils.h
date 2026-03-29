#ifndef __H_UTILS
#define __H_UTILS
#include "common.h"
#include "game.h"
#include "scStage.h"
#include "defines.h"
#include "item.h"
#include "math.h"

extern bool Modifiers[MOD_SIZE];
extern dAc_Py_c *Players[4];
extern int GlobalFrameTimer;

inline bool GetPlayers();
inline void getLevelInfo(u32*, u32*, u8*, u32*, u32*);
inline void SetLives();
ext void ToggleMods();
inline bool CallSpacer(int callsPerSecond);
inline dBase_c* GetNextOfType(Actors actorID);
inline void GetAllOfType(Actors actorID, u8 sizeOfArray, dEn_c* outBuff[], int* outSize);
inline void ClearObjVel(dEn_c* obj, u8 mode);

#endif