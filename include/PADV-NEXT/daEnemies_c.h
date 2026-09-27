#ifndef __H_ENEMIES
#define __H_ENEMIES
#include "PADV-NEXT/defines.h"
#define UnChar unsigned char
extern void *DAT_BOOSCALER;
extern void *DAT_ICICLESIZE;
extern void *DAT_ICICLEGROW; 
extern void *DAT_FOOTLENGTH;
extern void *LP_CHEEPSPAWNID;

extern volatile void LivePatch(u32 newInstr, void* ptr);
extern "C" static const u32 CreateLoadImmediate(u8, u16);

// Collection of Enemies ive looked at, and explored
// I dont know how to make headers actually align to ingame Memory, so im using methods instead, please forgive my sins (sizeof() appears to be wrong lol)
// dEn_c is 1714 bits (padded), which is appearently 0x24 too much
// Please forgive the halfassed functions, im really sorry but i dont really know how to find out which return type it is, or what inputs it takes, so i halfassed it, just to give a hint to smarter people where roughly to look.
// Again, i ask for your forgiveness.
// Also, there might be some sentimental sounding notes to this, but i like to kindly remind you that im fine, and that this is my perception of optimal commedy.
// Also Also note that i would not do this in a professional environment, just in case anyone looking to hire is here.

// TODO: Test Possible compatability issues, due to MagicNum type access. Maybe i should just generally fix that somehow... hmmm

class daBoo_c : public dEn_c
{
protected:
    int execute();
    int preDraw();
    void executeState_Dispatch();
    void calc();
    void dunnoAnymore();
    void executeState_search__7daBoo_cFv();
    void findNextTarget();
    void heavyMath(); // Here be dragons
    void moveToTarget();
    void selectAngle();
    void somethingRandom();
    void unk2();
    void unknownSetup();
    void updateGraphics();
    void validateTarget();

public:
    static const Actors actorID = EN_TERESA;

    u32 *getSearchEffectActive() const { return GetMemberFromOffset((void *)this, 0x8C8); } // Dont just randomly set this, it will crash
    u32 *getAnimateShakeCooldown() const { return GetMemberFromOffset((void *)this, 0x9AC); }
    u32 *getKnockedEffectInactive() const { return GetMemberFromOffset((void *)this, 0x9B0); }
    u32 *getInvisible() const { return GetMemberFromOffset((void *)this, 0x9C8); }
    u32 *getSpeed() const { return GetMemberFromOffset((void *)this, 0x9D4); }

    float *getWaitStateChange() const { return (float *) GetMemberFromOffset((void *)this, 0x668); } // 40c00000 when Looked at, 42c00000 when looked away
    float *getWaitBeforeSearch() const { return (float *) GetMemberFromOffset((void *)this, 0x6A0); }
    static float *getGlobalScaler() { return (float *)&DAT_BOOSCALER; } // This does also scale collision, strange isnt it, especially since it isnt instance-bound

    void *getEffectChaseInstance() const { return GetMemberFromOffset((void *)this, 0x824); }
};

class daBulletLauncher_c : public dEn_c
{
protected:
    int execute();
    void activate();
    void updateChildTable();
    void constructBullet();
    bool checkActivate();

public:
    static const Actors actorID = EN_KILLER_HOUDAI;
    u32 *getAnimAllowShoot() const { return GetMemberFromOffset((void *)this, 0x500); }
    u32 *getFrame() const { return GetMemberFromOffset((void *)this, 0xA3C); }
    u32 *getCooldown() const { return GetMemberFromOffset((void *)this, 0xE1C); }
    u32 *getState() const { return GetMemberFromOffset((void *)this, 0xE34); }
};

class daLemmyBall_c : public dEn_c
{
protected:
    int calcRender(); // might be true preDraw(), im assuming int.
    int preDraw();
    int execute();
    int postExecute();
    void *setup(); //???
    void executeState_Dispatch();
    void executeState_Normal();
    bool grounded(); // Might be a var lol
    void hashcall(); // No clue what this does *presses big red button*
    float limitOscillate();
    float oscillate();
    void somewithballs(); // Wow i was not having it that morning huh
    void spin();          // The trend continues
    void unknownBull();   // Dude really, swearing in your own headers now... why am i like this...

public:
    static const Actors actorID = EN_BOUNCE_BALL;

