#include "actor.h"

Actor::Actor(const ActorImageData& image)
{
    this->image = image;
//    mountPointList.fill(nullptr, image.getCellCount());
}

void Actor::clearBoundingBox()
{
    boudingBox.setRect(0, 0, 0, 0);
}

void Actor::setBoudingBox(const QRect &rect)
{
    boudingBox = rect;
}

void Actor::setAnimations(const AnimationList &animations)
{
    this->animations = animations;
}

void Actor::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(boudingBox.x());
    stream << static_cast<int32_t>(boudingBox.y());
    stream << static_cast<int32_t>(boudingBox.width());
    stream << static_cast<int32_t>(boudingBox.height());

//    ActorImageData
    image.write(stream);

//    ActorAnimation

    animations.write(stream);
}

void Actor::read(QDataStream &stream)
{
    int32_t x  = 0;
    stream >> x;
    int32_t y  = 0;
    stream >> y;
    int32_t w  = 0;
    stream >> w;
    int32_t h  = 0;
    stream >> h;
    boudingBox.setRect(x ,y, w, h);


}
