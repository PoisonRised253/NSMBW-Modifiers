#ifndef __H_CO
#define __H_CO

#include "main.h"
#include "Utils.h"

class dEnElevator_c : public dStageActor_c
{
private:
    float aoeX;
    float aoeY;
    float force;
    int mode;
    Vec bl;
    Vec tr;
    static dEnElevator_c *build();
    
public:
    static dEnElevator_c *create(Vec pos, Vec AreaOfEffect, float force, int mode);
    int beforeExecute();
    int execute();
    int afterExecute();
    int onCreate();
    int onDelete();
    bool isOutOfView();
};


#endif