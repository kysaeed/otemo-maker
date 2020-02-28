#ifndef ANIMATIONLIST_H
#define ANIMATIONLIST_H

#include "animationdata.h"
#include <QList>

class AnimationList
{
public:
    AnimationList();
    AnimationList(QList<AnimationData*> list);

    void addAnimationData(AnimationData* data);

    void setAnimationList(QList<AnimationData*> list);

    inline const QList<AnimationData*>& getList() const {
        return list;
    }

    inline QList<AnimationData*>& getList() {
        return list;
    }

    void write(QDataStream &stream) const;

protected:
    QList<AnimationData*> list;
};

#endif // ANIMATIONLIST_H