    u32 *getBounceState() const { return(u32 *) GetMemberFromOffset((void *)this, 0x360); } // 0x0=InAir, 0x00000001=OnGround, 0x00000002=Freeze

    bool *getPhysActive() const { return(bool *) GetMemberFromOffset((void *)this, 0x6A8); } // Default=0x00000001, 0x0 to disable interaction

    float *getPhysScale() const { return(float *) GetMemberFromOffset((void *)this, 0x6C8); }    // Default=3f80000000
    float *getDeformation() const { return(float *) GetMemberFromOffset((void *)this, 0x6E4); }  // Default=4198000000
    float *getMaxFallSpeed() const { return(float *) GetMemberFromOffset((void *)this, 0x0F8); } // Default=0xc0c00000
    float *getGravity() const { return(float *) GetMemberFromOffset((void *)this, 0x114); }      // Default=0xbe19999a
    float *getHitboxX() const { return(float *) GetMemberFromOffset((void *)this, 0x5D8); }      // Default=0x0000e000
    float *getHitboxY() const { return(float *) GetMemberFromOffset((void *)this, 0x5D0); }      // Default=0xffff2000
    float *getPhysRadius() const { return(float *) GetMemberFromOffset((void *)this, 0x670); }   // Default=0x41666667

    void setHitbox(int mode)
    {
        float size = 0.f;
        if (mode == 0)
        {
            size = 0.25f;
            *(u32 *)this->getHitboxX() = 0x00002000;
            *(u32 *)this->getHitboxY() = 0xffffd000;
        }
        else if (mode == 1)
        {
            size = 0.5f;
            *(u32 *)this->getHitboxX() = 0x00007000;
            *(u32 *)this->getHitboxY() = 0xffffa000;
        }
        else if (mode == 2)
        {
            size = 0.75f;
            *(u32 *)this->getHitboxX() = 0x00006500;
            *(u32 *)this->getHitboxY() = 0xffff3000;
        }
        else if (mode == 3)
        {
            size = 1.f;
            *(u32 *)this->getHitboxX() = 0x0000e000;
            *(u32 *)this->getHitboxY() = 0xffff2000;
        }
        else if (mode == 4)
        {
            size = 1.25f;
            *(u32 *)this->getHitboxX() = 0x00010000;
            *(u32 *)this->getHitboxY() = 0xffff0f00;
        }
        else if (mode == 5)
        {
            size = 1.5f;
            *(u32 *)this->getHitboxX() = 0x00013500;
            *(u32 *)this->getHitboxY() = 0xffff0000;
        }
        else if (mode == 6)
        {
            size = 1.75f;
            *(u32 *)this->getHitboxX() = 0x00015500;
            *(u32 *)this->getHitboxY() = 0xffff0fff;
        } // <- Best youll get i guess
        else if (mode == 7)
        {
            size = 2.f;
            *(u32 *)this->getHitboxX() = 0x00018000;
            *(u32 *)this->getHitboxY() = 0xffff0fff;
        } // <- Best youll get i guess
        else
            return;

        const int f = 0x41666667;
        *this->getPhysScale() = size;
        *this->getPhysRadius() = *(float *)&f * size;
        OSReport("Scale is now %f\n", size);
        return;
    }

    void setStatic(bool _static)
    {
        if (_static)
            *this->getBounceState() = 2;
        else
            *this->getBounceState() = 0;
        return;
    }
};

class daChainChomp_c : public dEn_c
{
public:
    static const Actors actorIDPole = EN_WANWAN_PILE;
    static const Actors actorIDChomp = EN_WANWAN;

