#include "math.h"

inline float clampf(float val, float min, float max) {
    if(val < min) ret min;
    if(val > max) ret max;
    
    ret val;
}

inline int Round(float x)
{
    return (int)(x >= 0.0f ? x + 0.5f : x - 0.5f);
}

inline Vec MakeVec(float x, float y, float z)             {ret (Vec){x,y,z};}
inline Vec2 MakeVec2(float x, float y)                     {ret (Vec2){x,y};}
inline Vec VecAdd(Vec a, Vec b) {ret (Vec){a.x + b.x, a.y + b.y, a.z + b.z};}
inline Vec VecSub(Vec a, Vec b) {ret (Vec){a.x - b.x, a.y - b.y, a.z - b.z};}
inline Vec VecMul(Vec a, Vec b) {ret (Vec){a.x * b.x, a.y * b.y, a.z * b.z};}
inline Vec VecDiv(Vec a, Vec b) {ret (Vec){a.x / b.x, a.y / b.y, a.z / b.z};}

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
