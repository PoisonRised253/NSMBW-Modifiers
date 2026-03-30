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


ext void preGameLoop();
ext void onGameLoop();
ext void onStageCreated();
ext void ApplyModifiers(bool);

#endif