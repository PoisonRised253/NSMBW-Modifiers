#ifndef __H_UTILS
#define __H_UTILS
#include "common.h"
#include "game.h"
#include "scStage.h"
#include "defines.h"

extern bool Modifiers[MOD_SIZE];
extern dAc_Py_c *Players[4];

inline bool GetPlayers();
inline void getLevelInfo(u32 *lOut, u32 *wOut, u8 *aOut);
inline void SetLives();
ext void ToggleMods();
inline float clampf(float val, float min, float max);
inline int Round(float x);
ext void changeActivePhysicsRect(dStageActor_c *actor, float xc, float yc, float xe, float ye);
#endif