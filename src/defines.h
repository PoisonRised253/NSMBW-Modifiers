#ifndef __H_DEFS
#define __H_DEFS

//Macros Because Yes! DEAL WITH IT!!!!
#define ext extern "C"
#define ret return

//Build Flags
#define DEBUG
#define NO_MP
#define MOD_SIZE 7

//Infinite-Lives "True" Amount
#define LIVES_AMOUNT 0x64

//Tower-Modifier
#define SPEEDCAP_TOWER 3.025f
#define SPEEDCAP_TOWER_MINI 2.25f

//Water-Modifier
#define SPEED_WATER_MOD 128.f

//Scaling
#define SCALE_MOD 0.00125f

//WM-Mode
#define MAP_SPEED 12;

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
#define NORMAL_EXIT 2

//GameMode
#define NORMAL_GAME 0

//Stage Flag
#define SF_NORMAL 0

#endif