#ifndef ANIMATIONFRAMETREEEVENTITEM_H
#define ANIMATIONFRAMETREEEVENTITEM_H

#include <QTreeWidgetItem>
#include "animationframeevent.h"

class AnimationFrameTreeEventItem : public QTreeWidgetItem
{
public:
    AnimationFrameTreeEventItem(QTreeWidgetItem* parent, AnimationFrameEvent* frameEvent);

    void updateTexts();

protected:
    AnimationFrameEvent* frameEvent;

};

#endif // ANIMATIONFRAMETREEEVENTITEM_H
