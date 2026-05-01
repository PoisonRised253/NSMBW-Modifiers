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
    bool playerWithin[4];
    Vec bl;
    Vec tr;
    static dEnElevator_c *build();
    bool isOutOfView();
    
public:
    static dEnElevator_c *create(Vec pos, Vec AreaOfEffect, float force, int mode);
    int beforeExecute();
    int execute();
    int afterExecute();
    int onCreate(float rotfix);
    int onDelete();
    void ApplyForce(dEn_c* actor);
};

class dParenting_c {
    private:
    bool isPopulated();
    dActor_c* parent;
    dActor_c* child;
    Vec offset;
    bool active;

    public:
    void update();

    dParenting_c(dActor_c* parent, dActor_c* child, bool active);
    ~dParenting_c();
};

#endif