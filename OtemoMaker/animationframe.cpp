#include "animationframe.h"

#include <QDebug>

AnimationFrame::AnimationFrame()
{
    cell = -1;
    frameCount = 1;
}

AnimationFrame::AnimationFrame(int cell, const QPoint& offset, int frameCount)
{
    this->cell = cell;
    this->offset = offset;
    this->frameCount = frameCount;
}


void AnimationFrame::setFrameCount(int count)
{
    if (count < 1) {
        count = 1;
    }

    frameCount = count;
}

int AnimationFrame::getCell() const
{
    return cell;
}

void AnimationFrame::setCell(int indexCell)
{
    if (indexCell < 0) {
        indexCell = 0;
    }
    cell = indexCell;
}

void AnimationFrame::setOffset(const QPoint &offset)
{
    this->offset = offset;
}

QByteArray AnimationFrame::toBytes() const
{
    QByteArray bytes;
    QDataStream stream(bytes);
    write(stream);

    return bytes;
}

void AnimationFrame::write(QDataStream &stream) const
{
    stream << (static_cast<int32_t>(cell)) << (static_cast<int32_t>(frameCount));
    stream << (static_cast<int32_t>(offset.x())) << (static_cast<int32_t>(offset.y()));

    stream << static_cast<int32_t>(events.count());
    foreach (const AnimationFrameEvent& e, events) {
        stream << e.toBytes();
    }
}

