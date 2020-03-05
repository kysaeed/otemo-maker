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
    stream << static_cast<int32_t>(boudingBox.x())
     << static_cast<int32_t>(boudingBox.y())
     << static_cast<int32_t>(boudingBox.width())
     << static_cast<int32_t>(boudingBox.height());

    image.write(stream);

    animations.write(stream);
}

void Actor::read(QDataStream &stream)
{
    int32_t x  = 0;
    int32_t y  = 0;
    int32_t w  = 0;
    int32_t h  = 0;

    stream >> x >> y >> w >> h;
    boudingBox.setRect(x ,y, w, h);

    image.read(stream);

}
