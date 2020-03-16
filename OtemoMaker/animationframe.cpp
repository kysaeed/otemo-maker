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

void AnimationFrame::read(QDataStream &stream)
{
    int32_t cell = 0;
    int32_t frameCount = 0;
    stream >> cell >> frameCount;
    this->cell = cell;
    this->frameCount = frameCount;

    int32_t x = 0;
    int32_t y = 0;
    stream >> x >> y;
    this->offset = QPoint(x, y);

    int32_t count = 0;
    stream >> count;
    for (int i = 0; i < count; i++) {
        AnimationFrameEvent* e = new AnimationFrameEvent();
        e->read(stream);
    }


}

void AnimationFrame::write(QDataStream &stream) const
{
    stream << (static_cast<int32_t>(cell)) << (static_cast<int32_t>(frameCount));
    stream << (static_cast<int32_t>(offset.x())) << (static_cast<int32_t>(offset.y()));

    stream << static_cast<int32_t>(events.count());
    foreach (AnimationFrameEvent* e, events) {
        e->write(stream);
    }
}

void AnimationFrame::addFrameEvent(AnimationFrameEvent *event)
{
    events.append(event);
}

