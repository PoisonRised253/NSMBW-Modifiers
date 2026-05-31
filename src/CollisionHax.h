#ifndef __H_COLHAX
#define __H_COLHAX

#include "Utils.h"

struct CollExtents
{
    static const char *GetAxisTypeByName(int rawType)
    {
        if (rawType == 0)
            ret "Point";
        if (rawType == 1)
            ret "Line";
        ret "";
    }

    static const char *GetAxisFromInt(int axisNum)
    {
        if (axisNum == 0)
            ret "Above";
        if (axisNum == 1)
            ret "Below";
        if (axisNum == 2 || axisNum == 3)
            ret "Left & Right";
        ret "";
    }

public:
    Vec3 Offsets[4];
    Vec3 ManualOffset[4];
    u32 Types[4];

    void Log()
    {
#ifdef DEBUG_COLLEXT
        OSReport("CollMgr: %p\n", this);
#endif

        for (int i = 0; i < 4; i++)
        {
            if (Types[i] == 0)
#ifdef DEBUG_COLLEXT
                OSReport("%s: %f, %f\n Type: %s\n", GetAxisFromInt(i), Offsets[i].x, Offsets[i].y, GetAxisTypeByName(Types[i]));
#endif
            if (Types[i] == 1)
            {
#ifdef DEBUG_COLLEXT
                OSReport("%s: (From) %f, %f; (To) %f, %f\n Type: %s\n", GetAxisFromInt(i), Offsets[i].x, Offsets[i].y, Offsets[i].z, GetAxisTypeByName(Types[i]));
#endif
            }
        }
    }

    CollExtents(dStageActor_c *actor)
    {
        sensorBase_s *sensors[3] = {actor->collMgr.pAboveInfo, actor->collMgr.pBelowInfo, actor->collMgr.pAdjacentInfo};
        for (int i = 0; i < 3; i++)
        {
            if (!sensors[i])
            {
                Offsets[i] = MakeVec(0, 0, 0);
                Types[i] = -1;
                continue;
            }

            Types[i] = sensors[i]->flags & SENSOR_TYPE_MASK;
            switch (Types[i])
            {
            case SENSOR_POINT:
            {
#ifdef DEBUG_COLLEXT
                OSReport("Point %i is a Point\n", i);
#endif
                Offsets[i] = MakeVec((sensors[i]->asPoint()->x / 4096), sensors[i]->asPoint()->y / 4096, 0);
                break;
            }

            case SENSOR_LINE:
            {
#ifdef DEBUG_COLLEXT
                OSReport("Point %i is a Line\n", i);
#endif
                Offsets[i] = MakeVec(
                sensors[i]->asLine()->lineA / 4096,
                sensors[i]->asLine()->distanceFromCenter / 4096,
                sensors[i]->asLine()->lineB / 4096);
                break;
            }
            }
#ifdef DEBUG_COLLEXT
            OSReport("Assembling CollMng part %i\n", i);
#endif
        }
#ifdef DEBUG_COLLEXT
        OSReport("Successfully assembled a full CollMng!\n");
#endif
    }

    ~CollExtents()
    {
        Offsets[0].x = 0;
        Offsets[0].y = 0;
        Offsets[1].x = 0;
        Offsets[1].y = 0;
        Offsets[2].x = 0;
        Offsets[2].y = 0;

        Types[0] = 0;
        Types[1] = 0;
        Types[2] = 0;
    }
};

struct PhysRect {
    Vec2 TopLeft, TopRight, BottomLeft, BottomRight;

    bool operator==(const PhysRect& other) const {
        ret (
        TopLeft.x == other.TopLeft.x &&
        TopLeft.y == other.TopLeft.y &&
        TopRight.x == other.TopRight.x &&
        TopRight.y == other.TopRight.y &&
        BottomLeft.x == other.BottomLeft.x &&
        BottomLeft.y == other.BottomLeft.y &&
        BottomRight.x == other.BottomRight.x &&
        BottomRight.y == other.BottomRight.y
        );
    }

    bool operator!=(const PhysRect& other) const {
        ret !(
        TopLeft.x == other.TopLeft.x &&
        TopLeft.y == other.TopLeft.y &&
        TopRight.x == other.TopRight.x &&
        TopRight.y == other.TopRight.y &&
        BottomLeft.x == other.BottomLeft.x &&
        BottomLeft.y == other.BottomLeft.y &&
        BottomRight.x == other.BottomRight.x &&
        BottomRight.y == other.BottomRight.y
        );
    }

    void operator+=(const PhysRect& other) {
        this->TopLeft.x     += other.TopLeft.x;
        this->TopLeft.y     += other.TopLeft.y;
        this->TopRight.x    += other.TopRight.x;
        this->TopRight.y    += other.TopRight.y;
        this->BottomLeft.x  += other.BottomLeft.x;
        this->BottomLeft.y  += other.BottomLeft.y;
        this->BottomRight.x += other.BottomRight.x;
        this->BottomRight.y += other.BottomRight.y;
    }

