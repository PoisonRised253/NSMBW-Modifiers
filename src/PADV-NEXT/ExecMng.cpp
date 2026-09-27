#include "PADV-NEXT/ExecMng.h"
const char* Signature = "\nIn some cases, extreme high blood sugar can lead to coma or death.\nOther risks include decreases in white blood cells, which can be serious,\ndizziness upon standing, seizures, trouble swallowing,\nand impaired judgement or motor skill\n";
int FrameTimer = 0;
ExecPhase currentPhase;
bool isInitialized = false;
bool isInStage = false;
dEn_c* smitePlayer = NULL;

dAcPy_c* Players[4] = {NULL};
dGameKeyCore_c* Inputs[4] = {NULL};
dBlower_c* Blowers[8] = {NULL};
const Modifier Mods[MODS_SIZE] = {
    Modifier(41, 1, 0, POST, (void (*)(void *))NahFuckThat, 0, (void *)true, true),
    Modifier(1, 1, 0, POST, (void (*)(void *))Lonely, TIMER_CLEAR, (void *)NULL, false),
    Modifier(2, 1, 0, ALL, (void (*)(void *))SpinEternally, 0, (void *)NULL, false),
    Modifier(3, 1, 0, PRE, (void (*)(void *))MiniPlusPlus, 0, (void *)NULL, false),
    Modifier(22, 1, 0, POST, (void (*)(void *))TowerFunc, 0, (void *)NULL, false),
    Modifier(4, 1, 0, POST, (void (*)(void *))MarioCantBreatheUnderwater, 0, (void *)NULL, false),
    Modifier(5, 1, 0, PRE, (void (*)(void *))SuperCold, 0, (void *)NULL, false),
    Modifier(6, 1, 0, PRE, (void (*)(void *))ShyRollers, 15, (void *)NULL, false),
    Modifier(24, 1, 0, POST, (void (*)(void *))TrustYourSenses, 0, (void *)NULL, false),

    Modifier(1, 2, 0, POST, (void (*)(void *))NoTakeBacks, 0, (void *)NULL, false),
    Modifier(2, 2, 0, POST, (void (*)(void *))Inverter, 0, (void *)NULL, false),
    Modifier(3, 2, 0, PRE, (void (*)(void *))LiterallyBulletHell, 0, (void *)NULL, false),
    Modifier(22, 2, 0, PRE, (void (*)(void *))WeGoWee, 0, (void *)NULL, false), 
    Modifier(4, 2, 0, POST, (void (*)(void *))SandyPain, 0, (void *)NULL, false),
    Modifier(5, 2, 0, POST, (void (*)(void *))PokeyLanParty, 0, (void *)NULL, false),
    Modifier(6, 2, 0, PRE, (void (*)(void *))FuckTwoSix, 0, (void *)NULL, false),
    Modifier(24, 2, 0, PRE, (void (*)(void *))FixRoys, 0, (void *)NULL, false), //Fixes Roy's endless loop by avoiding L:24,W:2,A:0
    Modifier(24, 2, 0, POST, (void (*)(void *))CastleBlowers, 6, (void *)(bool)dInfo_c::m_instance->m_startGameInfo.mArea, true), //Actual OverlayObject implementation, uses L:25 as a fake escape from Roy's A:0, also to seperate exec

    Modifier(1, 3, 0, PRE, (void (*)(void *))MarioSlide, 0, (void *)NULL, false),
    Modifier(2, 3, 0, PRE, (void (*)(void *))RealisticBullet, 0, (void *)NULL, false),
    Modifier(3, 3, 0, PRE, (void (*)(void *))Icey, 0, (void *)NULL, false),
    Modifier(21, 3, 0, POST, (void (*)(void *))BetterGhosts, 0, (void *)NULL, false),
    Modifier(22, 3, 0, PRE, (void (*)(void *))FloatyTower, 0, (void *)NULL, false),
    Modifier(4, 3, 0, PRE, (void (*)(void *))SlideyBlocks, 0, (void *)NULL, false),
    Modifier(5, 3, 0, PRE, (void (*)(void *))WierdLineBlock, 0, (void *)NULL, false),
    Modifier(24, 3, 0, PRE, (void (*)(void *))SnakeBlockFuckery, 0, (void *)NULL, false)
};

void ExecMng::Initialize() {
    Spawners::daIcicle_c::SetGlobalScale(1); //Run this to cache SMC's to avoid false base-data
    isInitialized = true;
    OSReport("PADV: %s\n", Signature);
    OSReport("PADV Initialization Completed\n");
}

//False = onNextScene
//True = onSceneCreate
void ExecMng::Reset(bool full) {
    //OSReport("Reset Type: %i\n", full);
    dSys_c::setFrameRate(1);
    ModifyMovement(0);
    
    if(!full) {
        dBaseActor_c* wmSwitchBroken = GetNextOfType(WM_SWITCH, NULL);
        if(wmSwitchBroken) {wmSwitchBroken->deleteRequest(); OSReport("Killed the Switch, hehe Killswitch\n");}
    }
    if(full) {
        for(int i = 0; i < dBlower_c::Capacity; i++) 
            {if(Blowers[i]) Blowers[i]->mDelayedDelete = true;} LivePatch(0x38600086, &LP_PARABOMBSPAWNID);
        *daBoo_c::getGlobalScaler() = 1.f;
        Spawners::daIcicle_c::SetGlobalScale(1);
    }

    dInfo_c *info = dInfo_c::getInstance();
    if(info) {
        info->clsStockItem(0);
        info->clsStockItem(1);
        info->clsStockItem(2);
        info->clsStockItem(3);
        info->clsStockItem(4);
        info->clsStockItem(5);
        info->clsStockItem(6);

        for (int i = 0; i < 100; i++)
        {
            info->addStockItem(0);
            info->addStockItem(1);
            info->addStockItem(2);
            info->addStockItem(3);
            info->addStockItem(4);
            info->addStockItem(5);
            info->addStockItem(6);
        }
        
        daPyMng_c::mRest[0] = 0x64;
        daPyMng_c::mRest[1] = 0x64;
        daPyMng_c::mRest[2] = 0x64;
        daPyMng_c::mRest[3] = 0x64;
    }
    OSReport("Passed on phase %i\n", full);
    return;
}

