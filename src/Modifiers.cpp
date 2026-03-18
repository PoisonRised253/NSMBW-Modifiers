#include "Modifiers.h"

// Mario is experiencing extreme grow sprout!!!
ext void Grow()
{
    if (!Players[0])
        ret;
    Players[0]->scale.y += 0.00125f;
    ret;
}

// The Red Plumber Man Lied!
ext void Shrink()
{
    if (!Players[0])
        ret;
    Players[0]->scale.y -= 0.00125f;
    ret;
}

// TODO: Add Multiplayer Support
ext void SmallerAndNoYoshi()
{
    Players[0]->scale.x = 0.25f;
    Players[0]->scale.y = 0.25f;
    Players[0]->scale.z = 0.25f;

    for (int i = 0; i < 4; i++)
    {
        if (YoshiPtr[i])
            YoshiPtr[i] = NULL;
    }
    MarPow = 0x03;
    OSReport("MP: %d, LP: %d, YTP: %d, BTP: %d\n", MarPow, LuiPow, YTPow, BTPow);
    ret;
}

//Triggers at L: 41, W: 1, A: 255, because funny!
//This will remove all instances of dAc_Py_c, which means the game refuses to commit video game.
ext void NahFuckThat(bool delP1)
{
    if(delP1) {
        OSReport("NahFuckThat() ran. Which means a softlock, this is intentional, and Pretty Funny.\n");
    #ifdef NO_MP
        OSReport("When this message appears, it likely means that you tried Playing with Multiple People.\n This is not yet supported.");
    #endif
    if (Players[0]) Players[0]->Delete(1);
    }

    if (Players[1])
        Players[1]->Delete(1);
    if (Players[2])
        Players[2]->Delete(1);
    if (Players[3])
        Players[3]->Delete(1);

    ret;
}

//This function causes all Player's Y Velocity to be Limited, which means you cant jump as high, and fall slower.
//This makes 22-1 pretty difficult.
ext void TowerFunc() {
    float maxY;
    for(int i = 0; i < 4; i++)
    {
        if(!Players[i]) continue;
        float speedY = Players[i]->speed.y;
        
        maxY = SPEEDCAP_TOWER;
        if(MarPow == 0x03) maxY = SPEEDCAP_TOWER_MINI;
        Players[i]->speed.y = clampf(speedY, -maxY, maxY);
        if(GetActiveRemocon()->heldButtons & WPAD_DOWN && MarPow == 0x03)
        Players[i]->speed.y = clampf(speedY, 0.055f, maxY);
    }
    ret;
}

//This function removes Velocity. 
//It replaces moving with positional change, which means Physics on the X axis are basically lost for the Player(s).
ext void WaterLevel() {
    for(int i = 0; i < 4; i++) {
        if(!Players[i]) continue;
        // float* c = &dWaterManager_c::instance->current;
        Players[i]->max_speed.x = SPEED_WATER_MOD;
        float* p = &Players[i]->pos.x;
        Players[i]->speed.x = 0;
        if(GetActiveRemocon()->heldButtons & WPAD_RIGHT) {*p += SPEED_WATER_MOD / 60; continue;}
        if(GetActiveRemocon()->heldButtons & WPAD_LEFT) {*p += -(SPEED_WATER_MOD / 60); continue;}
    }
    ret;
}

//Mode false: preGameLoop();
//Mode true: postGameLoop();
//This function makes WorldMap like movement happen in levels.
ext void Worldmapify(bool mode) {
    if(!Players[0]) ret;
    const Vec noVec = {0,0,0};
    u32 h = 0;
    float x = 0;
    float y = 0;
    static float mAmt = 0;

    if(mAmt == 0) {
        int tempSpeed = MAP_SPEED;
        mAmt = tempSpeed = Round(clampf(tempSpeed / 60, 1, FLOAT_MAX));
    }

    for (int i = 0; i < 4; i++)
    {
        if(!Players[i]) continue;

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
    }
    
    ret;
}

//This is a reference to the song Spin Eternally in Beat Saber
ext void SpinEternally() {
    dAcPy_c* P;
    Remocon* s = GetActiveRemocon();
    if(s)
        s->isShaking = 1;
    P = (dAcPy_c*)Players[0];
    if(P) {
        //P->initializeState_HipAttack(); This causes a funny, pressing up or down with this included causes mario to semi-permanently loose his collision
        P->initializeState_SpinJump();
        P->executeState_SpinJump();
    }

    ret;
}

