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

    if ((btns & dumpLevelData) == dumpLevelData)
    {
        ToggleMods();
    }
#endif

#ifdef NO_MP
#ifndef DEBUG
    if ((Players[1] || Players[2] || Players[3] && dScStage_c::instance()))
    {
        u32 lID = 0;
        getLevelInfo(&lID, NULL, NULL, NULL, NULL);

        if (lID != 256)
            NahFuckThat(false);
    }
#endif
#endif

    if (GlobalFrameTimer > 59)
        GlobalFrameTimer = 0;
    ret;
}

ext void onStageCreated()
{
    SetLives();
    LivePatch(dScStage_c::instance()->enteredWorld + 1, LP_NEXTCANNON);
    ModifyMovement(0);

    for (int i = 0; i < MOD_SIZE; i++)
        Modifiers[i] = false;
    if(!(GetActiveRemocon()->heldButtons & WPAD_B))
        ToggleMods();
    else OSReport("Modifiers were Disabled during Level Init\n");

#ifdef DEBUG
    for (int i = 0; i < MOD_SIZE; i++)
        OSReport("Modifiers[%d] is now: %d\n", i, Modifiers[i]);
#endif
    ret;
}

// Use this to reinit the mod, when the game reloads... i dont know if this is how it works, but eh why not
ext void onRecieveResetEvent()
{
    Players[0] = NULL;
    Players[1] = NULL;
    Players[2] = NULL;
    Players[3] = NULL;

    GlobalFrameTimer = 0;
    for (int i = 0; i < MOD_SIZE; i++)
    {
        Modifiers[i] = false;
    }

    ret;
}

ext void onBoot()
{
#ifdef DEBUG
    OSReport("\n\nStatic LivePatch Start!\n\n\n");
    LivePatch(INSTR_BLR, LP_ALLOWDEBUG);
#endif

    LivePatch(INSTR_BLR, LP_1UPEFFECT);
    LivePatch(INSTR_BRICKTIMER, LP_BRICKTIMER);
    LivePatch(INSTR_BLR, LP_NODEATHPAUSE);
    LivePatch(INSTR_BLR, LP_NOSCORE);

#ifdef DEBUG
    OSReport("\n\nStatic LivePatch Successfully!\n\n\n");
#endif
    ret;
}

// Relaying execution to here for clarity if something fails
ext void ApplyModifiers(bool pre)
{
    QOLModifications();

    if (!pre)
    {
        if (Modifiers[0])
            NahFuckThat(true);
        if (Modifiers[1] && CallSpacer(TIMER_CLEAR))
            Lonely();
        if (Modifiers[2] && CallSpacer(TIMER_SPIN) && !GetNextOfType(EN_GOALPOLE, false))
            SpinEternally();
        if (Modifiers[4])
            TowerFunc();
        if (Modifiers[5])
            MarioCantBreathUnderwater();
        if (Modifiers[6])
            Linearity();
        if(Modifiers[8]) 
            TrustYourSenses();
        if(Modifiers[9]) 
            ModifyMovement(1);
        if(Modifiers[10]) {
            ModifyMovement(4);
            for(int i = 0; i < 4; i++) {
                if(!Players[i]) continue;
                Players[i]->scale.x = -1;
                Players[i]->scale.z = -1;
            }
        }

        ret;
    }

    if (pre)
    {
        DeleteUnwanted();  // Makes sense here, since it automatically means, we're both in a game, and fully 
        if (Modifiers[3])
            SmallerAndNoYoshi();
        if (Modifiers[7] && CallSpacer(15))
            ShyRollers();

        ret;
    }

    ret;
}
