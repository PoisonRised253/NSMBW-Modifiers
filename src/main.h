#ifndef __H_TORTURE
#define __H_TORTURE

#include "common.h"
#include "game.h"
#include "scStage.h"
#include "course.h"
#include "dCourse.h"
#include "defines.h"
#include "Utils.h"
#include "Modifiers.h"

//Included to make the compiler stop screaming that preGameLoop() is at 0x0 of the compiled file.
ext void NullSub();
ext void preGameLoop();
ext void onGameLoop();
ext void onStageCreated();
ext void onNextScene();
ext void onRecieveResetEvent();
ext void onBoot();
ext void ApplyModifiers(bool);
ext void AntiBubble();

ext void DeathMushHandler(dAc_Py_c* toucher);
ext void onPlayerCollisionUpdated(void* playerptr);
ext void onPlayerPhysicsUpdated(void* playerptr);
extern dEn_c* smitePlayer;

#endif