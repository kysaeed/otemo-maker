#include "animationselectlistitem.h"

AnimationSelectListItem::AnimationSelectListItem(AnimationData* animation, QListWidget* parent) : QListWidgetItem(parent)
{
    this->animation = animation;
    updateTexts();
}

void AnimationSelectListItem::setAnimation(AnimationData* animation)
{
    this->animation = animation;
//    this->animation->reset();
    updateTexts();
}

void AnimationSelectListItem::updateTexts()
{
    setText(animation->getName());
}
