#ifndef ANIMATIONFRAMEEVENT_H
#define ANIMATIONFRAMEEVENT_H

#include <QPoint>
#include <QDataStream>
#include <QByteArray>

class AnimationFrameEvent
{
public:
    AnimationFrameEvent();
    void write(QDataStream& stream) const;
    void read(QDataStream& stream);

    inline int getId() const { return id; }
    inline const QPoint getOffset() const { return offset; }
    inline int getTriggerFrame() const { return triggerFrame; }

    void setId(int id);
    void setTriggerFrame(int frame);
    void setOffset(const QPoint& offset);


protected:
    int id;
    int triggerFrame;
    QPoint offset;
};

#endif // ANIMATIONFRAMEEVENT_H
