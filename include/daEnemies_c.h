#ifndef __H_ENEMIES
#define __H_ENEMIES
#include "Utils.h"

// Collection of Enemies ive looked at, and explored
// I dont know how to make headers actually align to ingame Memory, so im using methods instead, please forgive my sins (sizeof() appears to be wrong lol)
// dEn_c is 1714 bits (padded)
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

    u32 *getSearchEffectActive() const { ret GetMemberFromOffset((void *)this, 0x8C8); } // Dont just randomly set this, it will crash
    u32 *getAnimateShakeCooldown() const { ret GetMemberFromOffset((void *)this, 0x9AC); }
    u32 *getKnockedEffectInactive() const { ret GetMemberFromOffset((void *)this, 0x9B0); }
    u32 *getInvisible() const { ret GetMemberFromOffset((void *)this, 0x9C8); }
    u32 *getSpeed() const { ret GetMemberFromOffset((void *)this, 0x9D4); }

    float *getWaitStateChange() const { ret(float *) GetMemberFromOffset((void *)this, 0x668); } // 40c00000 when Looked at, 42c00000 when looked away
    float *getWaitBeforeSearch() const { ret(float *) GetMemberFromOffset((void *)this, 0x6A0); }
    static float *getGlobalScaler() { ret(float *) 0x80AD4A94; } // This does also scale collision, strange isnt it, especially since it isnt instance-bound

    void *getEffectChaseInstance() const { ret GetMemberFromOffset((void *)this, 0x824); }
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
    u32 *getAnimAllowShoot() const { ret GetMemberFromOffset((void *)this, 0x500); }
    u32 *getFrame() const { ret GetMemberFromOffset((void *)this, 0xA3C); }
    u32 *getCooldown() const { ret GetMemberFromOffset((void *)this, 0xE1C); }
    u32 *getState() const { ret GetMemberFromOffset((void *)this, 0xE34); }
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

    u32 *getBounceState() const { ret(u32 *) GetMemberFromOffset((void *)this, 0x360); } // 0x0=InAir, 0x00000001=OnGround, 0x00000002=Freeze

    bool *getPhysActive() const { ret(bool *) GetMemberFromOffset((void *)this, 0x6A8); } // Default=0x00000001, 0x0 to disable interaction

    float *getPhysScale() const { ret(float *) GetMemberFromOffset((void *)this, 0x6C8); }    // Default=3f80000000
    float *getDeformation() const { ret(float *) GetMemberFromOffset((void *)this, 0x6E4); }  // Default=4198000000
    float *getMaxFallSpeed() const { ret(float *) GetMemberFromOffset((void *)this, 0x0F8); } // Default=0xc0c00000
    float *getGravity() const { ret(float *) GetMemberFromOffset((void *)this, 0x114); }      // Default=0xbe19999a
    float *getHitboxX() const { ret(float *) GetMemberFromOffset((void *)this, 0x5D8); }      // Default=0x0000e000
    float *getHitboxY() const { ret(float *) GetMemberFromOffset((void *)this, 0x5D0); }      // Default=0xffff2000
    float *getPhysRadius() const { ret(float *) GetMemberFromOffset((void *)this, 0x670); }   // Default=0x41666667

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
            ret;

        const int f = 0x41666667;
        *this->getPhysScale() = size;
        *this->getPhysRadius() = *(float *)&f * size;
        OSReport("Scale is now %f\n", size);
        ret;
    }

    void setStatic(bool _static)
    {
        if (_static)
            *this->getBounceState() = 2;
        else
            *this->getBounceState() = 0;
        ret;
    }
};

class daChainChomp_c : public dEn_c
{
public:
    static const Actors actorIDPole = EN_WANWAN_PILE;
    static const Actors actorIDChomp = EN_WANWAN;

    u32 *getChainLength() const { ret GetMemberFromOffset((void *)this, -0x64); } //(0x0-0xF else exception)
    u32 *getTurnDirection() const { ret GetMemberFromOffset((void *)this, -0x70); }
    u32 *getCooldownAfterLunge() const { ret GetMemberFromOffset((void *)this, -0x84); }    //(second byte only)
    u32 *getWaitForAttackCooldown() const { ret GetMemberFromOffset((void *)this, -0xDC); } //(last byte only)
    u32 *getAttackState() const { ret GetMemberFromOffset((void *)this, -0x388); }          //(last byte only)
    u32 *getHitsBeforeBreak() const { ret GetMemberFromOffset((void *)this, 0x568); }       // Default=3

    u8 *getUnknown() const { ret(u8 *) GetMemberFromOffset((void *)this, -0x178); }

    u16 *getWhileAttackCooldown() const { ret(u16 *) GetMemberFromOffset((void *)this, -0x1E8); }

    bool IsAttack() const { ret !(bool)*GetMemberFromOffset((void *)this, -0xD8); }
    bool *getIgnoreAnchorX() const { ret(bool *) GetMemberFromOffset((void *)this, -0x3A0); }

    float *getGravity() const { ret(float *) GetMemberFromOffset((void *)this, -0x5D4); } // Default=be400000
    float *getPoleX() const { ret(float *) GetMemberFromOffset((void *)this, 0xAC); }
    float *getPoleY() const { ret(float *) GetMemberFromOffset((void *)this, 0xB0); }
    float *getChompPivotX() const { ret(float *) GetMemberFromOffset((void *)this, -0xCC); }
    float *getChompPivotY() const { ret(float *) GetMemberFromOffset((void *)this, -0xC8); }
    float *getTargetAngle() const { ret(float *) GetMemberFromOffset((void *)this, -0xD4); }

    Vec2 *getPolePos() const { ret(Vec2 *) GetMemberFromOffset((void *)this, 0xAC); }

