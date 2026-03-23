#ifndef __H_MATH
#define __H_MATH

#include "game.h"

inline float clampf(float val, float min, float max);
inline int Round(float x);
inline Vec VecAdd(Vec a, Vec b);
inline Vec VecSub(Vec a, Vec b);
inline Vec VecMul(Vec a, Vec b);
inline Vec VecDiv(Vec a, Vec b);
inline Vec VecAddFloat(Vec v, float m);
inline Vec VecSubFloat(Vec v, float m);
inline Vec VecMulFloat(Vec v, float m);
inline Vec VecDivFloat(Vec v, float m);
inline bool VecCmp(Vec a, Vec b);

#endif