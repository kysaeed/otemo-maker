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
    stream << animations.size();
    foreach (const AnimationData* animation, animations) {
        animation->write(stream);
    }
}
