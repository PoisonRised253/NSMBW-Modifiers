#include "Modifiers.h"

// 1 - 1
// Deletes all Enemies, Powerups, and some spare objects.
ext void Lonely()
{
    StageE4::instance->killAllEnemiesAtLevelEnd(0);
    dBase_c *objects[FIND_ENTS] = {NULL};
    objects[0] = GetNextOfType(EN_CLOUDLT, false);
    objects[1] = GetNextOfType(EN_REDRING, false);
    objects[2] = GetNextOfType(EN_COIN, false);
    objects[3] = GetNextOfType(EN_COIN_FLOOR, false);
    objects[4] = GetNextOfType(EN_COIN_JUMP, false);
    objects[5] = GetNextOfType(AC_BLOCK_COIN, false);
    objects[6] = GetNextOfType(CHUKAN_POINT, false);

    for (int i = 0; i < FIND_ENTS; i++)
        if (objects[i])
            objects[i]->Delete();

    ret;
}

// 1 - 2
// This is a reference to the song Spin Eternally in Beat Saber
ext void SpinEternally(bool anotherBoolLol)
{
    dAcPy_c *P;
    for (int i = 0; i < 4; i++)
    {
        P = (dAcPy_c *)Players[i];

        if (!P)
            continue;
        // P->initializeState_HipAttack(); This causes a funny, pressing up or down with this included causes mario to semi-permanently loose his collision
        if(anotherBoolLol)
        P->initializeState_SpinJump();
        if(!anotherBoolLol)
        P->executeState_SpinJump();
    }

    ret;
}

// 1 - 3
// Turns Mario Very Mini
ext void MiniPlusPlus()
{
    if (!Players[0])
        ret;

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;

        Players[i]->scale.x = 0.25f;
        Players[i]->scale.y = 0.25f;
        Players[i]->scale.z = 0.25f;
        *GetPlayerPowerState(Players[i]) = POWER_MINI;
    }

    ret;
}

// 1 - 22
// This function causes all Player's Y Velocity to be Limited, which means you cant jump as high, and fall slower.
// This makes 1-22/Tower pretty difficult.
// TODO: Make jumping even lower based on how many players are playing. This way it doesnt become easier with more people.
ext void TowerFunc()
{
    float maxY;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;

        volatile int *pow = GetPlayerPowerState(Players[i]);
        float speedY = Players[i]->speed.y;
        if (!pow)
            continue;

        if (*pow == POWER_PROPELLER)
            *pow = POWER_BIG;

        maxY = SPEEDCAP_TOWER;
        if (*pow == POWER_MINI)
            maxY = SPEEDCAP_TOWER_MINI;
        Players[i]->speed.y = clampf(speedY, -maxY, maxY);
        if (GetActiveRemocon()->heldButtons & WPAD_DOWN && *pow == POWER_MINI)
            Players[i]->speed.y = clampf(speedY, 0.055f, maxY);
    }
    ret;
}

// 1 - 4
// This function drains any existing water by moving it downwards...
// Also tries to make specifically Players[0] have higher swim speed, but might apply to all players.
ext void MarioCantBreathUnderwater()
{
    daPlBase_c *p = (daPlBase_c *)Players[0];
    const float dps = WATER_DRAIN / 60;
    const float sps = SWIM_MOD / 60;
    dEn_c *water = (dEn_c *)GetNextOfType(AC_BG_WATER, false);
    if (water)
        water->pos.y -= dps;
    if (p)
        p->WaterSwimSpeed = sps;

    ret;
}

// 1 - 5
// This function removes Velocity on the X axis.
// It replaces moving with positional change, which means Physics on the X axis are basically lost for the Player(s).
// This is currently very broken in multiplayer
ext void Linearity()
{
    dEn_c *playerButDifferentClass = NULL;
    const float precalcSpeed = SPEED_WATER_MOD / 60;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        // float* c = &dWaterManager_c::instance->current;
        Players[i]->max_speed.x = SPEED_WATER_MOD;
        playerButDifferentClass = (dEn_c *)Players[i];
        u32 btn = GetActiveRemocon()->heldButtons;
        float *p = &Players[i]->pos.x;

        if (btn & WPAD_RIGHT)
        {
            *p += precalcSpeed;
        }
        else if (btn & WPAD_LEFT)
        {
            *p += -precalcSpeed;
        }

        Players[i]->speed.x = 0;
        if (!playerButDifferentClass)
            continue;
        playerButDifferentClass->velocity1.y = 0;
        playerButDifferentClass->velocity2.y = 0;
    }
    ret;
}

