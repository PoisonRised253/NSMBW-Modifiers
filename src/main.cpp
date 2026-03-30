#include "main.h"

ext void preGameLoop()
{
    ApplyModifiers(true);
    ret;
}

ext void onGameLoop()
{
    if (!GetPlayers())
        ret;
    GlobalFrameTimer++;

    ApplyModifiers(false);

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

ext void onBoot() {
    #ifdef DEBUG
    OSReport("\n\nLPInsert Patches Start!\n\n\n");
    LPInsert(INSTR_BLR, LP_ALLOWDEBUG);
    #endif
    LPInsert(INSTR_BLR, LP_1UPEFFECT);
    LPInsert(INSTR_BRICKTIMER, LP_BRICKTIMER);
    LPInsert(INSTR_BLR, LP_NODEATHPAUSE);

    #ifdef DEBUG
    OSReport("\n\nLPInsert Patches Successfully!\n\n\n");
    #endif
    ret;
}

//Relaying execution to here for clarity if something fails
ext void ApplyModifiers(bool pre) {
    DeleteUnwanted(); //Makes sense here, since it automatically means, we're both in a game, and fully initialized

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
    if (Modifiers[5])
        MarioCantBreathUnderwater();
    if (Modifiers[6])
        Linearity();
    if (Modifiers[7] && pre && CallSpacer(15)) {
        ShyRollers();
    }

    ret;
}
