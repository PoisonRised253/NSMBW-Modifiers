#include "PADV-NEXT/Modifiers.h"

// 1 - 1
// Deletes all Enemies, Powerups, and some spare objects.
// May need a rework. Currently does not function as supposed
ext void Lonely()
{
    dActor_c *objects[10] = {NULL};
    objects[0] = GetNextOfType(EN_CLOUDLT, NULL);
    objects[1] = GetNextOfType(EN_REDRING, NULL);
    objects[2] = GetNextOfType(EN_COIN, NULL);
    objects[3] = GetNextOfType(EN_COIN_FLOOR, NULL);
    objects[4] = GetNextOfType(EN_COIN_JUMP, NULL);
    objects[5] = GetNextOfType(AC_BLOCK_COIN, NULL);
    objects[6] = GetNextOfType(CHUKAN_POINT, NULL);
    objects[7] = GetNextOfType(EN_KURIBO, NULL);
    objects[8] = GetNextOfType(EN_NOKONOKO, NULL);
    objects[9] = GetNextOfType(EN_ITEM, NULL);

    for (int i = 0; i < 10; i++)
        if (objects[i])
            objects[i]->deleteRequest();

    return;
}

// 1 - 2
// This is a reference to the song Spin Eternally in Beat Saber
// aka Hot Feet
ext void SpinEternally()
{
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        if (CompareAgainstInput(WPAD_BUTTON_LEFT, i)) continue;

        if(*checkGrounded(Players[i]))
            Players[i]->changeState(dAcPy_c::StateID_SpinJump);
    }

    return;
}

// 1 - 3
// Turns Mario Very Mini
ext void MiniPlusPlus()
{
    if (!Players[0])
        return;

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;

        Players[i]->mScale.x = 0.25f;
        Players[i]->mScale.y = 0.25f;
        Players[i]->mScale.z = 0.25f;
        *GetPlayerPowerState(Players[i]) = POWER_MINI;
    }

    return;
}

// 1 - 22
// This function causes all Player's Y Velocity to be Limited, which means you cant jump as high, and fall slower.
// This makes 1-22/Tower pretty difficult.
// TODO: Make jumping even lower based on how many players are playing. This way it doesnt become easier with more people.
ext void TowerFunc()
{
    DisableItem(POWER_PROPELLER, POWER_MINI);
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        int *pow = GetPlayerPowerState(Players[i]);
        if (!pow)
            continue;

        float speedY = Players[i]->mSpeed.y;

        if(*pow != POWER_MINI) goto Normal;
        goto Mini;

        Normal:
        Players[i]->mSpeed.y = clamp(speedY, -SPEEDCAP_TOWER, SPEEDCAP_TOWER);
        continue;

        Mini:
        float lower = -SPEEDCAP_TOWER_MINI;
        if (CompareAgainstInput(WPAD_BUTTON_LEFT, i)) lower = 0.055f;
        Players[i]->mSpeed.y = clamp(speedY, lower, SPEEDCAP_TOWER_MINI);
        continue;
    }
    return;
}

// 1 - 4
// This function drains any existing water by moving it downwards...
// Also tries to make specifically Players[0] have higher swim speed, but might apply to all players. <- This part has been lost, due to Moving from Kamek2013 to PropelParts
ext void MarioCantBreatheUnderwater()
{
    static const float dps = WATER_DRAIN / 60;
    static const float sps = SWIM_MOD / 60;
    dEn_c *water = (dEn_c *)GetNextOfType(AC_BG_WATER, false);
    if (water)
        water->mPos.y -= dps;
    return;
}

// 1 - 5
// Makes the Player slower, based on how fast theyre trying to go. Letting go of all directions causes a sort of Slingshot effect.
ext void SuperCold()
{
    const float precalcSpeed = SPEED_WATER_MOD / 60;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        float *p = &Players[i]->mPos.x;
        bool r = CompareAgainstInput(WPAD_BUTTON_UP, i), l = CompareAgainstInput(WPAD_BUTTON_DOWN, i);

        if (r)
            *p += precalcSpeed;
        if (l)
            *p += -precalcSpeed;

        Players[i]->mSpeed.x = 0;
    }
    return;
}

