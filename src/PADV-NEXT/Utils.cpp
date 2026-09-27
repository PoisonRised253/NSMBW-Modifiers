#include "PADV-NEXT/Utils.h"

int currentMoveMod = 0;

ext bool GetAllInputs() {
    dGameKey_c* keyBase = dGameKey_c::m_instance;
    if(!keyBase) return false;
    Inputs[0] = keyBase->mRemocon[0];
    Inputs[1] = keyBase->mRemocon[1];
    Inputs[2] = keyBase->mRemocon[2];
    Inputs[3] = keyBase->mRemocon[3];
    return true;
}

ext dGameKeyCore_c* CompareToInputs(const int mask) {
    if (Inputs[0] && ((Inputs[0]->mPrevHoldButtons & mask) == mask) || ((Inputs[0]->mPrevDownButtons & mask) == mask))
        return Inputs[0];
    if (Inputs[1] && ((Inputs[1]->mPrevHoldButtons & mask) == mask) || ((Inputs[1]->mPrevDownButtons & mask) == mask))
        return Inputs[1];
    if (Inputs[2] && ((Inputs[2]->mPrevHoldButtons & mask) == mask) || ((Inputs[2]->mPrevDownButtons & mask) == mask))
        return Inputs[2];
    if (Inputs[3] && ((Inputs[3]->mPrevHoldButtons & mask) == mask) || ((Inputs[3]->mPrevDownButtons & mask) == mask))
        return Inputs[3];

    return NULL;
}

ext bool CompareAgainstInput(int mask, int controller) {
    if(!Inputs[controller]) return false;
    return ((Inputs[controller]->mPrevHoldButtons & mask) == mask) || ((Inputs[controller]->mPrevDownButtons & mask) == mask);
}

ext bool GetPlayers()
{
    Players[0] = GetSpecificPlayerActor(0);
    Players[1] = GetSpecificPlayerActor(1);
    Players[2] = GetSpecificPlayerActor(2);
    Players[3] = GetSpecificPlayerActor(3);
    //if(Players[0] || Players[1] || Players[2] || Players[3]);
    return Players[0];
}

ext dEn_c *GetNextOfType(Actors actorID, void* start)
{
    return (dEn_c *)fManager_c::searchBaseByProfName(actorID, (fBase_c*)start);
}

// 0 = Mushroom | 0x00
// 1 = FireFlower | 0x09
// 2 = IceFlower | 0x0E
// 3 = Penguin | 0x11
// 4 = Propeller | 0x15
// 5 = Mini | 0x19
// 6 = Star | 0x01
// 7 = 1-Up | 0x07
// 8 = Normal-Sized Mini | 0x79
ext int GetPowerupType(u32 settings)
{
    u32 b = settings & 0xF; // last two bits only
    switch (b)
    {
    case 0x00:
        return 0;
    case 0x09:
        return 1;
    case 0x0E:
        return 2;
    case 0x11:
        return 3;
    case 0x15:
        return 4;
    case 0x19:
        return 5;
    case 0x01:
        return 6;
    case 0x07:
        return 7;
    case 0x79:
        return 8;
    default:
        return 0;
    }
}

// Live-Patch
volatile void LivePatch(u32 newInstr, void *addr)
{
    *(u32*)addr = newInstr;
#ifdef DEBUG_LP
    if (*addr != newInstr)
    {
        OSReport("LPIns Failure! Val: %p, At: %p\n", *addr, addr);
        return;
    }
    else
        OSReport("LPIns Success at: %p\n", addr);
#endif

    DCFlushRange(addr, 4);
    ICInvalidateRange(addr, 4);
    return;
}

// Modes:
// 0 = Restore
// 1 = Disable Left
// 2 = Disable Right
// 3 = Disable Jump
// 4 = Inverse
// 5 = Maximum
ext void ModifyMovement(int mode)
{
    if (mode == currentMoveMod)
        return;

    currentMoveMod = mode;
    if (mode == 0)
    {
        LivePatch(0xa0030004, &LP_AUTOHOLDDOWN);
        LivePatch(DEFAULT_SPEED_LEFT, &LP_LEFTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, &LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_JUMP, &LP_INITIALJUMPSPEED);
        return;
    }

    if (mode == 1 && *(u32 *)&LP_LEFTSPEED != 0)
    {
        LivePatch(0, &LP_LEFTSPEED);
        return;
    }

    if (mode == 2 && *(u32 *)&LP_RIGHTSPEED != 0)
    {
        LivePatch(0, &LP_RIGHTSPEED);
        return;
    }

    if (mode == 3 && *(u32 *)&LP_INITIALJUMPSPEED)
    {
        LivePatch(0, &LP_INITIALJUMPSPEED);
        return;
    }

    if (mode == 4)
    {
        LivePatch(DEFAULT_SPEED_LEFT, &LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, &LP_LEFTSPEED);

        return;
    }

    if (mode == 5)
    {
        LivePatch(0xbfffffff, &LP_LEFTSPEED);
        LivePatch(0x3fffffff, &LP_RIGHTSPEED);

        return;
    }

    return;
}

