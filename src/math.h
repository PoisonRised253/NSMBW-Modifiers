#ifndef __H_MATH
#define __H_MATH

#include "game.h"

inline float clampf(float val, float min, float max);
inline int Round(float x);
inline Vec2 RoundToNearestTile(Vec pos);
inline bool IsNaN(float value);
inline Vec MakeVec(float x, float y, float z);
inline Vec2 MakeVec2(float x, float y);
inline Vec VecAdd(Vec a, Vec b);
inline Vec VecSub(Vec a, Vec b);
inline Vec VecMul(Vec a, Vec b);
inline Vec VecDiv(Vec a, Vec b);
inline Vec2 VecDist(Vec a, Vec b);
inline Vec VecAddFloat(Vec v, float m);
inline Vec VecSubFloat(Vec v, float m);
inline Vec VecMulFloat(Vec v, float m);
inline Vec VecDivFloat(Vec v, float m);
inline bool VecCmp(Vec a, Vec b);

#endif