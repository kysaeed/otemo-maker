#ifndef ANIMATIONFRAMETREEITEM_H
#define ANIMATIONFRAMETREEITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QPoint>
#include "animationframe.h"

class AnimationFrameTreeItem : public QTreeWidgetItem
{
public:
    AnimationFrameTreeItem(QTreeWidget* parent, AnimationFrame* frame);

    AnimationFrame* getFrame() const { return frame; }
    void setFrame(AnimationFrame* frame);

    void setFrameCount(int count);
    void setOffset(const QPoint& offset);

    void updateTexts();
protected:
    AnimationFrame* frame;
};

#endif // ANIMATIONFRAMETREEITEM_H
