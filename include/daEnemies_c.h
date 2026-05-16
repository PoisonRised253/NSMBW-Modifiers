#ifndef __H_ENEMIES
#define __H_ENEMIES
#include "Utils.h"

//Collection of Enemies ive looked at, and explored
//I dont know how to make headers actually align to ingame Memory, so im using methods instead, please forgive my sins (sizeof() appears to be wrong lol)
//dEn_c is 1714 bits (padded)

class daBoo_c : public dEn_c {
    public:
    
    u32* getSearchEffectActive()        const { ret GetMemberFromOffset((void*)this, 0x8C8); } // Dont just randomly set this, it will crash
    u32* getAnimateShakeCooldown()      const { ret GetMemberFromOffset((void*)this, 0x9AC); }
    u32* getKnockedEffectInactive()     const { ret GetMemberFromOffset((void*)this, 0x9B0); }
    u32* getInvisible()                 const { ret GetMemberFromOffset((void*)this, 0x9C8); }
    u32* getSpeed()                     const { ret GetMemberFromOffset((void*)this, 0x9D4); }

    float* getWaitStateChange()         const { ret (float*)GetMemberFromOffset((void*)this, 0x668); } //40c00000 when Looked at, 42c00000 when looked away
    float* getWaitBeforeSearch()        const { ret (float*)GetMemberFromOffset((void*)this, 0x6A0); }
    static float* getGlobalScaler()     { ret (float*)0x80AD4A94; } //This does also scale collision, strange isnt it, especially since it isnt instance-bound

    void* getEffectChaseInstance()      const { ret GetMemberFromOffset((void*)this, 0x824); } 
};

class daBulletLauncher_c : public dEn_c {
    int execute();
	void activate();

	public:
	u32* getAnimAllowShoot() const {ret GetMemberFromOffset((void*)this, 0x500); }
	u32* getFrame() const {ret GetMemberFromOffset((void*)this, 0xA3C); }
	u32* getCooldown() const {ret GetMemberFromOffset((void*)this, 0xE1C); }
	u32* getState() const {ret GetMemberFromOffset((void*)this, 0xE34); }
};

class daLemmyBall_c : public dEn_c {
    public:
    
    u32*   getBounceState()   const { ret (u32*)GetMemberFromOffset((void*)this, 0x360);   } //0x0=InAir, 0x00000001=OnGround, 0x00000002=Freeze
    
    bool*  getPhysActive()    const { ret (bool*)GetMemberFromOffset((void*)this, 0x6A8);  } //Default=0x00000001, 0x0 to disable interaction

    float* getPhysScale()     const { ret (float*)GetMemberFromOffset((void*)this, 0x6C8); } //Default=3f80000000
    float* getDeformation()   const { ret (float*)GetMemberFromOffset((void*)this, 0x6E4); } //Default=4198000000
    float* getMaxFallSpeed()  const { ret (float*)GetMemberFromOffset((void*)this, 0x0F8); } //Default=0xc0c00000
    float* getGravity()       const { ret (float*)GetMemberFromOffset((void*)this, 0x114); } //Default=0xbe19999a
    float* getHitboxX()       const { ret (float*)GetMemberFromOffset((void*)this, 0x5D8); } //Default=0x0000e000
    float* getHitboxY()       const { ret (float*)GetMemberFromOffset((void*)this, 0x5D0); } //Default=0xffff2000
    float* getPhysRadius()    const { ret (float*)GetMemberFromOffset((void*)this, 0x670); } //Default=0x41666667

    void setHitbox(int mode) {
        float size = 0.f;
        if(mode == 0)      {size = 0.25f; *(u32*)this->getHitboxX() = 0x00002000; *(u32*)this->getHitboxY() = 0xffffd000;}
        else if(mode == 1) {size = 0.5f; *(u32*)this->getHitboxX() = 0x00007000; *(u32*)this->getHitboxY() =  0xffffa000;}
        else if(mode == 2) {size = 0.75f; *(u32*)this->getHitboxX() = 0x00006500; *(u32*)this->getHitboxY() = 0xffff3000;}
        else if(mode == 3) {size = 1.f; *(u32*)this->getHitboxX() = 0x0000e000; *(u32*)this->getHitboxY() =   0xffff2000;}
        else if(mode == 4) {size = 1.25f; *(u32*)this->getHitboxX() = 0x00010000; *(u32*)this->getHitboxY() = 0xffff0f00;}
        else if(mode == 5) {size = 1.5f; *(u32*)this->getHitboxX() = 0x00013500; *(u32*)this->getHitboxY() =  0xffff0000;}
        else if(mode == 6) {size = 1.75f; *(u32*)this->getHitboxX() = 0x00015500; *(u32*)this->getHitboxY() = 0xffff0fff;} // <- Best youll get i guess
        else if(mode == 7) {size = 2.f; *(u32*)this->getHitboxX() = 0x00018000; *(u32*)this->getHitboxY() =   0xffff0fff;} // <- Best youll get i guess
        else ret;
        
        const int f = 0x41666667;
        *this->getPhysScale() = size;
        *this->getPhysRadius() = *(float*)&f * size;
        OSReport("Scale is now %f\n", size);
        ret;
    }

