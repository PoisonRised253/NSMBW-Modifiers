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

    //Peaches Castle (41 - 1)
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

#ifdef DEBUG
        OSReport("L: %d, W: %d, A: %d, E: %d, G: %d\n", LevelID, WorldID, AreaID, exit, game);
#endif
    ret;
}

inline float clampf(float val, float min, float max) {
    if(val < min) ret min;
    if(val > max) ret max;
    
    ret val;
}

inline int Round(float x)
{
    return (int)(x >= 0.0f ? x + 0.5f : x - 0.5f);
}

ext void changeActivePhysicsRect(dStageActor_c* actor, float xc, float yc, float xe, float ye) {
    ActivePhysics::Info info;
    info.xDistToCenter = xc;
    info.yDistToCenter = yc;
    info.xDistToEdge   = xe;
    info.yDistToEdge   = ye;

    info.category1  = actor->aPhysics.info.category1;
    info.category2  = actor->aPhysics.info.category2;
    info.bitfield1  = actor->aPhysics.info.bitfield1;
    info.bitfield2  = actor->aPhysics.info.bitfield2;
    info.unkShort1C = actor->aPhysics.info.unkShort1C;
    info.callback   = actor->aPhysics.info.callback;

    actor->aPhysics.removeFromList();
    actor->aPhysics.initWithStruct(actor, &info);
    actor->aPhysics.addToList();
    ret;
}