// 1 - 6
// Make all Rolling Hills invisible
ext void ShyRollers()
{
    dActor_c *n = (dActor_c *)GetNextOfType(AC_FLOOR_GYRATION, NULL);
    for (int i = 0; i < 6; i++)
    {
        if (n && !n->mVisible)
            n = (dActor_c *)GetNextOfType(AC_FLOOR_GYRATION, n);
        if (n)
            n->mVisible = false;
    }

    return;
}

// 1 - Castle
// Simple but hard, turns Mario and Friends invisible, then in second stage (bossfight) makes the ground rotate, to occasionally create slopes and wierd geometry.
// This should in theory be entirely softlock proof
ext void TrustYourSenses()
{
    // Using Scale because Players[X]->mVisible doesnt work.
    // Likely due to the fact that the Model is not directly attached to this actor itself, but instead its own class
    float s = 0;
    if (!GetNextOfType(OBJ_LARRY, false))
        s = 0;
    else
        s = 1;

    for (int i = 0; i < 4; i++)
    {
        if (Players[i])
        {
            Players[i]->mScale.x = s;
            Players[i]->mScale.y = s;
            Players[i]->mScale.z = s;
        }
    }

    dActor_c *n = (dActor_c *)GetNextOfType(OBJ_LARRY, NULL);
    for (int i = 0; i < 6; i++)
    {
        if (n)
        {
            n->mAngle.z += TYS_TURNSPEED;
            n = (dActor_c *)GetNextOfType(OBJ_LARRY, n);
            continue;
        }
        else
        {
            n = NULL;
            return;
        }
    }
    return;
}

// 2 - 1: ModifyMovement(1);
ext void NoTakeBacks() {
    DisableItem(POWER_PROPELLER, POWER_FIRE);
    ModifyMovement(1);
    return;
}

// 2 - 2: ModifyMovement(4); + inside-out scaling. Makes the player face and go the wrong way.
ext void Inverter() {
    DisableItem(POWER_PROPELLER, POWER_FIRE);
    ModifyMovement(4);
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        Players[i]->mScale.x = -1;
        Players[i]->mScale.z = -1;
    }
    return;
}

// 2 - 3
// Replaces Fire-Piranha's fire with fucking large bullets. Hence the name
// TODO: FIX DUPE | Completed
ext void LiterallyBulletHell()
{
    static bool justSpawned;
    if (justSpawned)
    {
        justSpawned = false;
        return;
    }

    dEn_c *fireball = GetNextOfType(PAKKUN_FIREBALL, false);
    Vec pos, vel;
    u8 dir;

    if (!fireball)
        return;

    dEn_c *newSpawned = (dEn_c *)dActor_c::construct(EN_MAGNUM_KILLER, 0, &fireball->mPos, &fireball->mAngle, 0);
    if (newSpawned)
    {
        justSpawned = true;
        newSpawned->mSpeed = fireball->mSpeed;
        newSpawned->mDirection = fireball->mDirection;

        fireball->deleteActor(1);
        fireball = NULL;
        dEn_c *childLight = (dEn_c *)newSpawned->createChild((Actors)550, newSpawned, 0, 0); //2 at end may break things
    }
}

// 2 - Tower (2-22)
// Disables Walljumping and Groundpound (TODO line 92)
// Broken
ext void WeGoWee()
{
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        u32 *state = GetMemberFromOffset(Players[i], 0x10D8);
        if (state && *state != 0x001BE000 && *state != 0x001B6000)
            LivePatch(0x50, state);
    }
}

// 2 - 4
// Disables moving rightward, requiring Wind to move.
// Uses thwomps in subareas to stop the effect | Broken on a leveldata-basis
ext void SandyPain()
{
    ModifyMovement(2);
    DisableItem(POWER_PROPELLER, POWER_FIRE);
    if (GetNextOfType(EN_DOSUN, false))
        ModifyMovement(0);
}