    u32 *getChainLength() const { return GetMemberFromOffset((void *)this, -0x64); }           //(0x0-0xF else exception)
    u32 *getTurnDirection() const { return GetMemberFromOffset((void *)this, -0x70); }
    u32 *getCooldownAfterLunge() const { return GetMemberFromOffset((void *)this, -0x84); }    //(second byte only)
    u32 *getWaitForAttackCooldown() const { return GetMemberFromOffset((void *)this, -0xDC); } //(last byte only)
    u32 *getAttackState() const { return GetMemberFromOffset((void *)this, -0x388); }          //(last byte only)
    u32 *getHitsBeforeBreak() const { return GetMemberFromOffset((void *)this, 0x568); }       // Default=3

    u8 *getUnknown() const { return(u8 *) GetMemberFromOffset((void *)this, -0x178); }

    u16 *getWhileAttackCooldown() const { return(u16 *) GetMemberFromOffset((void *)this, -0x1E8); }

    bool IsAttack() const { return !(bool)*GetMemberFromOffset((void *)this, -0xD8); }
    bool *getIgnoreAnchorX() const { return(bool *) GetMemberFromOffset((void *)this, -0x3A0); }

    float *getGravity() const { return(float *) GetMemberFromOffset((void *)this, -0x5D4); }   // Default=be400000
    float *getPoleX() const { return(float *) GetMemberFromOffset((void *)this, 0xAC); }
    float *getPoleY() const { return(float *) GetMemberFromOffset((void *)this, 0xB0); }
    float *getChompPivotX() const { return(float *) GetMemberFromOffset((void *)this, -0xCC); }
    float *getChompPivotY() const { return(float *) GetMemberFromOffset((void *)this, -0xC8); }
    float *getTargetAngle() const { return(float *) GetMemberFromOffset((void *)this, -0xD4); }

    mVec2_c *getPolePos() const { return(mVec2_c *) GetMemberFromOffset((void *)this, 0xAC); }

    mVec3_c *getPoleVisSize() const { return(mVec3_c *) GetMemberFromOffset((void *)this, 0xDC); }
    void *getSmtAbtGroundpound() const { return(void *) GetMemberFromOffset((void *)this, 0x648); }

    // Custom From Here
    mVec4_c getPoleHitboxExtents()
    {
        return mVec4_c(
            *(float *)GetMemberFromOffset((void *)this, 0x5EC),
            *(float *)GetMemberFromOffset((void *)this, 0x5F4),
            *(float *)GetMemberFromOffset((void *)this, 0x5F8),
            *(float *)GetMemberFromOffset((void *)this, 0x5F0));
    }

    void setPoleHitboxExtents(mVec4_c extents)
    {
        *(float *)GetMemberFromOffset((void *)this, 0x5EC) = extents.x; // ExtentsX-
        *(float *)GetMemberFromOffset((void *)this, 0x5F4) = extents.y; // ExtentsX+
        *(float *)GetMemberFromOffset((void *)this, 0x5F8) = extents.z; // ExtentsY-
        *(float *)GetMemberFromOffset((void *)this, 0x5F0) = extents.w; // ExtentsY+
        return;
    }

    bool IsDead() const { return(bool) * GetMemberFromOffset((void *)this, -0x2BC) && !(bool)*GetMemberFromOffset((void *)this, -0x2B8); }
    bool IsReleased() const { return(bool) * GetMemberFromOffset((void *)this, -0x2BC) && (bool)*GetMemberFromOffset((void *)this, -0x2B8); }

    bool isChompValid()
    {
        return(!IsDead() && !IsReleased());
    }
};

class daThwomp_c : public dEn_c
{
protected:
    int draw();
    int execute();
    void executeState_Dispatch();
    void executeState_Fall();
    void executeState_Fallen();
    void executeState_Rise();
    void executeState_Risen();
    void executeState_Wiggle();

public:
    static const Actors actorID = EN_DOSUN;
    u8 *getFaceID() const { return(u8 *) GetMemberFromOffset((void *)this, 0x5B8); }
    void *getRiseWaitTime() const { return GetMemberFromOffset((void *)this, 0x5DC); }
    float *getDropYSpeed() const { return(float *) GetMemberFromOffset((void *)this, 0x114); }
    u32 *getextraEffectToggle() const { return GetMemberFromOffset((void *)this, 0x5D0); }
};