    void operator+=(const float& other) {
        this->TopLeft.x     += other;
        this->TopLeft.y     += other;
        this->TopRight.x    += other;
        this->TopRight.y    += other;
        this->BottomLeft.x  += other;
        this->BottomLeft.y  += other;
        this->BottomRight.x += other;
        this->BottomRight.y += other;
    }

    void operator-=(const PhysRect& other) {
        this->TopLeft.x     -= other.TopLeft.x;
        this->TopLeft.y     -= other.TopLeft.y;
        this->TopRight.x    -= other.TopRight.x;
        this->TopRight.y    -= other.TopRight.y;
        this->BottomLeft.x  -= other.BottomLeft.x;
        this->BottomLeft.y  -= other.BottomLeft.y;
        this->BottomRight.x -= other.BottomRight.x;
        this->BottomRight.y -= other.BottomRight.y;
    }

    void operator-=(const float& other) {
        this->TopLeft.x     -= other;
        this->TopLeft.y     -= other;
        this->TopRight.x    -= other;
        this->TopRight.y    -= other;
        this->BottomLeft.x  -= other;
        this->BottomLeft.y  -= other;
        this->BottomRight.x -= other;
        this->BottomRight.y -= other;
    }

    void operator*=(const PhysRect& other) {
        this->TopLeft.x     *= other.TopLeft.x;
        this->TopLeft.y     *= other.TopLeft.y;
        this->TopRight.x    *= other.TopRight.x;
        this->TopRight.y    *= other.TopRight.y;
        this->BottomLeft.x  *= other.BottomLeft.x;
        this->BottomLeft.y  *= other.BottomLeft.y;
        this->BottomRight.x *= other.BottomRight.x;
        this->BottomRight.y *= other.BottomRight.y;
    }

    void operator*=(const float& other) {
        this->TopLeft.x     *= other;
        this->TopLeft.y     *= other;
        this->TopRight.x    *= other;
        this->TopRight.y    *= other;
        this->BottomLeft.x  *= other;
        this->BottomLeft.y  *= other;
        this->BottomRight.x *= other;
        this->BottomRight.y *= other;
    }

    void operator/=(const PhysRect& other) {
        this->TopLeft.x     /= other.TopLeft.x;
        this->TopLeft.y     /= other.TopLeft.y;
        this->TopRight.x    /= other.TopRight.x;
        this->TopRight.y    /= other.TopRight.y;
        this->BottomLeft.x  /= other.BottomLeft.x;
        this->BottomLeft.y  /= other.BottomLeft.y;
        this->BottomRight.x /= other.BottomRight.x;
        this->BottomRight.y /= other.BottomRight.y;
    }

    void operator/=(const float& other) {
        this->TopLeft.x     /= other;
        this->TopLeft.y     /= other;
        this->TopRight.x    /= other;
        this->TopRight.y    /= other;
        this->BottomLeft.x  /= other;
        this->BottomLeft.y  /= other;
        this->BottomRight.x /= other;
        this->BottomRight.y /= other;
    }

    PhysRect(float topLeftX, float topLeftY, float topRightX, float topRightY, float botLeftX, float botLeftY, float botRightX, float botRightY) {
        TopLeft = MakeVec2(topLeftX, topLeftY);
        TopRight = MakeVec2(topRightX, topRightY);
        BottomLeft = MakeVec2(botLeftX, botLeftY);
        BottomRight = MakeVec2(botRightX, botRightY);
    }

    PhysRect(Vec2 topLeft, Vec2 topRight, Vec2 botLeft, Vec2 botRight) {
        TopLeft = topLeft;
        TopLeft = topRight;
        BottomLeft = botLeft;
        BottomRight = botRight;
    }

    PhysRect() {
        this->TopLeft.x     = 0;
        this->TopLeft.y     = 0;
        this->TopRight.x    = 0;
        this->TopRight.y    = 0;
        this->BottomLeft.x  = 0;
        this->BottomLeft.y  = 0;
        this->BottomRight.x = 0;
        this->BottomRight.y = 0;
    }

    ~PhysRect() {
        this->TopLeft.x     = 0;
        this->TopLeft.y     = 0;
        this->TopRight.x    = 0;
        this->TopRight.y    = 0;
        this->BottomLeft.x  = 0;
        this->BottomLeft.y  = 0;
        this->BottomRight.x = 0;
        this->BottomRight.y = 0;
    }
};

struct APhysRect {
    float xOffset, yOffset;
    Vec2 TopLeft, TopRight, BottomLeft, BottomRight;

};

class BasicCollExt : public BasicCollider
{
    public:
    // LeftX, LeftY, RightX, RightY
    Vec4 getExtents() const;
    void setExtents(Vec4 extents);
};

class PhysExt : public Physics
{
    //Unfinished
    public:
    static PhysRect getRect(Physics* phys);
    void setRect(PhysRect rect);
    static void Log(Physics* p);
};

class ActivePhysExt : public ActivePhysics
{
    static APhysRect getRect(ActivePhysics* p);
    void setRect();
    static void Log(ActivePhysics* p);
};

ext CollExtents getExtents(dStageActor_c *actor);
ext void setExtents(dStageActor_c *actor, CollExtents newColl);

#endif