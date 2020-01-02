#include "animationframetree.h"

AnimationFrameTree::AnimationFrameTree(QWidget* parent) : QTreeWidget(parent)
{
    animation = nullptr;
    this->setColumnCount(2);

    connect(
        this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
        this, SLOT(onItemChanged(QTreeWidgetItem*, QTreeWidgetItem*))
    );

}

void AnimationFrameTree::insertFrame(int index, AnimationFrame* frame)
{
    AnimationFrameTreeItem* item = new AnimationFrameTreeItem(this, frame);
    this->insertTopLevelItem(index, item);
    this->setCurrentItem(item);

    syncListItemToAnimationData();
}

AnimationData* AnimationFrameTree::createAnimationData()
{


    AnimationData* animation = new AnimationData();

    int count = this->topLevelItemCount();
    for (int i = 0; i < count; i++) {
        AnimationFrameTreeItem* item = dynamic_cast<AnimationFrameTreeItem*>(topLevelItem(i));
        if (item != nullptr) {
            animation->pushFrame(item->getFrame());
        }
    }

    return animation;
}

void AnimationFrameTree::setAnimationData(AnimationData* animation)
{
    this->clear();
    animation->reset();
    for (int i = 0; i < animation->getFrameCount(); i++) {
        AnimationFrame* frame = animation->getCurrentFrame();
        animation->moveNextData();
        new AnimationFrameTreeItem(this, frame);
    }
    animation->reset();

    this->animation = animation;

    emit animationDataChanged(animation);
}

AnimationFrameTreeItem *AnimationFrameTree::getCurrentItem()
{
    AnimationFrameTreeItem* item = dynamic_cast<AnimationFrameTreeItem*>(currentItem());
    if (item == nullptr) {
        return nullptr;
    }
    return item;
}

void AnimationFrameTree::syncListItemToAnimationData()
{
    this->animation->clear();
    for (int i = 0; i < topLevelItemCount(); i++) {
        AnimationFrame* frame = getAnimationFrameData(i);
        if (frame != nullptr) {
            this->animation->pushFrame(frame);
        }
    }
}

AnimationFrame *AnimationFrameTree::getAnimationFrameData(int index)
{
    AnimationFrameTreeItem* item = dynamic_cast<AnimationFrameTreeItem*>(topLevelItem(index));
    if(item == nullptr) {
        return nullptr;
    }

    return item->getFrame();
}

void AnimationFrameTree::setOffset(const QPoint &offset)
{
    AnimationFrameTreeItem* item = getCurrentItem();
    if (item == nullptr) {
        return;
    }

    item->setOffset(offset);
}

void AnimationFrameTree::setFrameCount(int frameCount)
{
    AnimationFrameTreeItem* item = getCurrentItem();
    if (item == nullptr) {
        return;
    }
    item->setFrameCount(frameCount);
}

void AnimationFrameTree::onItemChanged(QTreeWidgetItem *current, QTreeWidgetItem* /*previous*/)
{
    qDebug("AnimationFrameTree::onItemChanged()");

    AnimationFrameTreeItem* item = dynamic_cast<AnimationFrameTreeItem*>(current);
    if (item == nullptr) {
        return;
    }

    emit frameSelected(item->getFrame());
}
