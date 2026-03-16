#include "main.h"

ext void preGameLoop()
{
    if(Modifiers[6]) {
        Worldmapify(false);
    }
}

ext void onGameLoop()
{
    if (!GetPlayers())
        ret;

    if (Modifiers[0])
        NahFuckThat(true);
    if (Modifiers[1])
        Grow();
    if (Modifiers[2])
        Shrink();
    if (Modifiers[3])
        SmallerAndNoYoshi();
    if (Modifiers[4])
        TowerFunc();
    if (Modifiers[5])
        WaterLevel();
    if (Modifiers[6])
        Worldmapify(true);

    #ifdef DEBUG
    const int buttons = WPAD_A | WPAD_B;
    if((GetActiveRemocon()->heldButtons & buttons) == buttons) {
        ToggleMods();
    }
    #endif

    #ifdef NO_MP
        if ((Players[1] || Players[2] || Players[3])) {
        u32 lID = 0;
        getLevelInfo(&lID, NULL, NULL, NULL, NULL);

        if(lID != 256)
            NahFuckThat(false);
    }
    #endif

    //This OSReport will crash everything!
    //OSReport("getGravityAttempt: %d\n", *(unsigned char*) (Players[0] + 0x1068));

    SetLives();
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