// 1 - 6
// Make all Rolling Hills invisible
ext void ShyRollers()
{
    dStageActor_c *n = (dStageActor_c *)GetNextOfType(AC_FLOOR_GYRATION, false);
    for (int i = 0; i < 12; i++)
    {
        if (n && !n->visible)
            n = (dStageActor_c *)FindActorByType(AC_FLOOR_GYRATION, (Actor *)n);
        if (n)
            n->visible = false;
    }

    ret;
}

// 1 - Castle
// Simple but hard, turns Mario and Friends invisible, then in second stage (bossfight) makes the ground rotate
ext void TrustYourSenses()
{
    // Using Scale because Players[X]->visible doesnt work.
    float s = 0;
    if (!GetNextOfType(OBJ_LARRY, false))
        s = 0;
    else
        s = 1;

    for (int i = 0; i < 4; i++)
    {
        if (Players[i])
        {
            Players[i]->scale.x = s;
            Players[i]->scale.y = s;
            Players[i]->scale.z = s;
        }
    }

    dStageActor_c *n = (dStageActor_c *)GetNextOfType(OBJ_LARRY, false);
    for (int i = 0; i < 6; i++)
    {
        if (n)
        {
            n->rot.z += TYS_TURNSPEED;
            n = (dStageActor_c *)FindActorByType(OBJ_LARRY, (Actor *)n);
            continue;
        }
        else
        {
            n = NULL;
            ret;
        }
    }
    ret;
}

// 2 - 1: ModifyMovement(1);

// 2 - 2: ModifyMovement(4); + inside-out scaling. Makes the player face and go the wrong way.

// 2 - 3
// Replaces Fire-Piranha's fire with fucking large bullets. Hence the name
ext void LiterallyBulletHell()
{
    dEn_c *fireball = GetNextOfType(PAKKUN_FIREBALL, false);
    Vec pos, vel;
    S16Vec rot;
    u8 dir;

    if (!fireball)
        fireball = GetNextOfType(PAKKUN_FIREBALL, true);
    if (!fireball)
        ret;
    pos = fireball->pos;
    vel = fireball->speed;
    rot = fireball->rot;
    dir = fireball->direction;

    dEn_c *newSpawned = (dEn_c *)dStageActor_c::create(EN_MAGNUM_KILLER, 0, &pos, &rot, 0);
    if (newSpawned)
    {
        fireball->Delete(1);
        fireball = NULL;
        newSpawned->speed = vel;
        newSpawned->direction = dir;
        dEn_c *childLight = (dEn_c *)newSpawned->createChild((Actors)550, newSpawned, 0, &newSpawned->pos, 0, 2);
    }
}

// 2 - Tower (2-22)
// Disables Walljumping and Groundpound (TODO line 92)
ext void WeGoWee()
{
    for(int i = 0; i < 4; i++)
    {
        if(!Players[i]) continue;
        u8 sDir = Players[i]->collMgr.currentSlopeDirection;
        u32* state = GetMemberFromOffset(Players[i], 0x10D8);
        if(state && sDir == 2.f)
            LivePatch(0x50, state);
    }
}

// 2 - 4
// Disables moving rightward, requiring Wind to move.
ext void SandyPain()
{
    ModifyMovement(2);
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        DisablePropeller();
    }
    if (GetNextOfType(EN_DOSUN, false))
        ModifyMovement(0);
}

// 2 - 5
ext void PokeyParty()
{
    dSys_c::setFrameRate(2);
    LivePatch(0xbfffffff, LP_LEFTSPEED);
    LivePatch(0x3fffffff, LP_RIGHTSPEED);
    ret;
}

