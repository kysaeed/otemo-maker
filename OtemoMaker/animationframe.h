#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include <QList>

#include "animationframeevent.h"


class AnimationFrame
{
public:
    AnimationFrame();
    AnimationFrame(int cell, const QPoint& offset, int frameCount);

    inline bool isNull() const {
        return (cell  < 0);
    }

    inline void clear() {
        cell = -1;
    }

    void setFrameCount(int count);
    inline int getFrameCount() const { return frameCount; }

    int getCell() const;
    void setCell(int indexCell);

    const QPoint& getOffset() const { return offset; }
    void setOffset(const QPoint& offset);

    QByteArray toBytes() const;
    void write(QDataStream& stream) const;

protected:
    int cell;
    QPoint offset;
    int frameCount;
    QList<AnimationFrameEvent> events;
};

#endif // ANIMATIONFRAME_H
