#ifndef PADV_UTILS
#define PADV_UTILS
#include "PADV-NEXT/defines.h"

ext bool GetAllInputs();
ext dGameKeyCore_c* CompareToInputs(int);
ext bool CompareAgainstInput(int mask, int controller);
ext bool GetPlayers();
ext dEn_c* GetNextOfType(Actors, void*);
ext int GetPowerupType(u32);
volatile void LivePatch(u32, void*);
ext void ModifyMovement(int mode);
ext void NahFuckThat(bool);
//ext bool ObjectBoundCheck(mVec3_c, mVec3_c, mVec3_c);
//ext bool ObjectBoundCheck(mVec4_c boundsA, mVec4_c boundsB);
ext bool* isDemo(dAcPy_c*);
ext int *GetPlayerPowerState(dAcPy_c*);
ext int *checkGrounded(dAcPy_c*);
ext int *checkAllowedMoves(dAcPy_c*);
ext int *GetPlayerState(dAcPy_c*);
ext bool isPause();
ext u32 NoJumping(u32);
ext void DisableItem(u32, u32);
ext void SetUpper(u32*, u16);
ext void SetLower(u32*, u16);
ext void WrapNumber(u32&, u32, u32);
ext void HandleHotkeys();
ext static const u32 CreateLoadImmediate(u8, u16);
ext void AntiBubble();

int FindNextFreeArrayEntry(void* Arr[], int);
int FindPointerInArray(void* Arr[], int, void*);
#endif