//BeginFrame, EndFrame
void ExecMng::Execute(ExecPhase phase) {
    if(!isInitialized) return;

    if (!GetPlayers() || !GetAllInputs()) return;
    isInStage = (bool)(dScStage_c::m_instance && Players[0] && Players[0]->mPos.x != 0);
    HandleHotkeys();
    currentPhase = phase;
    if (phase == PRE)
    {
        FrameTimer++;
        #ifdef DEBUG_EXEC_EXTREME
            OSReport("BeginFrame\n");
        #endif
        if(smitePlayer) {
            smitePlayer->mPos.y += -2048;
            smitePlayer = NULL;
        }
        AntiBubble();
    }
    else if(phase == POST) {
        if(FrameTimer > 60) FrameTimer = 0;
        #ifdef DEBUG_EXEC_EXTREME
            OSReport("EndFrame\n");
        #endif
    }
    if(!isInStage) return;
    for(int i = 0; i < MODS_SIZE; i++) {
        //OSReport("Running Mods %i\n", i);
        Mods[i].TryRun(phase);
    }

    for(int i = 0; i < dBlower_c::Capacity; i++) {
        if(Blowers[i] && Blowers[i]->Verify()) Blowers[i]->Execute();
    }

    Spawners::daIceAshibaSpawner_c* spawnah = (Spawners::daIceAshibaSpawner_c*)GetNextOfType(Spawners::daIceAshibaSpawner_c::actorID, NULL);
    if(spawnah) OSReport("Spawnah at %p\n", spawnah);

#ifdef DEBUG_EXEC_EXTREME
    OSReport("Frame: %i\n", FrameTimer);
    #ifdef DEBUG_PLAYERCOUNT
    OSReport("Players: %i, %i, %i, %i\n", (bool)Players[0], (bool)Players[1], (bool)Players[2], (bool)Players[3]);
#endif
#endif
    return;
}

//Execution Hooks
kmBranchDefCpp(0x800e4814, NULL, void, void) { ExecMng::Execute(PRE); }
kmBranchDefCpp(0x800e4874, NULL, void, void) { ExecMng::Execute(POST);}

kmBranchDefCpp(0x8015d82c, NULL, void, void) { ExecMng::Initialize(); }
kmBranchDefCpp(0x800bbbb4, NULL, void, void) { ExecMng::Reset(true);  }
kmBranchDefCpp(0x800e2030, NULL, void, void) { ExecMng::Reset(false); }

//Static Patch section
#ifdef DEBUG_PADV
kmWrite32(0x800F1960, INSTR_BLR); // Allow Debug (BLRs DeleteDebugMaterial)
#endif

kmWrite32(0x800e3ab8, 0x3c0001f4); // FuckTimers! | NO-OPs Timer Execution
kmWrite32(0x801591f0, 0x4e800020); // Disable1UpEffect! | Disables the 1Up Effect
kmWrite32(0x8010CDE0,  INSTR_BLR); // No Scores | NO-OPs ScoreManager Execution
kmWrite32(0x800b1910,  INSTR_BLR); // No Fukidashi | NO-OPs the Fuki Manager, to remove the pesky popups
kmWrite32(0x808efa70,  INSTR_BLR); // WMSWITCH is breaking the game, so this is a sort of tape-on fix, so i can keep developing. Something about res alloc. Idk and idc
kmWrite32(0x80907364,  INSTR_NOP); // Part 2 of ^^^ | Stops switch activation crash

//Deaht Mush Handling
kmWrite32(0x80a285f0,  INSTR_NOP); // Collect Items either way, for DeathMush Implementation
kmWrite32(0x80a285f4,  INSTR_NOP);
kmWrite32(0x80a285d4, 0x48000010);

#ifdef PADV_USE_MKWCAT_PATCHES
// No Death Pausing
kmWrite32(0x801410C4,  INSTR_NOP);
kmWrite32(0x801410D0,  INSTR_NOP);
kmWrite32(0x80141020,  INSTR_BLR);
kmWrite32(0x8013DA30,  INSTR_BLR);
kmWrite32(0x8013DB30,  INSTR_BLR);
kmWrite32(0x80150E54, 0x38600000); // li r3, 0
kmWrite32(0x80150E98, 0x38600000); // li r3, 0

// Exit Anywhere
kmWrite32(0x800B4EA8, 0x38600001); // li r3, 1

//Infinite Projectiles
kmWrite32(0x8011B0A4, 0x38600001);
kmWrite32(0x80124744, 0x38600001);
#else
kmWrite32(0x8004E050,  INSTR_BLR); // No Death Pause, pussy version
#endif