    void setStatic(bool _static) {
        if(_static) *this->getBounceState() = 2;
        else *this->getBounceState() = 0;
        ret;
    }
};

class daChainChomp_c : public dEn_c {
    public:

    u32* getChainLength()           const {ret GetMemberFromOffset((void*)this, -0x64);} //(0x0-0xF else exception)
    u32* getTurnDirection()         const {ret GetMemberFromOffset((void*)this, -0x70);}
    u32* getCooldownAfterLunge()    const {ret GetMemberFromOffset((void*)this, -0x84);} //(second byte only)
    u32* getWaitForAttackCooldown() const {ret GetMemberFromOffset((void*)this, -0xDC);} //(last byte only)
    u32* getAttackState()           const {ret GetMemberFromOffset((void*)this, -0x388);} //(last byte only)
    u32* getHitsBeforeBreak()       const {ret GetMemberFromOffset((void*)this,  0x568);} //Default=3
    
    u8*  getUnknown()               const {ret (u8*)GetMemberFromOffset((void*)this, -0x178);}

    u16* getWhileAttackCooldown()   const {ret (u16*)GetMemberFromOffset((void*)this, -0x1E8);}

    bool IsAttack()                 const {ret !(bool)*GetMemberFromOffset((void*)this, -0xD8);}
    bool* getIgnoreAnchorX()        const {ret (bool*)GetMemberFromOffset((void*)this, -0x3A0);}    

    float* getGravity()             const {ret (float*)GetMemberFromOffset((void*)this, -0x5D4);} //Default=be400000
    float* getPoleX()               const {ret (float*)GetMemberFromOffset((void*)this, 0xAC);}
    float* getPoleY()               const {ret (float*)GetMemberFromOffset((void*)this, 0xB0);}
    float* getChompPivotX()         const {ret (float*)GetMemberFromOffset((void*)this, -0xCC);}
    float* getChompPivotY()         const {ret (float*)GetMemberFromOffset((void*)this, -0xC8);}
    float* getTargetAngle()         const {ret (float*)GetMemberFromOffset((void*)this, -0xD4);}

    Vec2* getPolePos()              const {ret (Vec2*)GetMemberFromOffset((void*)this, 0xAC);}

    Vec3* getPoleVisSize()          const {ret (Vec3*)GetMemberFromOffset((void*)this, 0xDC);}
    void* getSmtAbtGroundpound()    const {ret (void*)GetMemberFromOffset((void*)this, 0x648);}

    //Custom From Here
    Vec4 getPoleHitboxExtents() {
        ret MakeVec4(
        *(float*)GetMemberFromOffset((void*)this, 0x5EC),
        *(float*)GetMemberFromOffset((void*)this, 0x5F4),
        *(float*)GetMemberFromOffset((void*)this, 0x5F8),
        *(float*)GetMemberFromOffset((void*)this, 0x5F0)
        );
    }

    void setPoleHitboxExtents(Vec4 extents) {
        *(float*)GetMemberFromOffset((void*)this, 0x5EC) = extents.x; //ExtentsX-
        *(float*)GetMemberFromOffset((void*)this, 0x5F4) = extents.y; //ExtentsX+
        *(float*)GetMemberFromOffset((void*)this, 0x5F8) = extents.z; //ExtentsY-
        *(float*)GetMemberFromOffset((void*)this, 0x5F0) = extents.w; //ExtentsY+
        ret;
    }

    bool IsDead()     const {ret (bool)*GetMemberFromOffset((void*)this, -0x2BC) && !(bool)*GetMemberFromOffset((void*)this, -0x2B8);}
    bool IsReleased() const {ret (bool)*GetMemberFromOffset((void*)this, -0x2BC) && (bool)*GetMemberFromOffset((void*)this, -0x2B8);}

    bool isChompValid() {
        ret (!IsDead() && !IsReleased());
    }
};

class daThwomp_c : public dEn_c {
    //Base: 0x815414a0
    //u8? FaceID at 81541a58 | LMFAO
    //??? DroppedCooldownUntilRise at 81541a7c
    //float DropSpeedY at 815415b4
    //u32 extraEffectToggle = 81541a70
};

#endif