class daFiresnake_c : public dEn_c
{
public:
    static const Actors actorID = EN_FIRESNAKE;

    // Base: 0x8153ffc0
    // someCooldown at 815404c0 <- Shrinking_Timer
};

class daSpikeball_c : public dEn_c
{
public:
    static const Actors actorID = EN_TOGETEKKYU;
    // Base: 0x8153f918
    // TurnSpeed at 8153FA34 <- frame-controlled, good luck
};

class daRotatingBurner_c : public dEn_c
{
protected:
    int draw();
    int execute();
    int postExecute();

    void initializeState_Dispatch();
    void executeState_Dispatch();
    void finalizeState_Dispatch();

    void initializeState_Stationary();
    void initializeState_FinishRotate();

    void finalizeState_Stationary();
    void finalizeState_Rotate();

    void rotate();
    void something();
    bool checkReachedTargetRotation();

public:
    static const Actors actorID = ROT_BARNAR;
    static const u32 StateID_Turning = 0x8099e838;
    static const u32 StateID_Stationary = 0x8099e878;

    u8 *getRotDirection() const { return(u8 *) GetMemberFromOffset((void *)this, 0x348); }

    u32 *getTurnTimer() const { return GetMemberFromOffset((void *)this, 0x4A4); }
    u32 *BlackMagicLiesHere() const { return GetMemberFromOffset((void *)this, 0xC); }

    float *getCurrentAngle() const { return(float *) GetMemberFromOffset((void *)this, 0x4A0); }
};

namespace Spawners
{

    class dParaBombSpawner_c : public dActor_c
    {
    public:
        static const Actors actorID = WAKI_PARABOM;

        u32 *getAllowDrop() const { return GetMemberFromOffset((void *)this, 0xF68); }
        u32 *getSpawnTimer() const { return GetMemberFromOffset((void *)this, 0xF70); } // Decreases only while not Grounded

        /*
        0=Normal
        1=Unk
        2=Longer Cooldown & More Drops at Once

        3=Behaviour changes to this order:
        countdown, spawn, cooldown, countdown ---|
        ^----------------------------------------|

        4=Unk
        5=Spawn upon Jump, either 1 or 2 spawns
        */
        u32 *getSpawnTimerMod() const { return GetMemberFromOffset((void *)this, 0xF78); }
    };

    class dPipeSpawner_c : public dActor_c
    {
    public:
        static const Actors actorID = DOKAN_WAKIDASHI;

        u32 *getSpawnTimer() const { return GetMemberFromOffset((void *)this, 0x390); }
        u32 *getTotalCycles() const { return GetMemberFromOffset((void *)this, 0x3A8); }

        u16 *getCurrentSpawnsCompleted() const { return(u16 *) GetMemberFromOffset((void *)this, 0x394); }
    };

    class dRollingSpawner_c : public dActor_c
    {
    public:
        static const Actors actorID = WAKI_TOGETEKKYU;
        // Base: 0x81541100
        // void* LatestSpawnPtr at 8154160c
        // u32 MaxSpawnedAtOnce at 81541498
        // u32 spawnTimer at 81541494,
        u16 *getRollingSpeed() const { return(u16 *) GetMemberFromOffset((void *)this, 0x004); } // i know its the dEn_c::settings var, but thats just how speed works on this object

        u32 *getMaxAliveChildren() const { return GetMemberFromOffset((void *)this, 0x398); } // Unlimited, unlike the dEn_c::settings ones
        u32 *getSpawnTimer() const { return GetMemberFromOffset((void *)this, 0x394); }       // Default=0x000000b4
        u32 *getSpawningType() const { return GetMemberFromOffset((void *)this, 0x39C); }     // Ball=0 or Barrel=1

        dEn_c *getLastSpawnedObject() const { return(dEn_c *) GetMemberFromOffset((void *)this, 0x50C); }
    };


