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

    //Peaches Castle (1-40)
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
    //1-6
    Modifiers[7] = (LevelID == 6 && WorldID == 1);

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

inline dBase_c* GetNextOfType(Actors actorID) {
    ret (dBase_c*)FindActorByType(actorID, (Actor*)Players[0]);
}

inline void GetAllOfType(Actors actorID, u8 sizeOfArray, dEn_c* outBuff[], int* outSize) {
    dEn_c* last;
    dEn_c* curr;
    if(!last) last = (dEn_c*)Players[0];
    for(int i = 0; i < sizeOfArray; i++) {
        curr = (dEn_c*)FindActorByType(actorID, (Actor*)last);
        if(!curr) ret;
        outBuff[i] = curr;
        last = curr;
    }

    ret;
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
    dEn_c* target = (dEn_c*)GetNextOfType(EN_BLOCK_HELP);
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