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

void AnimationMountPoint::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(id)
     << static_cast<int32_t>(offset.x())
     << static_cast<int32_t>(offset.y());

    qDebug("id:%d (%d, %d)",id , offset.x(), offset.y());
}

void AnimationMountPoint::read(QDataStream &stream)
{
    stream >> id
        >> offset.rx()
        >> offset.ry();
}