// Triggers at L: 41, W: 1, A: 255, because funny!
// This will remove all instances of dAc_Py_c, which means the game refuses to commit video game.
ext void NahFuckThat(bool delP1)
{
    if (delP1)
    {
        if (Players[0])
        {
            Players[0]->deleteActor(1);
            OSReport("NahFuckThat() ran. Which means a softlock, this is intentional, and Pretty Funny.\n");
#ifdef NO_MP
            OSReport("When this message appears, it likely means that you tried Playing with Multiple People.\n This is not supported in the current Build.");
#endif
        }
    }

    if (Players[1])
        Players[1]->deleteActor(1);
    if (Players[2])
        Players[2]->deleteActor(1);
    if (Players[3])
        Players[3]->deleteActor(1);

    return;
}

/*ext bool ObjectBoundCheck(mVec3_c boundsMin, mVec3_c boundsMax, mVec3_c pos)
{
    bool xWithin = false, yWithin = false;

    if (pos.x > boundsMin.x && pos.x < boundsMax.x)
        xWithin = true;
    if (pos.y > boundsMin.y && pos.y < boundsMax.y)
        yWithin = true;

#ifdef DEBUG_BOUNDS
    OSReport("IsWithin: %i\n", xWithin && yWithin);
#endif
    return(xWithin && yWithin);
}

ext bool ObjectBoundCheck(mVec4_c boundsA, mVec4_c boundsB)
{
    return !(
        boundsA.x + boundsA.z < boundsB.x - boundsB.z ||
        boundsA.x - boundsA.z > boundsB.x + boundsB.z ||
        boundsA.y + boundsA.w < boundsB.y - boundsB.w ||
        boundsA.y - boundsA.w > boundsB.y + boundsB.w);
}*/

int FindNextFreeArrayEntry(void *arr[], int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == NULL)
            return i;

    return 0xFFFF;
}

int FindPointerInArray(void *arr[], int size, void *ptr)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == ptr)
            return i;

    return 0xFFFF;
}

ext bool *isDemo(dAcPy_c *player) { return (bool *) GetMemberFromOffset(player, 0x1460); }
ext int *GetPlayerPowerState(dAcPy_c *player) { return (int *) GetMemberFromOffset(player, 0x14E0); }
ext int *checkGrounded(dAcPy_c *player) { return (int *) GetMemberFromOffset(player, 0x10D4); }
ext int *checkAllowedMoves(dAcPy_c *player) { return (int *) GetMemberFromOffset(player, 0x10D8); }
ext int *GetPlayerState(dAcPy_c *player) { return (int *) GetMemberFromOffset(player, 0x1478); }

ext bool isPause()
{
    PauseManager_c *instance = PauseManager_c::m_instance;
    if (!instance)
        return false;
    return (bool)*GetMemberFromOffset(instance, 0x4);
}

// Entirely made by ChatGPT, still dont know how to bitshift, someone please teach me
inline u32 NoJumping(u32 value)
{
    u32 x = (value >> 24) & 0xFF;
    if (x == 1 || x == 3)
        x = 0;
    return((value & 0x00FFFFFF) | (x << 24));
}

ext void DisableItem(u32 ItemID, u32 replaceWith)
{
    volatile int *itm = NULL;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        itm = GetPlayerPowerState(Players[i]);
        if (itm && *itm == ItemID)
            *itm = replaceWith;
    }
    return;
}

ext void SetUpper(u32 *variable, u16 value)
{
    u32 val = *variable;
    val &= 0x0000FFFF;
    val |= (value << 16);
    *variable = val;
}

ext void SetLower(u32 *variable, u16 value)
{
    u32 val = *variable;
    val &= 0xFFFF0000;
    val |= value;
    *variable = val;
}

#ifdef DEBUG_PADV
ext void DumpPlayer(int which)
{
    if (!Players[which])
    {
        OSReport("DumpPlayer: Player %i does not Exist\n", which);
        return;
    }
    OSReport("\n--------------------------------------\n---Player %i Dump:---\n---Power: %p---\n---IsDemo: %i---\n---IsPause: %i---\n---IsGrounded: %i---\n---State: %p---\n---Level: %i---\n---World: %i---\n---Area: %i---\n--------------------------------------\n\n", which, *GetPlayerPowerState(Players[which]), *isDemo(Players[which]), isPause(), (bool)*checkGrounded(Players[which]), *checkAllowedMoves(Players[which]), dScStage_c::m_instance->mCurrCourse, dScStage_c::m_instance->mCurrWorld, dScStage_c::m_instance->mCurrAreaNo);
    return;
}
#endif

