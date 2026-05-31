#include "main.h"
#include "daEnemies_c.h"
#include "ExecMng.h"
//Check Note in main.h to see why this exists
ext void NullSub() {asm("blr");}

dEn_c* smitePlayer = NULL;

ext void preGameLoop()
{
    GlobalFrameTimer++;
    ApplyModifiers(true);
    if(!Players[0]) ret;

    if(smitePlayer) {
        smitePlayer->pos.y -= 160;

        OSReport("Red is Sus!\n");
        smitePlayer = NULL;
    }

    #ifdef DEBUG_EXPERIMENTS
    u32 lid, wid;
    getLevelInfo(&lid, &wid, NULL, NULL, NULL);

    if(!GetNextOfType(EN_ITEM, false) && lid == 1 && wid == 9) {
        dStageActor_c* item = (dStageActor_c*)CreateActor(EN_ITEM, ITEM_UNKNOWN, MakeVec(734, -480, 3000), 0, 0);
        OSReport("Hello :D | %p\n", item);
    }
    #endif
    ret;
}

ext void onGameLoop()
{
    if(CallSpacer(60))
        SetLives();
    if (!GetPlayers())
        ret;


    for(int i = 0; i < 4; i++) {
        if(Players[i] && *GetPlayerState(Players[i]) != STATEID_BALLOON) Players[i]->scale = MakeVec(1,1,1);
        }

    ApplyModifiers(false);

    HandleHotkeys();

#ifdef DEBUG_EXPERIMENTS
    //DEBUG SECTION
    void* bar = (void*)GetNextOfType(daFiresnake_c::actorID, false);
    if(bar) OSReport("Firepenis: %p\n", bar);
    void* bar2 = (void*)GetNextOfType(daSpikeball_c::actorID, false);
    if(bar2) OSReport("Ouchie-Balls: %p\n", bar2);
    void* bar3 = (void*)GetNextOfType(AC_FLOOR_GYRATION, false);
    if(bar3) OSReport("Big Rotating Balls: %p\n", bar3);
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
    dExecMng_c::Reset();
    dSys_c::setFrameRate(1);
    ModifyMovement(0);

    //Speed up swimming, i hate slow water levels. Plus We're literally a water pokemon now, so it checks.
    daPlBase_c::WaterSwimSpeed = SWIM_MOD / 60;
    daPlBase_c::WaterMaxFallSpeed = SWIM_MOD / 120;
    daPlBase_c::WaterJumpSpeed = SWIM_MOD / 30;
    daPlBase_c::WaterWalkSpeed = SWIM_MOD / 45;
    *daBoo_c::getGlobalScaler() = 1.f;

    for (int i = 0; i < MOD_SIZE; i++)
        Modifiers[i] = false;
    if(!(GetActiveRemocon()->heldButtons & WPAD_B))
        ToggleMods();
    else { OSReport("Modifiers Disabled at Level Init\n"); ret; }

#ifdef DEBUG
    for (int i = 0; i < MOD_SIZE; i++)
        OSReport("Modifiers[%d] is now: %d\n", i, Modifiers[i]);
#endif
    ret;
}

ext void onNextScene() {
    dExecMng_c::Reset();
    GlobalFrameTimer = 0;
    ToggleMods();
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
    OSReport("Static LivePatch Start!\n");
    LivePatch(INSTR_BLR, LP_ALLOWDEBUG);
#endif

    LivePatch(INSTR_BLR, LP_1UPEFFECT);
    LivePatch(INSTR_BRICKTIMER, LP_BRICKTIMER);
    LivePatch(INSTR_BLR, LP_NOSCORE);
    LivePatch(INSTR_BLR, LP_FUKIDELETER);

    LivePatch(INSTR_EXITUNLCEARED, LP_EXITUNCLEARED_1);
    LivePatch(INSTR_EXITUNLCEARED, LP_EXITUNCLEARED_2);

    LivePatch(INSTR_NOP, (u32*)0x80a28610); //Makes Items be collected reguardless of wether Player originally has item (part 1)
    LivePatch(INSTR_NOP, (u32*)0x80a28614); //Part 2
    LivePatch(0x48000010,(u32*)0x80a285f4); //Part 3

    //Replacements/Less-Advanced versions of MKWCAT patches, incase they ask me not to use them...
    #ifndef USE_MKWCAT_PATCHES
    LivePatch(INSTR_BLR, LP_NODEATHPAUSE); //<- Replaced with Advanced Version by mkwcat (Check like 10 lines below this one)
    #endif

    //The Next Patches are stolen from mkwcat, go support them please.
    #ifdef USE_MKWCAT_PATCHES
    OSReport("Using mkwcat's Patches\n");
    //No Death Pause
    LivePatch(INSTR_NOP, (u32*)0x801410C4);
    LivePatch(INSTR_NOP, (u32*)0x801410D0);
    LivePatch(INSTR_BLR, (u32*)0x80141020);
    LivePatch(INSTR_BLR, (u32*)0x8013DA30);
    LivePatch(INSTR_BLR, (u32*)0x8013DB30);
    LivePatch(0x38600000, (u32*)0x80150E54); //li r3, 0
    LivePatch(0x38600000, (u32*)0x80150E98); //li r3, 0

    //Exit Anytime
    LivePatch(0x38600001, (u32*)0x800B4EA8); //li r3, 1

    //Infinite Projectiles
    LivePatch(0x38600001, (u32*)0x8011B0A4);
    LivePatch(0x38600001, (u32*)0x80124744);
    #endif

#ifdef DEBUG
    OSReport("Static LivePatch Successfully!\n");
#endif
    ret;
}

