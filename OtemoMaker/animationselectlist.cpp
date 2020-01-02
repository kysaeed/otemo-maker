#include "animationselectlist.h"

AnimationSelectList::AnimationSelectList(QWidget *parent) : QListWidget(parent)
{
    connect(
        this, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
        this, SLOT(onCurrentItemChanged(QListWidgetItem*, QListWidgetItem*))
    );
}

void AnimationSelectList::onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem * previous)
{
    AnimationSelectListItem* previousItem = dynamic_cast<AnimationSelectListItem*>(previous);
    if (previousItem != nullptr) {
//        emit animationUnselected(previousItem);
    }

    AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(current);
    if (item == nullptr) {
        return;
    }

    emit animationSelected(getAnimationData(item), getAnimationData(previousItem));
}

AnimationData *AnimationSelectList::getAnimationData(QListWidgetItem *item)
{
    if (item == nullptr) {
        return nullptr;
    }

    AnimationSelectListItem* animationItem = dynamic_cast<AnimationSelectListItem*>(item);
    if (animationItem == nullptr) {
        return nullptr;
    }

    return animationItem->getAnimation();
}

AnimationData *AnimationSelectList::getCurrentAnimation()
{
    AnimationSelectListItem* item = getCurrentItem();
    if (item == nullptr) {
        return nullptr;
    }

    return item->getAnimation();
}

void AnimationSelectList::addNewAnimation(const QString &name)
{
    AnimationSelectListItem* previousItem = dynamic_cast<AnimationSelectListItem*>(currentItem());
    if (previousItem != nullptr) {
//        emit animationUnselected(previousItem);
    }

//    name.sprintf("ani-%d", count());

    QString itemTitle = name;
    if (itemTitle.isEmpty()) {
        itemTitle.sprintf("animation-%d", this->count());
    }

    AnimationData* animation = new AnimationData(itemTitle);
    AnimationSelectListItem* item = new AnimationSelectListItem(animation, this);
    this->addItem(item);

    this->setItemSelected(item, true);

    emit animationSelected(getAnimationData(item), getAnimationData(previousItem));
}

QList<AnimationData*> AnimationSelectList::createAnimationList()
{
    QList<AnimationData*> animatonList;

    for (int i = 0; i < this->count(); i++) {
        AnimationSelectListItem* pItem = dynamic_cast<AnimationSelectListItem*>(item(i));
        animatonList.push_back(pItem->getAnimation());
    }

    return animatonList;
}

AnimationSelectListItem *AnimationSelectList::getCurrentItem()
{
    AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(currentItem());
    return item;
}

void AnimationSelectList::setAniamtionData(AnimationData* animation)
{
    AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(currentItem());
    if (item == nullptr) {
        return;
    }

    item->setAnimation(animation);  //@@
}
