#include "PADV-NEXT/OverlayObjects.h"
extern dBlower_c* Blowers[8];

//mVec2_c Rect is now *32 scaled, to avoid manual math lol (32 cuz both sides)
dBlower_c::dBlower_c(mVec3_c pos, mVec2_c rect, float intensity) {

    mPos = pos;
    mScale = mVec2_c(rect.x * 32, rect.y * 32);
    mIntensity = intensity;
    mIsDirty = true;
    mDelayedDelete = false;
    static const float effectScaleFix = 0.15625;
    mVec3_c effectScale = mVec3_c(rect.x + (effectScaleFix * rect.x), rect.y, 1);
    mVec3_c effectPos = mVec3_c(mPos.x, mPos.y - (mScale.y / 2), -6500.f);
    int freeSlot = FindNextFreeArrayEntry((void**)Blowers, Capacity);
    OSReport("freeSlot == %i\n", freeSlot);
    if(freeSlot != 0xFFFF) {
        mAssignedSlot = freeSlot;
        Blowers[freeSlot] = this;
        mEf::createEffect(getEffectName(), 0, &effectPos, &mAng3_c::Zero, &effectScale);
    }
    else mAssignedSlot = -1;
}

dBlower_c::~dBlower_c() {
    if(mAssignedSlot != -1)
        Blowers[mAssignedSlot] = NULL;
    
    this->mPos = mVec3_c::Zero;
    this->mScale = mVec2_c(0,0);
    this->mRect = mVec4_c(0,0,0,0);
    this->mIntensity = NULL;
    this->mIsDirty = NULL;
    this->mAssignedSlot = NULL;
    this->mDelayedDelete = NULL;
}

void dBlower_c::Execute() {
    //dActor_c* actorBuff[Capacity] = {NULL};
    dActor_c* forceBuff[Capacity] = {NULL};
    for(int i = 0; i < 4; i++) {
        if(!Players[i]) continue;
        if(CheckOverlap(MakeVec2(Players[i]->mPos.x, Players[i]->mPos.y))) {
            int freeSlot = FindNextFreeArrayEntry((void**)forceBuff, 8);
            if(freeSlot != 0xFFFF) forceBuff[freeSlot] = (dActor_c*)Players[i];
        }
    }
    if(forceBuff[0]) ApplyForce(forceBuff); //Just simply if buffer empty, fuck it.
}

//Generates mVec2_c BL, mVec2_c TR and smashes them together into one struct
mVec4_c dBlower_c::genAndStoreRect() {
    mVec4_c out = mVec4_c(
        mPos.x - (mScale.x / 2),
        mPos.y - (mScale.y * 1.5f),
        mPos.x + (mScale.x / 2),
        mPos.y + (mScale.y * 1.5f)
    );
    mRect = out;

    return out;
}

bool dBlower_c::CheckOverlap(mVec2_c pos) {
    static const mVec4_c Zero = mVec4_c(0,0,0,0);
    if(mRect == Zero || mIsDirty) genAndStoreRect();
    return pos.x >= mRect.x &&
           pos.x <= mRect.z &&
           pos.y >= mRect.y &&
           pos.y <= mRect.w;
}

void dBlower_c::ApplyForce(dActor_c* obj[]) {
    float inten = mIntensity / 60; //To keep Per-Frame-ness
    if(!obj[0]) return;
    for(int i = 0; i < Capacity; i++) {
        if(!obj[i]) return; //Since the Array fills from 0 onward without any spaces inbetween, just fuckin cancel shit if there is no more in the next slot
        float newSpeed = clamp(obj[i]->mSpeed.y += inten, -(mIntensity / 3), mIntensity);
        obj[i]->mSpeed.y = newSpeed;
    }
    return;
}

bool dBlower_c::Verify() {
    if(mAssignedSlot == -1 || mDelayedDelete) {delete this; return false;}
    return true;
}

const char* dBlower_c::getEffectName() {
    return "Wm_ob_stream";
}