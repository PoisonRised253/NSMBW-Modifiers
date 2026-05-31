#ifndef __H_MATH
#define __H_MATH

#include "game.h"

//Not Vanilla - PADV
typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    bool operator==(const Vec4& other) const {
        ret (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
    }

    Vec4 operator+=(const Vec4& other) {
        ret (Vec4){this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
    }

    Vec4 operator-=(const Vec4& other) {
        ret (Vec4){this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
    }
    
    Vec4 operator*=(const Vec4& other) {
        ret (Vec4){this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w};
    }

    Vec4 operator*=(const float other) {
        ret (Vec4){this->x * other, this->y * other, this->z * other, this->w * other};
    }

    Vec4 operator/=(const Vec4& other) {
        ret (Vec4){this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w};
    }

    Vec4 operator/=(const float other) {
        ret (Vec4){this->x / other, this->y / other, this->z / other, this->w / other};
    }
};

inline float clampf(float val, float min, float max);
inline int Round(float x);
inline Vec2 RoundToNearestTile(Vec pos);
inline bool IsNaN(float value);
inline Vec MakeVec(float x, float y, float z);
inline Vec2 MakeVec2(float x, float y);
inline S16Vec MakeVec16(s16 x, s16 y, s16 z);
inline Vec4 MakeVec4(float x, float y, float z, float w);
inline Vec VecAdd(Vec a, Vec b);
inline Vec VecSub(Vec a, Vec b);
inline Vec VecMul(Vec a, Vec b);
inline Vec VecDiv(Vec a, Vec b);
inline Vec2 VecDist(Vec a, Vec b);
inline Vec2 DistSq(const Vec3& a, const Vec3& b);
inline Vec VecAddFloat(Vec v, float m);
inline Vec VecSubFloat(Vec v, float m);
inline Vec VecMulFloat(Vec v, float m);
inline Vec VecDivFloat(Vec v, float m);
inline bool VecCmp(Vec a, Vec b);
inline bool VecCmp2(Vec2 a, Vec2 b);

#endif