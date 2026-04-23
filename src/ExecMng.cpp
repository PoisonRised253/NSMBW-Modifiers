#include "ExecMng.h"

dEnElevator_c *elevators[CO_ARRAY_SIZE];

// 0 = pre
// 1 = exec
// 2 = post
void dExecMng_c::DRYExecute(int stage)
{    
    if(isPause()) ret;
    
    RunCustom(stage);
    switch(stage) {
        case 0: {
            preGameLoop();
            ret;
        }

        case 1: {
            onGameLoop();
            ret;
        }

        case 2: {
            ret;
        }
    } 
    ret;
}

void dExecMng_c::Reset()
{
    for (int i = 0; i < CO_ARRAY_SIZE; i++)
    {
        if (elevators[i])
            elevators[i]->Delete(1);
        elevators[i] = NULL;
    }
}

void dExecMng_c::Register(dStageActor_c* obj, int typeID, bool force) {
    if(!obj) ret;
    int freeSlot = 0;

    switch(typeID) {
        default: {
            #ifdef DEBUG
            OSReport("Register() failed, Unknown Type\n"); 
            #endif
            ret;
        }

        case 0: {
            freeSlot = GetNextFreeArrayEntry(elevators, CO_ARRAY_SIZE);
            if(freeSlot == 0xFFFF && force) freeSlot = 0;
            else if (freeSlot == 0xFFFF && !force) {
                #ifdef DEBUG
                    OSReport("Register() failed, Full Array without Force\n");
                #endif
                ret;
            }
            elevators[freeSlot] = (dEnElevator_c*)obj;
            #ifdef DEBUG
                OSReport("Registered an Elevator at Arr + %i\n", freeSlot);
            #endif
            ret;
        }
    }
}

//This function is made this way, to avoid too much compiled size.
//Also i dont like virtual calls, so like... you wont be seeing them here
void dExecMng_c::RunCustom(int action) {
    for(int i = 0; i < CO_ARRAY_SIZE; i++) {
        if (action == 0 && elevators[i]) {elevators[i]->beforeExecute();}
        if (action == 1 && elevators[i]) {elevators[i]->execute();}
        if (action == 2 && elevators[i]) {elevators[i]->afterExecute();}
    }
}