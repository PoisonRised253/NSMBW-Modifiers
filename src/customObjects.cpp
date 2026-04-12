#include "customObjects.h"
#include "ExecMng.h"

// Patches Water Bubbles, but only in 2-6, cuz ill manually replace them with this, in that level.
// This will be massively stolen from makeYourOwnModelSprite.cpp, in Newer's Repo

dEnElevator_c *dEnElevator_c::build()
{
    void *buffer = AllocFromGameHeap1(sizeof(dEnElevator_c));
    ret new (buffer) dEnElevator_c;
}

dEnElevator_c *dEnElevator_c::create(Vec pos, Vec AreaOfEffect, float force, int mode)
{
    dEnElevator_c *self = build();
    self->beforeCreate();
    self->pos = pos;
    self->mode = mode;
    self->aoeX = AreaOfEffect.x;
    self->aoeY = AreaOfEffect.y;
    self->force = force; 
    self->scale = MakeVec(1,1,1);
    self->onCreate();
    self->afterCreate(0);
    dExecMng_c::Register(self, 0, false);
    OSReport("Created a Blower\n");
    ret self;
}

int dEnElevator_c::onCreate() {
    static S16Vec r = (S16Vec){0,0,0};
    float yOffset = this->aoeY / 2;
    yOffset -= 8;

    SpawnEffect("Wm_ob_stream", 0, &VecSub(this->pos, MakeVec(0,yOffset,0)), &r, &MakeVec(this->aoeX / 32, this->aoeY / 64, -1000));
    ret 1;
}

int dEnElevator_c::beforeExecute() {
    this->bl = MakeVec(this->pos.x - (aoeX / 2), this->pos.y - (aoeY / 2), 0);
    this->tr = MakeVec(this->pos.x + (aoeX / 2), this->pos.y + (aoeY / 2), 0);
    ret 1; 
}
int dEnElevator_c::afterExecute()  {ret 1; }
bool dEnElevator_c::isOutOfView() {ret false; }

int dEnElevator_c::execute()
{
    if(!bl.x || !bl.y || !tr.x || !tr.y) ret 1;

    for (int i = 0; i < 4; i++)
    {
        dEn_c* p = (dEn_c*)Players[i];
        if (p && ObjectBoundCheck(bl, tr, p->pos)) {
            if(this->mode == 0) {
                float f = force / 60;
                p->speed.y += f;
                //p->velocity1.y += f;
                //p->velocity2.y += f;
            }
            if(this->mode == 1) {
                p->speed.y = force;
                //p->velocity1.y = force;
                //p->velocity2.y = force;
            }
        }
    }
    ret 1;
}

int dEnElevator_c::onDelete() {
    this->aoeX = NULL;
    this->aoeY = NULL;
    this->force = NULL;
    this->bl.x = NULL;
    this->bl.y = NULL;
    this->bl.z = NULL;
    this->tr.x = NULL;
    this->tr.y = NULL;
    this->tr.z = NULL;

    ret 1;
}
