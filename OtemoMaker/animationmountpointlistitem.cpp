#include "animationmountpointlistitem.h"

AnimationMountPointListItem::AnimationMountPointListItem(QListWidget* parent, AnimationMountPoint* mountPoint) : QListWidgetItem(parent, 0)
{
    this->mountPoint = mountPoint;
    updateText();
}

void AnimationMountPointListItem::updateText()
{
    QString caption;
    caption.sprintf("id:%d (%d, %d)", mountPoint->getId(), mountPoint->getOffset().x(), mountPoint->getOffset().y());
    setText(caption);
}
