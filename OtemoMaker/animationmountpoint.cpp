#include "animationmountpoint.h"

AnimationMountPoint::AnimationMountPoint()
{
    id = 0;
}

void AnimationMountPoint::setId(int id)
{
    this->id = id;
}

void AnimationMountPoint::setOffset(const QPoint &offset)
{
    this->offset = offset;
}
