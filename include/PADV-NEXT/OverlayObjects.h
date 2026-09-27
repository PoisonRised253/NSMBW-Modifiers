#ifndef PADV_OBJECTS
#define PADV_OBJECTS
#include "PADV-NEXT/defines.h"
#include <game/mLib/m_effect.hpp>
extern int FrameTimer;

class dBlower_c {
    private:
    static const int MaxSpeed = 12;
    mVec3_c mPos;
    mVec2_c mScale;
    mVec4_c mRect; //To store generateRect(), avoiding repeat calls
    float mIntensity;
    bool mIsDirty;
    int mAssignedSlot;
    
    static const char* getEffectName();
    mVec4_c genAndStoreRect();
    bool CheckOverlap(mVec2_c pos);
    void ApplyForce(dActor_c* obj[]);
    public:
    dBlower_c(mVec3_c pos, mVec2_c scale, float intensity);
    ~dBlower_c();
    void Execute();
    bool Verify();
    static const int Capacity = 8;
    bool mDelayedDelete;
};
#endif