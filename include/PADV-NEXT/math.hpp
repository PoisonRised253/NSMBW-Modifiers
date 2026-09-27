#ifndef PADV_MATH
#define PADV_MATH
#include "PADV-NEXT/defines.h"

template <typename T>
T clamp(T value, T min, T max)
{
    if (value <= min)
        return min;
    if (value >= max)
        return max;
    return value;
}

template <typename T>
T Abs(T value) {
    if(value < 0) return -value;
    return value;
}

template <typename T>
T Absnt(T value)
{
    if (value > 0) return -value;
    return value;
}

inline mVec2_c MakeVec2(float x, float y) { return mVec2_c(x, y); }
inline mVec3_c MakeVec(float x, float y, float z) { return mVec3_c(x, y, z); }
inline mVec3_c VecAdd(mVec3_c a, mVec3_c b) { return mVec3_c(a.x + b.x, a.y + b.y, a.z + b.z); }
inline mVec3_c VecSub(mVec3_c a, mVec3_c b) { return mVec3_c(a.x - b.x, a.y - b.y, a.z - b.z); }
inline mVec3_c VecMul(mVec3_c a, mVec3_c b) { return mVec3_c(a.x * b.x, a.y * b.y, a.z * b.z); }
inline mVec3_c VecDiv(mVec3_c a, mVec3_c b) { return mVec3_c(a.x / b.x, a.y / b.y, a.z / b.z); }
inline mVec2_c VecDist(mVec3_c a, mVec3_c b)
{
    float xd = b.x - a.x;
    float yd = b.y - a.y;
    return MakeVec2(xd, yd);
}

inline int Round(float x)
{
    return (int)(x >= 0.0f ? x + 0.5f : x - 0.5f);
}

inline mVec2_c RoundToNearestTile(mVec3_c pos) {
    mVec2_c newPos = MakeVec2(
    (pos.x / 16.f + 0.5f) * 16.f,
    (pos.y / 16.f + 0.5f) * 16.f
    );
    
    return newPos;
}

inline bool IsNaN(float value) { return value != value; }

#endif