    class daLakitu : public dEn_c {
        //The cloud appears to be constructed using ID 56 and the settings 102, unless 0x00X00000 is set to 1, in which case its 100
        public:
        u16* getIsPissingOff() const { return (u16*)GetMemberFromOffset((void*)this, 0x438); }

        void setPissOff() {
            u32 value = this->mParam;
            value &= ~0xF0;                 // clear X
            value |= (1 & 0xF) << 4;        // set X
            this->mParam = value;
            *getIsPissingOff() = (u16)1;
            return;
        }
    };

    class daIceAshibaSpawner_c : public dActor_c {
        public:
        static const Actors actorID = WAKI_ICE_ASHIBA;
        /*
        Base: 81541CE0
        u8 SpawnTimer: 81542078
        u16 prng: 81542076

        PRNG Size Picker statuses:
        < 7 = Small 4x4
        7 = 4x6
        22 = 6x8
        23 = 10x10?
        27 = 12x10???
        28 = 2x4.5??
        29 = 3x3?
        30 = 6x3
        */
    };

    class daIcicle_c : public dEn_c {
        public:
        static const Actors actorID = EN_ICICLE;
        static const float* getMaxSize() {return (const float*)&DAT_ICICLESIZE; } //Default: 0x3f800000
        static const float* getGrowStep() {return (const float*)&DAT_ICICLEGROW; } //Default: 0x3b888889

        const bool getIsParent() const {return *(unsigned char*)GetMemberFromOffset((void*)this, 0x4) == 0; }
        dActor_c* getChild() const {return (dActor_c*)(((unsigned char*)*GetMemberFromOffset((void*)this, 0x14)) - 0x10); }
        
        float* getSpeedY()       const {return (float*)GetMemberFromOffset((void*)this,  0xEC); }
        float* getSpeedAccellY() const {return (float*)GetMemberFromOffset((void*)this, 0x114); }
        bool getIcicleType()     const {return   (bool)GetMemberFromOffset((void*)this, 0x610); }

        void LogExistence() {
            dActor_c* child;
            if(getIsParent()) child = this->getChild();
            else {OSReport("IcicleChild: %p\n", this); return; }
            if(child == 0x0 || child == (dActor_c*)0xFFFFFFF0) return;
            OSReport("Icicle: P:%p, C:%p\n", this, child);
        }

        static void SetGlobalScale(float multiplier) {
            static const float GrowStep = *getGrowStep();
            static const float MaxSize = *getMaxSize();

            float newGrowStep = GrowStep * multiplier;
            float newMaxSize = MaxSize * multiplier;
            
            LivePatch(*(u32*)&newMaxSize, (void*)getMaxSize());
            LivePatch(*(u32*)&newGrowStep, (void*)getGrowStep());
            return;
        }

        void SetFoot(u16 newSize) {
            u32* doublePtr;
            bool isChild = !getIsParent();
            if(isChild) doublePtr = GetMemberFromOffset((void*)this, 0x1F4);
            else doublePtr = GetMemberFromOffset((void*)this->getChild(), 0x1F4);
            if(!doublePtr || doublePtr < (u32*)0x80000000) return;
            if((mParam & 0xFF) == 0) newSize += (u16)(*getMaxSize());
            u32 result = ((u32)newSize << 16) | 0x0000;

            u32* Field = (u32*)(((unsigned char*)*doublePtr) + 0x8);
            *Field = result;
            
            return;
        }
    };

    class dCheepSpawner_c : public dActor_c {
        static const Actors actorID = AC_WAKI_TOBIPUKU;
        static void ChangeSpawnID(u16 newSpawnID) {
            u32 instr = CreateLoadImmediate(3, newSpawnID);
            LivePatch(instr, LP_CHEEPSPAWNID);
        }
    };
}

class dRollingHill_c : public dActor_c
{
protected:
    void *build();
    void buildModel();
    void deconstructMembers();
    int draw();
    int execute();
    int onDelete();
    void initializeState_Dispatch();
    void executeState_Dispatch(); // This Class does not have any states... what a blunder nintendo, just look at the compile-size rise unecessarily and cry!
    void finalizeState_Dispatch();
    void rotateTouchingObjects();

public:
    u8 *getWierdThing() const { return(u8 *) GetMemberFromOffset((void *)this, 0x4C4); }

