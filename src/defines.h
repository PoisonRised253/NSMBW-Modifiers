#ifndef __H_DEFS
#define __H_DEFS

//Macros Because Yes! DEAL WITH IT!!!!
#define ext extern "C"
#define ret return

//Build Flags
#define DEBUG
#define DEBUG_EXPERIMENTS
//#define DEBUG_COLLEXT
#define DEBUG_PHYSEXT
#define PROPER

//#define NO_MP

//This section, if uncommented, will enable all debugs. Warning, the logs will flood constantly.
/*#ifdef DEBUG
#define DEBUG_LP
#define DEBUG_CS
#define DEBUG_UNUSED
#define DEBUG_BOUNDS
#define DEBUG_SLOPE
#define DEBUG_BALLS
#define DEBUG_EXPERIMENTS

#endif*/
//Patch defines:
#define USE_MKWCAT_PATCHES

//Current amount of activatable modifiers
#define MOD_SIZE 21

//Infinite-Lives "True" Amount
#define LIVES_AMOUNT 0x64

//Tower-Modifier
#define SPEEDCAP_TOWER 3.025f
#define SPEEDCAP_TOWER_MINI 2.25f

//Water-Modifiers
#define SPEED_WATER_MOD 128.f
#define WATER_DRAIN 4.f
#define SWIM_MOD 128.f

//Scaling (Legacy)
#define SCALE_MOD 0.00125f
#define SCALE_MOD_OTHER 143.36

//WM-Mode
#define MAP_SPEED 12

//SpinEternally
#define TIMER_SPIN 15

//Lonely
#define TIMER_CLEAR 6
#define FIND_ENTS 7

//SANY - Small and No Yoshi
#define MOVE_MOD 1.05f

//TrustYourSenses
#define TYS_TURNSPEED (s16)8

#define MARIOSLIDE_SPEED 1.5f
#define MARIOSLIDE_LIMIT 100

//MAXIMUMs and MINIMUMs
#define FLOAT_MAX 65504.f
#define FLOAT_MIN -65504.f
#define FLOAT_MAX_ENCODED 0x47FF0000


//This is just free data storage, since its entirely compiletime, but ofcourse entirely constant.
//This is to set the current Powerup State.
//It might also help by using 'li rX, data' instead of loading from a static location, which would require multiple operations in some cases
#ifndef PROPER
#define POWER_SMALL     0x00
#define POWER_BIG       0x01
#define POWER_FIRE      0x02
#define POWER_MINI      0x03
#define POWER_PROPELLER 0x04
#define POWER_PENGUIN   0x05
#define POWER_ICE       0x06

//Item Spawning Made Easy
#define ITEM_MUSHROOM   0x00
#define ITEM_FIRE       0x09
#define ITEM_ICE        0x0E
#define ITEM_PENGUIN    0x11
#define ITEM_PROPELLER  0x15
#define ITEM_MINI       0x19
#define ITEM_STAR       0x01
#define ITEM_1UP        0x07
#define ITEM_UNKNOWN    0xF9

//dScStage_c::m_exitMode
#define EXIT_SUCCESS 0
#define EXIT_FAIL 1
#define EXIT_PLAYER_CHOICE 2
#define EXIT_DEFAULT 3

//dScStage_c::m_gameMode
#define GAME_NORMAL 0
#define GAME_LUIGI_GUIDE 1
#define GAME_TITLE 2
#define GAME_RETURN_ON_INPUT 3
#define GAME_MOVIE 4 //1-41's Hint Movies

//dScStage_c::m_miniGame
#define MINIGAME_NONE 0
#define MINIGAME_STAR_HOUSE 1
#define MINIGAME_TOAD_HOUSE 2
//TODO: Add the others
#endif