// 2 - 5
// we go fast... also artificial lag, in spirit of the average Nintendo Online experience at Mario Maker 2's peak.
ext void PokeyLanParty()
{
    dSys_c::setFrameRate(2);
    ModifyMovement(5);
    return;
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
            return;
        lcl->mVisible = desiredState;
    }
}

ext void FixRoys()
{
    dScStage_c* stage = dScStage_c::m_instance;
    if (!stage)
        return;

    if (dInfo_c::m_instance && dInfo_c::m_instance->m_startGameInfo.mArea != 1 && Players[0] && Players[0]->mPos.x != 0)
    {
        dNext_c *n = dNext_c::m_instance;
        if (!n)
            return;

        asm("li r7, 1");
        n->setChangeSceneNextDat(0x0, 0x2, dFader_c::FADER_BOWSER);
        daPlBase_c *player = (daPlBase_c *)Players[0];
        if (!player)
            return;
        player->changeNextScene(1);
        stage->mCurrAreaNo = 1;
        stage->mCurrCourse = 0x18;
        dInfo_c::m_instance->m_startGameInfo.mArea = 1;
    }
    return;
}

// TODO: PLEASE FIX HomeMenu pause exploit. | DONE
// TODO: Fix MP failure to die, when floating infinitely.
ext void CastleBlowers(bool isReady) {
    static bool JustSpawned = false;
    dActor_c *n = GetNextOfType(OBJ_ROY, NULL);
    for (int i = 0; i < 6; i++)
    {
        if (n)
        {
            n->mVisible = false;
            n = GetNextOfType(OBJ_ROY, n);
            continue;
        }
        else
        {
            n = NULL;
        }
    }

    dActor_c *obj = GetNextOfType(AC_AUTOSCROOL_SWICH, NULL);
    if (!obj)
        return;

    if (JustSpawned)
    {
        JustSpawned = false;
        return;
    }

    //if (IsNaN(obj->mPos.x) || IsNaN(obj->mPos.y))
    //    return;

    mVec3_c newPos = obj->mPos;
    int which = obj->mParam;
    if (which <= 0)
        return;
    JustSpawned = true;
    dBlower_c* blower;

    if (which == 1)
    {
        mVec2_c area = mVec2_c(8.75f, 2.f);
        blower = new dBlower_c(newPos, area, 12.f);
        area.~mVec2_c();
        goto skip;
    }
    else if (which == 2)
    {
        mVec2_c area = mVec2_c(16.f, 6.f);
        blower = new dBlower_c(newPos, area, 12.f);
        area.~mVec2_c();
        goto skip;
    }
    else if (which == 3)
    {
        mVec2_c area = mVec2_c(256.f, 64.f);
        blower = new dBlower_c(newPos, area, 32.f);
        area.~mVec2_c();
        goto skip;
    }
    else if (which == 4)
    {
        mVec2_c area = mVec2_c(96.f, 256.f);
        blower = new dBlower_c(newPos, area, 32.f);
        area.~mVec2_c();
        goto skip;
    }

    skip:
    obj->deleteRequest();
    JustSpawned = true;
    which = 0;
    return;
}

// A wordplay on Mario Run, the hit(n't) mobile game
// Not perfect, but itll do for now, optimize for gameplay later
ext void MarioSlide()
{
    for(int i = 0; i < 4; i++) {
        if(!Players[i]) continue;
        if(!Players[i]->mPos.x) continue;
        *GetPlayerPowerState(Players[i]) = POWER_PENGUIN;
        bool grounded = *checkGrounded(Players[i]);
        if(CompareAgainstInput(WPAD_BUTTON_RIGHT, i)) goto stop;
        if(CompareAgainstInput(WPAD_BUTTON_UP, i)) Players[i]->mDirection = DIR_LR_L;
        if(CompareAgainstInput(WPAD_BUTTON_DOWN, i)) Players[i]->mDirection = DIR_LR_R;

        
        if(grounded) {
            if(Players[i]->mDirection == DIR_LR_R) {
                Players[i]->mSpeed.x = clamp(Players[i]->mSpeed.x, 2.f, 128.f);
            } else {
                Players[i]->mSpeed.x = clamp(Players[i]->mSpeed.x, -2.f, -128.f);
            }
            if(*Players[i]->mStateMgr.getStateID() != dAcPy_c::StateID_PenguinSlide)
                Players[i]->changeState(dAcPy_c::StateID_PenguinSlide);
        }
        continue;

        stop:
        Players[i]->mSpeed.x = 0;
        Players[i]->mSpeedF = 0;
        continue; 
    }
}

