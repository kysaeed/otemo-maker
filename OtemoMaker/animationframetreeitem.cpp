#include "animationframetreeitem.h"

AnimationFrameTreeItem::AnimationFrameTreeItem(QTreeWidget* parent, AnimationFrame* frame) : QTreeWidgetItem(parent, QTreeWidgetItem::ShowIndicator)
{
    setFrame(frame);
    updateTexts();
}

void AnimationFrameTreeItem::setFrame(AnimationFrame* frame)
{
    this->frame = frame;
    updateTexts();
}

void AnimationFrameTreeItem::setFrameCount(int frameCount)
{
    frame->setFrameCount(frameCount);
    updateTexts();
}

void AnimationFrameTreeItem::setOffset(const QPoint &offset)
{
    frame->setOffset(offset);
    updateTexts();
}

void AnimationFrameTreeItem::updateTexts()
{
qDebug("AnimationFrameTreeItem::updateTexts()");

    QString subject;
    subject.sprintf("cell[%d] x %d", frame->getCell(), frame->getFrameCount());
    setText(0, subject);

    QString position;
    position.sprintf("x:%d, y:%d", frame->getOffset().x(), frame->getOffset().y());
    setText(1, position);
}
