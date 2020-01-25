#include "actorimagecelldata.h"

ActorImageCellData::ActorImageCellData()
{
    //
}

void ActorImageCellData::setBoundingBox(const QRect &box)
{
    boundingBox = box;
}

void ActorImageCellData::addNewMountPoint(AnimationMountPoint *mountPoint)
{
    mountPoints.push_back(mountPoint);
}

void ActorImageCellData::clearMountPoints()
{
    mountPoints.clear();
}