ext void HandleHotkeys()
{
    if (!Players[0])
        return;
#ifdef DEBUG_PADV
    for(int i = 0; i < 4; i++) {
        const int dumpPlayer = WPAD_BUTTON_B | WPAD_BUTTON_1;
        bool active = CompareAgainstInput(dumpPlayer, i);
        if(active)
        {
            DumpPlayer(i);
        }
    }

#ifdef DEBUG_BALLS
    if (CallSpacer(15))
        FondleBalls();
#endif

#ifdef DEBUG_EXPERIMENTS_
    if (!CallSpacer(6))
        return;
    static const mVec3_c pos = MakeVec(1486, -475, 3000);
    static int selected = 0;
    const int spawnActor = WPAD_A | WPAD_ONE;
    if ((btns & spawnActor) == spawnActor)
    {
        OSReport("Spawning: %i\n", selected);
        dStageActor_c *spawned = CreateActor(selected, 0, pos, 0, 0);
        if (spawned)
            OSReport("Spawned %i at %p", selected, spawned);
    }

    const int changeActorUP = WPAD_A | WPAD_UP;
    const int changeActorDOWN = WPAD_A | WPAD_DOWN;
    if ((btns & changeActorUP) == changeActorUP)
    {
        selected++;
        OSReport("Selected is now: %i\n", selected);
    }
    if ((btns & changeActorDOWN) == changeActorDOWN)
    {
        selected--;
        OSReport("Selected is now: %i\n", selected);
    }

#endif
#endif
    return;
}

/*ext dEn_c *GetNearestPlayer(mVec3_c relativeTo)
{
    dEn_c *Winner = NULL;
    float bestDist = 1000.f;

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        Vec2 res = DistSq(relativeTo, Players[i]->pos);
        float current = res.x + res.y;
        if (current < bestDist && current > 0.0125f)
        {
            bestDist = current;
            Winner = (dEn_c *)Players[i];
        }
    }

    return Winner;
}*/

ext void WrapNumber(u32& value, u32 min, u32 max)
{
    if (value >= max)
        value = min;
    else if (value <= min)
        value = max;
    return;
}

ext static const u32 CreateLoadImmediate(u8 reg, u16 val) {
    return (0x38000000 | (reg << 21) | val);
}

ext void AntiBubble()
{
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        if (*GetPlayerState(Players[i]) != STATEID_BALLOON)
            continue;
        dAcPy_c *p = Players[clamp<int>(i - 1, 0, 3)];
        dAcPy_c *p2 = Players[clamp<int>(i + 1, 0, 3)];

        if (i > 0 && p != NULL)
        {
            Players[i]->mPos = VecAdd(p->mPos, MakeVec(0, 8.f, 0));
            Players[i]->mScale = MakeVec(0, 0, 0);
        }
        else if (p2)
        {
            Players[i]->mPos = VecAdd(p2->mPos, MakeVec(0, 8.f, 0));
            Players[i]->mScale = MakeVec(0, 0, 0);
        }
        dEn_c *bubble = GetNextOfType(EN_HATENA_BALLOON, NULL);
        if (!bubble)
            continue;
        bubble->mVisible = false;
        bubble->mPos = Players[i]->mPos;
    }
    return;
}

#ifdef DEBUG_BALLS
#include "daEnemies_c.h"

ext void FondleBalls()
{
    static u32 inputCounter = 0;
    static bool staticness = false;
    const int maskUp = WPAD_UP | WPAD_A;
    const int maskDown = WPAD_DOWN | WPAD_A;
    u32 btn = GetActiveRemocon()->heldButtons;
    daLemmyBall_c *ball = (daLemmyBall_c *)GetNextOfType(EN_BOUNCE_BALL, false);
    if (!ball)
        daLemmyBall_c *ball = (daLemmyBall_c *)GetNextOfType(EN_BOUNCE_BALL, true);
    if (!btn || !ball)
    {
        return;
    }

    if ((btn & maskUp) == maskUp)
        inputCounter++;
    else if ((btn & maskDown) == maskDown)
        inputCounter--;
    else if (btn & WPAD_B)
    {
        ball->setStatic(!staticness);
        staticness = !staticness;
    }
    else
        return;

    inputCounter = clamp((int)inputCounter, 0, 7);
    ball->setHitbox(inputCounter);
    OSReport("BallSizer() State: %i\n", inputCounter);
    return;
}
#endif