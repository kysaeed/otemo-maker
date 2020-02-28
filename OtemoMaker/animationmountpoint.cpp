#include "animationmountpoint.h"

AnimationMountPoint::AnimationMountPoint()
{
    id = 0;
}

AnimationMountPoint::AnimationMountPoint(int id, const QPoint &offset)
{
    this->id = id;
    this->offset = offset;
}

void AnimationMountPoint::setId(int id)
{
    this->id = id;
}

void AnimationMountPoint::setOffset(const QPoint &offset)
{
    this->offset = offset;
}

void AnimationMountPoint::write(QDataStream &stream)
{
    stream << static_cast<int32_t>(id);
    stream << static_cast<int32_t>(offset.x());
    stream << static_cast<int32_t>(offset.y());
}
