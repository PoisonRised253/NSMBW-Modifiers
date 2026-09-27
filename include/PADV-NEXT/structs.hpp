#ifndef PADV_STRUCTS
#define PADV_STRUCTS
#include "PADV-NEXT/defines.h"
#include "PADV-NEXT/Utils.h"

enum ExecPhase  { NONE = 0, PRE = 1, POST = 2, ALL = 3 };

// Level and World are 1-Indexed. Do not enter 0 unless it shouldnt ever work.
struct Modifier {
    typedef void (*ModFunc)(void*);
    typedef void (*ModFuncNoArg)();
    public:
    const u8 Level;
    const u8 World;
    const u8 Area; // 0 for All
    const ExecPhase Phase;
    const ModFunc Mod;
    const ModFuncNoArg ModNoArg;
    int Timer; //0 for None
    void* arg;
    bool useArg;

    void TryRun(ExecPhase phase) const {
        dScStage_c* stage = dScStage_c::getInstance();
        if(!stage || (!Mod && !ModNoArg)) return;
        if(Phase == NONE || phase != Phase && Phase != ALL) return;
        if(Level == 0 || World == 0) goto special;
        else if(Level != stage->mCurrCourse + 1 || World != stage->mCurrWorld + 1) return;
        if(Area != 0 && Area != stage->mCurrAreaNo + 1) return;
        special:
        if(Timer == 0) {
            if(!useArg) { this->ModNoArg(); }
            else { this->Mod(arg); }
        } else if(CallSpacer(Timer)){
            if(!useArg) { this->ModNoArg(); }
            else { this->Mod(arg); }
        }
    }

    Modifier(u8 level, u8 world, u8 area, ExecPhase phase, void (func)(void *), int timer, void *argument, bool UseArg) : Level(level), World(world), Area(area), Phase(phase), Mod((ModFunc)func), ModNoArg((ModFuncNoArg)func)
    {
        Timer = timer;
        arg = argument;
        useArg = UseArg;
    }
};

typedef struct mVec4_c
{
    float x;
    float y;
    float z;
    float w;

    bool operator==(const mVec4_c &other) const
    {
        return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
    }

    mVec4_c operator+=(const mVec4_c &other)
    {
        return mVec4_c(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
    }

    mVec4_c operator-=(const mVec4_c &other)
    {
        return mVec4_c(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
    }

    mVec4_c operator*=(const mVec4_c &other)
    {
        return mVec4_c(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
    }

    mVec4_c operator*=(const float other)
    {
        return mVec4_c(this->x * other, this->y * other, this->z * other, this->w * other);
    }

    mVec4_c operator/=(const mVec4_c &other)
    {
        return mVec4_c(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
    }

    mVec4_c operator/=(const float other)
    {
        return mVec4_c(this->x / other, this->y / other, this->z / other, this->w / other);
    }

    mVec4_c() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    mVec4_c(float X, float Y, float Z, float W) {
        x = X;
        y = Y;
        z = Z;
        w = W;
    }

    mVec4_c(mVec2_c a, mVec2_c b)
    {
        x = a.x;
        y = a.y;
        z = b.x;
        w = b.y;
    }

    ~mVec4_c()
    {
        this->x = NULL;
        this->y = NULL;
        this->z = NULL;
        this->w = NULL;
    }

} Rect2D;

typedef struct mVecU16_c
{
    u16 x;
    u16 y;

    bool operator==(const mVecU16_c &other) const
    {
        return (this->x == other.x && this->y == other.y);
    }

    mVecU16_c operator+=(const mVecU16_c &other)
    {
        return mVecU16_c(this->x + other.x, this->y + other.y);
    }

    mVecU16_c operator-=(const mVecU16_c &other)
    {
        return mVecU16_c(this->x - other.x, this->y - other.y);
    }

    mVecU16_c operator*=(const mVecU16_c &other)
    {
        return mVecU16_c(this->x * other.x, this->y * other.y);
    }

    mVecU16_c operator*=(const u16 other)
    {
        return mVecU16_c(this->x * other, this->y * other);
    }

    mVecU16_c operator/=(const mVecU16_c &other)
    {
        return mVecU16_c(this->x / other.x, this->y / other.y);
    }

    mVecU16_c operator/=(const u16 other)
    {
        return mVecU16_c(this->x / other, this->y / other);
    }

    mVecU16_c() {
        x = 0;
        y = 0;
    }

    mVecU16_c(u16 X, u16 Y) {
        x = X;
        y = Y;
    }

    ~mVecU16_c()
    {
        this->x = NULL;
        this->y = NULL;
    }

};

enum Powers  
{
    POWER_SMALL = 0,
    POWER_BIG = 1,
    POWER_FIRE = 2,
    POWER_MINI = 3,
    POWER_PROPELLER = 4,
    POWER_PENGUIN = 5,
    POWER_ICE = 6
};

// DEATHMUSH is not actually in this game, but im going to change that.
// If you spawn DEATHMUSH in the vanilla game, you get a normal-mush-scaled Minimush, which acts like a minimush.
// Time for me to find what function occours when you get a powerup.
enum ItemVariants  
{
    ITEM_MUSHROOM = 0x00,
    ITEM_STAR = 0x01,
    ITEM_ONEUP = 0x07,
    ITEM_FIRE = 0x09,
    ITEM_ICE = 0x0E,
    ITEM_PENGUIN = 0x11,
    ITEM_PROPELLER = 0x15,
    ITEM_MINI = 0x19,
    ITEM_DEATHMUSH = 0xF9
};

enum ExitMode  
{
    EXIT_SUCCESS = 0,
    EXIT_FAIL = 1,
    EXIT_PLAYER_CHOICE = 2,
    EXIT_DEFAULT = 3
};

enum GameMode  
{
    GAME_NORMAL = 0,
    GAME_LUIGI_GUIDE = 1,
    GAME_TITLE = 2,
    GAME_RETURN_ON_INPUT = 3,
    GAME_MOVIE = 4 // 1-41's Hint Movies
};

enum Minigame  
{
    MINIGAME_NONE = 0,
    MINIGAME_STAR_HOUSE = 1,
    MINIGAME_TOAD_HOUSE = 2
};

// If i ever need to overwrite a class, here's the ones that do nothing
// dDummyDoorParent_c and dDummyDoorChild_c are not included, as they execute... just ... unknown things.. They dont even need eachother btw
enum Dummy  
{
    SLOW_QUICK_TAG_C = (int)SLOW_QUICK_TAG,
    KAWANAGARE_C = (int)KAWANAGARE,
    HANA_MOUNTAIN_C = (int)HANA_MOUNTAIN,
    TAG_THUNDER_C = (int)TAG_THUNDER,
    BRANCH_C = (int)BRANCH,
    AC_LIFT_ICE_SPRING_C = (int)AC_LIFT_ICE_SPRING,
    EN_BLUR_C = (int)EN_BLUR
};

enum Broken 
{
    AC_LIFT_OBJBG_HMOVE_BIG_C = (int)AC_LIFT_OBJBG_HMOVE_BIG
};

#endif
