#ifndef __H_MODIFIERS
#define __H_MODIFIERS
#include "Utils.h"

ext void Grow(); //Test Func, to be replaced, Grows Y on player->scale
ext void Shrink(); //Test Func, to be replaced, Shrinks Y on player->scale
ext void SmallerAndNoYoshi(); //Empties yoshiID and makes Mario be forced into MINI++ state.
ext void NahFuckThat(bool); //Stops dAc_Py_c from existing
ext void TowerFunc(); //Lower Jumping
ext void WaterLevel(); //Increases SpeedPerFrame and MaxSpeed, per frame
ext void Worldmapify(bool); //Makes the Level kinda like WM
ext void SpinEternally();

#endif