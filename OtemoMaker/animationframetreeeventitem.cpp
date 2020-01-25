#include "animationframetreeeventitem.h"

AnimationFrameTreeEventItem::AnimationFrameTreeEventItem(QTreeWidgetItem* parent, AnimationFrameEvent* frameEvent) : QTreeWidgetItem(parent)
{
    this->frameEvent = frameEvent;

    updateTexts();
}

void AnimationFrameTreeEventItem::updateTexts()
{
    if (frameEvent == nullptr) {
        return;
    }

    QString caption;
    caption.sprintf("event[%d] : from:%d", frameEvent->getId(), frameEvent->getTriggerFrame());
    setText(0, caption);

    QString text;
    text.sprintf("x:%d, y:%d", frameEvent->getOffset().x(), frameEvent->getOffset().y());
    setText(1, text);
}
