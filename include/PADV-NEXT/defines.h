#ifndef PADV
#define PADV
#ifndef REVOLUTION
#define REVOLUTION
#endif

#define ext extern "C"
#define MODS_SIZE 26 //Mods Array Size

#define INSTR_BLR 0x4e800020
#define INSTR_NOP 0x60000000

//Defaults
#define DEFAULT_SPEED_RIGHT 0x3f800000
#define DEFAULT_SPEED_LEFT 0xbf800000
#define DEFAULT_SPEED_JUMP 0x40683127
#define STATEID_BALLOON 0x80376870

#define DEBUG_PADV
#define DEBUG_PADV_ALL
#define PADV_USE_MKWCAT_PATCHES

#ifdef DEBUG_PADV_ALL
#define DEBUG_EXEC
#endif

#include "kamek.h"
#include "types_nw4r.h"
#include <game\bases\d_system.hpp>
#include <game/bases/d_next.hpp>

#include <game/mLib/m_mtx.hpp>
#include <game/mLib/m_vec.hpp>
#include <game/clib/c_math.hpp>
#include <game/bases/d_game_key.hpp>
#include <game/framework/f_manager.hpp>
#include <game/framework/f_profile_name.hpp>
#include <game/bases/d_bg.hpp>
#include <game/bases/d_bg_ctr.hpp>
#include <game/bases/d_enemy.hpp>
#include <game/bases/d_actor.hpp>
#include <game/bases/d_a_player.hpp>
#include <game/bases/d_a_yoshi.hpp>
#include <game/bases/d_s_stage.hpp>
#include <game/bases/d_pause_manager.hpp>
#include <game/bases/d_base_actor.hpp>
#include <game/bases/d_a_player_manager.hpp>
#include <game/bases/d_enemy_manager.hpp>
#include <game/bases/d_game_com.hpp>

#include "PADV-NEXT/predefines.hpp"
#include "PADV-NEXT/Utils.h"
#include "PADV-NEXT/structs.hpp"
#include "PADV-NEXT/OverlayObjects.h"
#include "PADV-NEXT/ExecMng.h"
#include "PADV-NEXT/math.hpp"
#include "PADV-NEXT/Modifiers.h"
#include "PADV-NEXT/daEnemies_c.h"

// Current amount of activatable modifiers
#define MOD_SIZE 26

extern int FrameTimer;
extern ExecPhase currentPhase;
extern bool isInitialized;
extern bool isInStage;
extern int currentMoveMod;
extern dEn_c* smitePlayer;
extern const char* Signature;

extern dAcPy_c* Players[4];
extern dGameKeyCore_c* Inputs[4]; 
extern const Modifier Mods[MOD_SIZE];


// Infinite-Lives "True" Amount
#define LIVES_AMOUNT 0x64

// Tower-Modifier
#define SPEEDCAP_TOWER 3.025f
#define SPEEDCAP_TOWER_MINI 2.25f

// Water-Modifiers
#define SPEED_WATER_MOD 128.f
#define WATER_DRAIN 4.f
#define SWIM_MOD 128.f

// Scaling (Legacy)
#define SCALE_MOD 0.00125f
#define SCALE_MOD_OTHER 143.36

// WM-Mode
#define MAP_SPEED 12

// SpinEternally
#define TIMER_SPIN 15

// Lonely
#define TIMER_CLEAR 6
#define FIND_ENTS 7

// SANY - Small and No Yoshi
#define MOVE_MOD 1.05f

// TrustYourSenses
#define TYS_TURNSPEED (s16)8

#define MARIOSLIDE_SPEED 1.5f
#define MARIOSLIDE_LIMIT 100

// MAXIMUMs and MINIMUMs
#define FLOAT_MAX 65504.f
#define FLOAT_MIN -65504.f
#define FLOAT_MAX_ENCODED 0x47FF0000

// Live Patch Helper Stuff

#define INSTR_BLR 0x4e800020
#define INSTR_NOP 0x60000000
#define INSTR_BRICKTIMER 0x3C0001F4
#define INSTR_EXITUNLCEARED 0x48000018

// Player related Stuff
#define DEFAULT_SPEED_RIGHT 0x3f800000
#define DEFAULT_SPEED_LEFT 0xbf800000
#define DEFAULT_SPEED_JUMP 0x40683127
#define STATEID_BALLOON 0x80376870

extern "C" dAcPy_c *GetSpecificPlayerActor(int number);
extern void *LP_ONEUPEFFECT; //==
extern void *LP_BRICKTIMER; //==
extern void *LP_NODEATHPAUSE; //==
extern void *LP_ALLOWDEBUG; //==
extern void *LP_NEXTCANNON; //==
extern void *LP_NOSCORE;    //==
extern void *LP_RIGHTSPEED; //==
extern void *LP_LEFTSPEED;  //==
extern void *LP_INITIALJUMPSPEED; //==
extern void *LP_ALLOWPRESSTWO; //==
extern void *LP_ALLOWHOLDTWO; //==
extern void *LP_AUTOICE; //!=
extern void *LP_GROWICE; //!=, PAL1=80ad0f24
extern void *LP_AUTOHOLDDOWN; //==
extern void *LP_FUKIDELETER; //==
extern void *LP_EXITUNCLEARED_1; //==
extern void *LP_EXITUNCLEARED_2; //==
extern void *LP_PSSLOTLIMIT_1; //!=, PAL1=80abb680
extern void *LP_PSSLOTLIMIT_2; //!=, PAL1=80abb720
extern void *LP_PIPESPAWNID_1; //!=, PAL1=80abb6cc, Default: li r3, 51
extern void *LP_PIPESPAWNID_2; //!=, PAL1=80abb76c, Default: li r3, 133
extern void *LP_DEATHMUSHSETUP_1; //==
extern void *LP_DEATHMUSHSETUP_2; //==
extern void *LP_FALLPLATPATCH;    //!=, PAL1=80837a70
extern void *LP_PARABOMBSPAWNID; //Default: li r3, 134
extern void *LP_CHEEPSPAWNID; //li r3, 389

//Data segment, for absolute SMCs
#endif
                               // Remains of the old LivePatch Address Library, here to see instructions
                               // #define LP_PSSLOTLIMIT_1 (u32 *)0x80abb6a0 // cmpwi instr
                               // #define LP_PSSLOTLIMIT_2 (u32 *)0x80abb740 // cmpwi instr

    // #define LP_PIPESPAWNID_1 (u32 *)0x80abb6ec // li instr
    // #define LP_PIPESPAWNID_2 (u32 *)0x80abb78c // li instr

    // #define LP_DEATHMUSHSETUP_1 (u32 *)0x80145c04 // mflr r29
    // #define LP_DEATHMUSHSETUP_2 (u32 *)0x80145c80 // mtlr r29