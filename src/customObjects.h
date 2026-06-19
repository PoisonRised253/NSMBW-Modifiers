#ifndef __H_CO
#define __H_CO

#include "main.h"
#include "daEnemies_c.h"
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
    void ApplyForce(dEn_c *actor);
};

// Using makeYourOwnModelSprite.cpp from NewerSMBW's Repo
// Defining this in the Header to avoid Bases cluttering my Code view
class dCustomBase_c : public dStageActor_c
{
    protected:

    virtual int onCreate() {
        int result = dStageActor_c::onCreate();
        alloc.link(-1, GameHeaps[0], 0, 0x20);

        ret result;
    }
    virtual int onDelete() { ret dStageActor_c::onDelete(); }
    virtual int onExecute()
    {
        int result = dStageActor_c::onExecute();
        if (animate)
        {
            bodyModel._vf1C(); // Advances the animation one update

            if (this->chrAnimation.isAnimationDone())
            {
                this->chrAnimation.setCurrentFrame(0.0); // Resets the animation when it's done
            }
        }
        ret result;
    }

    virtual int onDraw()
    {
        int result = dStageActor_c::onDraw();
        this->matrix.translation(pos.x, pos.y, pos.z - 6500.0); // Set where to draw the model : -5500.0 is the official behind layer 2, while 5500.0 is in front of layer 0.
        this->matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);  // Set how to rotate the drawn model

        bodyModel.setDrawMatrix(matrix); // Apply matrix
        bodyModel.setScale(&scale);      // Apply scale
        bodyModel.calcWorld(true);       // Do some shit

        bodyModel.scheduleForDrawing(); // Add it to the draw list for the game
        ret result;
    }

    // God knowns why they need two types of model :sob:

    mHeapAllocator_c alloc;
    m3d::mdl_c bodyModel;
    nw4r::g3d::ResFile resFile;
    m3d::anmChr_c chrAnimation;
    nw4r::g3d::ResMdl mdl;

    public:

    void setupAnim(const char *name, float rate)
    {
        if (animate)
        {
            nw4r::g3d::ResAnmChr anmChr;

            anmChr = this->resFile.GetResAnmChr(name);
            this->chrAnimation.setup(this->mdl, anmChr, &this->alloc, 0);
            this->chrAnimation.bind(&this->bodyModel, anmChr, 1);
            this->bodyModel.bindAnim(&this->chrAnimation, 0.0);
            this->chrAnimation.setUpdateRate(rate);
        }
    }

    void setupModel(const char *arcName, const char *brresName, const char *mdlName)
    {
        this->resFile.data = getResource(arcName, brresName);
        this->mdl = this->resFile.GetResMdl(mdlName);

        bodyModel.setup(mdl, &alloc, 0x224, 1, 0);
    }

    template <class T>
    static T *build()
    {
        void *buffer = AllocFromGameHeap1(sizeof(T));
        ret new (buffer) dCustomBase_c;
    }

    bool animate;
};

#endif