    Vec3 *getPoleVisSize() const { ret(Vec3 *) GetMemberFromOffset((void *)this, 0xDC); }
    void *getSmtAbtGroundpound() const { ret(void *) GetMemberFromOffset((void *)this, 0x648); }

    // Custom From Here
    Vec4 getPoleHitboxExtents()
    {
        ret MakeVec4(
            *(float *)GetMemberFromOffset((void *)this, 0x5EC),
            *(float *)GetMemberFromOffset((void *)this, 0x5F4),
            *(float *)GetMemberFromOffset((void *)this, 0x5F8),
            *(float *)GetMemberFromOffset((void *)this, 0x5F0));
    }

    void setPoleHitboxExtents(Vec4 extents)
    {
        *(float *)GetMemberFromOffset((void *)this, 0x5EC) = extents.x; // ExtentsX-
        *(float *)GetMemberFromOffset((void *)this, 0x5F4) = extents.y; // ExtentsX+
        *(float *)GetMemberFromOffset((void *)this, 0x5F8) = extents.z; // ExtentsY-
        *(float *)GetMemberFromOffset((void *)this, 0x5F0) = extents.w; // ExtentsY+
        ret;
    }

    bool IsDead() const { ret(bool) * GetMemberFromOffset((void *)this, -0x2BC) && !(bool)*GetMemberFromOffset((void *)this, -0x2B8); }
    bool IsReleased() const { ret(bool) * GetMemberFromOffset((void *)this, -0x2BC) && (bool)*GetMemberFromOffset((void *)this, -0x2B8); }

    bool isChompValid()
    {
        ret(!IsDead() && !IsReleased());
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
    u8 *getFaceID() const { ret(u8 *) GetMemberFromOffset((void *)this, 0x5B8); }
    void *getRiseWaitTime() const { ret GetMemberFromOffset((void *)this, 0x5DC); }
    float *getDropYSpeed() const { ret(float *) GetMemberFromOffset((void *)this, 0x114); }
    u32 *getextraEffectToggle() const { ret GetMemberFromOffset((void *)this, 0x5D0); }
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

    u8 *getRotDirection() const { ret(u8 *) GetMemberFromOffset((void *)this, 0x348); }

    u32 *getTurnTimer() const { ret GetMemberFromOffset((void *)this, 0x4A4); }
    u32 *BlackMagicLiesHere() const { ret GetMemberFromOffset((void *)this, 0xC); }

    float *getCurrentAngle() const { ret(float *) GetMemberFromOffset((void *)this, 0x4A0); }
};

namespace Spawners
{

    class dParaBombSpawner_c : public Actor
    {
    public:
        static const Actors actorID = WAKI_PARABOM;

        u32 *getAllowDrop() const { ret GetMemberFromOffset((void *)this, 0xF68); }
        u32 *getSpawnTimer() const { ret GetMemberFromOffset((void *)this, 0xF70); } // Decreases only while not Grounded

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
        u32 *getSpawnTimerMod() const { ret GetMemberFromOffset((void *)this, 0xF78); }
    };

    class dPipeSpawner_c : public Actor
    {
    public:
        static const Actors actorID = DOKAN_WAKIDASHI;

        u32 *getSpawnTimer() const { ret GetMemberFromOffset((void *)this, 0x390); }
        u32 *getTotalCycles() const { ret GetMemberFromOffset((void *)this, 0x3A8); }

        u16 *getCurrentSpawnsCompleted() const { ret(u16 *) GetMemberFromOffset((void *)this, 0x394); }
    };

    class dRollingSpawner_c : public Actor
    {
    public:
        static const Actors actorID = WAKI_TOGETEKKYU;
        // Base: 0x81541100
        // void* LatestSpawnPtr at 8154160c
        // u32 MaxSpawnedAtOnce at 81541498
        // u32 spawnTimer at 81541494,
        u16 *getRollingSpeed() const { ret(u16 *) GetMemberFromOffset((void *)this, 0x004); } // i know its the dEn_c::settings var, but thats just how speed works on this object

        u32 *getMaxAliveChildren() const { ret GetMemberFromOffset((void *)this, 0x398); } // Unlimited, unlike the dEn_c::settings ones
        u32 *getSpawnTimer() const { ret GetMemberFromOffset((void *)this, 0x394); }       // Default=0x000000b4
        u32 *getSpawningType() const { ret GetMemberFromOffset((void *)this, 0x39C); }     // Ball=0 or Barrel=1

        dEn_c *getLastSpawnedObject() const { ret(dEn_c *) GetMemberFromOffset((void *)this, 0x50C); }
    };

}

class dRollingHill_c : public Actor
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
    u8 *getWierdThing() const { ret(u8 *) GetMemberFromOffset((void *)this, 0x4C4); }

    u16 *getRoll() const { ret(u16 *) GetMemberFromOffset((void *)this, 0x104); }
    u16 *getRollSpeed() const { ret(u16 *) GetMemberFromOffset((void *)this, 0x4D0); }
    u16 *getCollToggle() const { ret(u16 *) GetMemberFromOffset((void *)this, 0x450); }

    u32 *getCollStuff() const { ret GetMemberFromOffset((void *)this, 0x420); }

    float *getPhysRadius() const { ret(float *) GetMemberFromOffset((void *)this, 0x4D4); }
    float *getVisScale() const { ret(float *) GetMemberFromOffset((void *)this, 0x4D8); }
    float *getDriftCap() const { ret(float *) GetMemberFromOffset((void *)this, 0x4DC); } // Often Empty. Maybe overwrite in preGameLoop()

    // This is a static const somewhere around rtoc + 0x77??, No idea what it does :shrug:
    const float *getSomething() { ret(float *) 0x8042BC48; }
};

#endif