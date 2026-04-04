#include "Utils.h"

bool Modifiers[MOD_SIZE] = {false};
dAc_Py_c *Players[4] = {NULL, NULL, NULL, NULL};
int GlobalFrameTimer = 0;

inline bool GetPlayers() {
    Players[0] = GetSpecificPlayerActor(0);
    Players[1] = GetSpecificPlayerActor(1);
    Players[2] = GetSpecificPlayerActor(2);
    Players[3] = GetSpecificPlayerActor(3);
    ret Players[0] != NULL;
}

inline void getLevelInfo(u32* lOut, u32* wOut, u8* aOut, u32* exitOut, u32* gameOut) {
    dScStage_c* s = dScStage_c::instance();
    if(!s) ret;
    if(lOut != NULL) *lOut = s->enteredLevel + 1;
    if(wOut != NULL) *wOut = s->enteredWorld + 1;
    if(aOut != NULL) *aOut = s->area;
    if(exitOut != NULL) *exitOut = s->m_exitMode;
    if(gameOut != NULL) *gameOut = s->m_gameMode;
    ret;
}

inline void SetLives() {
    if(!Player_Lives) ret;
    Player_Lives[0] = LIVES_AMOUNT;
    Player_Lives[1] = LIVES_AMOUNT;
    Player_Lives[2] = LIVES_AMOUNT;
    Player_Lives[3] = LIVES_AMOUNT;
    for(int i = 0; i < 100; i++) {
        dInfo_c::m_instance->addStockItem(0);
        dInfo_c::m_instance->addStockItem(1);
        dInfo_c::m_instance->addStockItem(2);
        dInfo_c::m_instance->addStockItem(3);
        dInfo_c::m_instance->addStockItem(4);
        dInfo_c::m_instance->addStockItem(5);
        dInfo_c::m_instance->addStockItem(6);
    }
    ret;
}

ext void ToggleMods() {
    u32 LevelID = 0;
    u32 WorldID = 0;
    u8 AreaID = 0;
    #ifdef DEBUG
    u32 game = 0;
    u32 exit = 0;

    getLevelInfo(&LevelID, &WorldID, &AreaID, &exit, &game);
    #endif

    #ifndef DEBUG
    getLevelInfo(&LevelID, &WorldID, &AreaID, NULL, NULL);
    #endif

    if(LevelID == NULL && WorldID == NULL) ret;

    //Peaches Castle (1 - 40)
    Modifiers[0] = (LevelID == 41 && WorldID == 1);
    //1 - 1
    Modifiers[1] = (LevelID == 1 && WorldID == 1);
    //1 - 2
    Modifiers[2] = (LevelID == 2 && WorldID == 1);
    //1 - 3
    Modifiers[3] = (LevelID == 3 && WorldID == 1);
    //1 - Tower 
    Modifiers[4] = (LevelID == 22 && WorldID == 1);
    //1 - 4
    Modifiers[5] = (LevelID == 4 && WorldID == 1);
    //1 - 5
    Modifiers[6] = (LevelID == 5 && WorldID == 1);
    //1 - 6
    Modifiers[7] = (LevelID == 6 && WorldID == 1);
    //1 - Castle
    Modifiers[8] = (LevelID == 24 && WorldID == 1);
    //2 - 1
    Modifiers[9] = (LevelID == 1 && WorldID == 2);
    //2 - 2
    Modifiers[10] = (LevelID == 2 && WorldID == 2);
    //2 - 3
    Modifiers[11] = (LevelID == 3 && WorldID == 2);
    //2 - Tower (2 - 22)
    Modifiers[12] = (LevelID == 22 && WorldID == 2);
    //2 - 4
    Modifiers[13] = (LevelID == 4 && WorldID == 2);
    //2 - 5
    Modifiers[14] = (LevelID == 5 && WorldID == 2);
    //2 - 6
    Modifiers[15] = (LevelID == 6 && WorldID == 2);

#ifdef DEBUG
        OSReport("L: %d, W: %d, A: %d, E: %d, G: %d\n", LevelID, WorldID, AreaID, exit, game);
#endif
    ret;
}

//More CallsPerSecond = Less Calls. Basically inverted... Think 30 = 2 Calls/s
inline bool CallSpacer(int callsPerSecond)
{
    #ifdef DEBUG_CS
    bool retb = callsPerSecond && (GlobalFrameTimer % callsPerSecond == 0);
    if(retb) OSReport("Call Spacer Allowed Call on frame: %d\n", GlobalFrameTimer);
    ret retb;
    #endif

    #ifndef DEBUG_CS
    ret callsPerSecond && (GlobalFrameTimer % callsPerSecond == 0);
    #endif
}

