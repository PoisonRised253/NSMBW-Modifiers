#include "Modifiers.h"

// TODO: Add Multiplayer Support
ext void SmallerAndNoYoshi()
{
    Players[0]->scale.x = 0.25f;
    Players[0]->scale.y = 0.25f;
    Players[0]->scale.z = 0.25f;
    Vec position = Players[0]->pos;
    position.y += 50;

    for (int i = 0; i < 4; i++)
    {
        dEn_c* itm = (dEn_c*)CreateActor(EN_ITEM, 0xF019, Players[0]->pos, 0, 0);
        if(itm) {
            itm->visible = false;
        }
        if (YoshiPtr[i])
            YoshiPtr[i] = NULL;
    }

    

    #ifdef DEBUG
    static int counter = 0x0;
    if(GetActiveRemocon()->heldButtons & WPAD_B) 
    {
        dItem_c* item = (dItem_c*)CreateActor(EN_ITEM,counter,position,0,0);
        OSReport("Item Spawn: %p, SETT: 0x%08X\n", &item, counter);
        counter++;
    }
    #endif
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
        Players[i]->last_pos = Players[i]->pos;
    }
    
    ret;
}

//This is a reference to the song Spin Eternally in Beat Saber
ext void SpinEternally() {
    dAcPy_c* P;
    P = (dAcPy_c*)Players[0];
    if(!P) ret;
        //P->initializeState_HipAttack(); This causes a funny, pressing up or down with this included causes mario to semi-permanently loose his collision
    P->initializeState_SpinJump();
    P->executeState_SpinJump();

    ret;
}

ext void Lonely() {
    StageE4::instance->killAllEnemiesAtLevelEnd(0);
    dBase_c* objects[FIND_ENTS] = {NULL};
    objects[0] = GetNextOfType(AC_FLOOR_GYRATION);
    objects[1] = GetNextOfType(AC_FLOOR_HOLE_DOKAN);
    objects[2] = GetNextOfType(AC_FLOOR_DOKAN_EIGHT);
    objects[3] = GetNextOfType(EN_CLOUDLT);
    objects[4] = GetNextOfType(EN_REDRING);
    objects[5] = GetNextOfType(EN_COIN);
    objects[6] = GetNextOfType(EN_COIN_FLOOR);
    objects[7] = GetNextOfType(EN_COIN_JUMP);
    objects[8] = GetNextOfType(AC_BLOCK_COIN);
    objects[9] = GetNextOfType(CHUKAN_POINT);

    for(int i = 0; i < FIND_ENTS; i++)
    if(objects[i]) objects[i]->Delete();
    

    ret;
}


