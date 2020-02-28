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
    mountPoints.append(mountPoint);
}

void ActorImageCellData::clearMountPoints()
{
    mountPoints.clear();
}

void ActorImageCellData::setMountPoints(const QList<AnimationMountPoint *> &points)
{
    mountPoints = points;
}

void ActorImageCellData::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(boundingBox.x());
    stream << static_cast<int32_t>(boundingBox.y());
    stream << static_cast<int32_t>(boundingBox.width());
    stream << static_cast<int32_t>(boundingBox.height());

    stream << mountPoints.size();
    foreach (AnimationMountPoint* m, mountPoints) {
        m->write(stream);
    }
}
