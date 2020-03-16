#include "animationframeevent.h"

AnimationFrameEvent::AnimationFrameEvent()
{
    id = 0;
    triggerFrame = 0;
}

void AnimationFrameEvent::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(id);
    stream << static_cast<int32_t>(offset.x()) << static_cast<int32_t>(offset.y());
}

void AnimationFrameEvent::read(QDataStream &stream)
{
    int32_t id = 0;
    int32_t x = 0;
    int32_t y = 0;

    stream >> id >> x >> y;
    this->id = id;
    this->offset = QPoint(x, y);
}

void AnimationFrameEvent::setId(int id)
{
    this->id = id;
}

void AnimationFrameEvent::setTriggerFrame(int frame)
{
    this->triggerFrame = frame;
}

void AnimationFrameEvent::setOffset(const QPoint &offset)
{
    this->offset = offset;
}
