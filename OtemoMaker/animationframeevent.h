#ifndef ANIMATIONFRAMEEVENT_H
#define ANIMATIONFRAMEEVENT_H

#include <QPoint>
#include <QByteArray>

class AnimationFrameEvent
{
public:
    AnimationFrameEvent();
    QByteArray toBytes() const;

protected:
    QPoint offset;
    int id;
};

#endif // ANIMATIONFRAMEEVENT_H
