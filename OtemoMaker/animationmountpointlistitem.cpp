#include "animationmountpointlistitem.h"

AnimationMountPointListItem::AnimationMountPointListItem(QListWidget* parent, AnimationMountPoint* mountPoint) : QListWidgetItem(parent, 0)
{
    this->mountPoint = mountPoint;
}
