#ifndef __H_DEFS
#define __H_DEFS

//Macros Because Yes! DEAL WITH IT!!!!
#define ext extern "C"
#define ret return

//Build Flags
#define DEBUG
#define NO_MP
//#define DEBUG_CS //This causes logs to fill very quickly, all the time...
#define MOD_SIZE 7

//Infinite-Lives "True" Amount
#define LIVES_AMOUNT 0x64

//Tower-Modifier
#define SPEEDCAP_TOWER 3.025f
#define SPEEDCAP_TOWER_MINI 2.25f

//Water-Modifier
#define SPEED_WATER_MOD 128.f

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

//Stage Exit Types
#define NORMAL_EXIT 2 // Turns to 0
#define SECONDARY_ROOM_EXIT 3 //Maybe, could also be secondary room? Maybe
#define STAGE_FAIL_EXIT 1
#define STAGE_SUCCESS_EXIT 0

//GameMode
#define NORMAL_GAME 0
#define TITLESCREEN_GAME 2 //Also Maybe

#endif