#ifdef PROPER
enum Powers {
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
enum ItemVariants {
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

enum ExitMode {
    EXIT_SUCCESS = 0,
    EXIT_FAIL = 1,
    EXIT_PLAYER_CHOICE = 2,
    EXIT_DEFAULT = 3
};

enum GameMode {
    GAME_NORMAL = 0,
    GAME_LUIGI_GUIDE = 1,
    GAME_TITLE = 2,
    GAME_RETURN_ON_INPUT = 3,
    GAME_MOVIE = 4 //1-41's Hint Movies
};

enum Minigame {
    MINIGAME_NONE = 0,
    MINIGAME_STAR_HOUSE = 1,
    MINIGAME_TOAD_HOUSE = 2
};

//If i ever need to overwrite a class, here's the ones that do nothing
//dDummyDoorParent_c and dDummyDoorChild_c are not included, as they execute... just ... unknown things.. They dont even need eachother btw
enum Dummy {
    SLOW_QUICK_TAG_C = 20,
    KAWANAGARE_C = 41,
    HANA_MOUNTAIN_C = 50,
    TAG_THUNDER_C = 122,
    BRANCH_C = 210,
    
    AC_LIFT_ICE_SPRING_C = 536,
    EN_BLUR_C = 603
};

enum Broken {
    AC_LIFT_OBJBG_HMOVE_BIG_C = 435
};
#endif

//Live Patch Helper Stuff

#define INSTR_BLR                0x4e800020
#define INSTR_NOP                0x60000000
#define INSTR_BRICKTIMER         0x3C0001F4
#define INSTR_EXITUNLCEARED      0x48000018

//TODO: These are for EU_1 / EU_2, and will very likely break immensely in other regions.
//Please Group these by Region, then figure out how you can enable them per makeGame's chosen region target.
//Live Patch Addresses
#define LP_1UPEFFECT        (u32*)0x801591F0
#define LP_BRICKTIMER       (u32*)0x800E3AB8
#define LP_NODEATHPAUSE     (u32*)0x8004E050
#define LP_ALLOWDEBUG       (u32*)0x800F1960
#define LP_NEXTCANNON       (u32*)0x802F4CF0
#define LP_NOSCORE          (u32*)0x8010CDE0
#define LP_RIGHTSPEED       (u32*)0x8042BB20
#define LP_LEFTSPEED        (u32*)0x8042BB24
#define LP_INITIALJUMPSPEED (u32*)0x8042BB28
#define LP_FREEROY          (u32*)0x8042DE28
#define LP_ALLOWPRESSTWO    (u32*)0x8005e574
#define LP_ALLOWHOLDTWO     (u32*)0x8005e584
#define LP_AUTOICE          (u32*)0x80a215dc
#define LP_GROWICE          (u32*)0x80ad0f44
#define LP_AUTOHOLDDOWN     (u32*)0x8005e500
#define LP_FUKIDELETER      (u32*)0x800b1910

#define LP_EXITUNCLEARED_1  (u32*)0x800d0d40
#define LP_EXITUNCLEARED_2  (u32*)0x800d0e88

#define LP_PSSLOTLIMIT_1    (u32*)0x80abb6a0 //cmpwi instr
#define LP_PSSLOTLIMIT_2    (u32*)0x80abb740 //cmpwi instr

#define LP_PIPESPAWNID_1    (u32*)0x80abb6ec //li instr
#define LP_PIPESPAWNID_2    (u32*)0x80abb78c //li instr

#define LP_DEATHMUSHSETUP_1 (u32*)0x80145c04 //mflr r29
#define LP_DEATHMUSHSETUP_2 (u32*)0x80145c80 //mtlr r29


//Player related Stuff
#define DEFAULT_SPEED_RIGHT       0x3f800000
#define DEFAULT_SPEED_LEFT        0xbf800000
#define DEFAULT_SPEED_JUMP        0x40683127
#define STATEID_BALLOON           0x80376870

#endif

//This line of code, makes a beautifiul effect appear, use with CallSpacer(30)
//SpawnEffect("Wm_bs_kameckmagic", 0, &this->pos, &r, &MakeVec(this->aoeX / 32, this->aoeY / 64, 1));