// Relaying execution to here for clarity if something fails
ext void ApplyModifiers(bool pre)
{
    AntiBubble();

    //Isolate Modifier[2], to allow to trigger it either way, with a difference in action based on 'bool pre'
    if (Modifiers[2] && CallSpacer(TIMER_SPIN) && !GetNextOfType(EN_GOALPOLE, false))
            SpinEternally(pre);

    if (!pre)
    {
        if (Modifiers[0])
            NahFuckThat(true);
        if (Modifiers[1] && CallSpacer(TIMER_CLEAR))
            Lonely();
        if (Modifiers[4])
            TowerFunc();
        if (Modifiers[5])
            MarioCantBreathUnderwater();
        if(Modifiers[8]) 
            TrustYourSenses();
        if(Modifiers[9]) {
            ModifyMovement(1);
            DisablePropeller(POWER_FIRE);
        }
        if(Modifiers[10]) {
            DisablePropeller(POWER_ICE);
            ModifyMovement(4);
            for(int i = 0; i < 4; i++) {
                if(!Players[i]) continue;
                Players[i]->scale.x = -1;
                Players[i]->scale.z = -1;
            }
        }
        if(Modifiers[13]) 
            SandyPain();
        if (Modifiers[14])
            PokeyParty();
        if (Modifiers[17])
            MarioSlide();

        ret;
    }

    if (pre)
    {
        DeleteUnwanted();  // Makes sense here, since it automatically means, we're both in a game, and fully 
        if (Modifiers[3])
            MiniPlusPlus();
        if (Modifiers[6])
            Linearity();
        if (Modifiers[7] && CallSpacer(15))
            ShyRollers();
        if (Modifiers[11])
            LiterallyBulletHell();
        if (Modifiers[12]) 
            WeGoWee();

        if (Modifiers[15])
            FuckTwoSix();
        if (Modifiers[16])
            CastleBlowers();

        if (Modifiers[17])
            MarioSlide();

        if (Modifiers[18])
            RealisticBullet();
        if (Modifiers[19])
            Icey();
        if (Modifiers[20])
            BetterGhosts();

        #ifdef DEBUG_SLOPE
        if(Players[0])
            OSReport("SlopeInfo{A: %p, D: %p}\n", Players[0]->collMgr.currentSlopeAngle, Players[0]->collMgr.currentSlopeDirection);
        #endif

        ret;
    }

    ret;
}

ext void AntiBubble() {
    for(int i = 0; i < 4; i++) {
        if(!Players[i]) continue;
        if(*GetPlayerState(Players[i]) != STATEID_BALLOON) continue;
        dAc_Py_c* p = Players[clamp(i - 1, 0, 4)];
        dAc_Py_c* p2 = Players[clamp(i + 1, 0, 4)];

        if(i > 0 && p != NULL) { Players[i]->pos = VecAdd(p->pos, MakeVec(0, 8.f, 0)); Players[i]->scale = MakeVec(0,0,0);}
        else if(p2) {Players[i]->pos = VecAdd(p2->pos, MakeVec(0, 8.f, 0)); Players[i]->scale = MakeVec(0,0,0); }
        dEn_c* bubble = GetNextOfType(EN_HATENA_BALLOON, false);
        if(!bubble) continue;
        bubble->visible = false;
        bubble->pos = Players[i]->pos;
    }
    ret;
}

ext void DeathMushHandler(dAc_Py_c* toucher) {
    asm("lwz r25, +0x04(r31)\nandi. r25, r25, 0xFF\ncmpwi r25, 0xF9\n bne+ skip");
    smitePlayer = (dEn_c*)toucher;
    asm("skip:");
    ret;
}

//Attempt to hook the end of dAcPy_c::setBcData() to manually fuck with collision each frame
//Time to build a struct to keep track of what to set it to :(
//r31=Player
ext void onPlayerCollisionUpdated(void* playerptr) {
    //Setup, includes PhysExt, CollMgr and soon ActivePhysics
    dAcPy_c* player = (dAcPy_c*)playerptr;
    CollExtents extents = getExtents(player);


    #ifdef DEBUG_COLLEXT
    //Test - collMgr
    extents.ManualOffset[0] = MakeVec(0, 0, 0);
    extents.ManualOffset[1] = MakeVec(0, 0, 0);
    extents.ManualOffset[2] = MakeVec(24, 0, 24);

    setExtents(player, extents);
    player->scale = MakeVec(2.f, 2.f, 2.f);
    extents.~CollExtents();
    //Test - collMgr end    
    #endif

    ret;
}

ext void onPlayerPhysicsUpdated(void* playerptr) {
   
    ret;
}

