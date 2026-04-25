#include "math.h"

inline float clampf(float val, float min, float max) {
    if(val < min) ret min;
    if(val > max) ret max;
    
    ret val;
}

inline int Round(float x)
{
    ret (int)(x >= 0.0f ? x + 0.5f : x - 0.5f);
}

inline Vec2 RoundToNearestTile(Vec pos) {
    Vec2 newPos = {
        (int)((float)pos.x / 16.f + 0.5f) * 16.f,
        (int)((float)pos.y / 16.f + 0.5f) * 16.f
    };
    ret newPos;
}

inline bool IsNaN(float value) {ret value != value;}

inline Vec MakeVec(float x, float y, float z)             {ret (Vec){x,y,z};}
inline Vec2 MakeVec2(float x, float y)                     {ret (Vec2){x,y};}
inline S16Vec MakeVec16(s16 x, s16 y, s16 z)           {ret (S16Vec){x,y,z};}
inline Vec VecAdd(Vec a, Vec b) {ret (Vec){a.x + b.x, a.y + b.y, a.z + b.z};}
inline Vec VecSub(Vec a, Vec b) {ret (Vec){a.x - b.x, a.y - b.y, a.z - b.z};}
inline Vec VecMul(Vec a, Vec b) {ret (Vec){a.x * b.x, a.y * b.y, a.z * b.z};}
inline Vec VecDiv(Vec a, Vec b) {ret (Vec){a.x / b.x, a.y / b.y, a.z / b.z};}
inline Vec2 VecDist(Vec a, Vec b) {float xd = b.x - a.x; float yd = b.y - a.y; ret MakeVec2(xd, yd); }

inline Vec VecAddFloat(Vec v, float m) {
    v.x += m;
    v.y += m;
    v.z += m;
    ret v;
}

inline Vec VecSubFloat(Vec v, float m) {
    v.x -= m;
    v.y -= m;
    v.z -= m;
    ret v;
}

inline Vec VecMulFloat(Vec v, float m) {
    v.x *= m;
    v.y *= m;
    v.z *= m;
    ret v;
}

inline Vec VecDivFloat(Vec v, float m) {
    v.x /= m;
    v.y /= m;
    v.z /= m;
    ret v;
}

inline bool VecCmp(Vec a, Vec b) {
    ret (a.x == b.x && a.y == b.y && a.z == b.z);
}