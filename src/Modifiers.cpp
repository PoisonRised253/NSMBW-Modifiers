#include "Modifiers.h"

// TODO: Add Multiplayer Support
ext void SmallerAndNoYoshi()
{
    if(!Players[0]) ret;
    bool fullRun = CallSpacer(30);
    static daYoshi_c *yoshis[4];

    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;

        Players[i]->scale.x = 0.25f;
        Players[i]->scale.y = 0.25f;
        Players[i]->scale.z = 0.25f;

        if (fullRun && Players[i]->speed.x)
        {
            dEn_c *itm = (dEn_c *)CreateActor(EN_ITEM, 0xF019, Players[i]->pos, 0, 0);
            if (itm)
            {
                itm->visible = false;
            }
        }
    }

    if (fullRun)
    {
        yoshis[0] = (daYoshi_c *)GetNextOfType(YOSHI, false);
        if (yoshis[0])
            yoshis[1] = (daYoshi_c *)FindActorByType(YOSHI, (Actor *)yoshis[0]);
        if (yoshis[1])
            yoshis[2] = (daYoshi_c *)FindActorByType(YOSHI, (Actor *)yoshis[1]);
        if (yoshis[2])
            yoshis[3] = (daYoshi_c *)FindActorByType(YOSHI, (Actor *)yoshis[2]);

        if (yoshis[0])
            yoshis[0]->id = 0;
        if (yoshis[1])
            yoshis[1]->id = 0;
        if (yoshis[2])
            yoshis[2]->id = 0;
        if (yoshis[3])
            yoshis[3]->id = 0;
    }
    ret;
}

// Triggers at L: 41, W: 1, A: 255, because funny!
// This will remove all instances of dAc_Py_c, which means the game refuses to commit video game.
ext void NahFuckThat(bool delP1)
{
    if (delP1)
    {
        OSReport("NahFuckThat() ran. Which means a softlock, this is intentional, and Pretty Funny.\n");
#ifdef NO_MP
        OSReport("When this message appears, it likely means that you tried Playing with Multiple People.\n This is not yet supported.");
#endif
        if (Players[0])
            Players[0]->Delete(1);
    }

    if (Players[1])
        Players[1]->Delete(1);
    if (Players[2])
        Players[2]->Delete(1);
    if (Players[3])
        Players[3]->Delete(1);

    ret;
}

// This function causes all Player's Y Velocity to be Limited, which means you cant jump as high, and fall slower.
// This makes 22-1 pretty difficult.
ext void TowerFunc()
{
    dEn_c* item = GetNextOfType(EN_ITEM, false);
    if(item) {
        if(GetPowerupType(item->settings) == 4)
        item->Delete(1);
    }
    float maxY;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        float speedY = Players[i]->speed.y;

        maxY = SPEEDCAP_TOWER;
        if (MarPow == 0x03)
            maxY = SPEEDCAP_TOWER_MINI;
        Players[i]->speed.y = clampf(speedY, -maxY, maxY);
        if (GetActiveRemocon()->heldButtons & WPAD_DOWN && MarPow == 0x03)
            Players[i]->speed.y = clampf(speedY, 0.055f, maxY);
    }
    ret;
}

// This function removes Velocity.
// It replaces moving with positional change, which means Physics on the X axis are basically lost for the Player(s).
ext void Linearity()
{
    const float precalcSpeed = SPEED_WATER_MOD / 60;
    for (int i = 0; i < 4; i++)
    {
        if (!Players[i])
            continue;
        // float* c = &dWaterManager_c::instance->current;
        Players[i]->max_speed.x = SPEED_WATER_MOD;
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
    }
    ret;
}

// Mode false: preGameLoop();
// Mode true: postGameLoop();
// This function makes WorldMap like movement happen in levels.
ext void Worldmapify(bool mode)
{
    if (!Players[0])
        ret;
    const Vec noVec = {0, 0, 0};
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

// This is a reference to the song Spin Eternally in Beat Saber
ext void SpinEternally()
{
    dAcPy_c *P;
    P = (dAcPy_c *)Players[0];
    if (!P)
        ret;
    // P->initializeState_HipAttack(); This causes a funny, pressing up or down with this included causes mario to semi-permanently loose his collision
    P->initializeState_SpinJump();
    P->executeState_SpinJump();

    ret;
}

ext void Lonely()
{
    StageE4::instance->killAllEnemiesAtLevelEnd(0);
    dBase_c *objects[FIND_ENTS] = {NULL};
    objects[0] = GetNextOfType(AC_FLOOR_GYRATION, false);
    objects[1] = GetNextOfType(AC_FLOOR_HOLE_DOKAN, false);
    objects[2] = GetNextOfType(AC_FLOOR_DOKAN_EIGHT, false);
    objects[3] = GetNextOfType(EN_CLOUDLT, false);
    objects[4] = GetNextOfType(EN_REDRING, false);
    objects[5] = GetNextOfType(EN_COIN, false);
    objects[6] = GetNextOfType(EN_COIN_FLOOR, false);
    objects[7] = GetNextOfType(EN_COIN_JUMP, false);
    objects[8] = GetNextOfType(AC_BLOCK_COIN, false);
    objects[9] = GetNextOfType(CHUKAN_POINT, false);

    for (int i = 0; i < FIND_ENTS; i++)
        if (objects[i])
            objects[i]->Delete();

    ret;
}

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

ext void ShyRollers()
{
    dStageActor_c *n = (dStageActor_c *)GetNextOfType(AC_FLOOR_GYRATION, false);
    for(int i = 0; i < 12; i++) {
        if(n && !n->visible) n = (dStageActor_c*)FindActorByType(AC_FLOOR_GYRATION, (Actor*)n);
        if(n) n->visible = false;
    }
   
    ret;
}

//Simple but hard
ext void TrustYourSenses() {
    //Using Scale because Players[X]->visible doesnt work.
    float s = 0;
    if(!GetNextOfType(OBJ_LARRY, false)) s = 0;
    else s = 1;

    for(int i = 0; i < 4; i++) {
        if(Players[i]) { 
            Players[i]->scale.x = s;
            Players[i]->scale.y = s;
            Players[i]->scale.z = s;
        }
    }


    dStageActor_c *n = (dStageActor_c *)GetNextOfType(OBJ_LARRY, false);
    for(int i = 0; i < 6; i++) {
        if(n) {
            n->rot.z += TYS_TURNSPEED;
            n = (dStageActor_c*)FindActorByType(OBJ_LARRY, (Actor*)n);
            continue;
        } 
        else {
            n = NULL;
            ret;
        }
    }
    ret;
}

//Modes:
//0 = Restore
//1 = Disable Left
//2 = Disable Right
//3 = Disable Jump
//4 = Inverse
ext void ModifyMovement(int mode) {

    if(mode == 0) {
        LivePatch(DEFAULT_SPEED_LEFT, LP_LEFTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_JUMP, LP_INITIALJUMPSPEED);
        ret;
    } 

    if(mode == 1 && *LP_LEFTSPEED != 0) {
        LivePatch(0, LP_LEFTSPEED); ret; }

    if(mode == 2 && *LP_RIGHTSPEED != 0) {
        LivePatch(0, LP_RIGHTSPEED); ret; }
    
    if(mode == 3 && *LP_INITIALJUMPSPEED) {
        LivePatch(0, LP_INITIALJUMPSPEED); ret; }

    if(mode == 4) {
        LivePatch(DEFAULT_SPEED_LEFT, LP_RIGHTSPEED);
        LivePatch(DEFAULT_SPEED_RIGHT, LP_LEFTSPEED);
        
        ret;
    }

    
    
    ret;
}
