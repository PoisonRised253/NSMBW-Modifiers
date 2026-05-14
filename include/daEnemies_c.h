#ifndef __H_ENEMIES
#define __H_ENEMIES
#include "Utils.h"

//Collection of Enemies ive looked at, and explored
//I dont know how to make headers actually align to ingame Memory, so im using methods instead, please forgive my sins (sizeof() appears to be wrong lol)
//dEn_c is 1714 bits (padded)

class daBoo_c : public dEn_c {
    public:
    float* getWaitStateChange()         const { ret (float*)GetMemberFromOffset((void*)this, 0x668); } //40c00000 when Looked at, 42c00000 when looked away
    float* getWaitBeforeSearch()        const { ret (float*)GetMemberFromOffset((void*)this, 0x6A0); }
    void* getEffectChaseInstance()      const { ret GetMemberFromOffset((void*)this, 0x824); }
    u32* getSearchEffectActive()        const { ret GetMemberFromOffset((void*)this, 0x8C8); } // Dont just randomly set this, it will crash
    u32* getAnimateShakeCooldown()      const { ret GetMemberFromOffset((void*)this, 0x9AC); }
    u32* getKnockedEffectInactive()     const { ret GetMemberFromOffset((void*)this, 0x9B0); }
    u32* getInvisible()                 const { ret GetMemberFromOffset((void*)this, 0x9C8); }
    u32* getSpeed()                     const { ret GetMemberFromOffset((void*)this, 0x9D4); }
    
    static float* getGlobalScaler() { ret (float*)0x80AD4A94; } //This does also scale collision, strange isnt it, especially since it isnt instance-bound
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
    float* getMaxFallSpeed()  const { ret (float*)GetMemberFromOffset((void*)this, 0x0F8); } //Default=0xc0c00000
    float* getGravity()       const { ret (float*)GetMemberFromOffset((void*)this, 0x114); } //Default=0xbe19999a
    u32*   getBounceState()   const { ret (u32*)GetMemberFromOffset((void*)this, 0x360);   } //0x0=InAir, 0x00000001=OnGround, 0x00000002=Freeze
    float* getHitboxX()       const { ret (float*)GetMemberFromOffset((void*)this, 0x5D8); } //Default=0x0000e000
    float* getHitboxY()       const { ret (float*)GetMemberFromOffset((void*)this, 0x5D0); } //Default=0xffff2000
    float* getPhysRadius()    const { ret (float*)GetMemberFromOffset((void*)this, 0x670); } //Default=0x41666667
    bool*  getPhysActive()    const { ret (bool*)GetMemberFromOffset((void*)this, 0x6A8);  } //Default=0x00000001, 0x0 to disable interaction
    float* getPhysScale()     const { ret (float*)GetMemberFromOffset((void*)this, 0x6C8); } //Default=3f80000000
    float* getDeformation()   const { ret (float*)GetMemberFromOffset((void*)this, 0x6E4); } //Default=4198000000

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
    //These addresses appear to be negative, dont abs them
    //Base: 0x81541430
    //attackState at 815410A8:0x1=Get Ready, 0x2=Attacking/Attacked, 0x3=ReadyToAttack
};

#endif