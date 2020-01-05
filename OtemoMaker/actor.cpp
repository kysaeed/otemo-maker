#include "actor.h"

Actor::Actor()
{
}

void Actor::clearBoundingBox()
{
    boudingBox.setRect(0, 0, 0, 0);
}

void Actor::setBoudingBox(const QRect &rect)
{
    boudingBox = rect;
}

void Actor::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(boudingBox.x());
    stream << static_cast<int32_t>(boudingBox.y());
    stream << static_cast<int32_t>(boudingBox.width());
    stream << static_cast<int32_t>(boudingBox.height());

//    stream << animations.size();
//    foreach (const AnimationData* animation, animations) {
//        animation->write(stream);
//    }
}