    u16 *getRoll() const { return(u16 *) GetMemberFromOffset((void *)this, 0x104); }
    u16 *getRollSpeed() const { return(u16 *) GetMemberFromOffset((void *)this, 0x4D0); }
    u16 *getCollToggle() const { return(u16 *) GetMemberFromOffset((void *)this, 0x450); }

    u32 *getCollStuff() const { return GetMemberFromOffset((void *)this, 0x420); }

    float *getPhysRadius() const { return(float *) GetMemberFromOffset((void *)this, 0x4D4); }
    float *getVisScale() const   { return(float *) GetMemberFromOffset((void *)this, 0x4D8); }
    float *getDriftCap() const   { return(float *) GetMemberFromOffset((void *)this, 0x4DC); } // Often Empty. Maybe overwrite in preGameLoop()

    // This is a static const somewhere around rtoc + 0x77??, No idea what it does :shrug:
    const float *getSomething() { return(float *) 0x8042BC48; }
};

//This Class has been patched, to allow Upwards movement. 0x000000X0 sets fall type, 2 + 3 we're added
class dFallPlatform_c : public dActorState_c {
    public:
    static const Actors actorID = AC_LIFT_FALL;
    float* getFallSpeed() const { return (float*)GetMemberFromOffset((void*)this, 0x114); }
};

//This was a complete waste of my time :(
class dBouncyCloud : public dActor_c {
    public:
    static const Actors actorID = EN_LIFT_REMOCON_TRPLN; //Strange way to say bouncy cloud, Nintendo (its likely because Newer shifts actors (This is grabbed from the Newer Patch for Reggie!-Next))  
};

class dRollingLinePlatform_c : public dActor_c {
    public:
    static const Actors actorID = LINE_KINOKO_BLOCK;
    float* getMoveSpeed() const {return (float*)GetMemberFromOffset((void*)this, 0x5CC); }
    u16* getRotateSpeed() const {return   (u16*)GetMemberFromOffset((void*)this, 0x5D0); }
};

//This is the part where i stop knowing what is and is not reguarded as "da"
class daIceAshibaBase_c : public dActor_c {
    public:
    static const Actors actorID_Normal = ICE_ASHIBA;
    static const Actors actorID_Water = ICE_ASHIBA_WATER;
    static const Actors actorID_Rail = ICE_ASHIBA_RAIL;
    protected:
    ~daIceAshibaBase_c();

    void callBackF(dActor_c*, dActor_c*);
    void callBackH(dActor_c*, dActor_c*);
    void callBackW(dActor_c*, dActor_c*);

    bool checkRevFoot(dActor_c*, dActor_c*); //Interpreted as bool due to "check", maybe be incorrect. Im just porting these blindly as they were already found within my symbols.
    bool checkRevHead(dActor_c*, dActor_c*);
    bool checkRevWall(dActor_c*, dActor_c*, unsigned char);

    void* CreateModel(const char*);
    int doDelete();
    int draw();
    int execute();
    int init();
    void move();
    void quit();

    //static member const "figure data" here(n't?).

    public:
    int create();

    UnChar *getAnimationDecelerator()   const {return (UnChar*)GetMemberFromOffset((void*)this, 0x4E0); }
    const UnChar *getWobbleState()      const {return (UnChar*)GetMemberFromOffset((void*)this, 0x534); }
    UnChar *getWobbleToggle()           const {return (UnChar*)GetMemberFromOffset((void*)this, 0x536); }
    
    u16* getPathDirection()             const {return (u16*)GetMemberFromOffset((void*)this, 0x508); }
    u16* getPathTarget()                const {return (u16*)GetMemberFromOffset((void*)this, 0x50A); }

    u32* getMoveStopTimer()             const {return GetMemberFromOffset((void*)this, 0x504); }
    u32* getSomeTimer()                 const {return GetMemberFromOffset((void*)this, 0x510); }
    u32* getVisOscillatedRot()          const {return GetMemberFromOffset((void*)this, 0x530); }

