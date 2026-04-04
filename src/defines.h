#ifndef __H_DEFS
#define __H_DEFS

//Macros Because Yes! DEAL WITH IT!!!!
#define ext extern "C"
#define ret return

//Build Flags
#define DEBUG
#define NO_MP

/*#ifdef DEBUG
#define DEBUG_LP
#define DEBUG_CS
#define DEBUG_UNUSED
#endif*/

//Current amount of activatable modifiers
#define MOD_SIZE 16

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
#define FIND_ENTS 10

//SANY - Small and No Yoshi
#define MOVE_MOD 1.05f

//TrustYourSenses
#define TYS_TURNSPEED (s16)8

//MAXIMUMs and MINIMUMs
#define FLOAT_MAX 65504.f
#define FLOAT_MIN -65504.f

//This is to set the current Powerup State.
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
#define SUCCESS_EXIT 0
#define EXIT_FAIL 1
#define EXIT_PLAYER_CHOICE 2
#define EXIT_DEFAULT 3

//dScStage_c::m_gameMode
#define GAME_NORMAL 0
#define GAME_LUIGI_GUIDE 1
#define GAME_TITLE 2
#define GAME_RETURN_ON_INPUT 3
#define GAME_MOVIE 4 //Idk, it spawns some strange overlay, and changes nothing

//dScStage_c::m_miniGame
#define MINIGAME_NONE 0
#define MINIGAME_STAR 1
#define MINIGAME_TOAD_HOUSE 2
//TODO: Add the others

//Live Patch Helper Stuff

#define INSTR_BLR                0x4e800020
#define INSTR_NOP                0x60000000
#define INSTR_BRICKTIMER         0x3C0001F4

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

//Player related Stuff
#define DEFAULT_SPEED_RIGHT       0x3f800000
#define DEFAULT_SPEED_LEFT        0xbf800000
#define DEFAULT_SPEED_JUMP        0x40683127
#define STATEID_BALLOON           0x8032692c

#endif
