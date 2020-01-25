#include "animationframeevent.h"

AnimationFrameEvent::AnimationFrameEvent()
{
    id = 0;
    triggerFrame = 0;
}

void AnimationFrameEvent::write(QDataStream &stream)
{
    stream << static_cast<int32_t>(id);
    stream << static_cast<int32_t>(offset.x()) << static_cast<int32_t>(offset.y());
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
