#include "animationselectlist.h"

AnimationSelectList::AnimationSelectList(QWidget *parent) : QListWidget(parent)
{
    animations = nullptr;

    connect(
        this, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
        this, SLOT(onCurrentItemChanged(QListWidgetItem*, QListWidgetItem*))
    );
}

void AnimationSelectList::onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem * previous)
{
    AnimationSelectListItem* previousItem = dynamic_cast<AnimationSelectListItem*>(previous);
    AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(current);
    if (item == nullptr) {
        return;
    }

    emit animationSelected(getAnimationData(item), getAnimationData(previousItem));
}

void AnimationSelectList::syncData()
{
    if (animations == nullptr) {
        return;
    }

    QList<AnimationData*> lsit;
    for (int i = 0; i < count(); i++) {
        AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(this->item(i));
        lsit.append(item->getAnimation());
    }

    animations->setAnimationList(lsit);
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

AnimationList *AnimationSelectList::getAnimationList()
{
    return animations;
}

void AnimationSelectList::setAnimations(AnimationList *animatoins)
{
    if (animations == nullptr) {
        return;
    }

    clear();
    foreach (AnimationData* animation, animatoins->getList()) {
        AnimationSelectListItem* item = new AnimationSelectListItem(animation, this);
        addItem(item);
    }
}

void AnimationSelectList::addNewAnimation(const QString &name)
{
    AnimationSelectListItem* previousItem = dynamic_cast<AnimationSelectListItem*>(currentItem());

    QString itemTitle = name;
    if (itemTitle.isEmpty()) {
        itemTitle.sprintf("animation-%d", this->count());
    }

    AnimationData* animation = new AnimationData(itemTitle);
    AnimationSelectListItem* item = new AnimationSelectListItem(animation, this);
    addItem(item);
    setItemSelected(item, true);

    syncData();

    emit animationSelected(getAnimationData(item), getAnimationData(previousItem));
}

QList<AnimationData*> AnimationSelectList::createAnimationList()
{
    QList<AnimationData*> animatonList;

    for (int i = 0; i < this->count(); i++) {
        AnimationSelectListItem* item = dynamic_cast<AnimationSelectListItem*>(this->item(i));
        animatonList.append(item->getAnimation());
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

    item->setAnimation(animation);
}
