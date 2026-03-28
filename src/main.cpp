#include "main.h"

ext void preGameLoop()
{
    if(Modifiers[6]) {
        Worldmapify(false);
    }
}

/*
    Testing Asset
    
    if(Modifiers[1])
        Grow();
    if(Modifiers[2])
        Shrink();
*/

ext void onGameLoop()
{
    if (!GetPlayers())
        ret;
    GlobalFrameTimer++;
    

    if (Modifiers[0])
        NahFuckThat(true);
    if (Modifiers[1] && CallSpacer(TIMER_CLEAR))
        Lonely();
    if(Modifiers[2] && CallSpacer(TIMER_SPIN) && !GetNextOfType(EN_GOALPOLE))
        SpinEternally();
    if (Modifiers[3])
        SmallerAndNoYoshi();
    if (Modifiers[4])
        TowerFunc();
    //if (Modifiers[5])
        //WaterLevel();
    if (Modifiers[6])
        WaterLevel();

    #ifdef DEBUG
    u32 btns = GetActiveRemocon()->heldButtons;
    const int dumpLevelData = WPAD_A | WPAD_B;

    if((btns & dumpLevelData) == dumpLevelData) {
        ToggleMods(); }
    #endif

    #ifdef NO_MP
    #ifndef DEBUG
        if ((Players[1] || Players[2] || Players[3])) {
        u32 lID = 0;
        getLevelInfo(&lID, NULL, NULL, NULL, NULL);

        if(lID != 256)
            NahFuckThat(false);
    }
    #endif
    #endif

    //This OSReport will crash everything!
    //OSReport("getGravityAttempt: %d\n", *(unsigned char*) (Players[0] + 0x1068));

    SetLives();
    if(GlobalFrameTimer > 59) GlobalFrameTimer = 0;
    ret;
}

ext void onStageCreated()
{
    for (int i = 0; i < MOD_SIZE; i++)
        Modifiers[i] = false;
    ToggleMods();

    #ifdef DEBUG
    for (int i = 0; i < MOD_SIZE; i++)
        OSReport("Modifiers[%d] is now: %d\n", i, Modifiers[i]);
    #endif
    ret;
}

//Use this to reinit the mod, when the game reloads... i dont know if this is how it works, but eh why not
ext void onRecieveResetEvent() {
    Players[0] = NULL;
    Players[1] = NULL;
    Players[2] = NULL;
    Players[3] = NULL;

    GlobalFrameTimer = 0;
    for(int i = 0; i < MOD_SIZE; i++) {
        Modifiers[i] = false;
    }

    ret;
}
