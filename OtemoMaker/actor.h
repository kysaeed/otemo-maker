#ifndef ACTOR_H
#define ACTOR_H

#include <QList>
#include <QRect>
#include <QDataStream>
#include "actorimagedata.h"
#include "animationdata.h"

using AnimationList = QList<AnimationData*>;


class Actor
{
public:
    Actor();

    inline const ActorImageData& getImage() {
        return image;
    }

    inline const QRect& getBoudingBox() const {
        return boudingBox;
    }

    void clearBoundingBox();
    void setBoudingBox(const QRect& rect);


    AnimationList& getAnimaitons() {
        return  animations;
    }


    void write(QDataStream &stream) const;

protected:
    AnimationList animations;
    ActorImageData image;
    QRect boudingBox;
};

#endif // ACTOR_H
