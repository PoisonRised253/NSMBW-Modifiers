#ifndef __H_DEFS
#define __H_DEFS

//Macros Because Yes! DEAL WITH IT!!!!
#define ext extern "C"
#define ret return

//Build Flags
#define DEBUG
#define NO_MP
//#define DEBUG_CS //This causes logs to fill very quickly, all the time...

//Current amount of activatable modifiers
#define MOD_SIZE 8

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

//MAXIMUMs and MINIMUMs
#define FLOAT_MAX 65504.f
#define FLOAT_MIN -65504.f

//This is to set the current Powerup State.
//Enums wont work as intended for some reason so this exists instead.
#define SMALL 0x00
#define BIG 0x01
#define FIRE 0x02
#define MINI 0x03
#define PROPELLER 0x04
#define PENGUIN 0x05
#define ICE 0x06

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

//Live Patch Helper Stuff

#define INSTR_BLR 0x4e800020
#define INSTR_NOP 0x60000000
#define INSTR_BRICKTIMER 0x3C0001F4

//Live Patch Addresses
#define LP_1UPEFFECT (u32*)0x801591F0
#define LP_BRICKTIMER (u32*)0x800E3AB8
#define LP_NODEATHPAUSE (u32*)0x8004e050
#define LP_ALLOWDEBUG (u32*)0x800F1960

#endif
