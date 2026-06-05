#include "CollisionHax.h"

Vec4 BasicCollExt::getExtents() const
{
    if (this->type == 0 || this->type == 2)
        ret MakeVec4(
            this->leftX,
            this->leftY,
            this->rightX,
            this->rightY);
    else
        ret MakeVec4(NULL, NULL, NULL, NULL);
}

void BasicCollExt::setExtents(Vec4 extents)
{
    this->leftX = extents.x;
    this->leftY = extents.y;
    this->rightX = extents.z;
    this->rightY = extents.w;
    ret;
}

//TopLeft, TopRight, BottomLeft, BottomRight | Theyre all just basically verts.
PhysRect PhysExt::getRect(Physics* p)
{
    ret PhysRect(
    // TopLeft
    p->unkArray[0].x,
    p->unkArray[0].y,
    // TopRight
    p->unkArray[3].x,
    p->unkArray[3].y,
    // BottomLeft
    p->unkArray[1].x,
    p->unkArray[1].y,
    // BottomRight
    p->unkArray[2].x,
    p->unkArray[2].y);
}

void PhysExt::Log(Physics* p) {
    PhysRect rect = getRect(p);
    if(rect == PhysRect()) ret;
    OSReport("PhysExt::Log():\nTopLeft: %f, %f\nTopRight: %f, %f\nBottomLeft: %f, %f\nBottomRight: %f, %f\nPhysExt::Log() End\n",
    rect.TopLeft.x,
    rect.TopLeft.y, 
    rect.TopRight.x, 
    rect.TopRight.y, 
    rect.BottomLeft.x, 
    rect.BottomLeft.y, 
    rect.BottomRight.x, 
    rect.BottomRight.y
    );
    ret;
}

void PhysExt::setRect(PhysRect rect)
{
    this->unkArray[0].x = rect.TopLeft.x;
    this->unkArray[0].y = rect.TopLeft.y;
    this->unkArray[3].x = rect.TopRight.x;
    this->unkArray[3].y = rect.TopRight.y;
    this->unkArray[1].x = rect.BottomLeft.x;
    this->unkArray[1].y = rect.BottomLeft.y;
    this->unkArray[2].x = rect.BottomRight.x;
    this->unkArray[2].y = rect.BottomRight.y;
    ret;
}

ext CollExtents getExtents(dStageActor_c *actor)
{
    ret CollExtents(actor);
}

ext void setExtents(dStageActor_c *actor, CollExtents newColl)
{
    sensorBase_s *sensors[3] = {actor->collMgr.pAboveInfo, actor->collMgr.pBelowInfo, actor->collMgr.pAdjacentInfo};
#ifdef DEBUG_COLLEXT
    OSReport("Setting Collision at %p\n", &actor->collMgr);
#endif
    for (int i = 0; i < 3; i++)
    {
        sensorBase_s *sensor = sensors[i];
        if (!sensor)
            continue;
        lineSensor_s *l = sensor->asLine();
        pointSensor_s *p = sensor->asPoint();

        u32 type = sensor->flags & SENSOR_TYPE_MASK;

        if (type == SENSOR_POINT && p)
        {
#ifdef DEBUG_COLLEXT
            OSReport("Success Applying Collider changes on %i\n", i);
#endif
            p->x = (s32)(newColl.Offsets[i].x + newColl.ManualOffset->x) * 4096;
            p->y = (s32)(newColl.Offsets[i].y + newColl.ManualOffset->y) * 4096;
            continue;
        }
        if (type == SENSOR_LINE && l)
        {
#ifdef DEBUG_COLLEXT
            OSReport("Success Applying Collider changes on %i\n", i);
#endif
            if (i < 2)
            {
                // Left-To-Right
                l->lineA = (s32)(newColl.Offsets[i].x + newColl.ManualOffset[i].x) * 4096;
                l->distanceFromCenter = (s32)(newColl.Offsets[i].y + newColl.ManualOffset[i].y) * 4096;
                l->lineB = (s32)(newColl.Offsets[i].z + newColl.ManualOffset[i].z) * 4096;
            }
            else
            {
                // Up-To-Down
                l->lineA = (s32)(newColl.Offsets[i].y + newColl.ManualOffset[i].x) * 4096;
                l->distanceFromCenter = (s32)(newColl.Offsets[i].x + newColl.ManualOffset[i].y) * 4096;
                l->lineB = (s32)(newColl.Offsets[i].z + newColl.ManualOffset[i].z) * 4096;
            }
            continue;
        }
    }
#ifdef DEBUG_COLLEXT
    OSReport("Success Applying Collider changes\n");
#endif
    ret;
}