// 3 - 2
// The Heavy Approves, plumber-tested.
// Maybe these bullets truely do cost $200 per shot.
ext void RealisticBullet()
{
    daBulletLauncher_c *launcher = NULL;
    for (int i = 0; i < 8; i++)
    {
        if (!launcher)
            launcher = (daBulletLauncher_c *)GetNextOfType(EN_KILLER_HOUDAI, NULL);
        if (!launcher) break;
        if (launcher)
        {
            *launcher->getCooldown() = clamp((int)*launcher->getCooldown(), 1, 10);
            *launcher->getAnimAllowShoot() = 0;
            launcher = (daBulletLauncher_c *)GetNextOfType(EN_KILLER_HOUDAI, launcher);
        }
    }

    dEn_c *bullet = GetNextOfType(EN_KILLER, NULL);
    if (!bullet)
        return;

    for (int i = 0; i < 40; i++)
    {
        if (bullet->mDirection == DIR_LR_L)
        {
            bullet->mPos.x -= 8;
        }
        else if (bullet->mDirection == DIR_LR_R)
        {
            bullet->mPos.x += 8;
        }

        bullet = (dEn_c *)GetNextOfType(EN_KILLER, bullet);
        if (bullet)
            continue;
        else
            return;
    }
}

//Under construction
ext void Icey()
{
    daIceAshibaBase_c* block = (daIceAshibaBase_c*)GetNextOfType(daIceAshibaBase_c::actorID_Rail, NULL);
    Spawners::daIcicle_c* icicle = (Spawners::daIcicle_c*)GetNextOfType(Spawners::daIcicle_c::actorID, NULL);
    if(!isInStage) return;
    Spawners::daIcicle_c::SetGlobalScale(2);
    
    for(int i = 0; i < 4; i++) {
        if(!block) break;
        *block->getPathingGoalPosition() = mVec2_c(Players[0]->mPos.x, Players[0]->mPos.y);
        block = (daIceAshibaBase_c*)GetNextOfType(daIceAshibaBase_c::actorID_Rail, block);        
    }

    for(int i = 0; i < 16; i++) {
        if(!icicle) break;
        icicle->SetFoot(0xFFFC);
        icicle = (Spawners::daIcicle_c*)GetNextOfType(Spawners::daIcicle_c::actorID, icicle);
    }
    return;
}

// 3 - G
// Yes, this is a test, not a joke
ext void BetterGhosts()
{
    *daBoo_c::getGlobalScaler() = 3.f;
    daBoo_c* boo = (daBoo_c*)GetNextOfType(daBoo_c::actorID, NULL);
    for(int i = 0; i < 8; i++) {
        if(!boo) break;
        boo->mSpeedF = 16;
        boo->mMaxSpeedF = 32;

        boo = (daBoo_c*)GetNextOfType(daBoo_c::actorID, boo);
    }
    return;
}

// 3 - T
// No solid idea yet, workin on it.
ext void FloatyTower()
{

}

