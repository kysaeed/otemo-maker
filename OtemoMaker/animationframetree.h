#ifndef ANIMATIONFRAMETREE_H
#define ANIMATIONFRAMETREE_H

#include <QTreeWidget>
#include <QPoint>
#include "animationframe.h"
#include "animationdata.h"
#include "animationframetreeitem.h"

class AnimationFrameTree : public QTreeWidget
{
    Q_OBJECT
public:
    AnimationFrameTree(QWidget* parent);

    void insertFrame(int index, AnimationFrame* frame);

    AnimationData* createAnimationData();

    void setAnimationData(AnimationData* animation);

    AnimationFrameTreeItem* getCurrentItem();

protected:
    void syncListItemToAnimationData();
    AnimationFrame* getAnimationFrameData(int index);
    AnimationData* animation;

signals:
    void animationDataChanged(AnimationData* animationData);
    void frameSelected(AnimationFrame* frame);

public slots:
    void setOffset(const QPoint& offset);
    void setFrameCount(int frameCount);

protected slots:
    void onItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

};

#endif // ANIMATIONFRAMETREE_H