// I hate 2 - 6 lol
// This is likely to be very miserable. It turns the spinny platform invisible, cuz i hate that level so much.
// Why not sabotage it.
ext void FuckTwoSix()
{
    bool desiredState = CallSpacer(60);

    dEn_c *lcl = GetNextOfType(LINE_KINOKO_BLOCK, false);

    for (int i = 0; i < 4; i++)
    {
        if (!lcl)
            lcl = GetNextOfType(LINE_KINOKO_BLOCK, true);
        if (!lcl)
            ret;
        lcl->visible = desiredState;
    }
}



ext void CastleBlowers()
{
    if(!dScStage_c::instance()) ret;
    //if(&dScStage_c::instance()->area != NULL && dScStage_c::instance()->area != 255 && dScStage_c::instance()->area != 0) ret;
    static bool fuse = false;
    static bool JustSpawned = false;

    if(!fuse && dScStage_c::instance()->area == 255 && Players[0] && Players[0]->pos.x != 0) {
        dNext_c* n = dNext_c::get();
        if(!n) ret;
        fuse = true;

        dScStage_c::instance()->area = 0;
        dScStage_c::instance()->enteredLevel = 0x18;
        dInfo_c::m_instance->m_startGameInfo->level1 = 25;

        asm("li r7, 1");
        n->setChangeSceneNextDat(0x0, 0x2, 5);
        //n->simpleChangeScene(0x0, 0x2, 5); half-worked
        daPlBase_c* player = (daPlBase_c*)Players[0];
        if(!player) ret;
        player->changeNextScene(1);

        dScStage_c::instance()->setLoopType(0);
        dScStage_c::m_loopType = 0;
    }

    if(dScStage_c::instance()->area == 255) fuse = false;

    dStageActor_c *obj = GetNextOfType(AC_AUTOSCROOL_SWICH, false);
    if (!obj)
        GetNextOfType(AC_AUTOSCROOL_SWICH, true);
    if (!obj)
        ret;

    if (JustSpawned)
    {
        JustSpawned = false;
        ret;
    }

    if (IsNaN(obj->pos.x) || IsNaN(obj->pos.y))
        ret;

    Vec newPos = obj->pos;
    int which = obj->settings;
    JustSpawned = true;
    switch (which)
    {
    default:
        ret;
    case 1:
    {
        Vec area = MakeVec(32.f, 128.f, 0.f);
        dEnElevator_c::create(newPos, area, 64.f, 0);
        // CreateActor(EN_COIN_FLOOR, 0, newPos, 0, 0);
        obj->Delete(1);
        JustSpawned = true;
        which = 0;
        ret;
    }
    case 2:
    {
        Vec area = MakeVec(384.f, 320.f, 0.f);
        dEnElevator_c::create(newPos, area, 15.f, 0);
        // CreateActor(EN_COIN_FLOOR, 0, newPos, 0, 0);
        obj->Delete(1);
        JustSpawned = true;
        which = 0;
        ret;
    }
    }
}

// Unused stuff:
#ifdef DEBUG_UNUSED
// Mode false: preGameLoop();
// Mode true: postGameLoop();
// This function makes WorldMap like movement happen in levels.
// Currently unused
ext void Worldmapify(bool mode)
{
    if (!Players[0])
        ret;
    static const Vec noVec = {0, 0, 0};
    u32 h = 0;
    float x = 0;
    float y = 0;
    static float mAmt = 0;

    if (mAmt == 0)
    {
        int tempSpeed = MAP_SPEED;
        mAmt = tempSpeed = Round(clampf(tempSpeed / 60, 1, FLOAT_MAX));
    }

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;

        Players[i]->speed.x = 0;
        Players[i]->speed.y = 0;
        Players[i]->max_speed = noVec;

        if (mode == true)
        {
            h = GetActiveRemocon()->heldButtons;
            x = Players[i]->pos.x;
            y = Players[i]->pos.y;

            if (h & WPAD_UP)
                y += mAmt;
            if (h & WPAD_DOWN)
                y -= mAmt;
            if (h & WPAD_LEFT)
                x -= mAmt;
            if (h & WPAD_RIGHT)
                x += mAmt;
        }

        Players[i]->pos.x = Round(x);
        Players[i]->pos.y = Round(y);
        Players[i]->pos_delta = noVec;
        Players[i]->pos_delta2 = noVec;
        Players[i]->last_pos = Players[i]->pos;
    }

    ret;
}

#endif