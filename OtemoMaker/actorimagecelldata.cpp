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
    stream << static_cast<int32_t>(boundingBox.x())
     << static_cast<int32_t>(boundingBox.y())
     << static_cast<int32_t>(boundingBox.width())
     << static_cast<int32_t>(boundingBox.height());

    stream << static_cast<int32_t>(mountPoints.size());
    foreach (AnimationMountPoint* m, mountPoints) {
        m->write(stream);
    }
}

void ActorImageCellData::read(QDataStream &stream)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t w = 0;
    int32_t h = 0;
    stream >> x >> y >> w >> h;

    mountPoints.clear();
    int32_t pointCount = 0;
    stream >> pointCount;
    for (int i = 0; i < pointCount; i++) {
        AnimationMountPoint* p = new AnimationMountPoint();
        p->read(stream);
        mountPoints.append(p);
    }
}