// 3 - 4
// NO
ext void SlideyBlocks()
{
    u16 x, y;
    dBg_c *gm = dBg_c::m_bg_p;
    if (!gm)
        return;

    bool layers[3] = {gm->CheckExistLayer(-1), gm->CheckExistLayer(0), gm->CheckExistLayer(1)};

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        if (!Players[i]->mPos.x)
            return;
        x = ((u16)Players[i]->mPos.x) & 0xFFF0;
        y = ((u16)(-Players[i]->mPos.y)) & 0xFFF0;
        y -= 16;

        static const int spawnThisTileForFuckSake = 0;
        static const u16 PipeUpper = 0x006c;
        static const u16 PipeLower = 0x007c;

        u16 *NearestTiles[4] = {
            gm->__GetUnitPointer(x - 16, y, 0, NULL, NULL),
            gm->__GetUnitPointer(x + 16, y, 0, NULL, NULL),
            gm->__GetUnitPointer(x, y - 16, 0, NULL, NULL),
            gm->__GetUnitPointer(x, y + 16, 0, NULL, NULL)};

        if (*NearestTiles[0] != 0x0 && *NearestTiles[0] != PipeUpper && *NearestTiles[0] != PipeLower)
        {
            if(layers[0])gm->BgUnitChange(x - 16, y, -1, spawnThisTileForFuckSake);
            if(layers[1])gm->BgUnitChange(x - 16, y, 0, spawnThisTileForFuckSake);
            if(layers[2])gm->BgUnitChange(x - 16, y, 1, spawnThisTileForFuckSake);
            dActor_c::construct(SLIDE_BLOCK, 0, &MakeVec(Round(Players[i]->mPos.x - 16), Round(Players[i]->mPos.y), 0), &mAng3_c::Zero, 0);
        }

        if (*NearestTiles[1] != 0x0 && *NearestTiles[1] != PipeUpper && *NearestTiles[1] != PipeLower)
        {
            if(layers[0])gm->BgUnitChange(x + 16, y, -1, spawnThisTileForFuckSake);
            if(layers[1])gm->BgUnitChange(x + 16, y, 0, spawnThisTileForFuckSake);
            if(layers[2])gm->BgUnitChange(x + 16, y, 1, spawnThisTileForFuckSake);
            dActor_c::construct(SLIDE_BLOCK, 0, &MakeVec(Round(Players[i]->mPos.x + 16), Round(Players[i]->mPos.y), 0), &mAng3_c::Zero, 0);
        }

        if (*NearestTiles[3] != 0x0)
        {
            if(layers[0])gm->BgUnitChange(x, y + 16, -1, spawnThisTileForFuckSake);
            if(layers[1])gm->BgUnitChange(x, y + 16, 0, spawnThisTileForFuckSake);
            if(layers[2])gm->BgUnitChange(x, y + 16, 1, spawnThisTileForFuckSake);
            dActor_c::construct(SLIDE_BLOCK, 0, &MakeVec(Round(Players[i]->mPos.x), Round(Players[i]->mPos.y - 16), 0), &mAng3_c::Zero, 0);
        }
    }
    return;
}

// 3- 5
// This makes the Mushroom platform oscillate its rotation speed
ext void WierdLineBlock()
{
    static int state = 0;
    static bool flip = false;
    dRollingLinePlatform_c *platform = (dRollingLinePlatform_c *)GetNextOfType(dRollingLinePlatform_c::actorID, false);
    if (!platform || !CallSpacer(15))
        return;

    if (state > 30)
    {
        flip = true;
        state--;
        return;
    }
    if (state < -30)
    {
        flip = false;
        state++;
        return;
    }
    if (!flip)
    {
        *platform->getRotateSpeed() -= 15;
        state++;
    }
    else
    {
        *platform->getRotateSpeed() += 15;
        state--;
    }
    return;
}

// 3 - C
// This Generates holes within the snake block each second
// Also makes balls funny. Yes, that is infact a proper descirption of what this does...
ext void SnakeBlockFuckery()
{
    LivePatch(0x38600232, &LP_PARABOMBSPAWNID);
    daLemmyBall_c* ball = (daLemmyBall_c*)GetNextOfType(daLemmyBall_c::actorID, NULL);
    for(int i = 0; i < 8; i++) {
        if(ball) {
            ball->setHitbox(2);
            ball = (daLemmyBall_c*)GetNextOfType(daLemmyBall_c::actorID, ball);
        } else break;
    }

    if (!CallSpacer(30))
        return;
    daSnakeBlock_c *s = (daSnakeBlock_c *)GetNextOfType(daSnakeBlock_c::actorID, NULL);
    if (s) s->GenerateHoleNow();
    return;
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