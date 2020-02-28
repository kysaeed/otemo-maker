#ifndef ACTOR_H
#define ACTOR_H

#include <QList>
#include <QRect>
#include <QDataStream>
#include <QVector>

#include "actorimagedata.h"
#include "animationdata.h"
#include "animationlist.h"
#include "animationmountpoint.h"

//using AnimationList = QList<AnimationData*>;


class Actor
{
public:
    Actor(const ActorImageData& image = ActorImageData());

    inline ActorImageData* getImage() {
        return &image;
    }

    inline QRect* getBoudingBox() {
        return &boudingBox;
    }

    void clearBoundingBox();
    void setBoudingBox(const QRect& rect);

    AnimationList& getAnimaitons() {
        return  animations;
    }

    const AnimationList& getAnimaitons() const {
        return  animations;
    }

    void setAnimations(const AnimationList& animations);

    void write(QDataStream &stream) const;
    void read(QDataStream &stream);

protected:
    AnimationList animations;
    ActorImageData image;
    QRect boudingBox;
};

#endif // ACTOR_H