inline dEn_c* GetNextOfType(Actors actorID, bool fromPlayer) {
    if(fromPlayer) ret (dEn_c*)FindActorByType(actorID, (Actor*)Players[0]);
    ret (dEn_c*)FindActorByType(actorID, (Actor*)NULL);
}

//Mode 0: x only
//Mode 1: y only
//Mode 2: x & y
inline void ClearObjVel(dEn_c* obj, u8 mode) {
    if(!obj) ret;
    switch(mode) {
        case 0: obj->speed.x = 0; ret;
        case 1: obj->speed.y = 1; ret;
        case 2: obj->speed.x = 0; obj->speed.y = 0; ret;
        default: ret;
    }

    ret;
}

inline void DeleteUnwanted() {
    dEn_c* target = (dEn_c*)GetNextOfType(EN_BLOCK_HELP, false);
    if(target) target->Delete(1);
}

//0 = Mushroom | 0x00
//1 = FireFlower | 0x09
//2 = IceFlower | 0x0E
//3 = Penguin | 0x11
//4 = Propeller | 0x15
//5 = Mini | 0x19
//6 = Star | 0x01
//7 = 1-Up | 0x07
//8 = Normal-Sized Mini | 0x79
inline int GetPowerupType(u32 settings) {
    u32 b = settings & 0x03; // last two bits only
    switch(b) {
        case 0x00: ret 0;
        case 0x09: ret 1;
        case 0x0E: ret 2;
        case 0x11: ret 3;
        case 0x15: ret 4;
        case 0x19: ret 5;
        case 0x01: ret 6;
        case 0x07: ret 7;
        case 0x79: ret 8;
        default: ret 0;
    }
}

volatile inline int* GetPlayerPowerState(dAc_Py_c* player) {
    unsigned char* powerStateProbs = (unsigned char*)player + (0x14E0);
    ret (int*)powerStateProbs;
}

volatile inline int* checkGrounded(dAc_Py_c* player) {
    unsigned char* grounded = (unsigned char*)player + (0x1564);
    ret (int*)grounded;
}

//Live-Patch
volatile void LivePatch(u32 newInstr, u32* addr) {
    if(*addr == newInstr) ret;
    *addr = newInstr;
    #ifdef DEBUG_LP
    if(*addr != newInstr) {OSReport("LPIns Failure! Val: %p, At: %p\n", *addr, addr); ret;}
    else OSReport("LPIns Success at: %p\n", addr);
    #endif

    DCFlushRange(addr, 32);
    ICInvalidateRange(addr, 32);
    ret;
}

ext void QOLModifications() {
    //Nullsub for now, last idea didnt work
    ret;
}

// Modes:
// 0 = Restore
// 1 = Disable Left
// 2 = Disable Right
// 3 = Disable Jump
// 4 = Inverse
ext void ModifyMovement(int mode)
{

    if (mode == 0)
    {
        LivePatch(DEFAULT_SPEED_LEFT, LP_LEFTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_JUMP, LP_INITIALJUMPSPEED);
        ret;
    }

    if (mode == 1 && *LP_LEFTSPEED != 0)
    {
        LivePatch(0, LP_LEFTSPEED);
        ret;
    }

    if (mode == 2 && *LP_RIGHTSPEED != 0)
    {
        LivePatch(0, LP_RIGHTSPEED);
        ret;
    }

    if (mode == 3 && *LP_INITIALJUMPSPEED)
    {
        LivePatch(0, LP_INITIALJUMPSPEED);
        ret;
    }

    if (mode == 4)
    {
        LivePatch(DEFAULT_SPEED_LEFT, LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, LP_LEFTSPEED);

        ret;
    }

    ret;
}

// Triggers at L: 41, W: 1, A: 255, because funny!
// This will remove all instances of dAc_Py_c, which means the game refuses to commit video game.
ext void NahFuckThat(bool delP1)
{
    if (delP1)
    {
        if (Players[0])
        {
            Players[0]->Delete(1);
            OSReport("NahFuckThat() ran. Which means a softlock, this is intentional, and Pretty Funny.\n");
#ifdef NO_MP
            OSReport("When this message appears, it likely means that you tried Playing with Multiple People.\n This is not yet supported.");
#endif
        }
    }

    if (Players[1])
        Players[1]->Delete(1);
    if (Players[2])
        Players[2]->Delete(1);
    if (Players[3])
        Players[3]->Delete(1);

    ret;
}