    mVec2_c* getPathingGoalPosition()   const {return (mVec2_c*)GetMemberFromOffset((void*)this, 0x4EC); }
    mVec2_c* getPathingNextPosition()   const {return (mVec2_c*)GetMemberFromOffset((void*)this, 0x518); }
    mVec2_c* getRailOffset()            const {return (mVec2_c*)GetMemberFromOffset((void*)this, 0x524); }

    float* getPathingModifierX()        const {return (float*)GetMemberFromOffset((void*)this, 0x4F0);   }
    float* getPathingModifierY()        const {return (float*)GetMemberFromOffset((void*)this, 0x51C);   }
};

//This actor does have a few members, but nothing interesting enough that i can modify to mess with things
class daSnakeBlock_c : public dEn_c {
    public:
    static const Actors actorID = EN_SNAKEBLOCK;
    void GenerateHoleNow() {
        float* b = (float*)GetMemberFromOffset(this, 0x95C); //get most forward block's position
        if(b == (float*)0x0000095C || b == NULL) return;
        *b = 0;
        return;
    }
};

//Come back later
class daHuckit_c : public dActor_c {
    static const Actors actorID = EN_KANIBO;
};

class dCheep_c : public dActor_c {
    static const Actors actorID = EN_TOBIPUKU;
    u32* getUnkTimer()               const {return          GetMemberFromOffset((void*)this, 0xE60);}
    u32* getShouldAnimate()          const {return          GetMemberFromOffset((void*)this, 0xEA0);}

    u8* getSpinAnimationState()      const {return      (u8*)GetMemberFromOffset((void*)this, 0xE76);}
    u8* getSpinAnimationMultiplier() const {return      (u8*)GetMemberFromOffset((void*)this, 0xE7A);}

    mVec4_c* getPathLimits()         const {return (mVec4_c*)GetMemberFromOffset((void*)this, 0x618);}
};

//Next up
class dPorcuPuffer_c : public dEn_c {
    static const Actors actorID = EN_IGAPUKU;
    mVec2_c* getVelocityOverride()  const {return (mVec2_c*)GetMemberFromOffset((void*)this, 0x114); } //Applies after jumping, if done wrong will cause it to fly offscreen
    mVec2_c* getHitboxScale()       const {return (mVec2_c*)GetMemberFromOffset((void*)this, 0x16C); } //Not per-frame set! Lets gooo
    mVec4_c* getSplashEffecPos()    const {return (mVec4_c*)GetMemberFromOffset((void*)this, 0x5C8); } //What the hell does W do? :sob:

    float* getTurnEaseSpeed()       const {return (float*)GetMemberFromOffset((void*)this, 0x11C); }
    float* getRightMoveEdge()       const {return (float*)GetMemberFromOffset((void*)this, 0x5DC); } //Mostly Right Screen edge, or stage edge. Possibly set per frame.
    float* getBuoyancyPostJump()    const {return (float*)GetMemberFromOffset((void*)this, 0x5D8); } //Why is this spelt like that :sob:

    u8* getDirectionRaw()           const {return (u8*)GetMemberFromOffset((void*)this, 0x348); }

    u32* getJumpState()             const {return GetMemberFromOffset((void*)this, 0x360); }

    u16* getWaterSlideEffLink()     const {return (u16*)GetMemberFromOffset((void*)this, 0x664); } //This detaches the effect, which also means it will live forever at a modifiable position.
    u16* getWaterSlideHandle()      const {return (u16*)GetMemberFromOffset((void*)this, 0x666); } //The Devil, dun dun duuuhhhhhhhhhhhhhh + ^^^^^^ applies.
    u16* getWaterSplashEffLink()    const {return (u16*)GetMemberFromOffset((void*)this, 0x78C); } //May be effectID, not sure yet.
    u16* getWaterSplashHandle()     const {return (u16*)GetMemberFromOffset((void*)this, 0x78E); } //^^^^^^ applies.
};

#undef UnChar
#endif