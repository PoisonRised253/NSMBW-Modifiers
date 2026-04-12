#ifndef __H_COMAN
#define __H_COMAN

#include "Utils.h"
#include "customObjects.h"

#define CO_ARRAY_SIZE 32
extern dEnElevator_c* elevators[CO_ARRAY_SIZE];

class dExecMng_c {
    private:
    static void DRYExecute(int stage);
    static void RunCustom(int action);

    public:
    static void Reset();
    static void Register(dStageActor_c* obj, int typeID, bool force);
};

#endif