#ifndef ANIMATIONMOUNTPOINTLISTITEM_H
#define ANIMATIONMOUNTPOINTLISTITEM_H

#include <QListWidget>
#include <QListWidgetItem>

#include "animationmountpoint.h"


class AnimationMountPointListItem : public QListWidgetItem
{
public:
    AnimationMountPointListItem(QListWidget* parent, AnimationMountPoint* mountPoint);

    inline AnimationMountPoint* getMountPoint() {
        return mountPoint;
    }

    void updateText();

protected:
    AnimationMountPoint* mountPoint;
};

#endif // ANIMATIONMOUNTPOINTLISTITEM_H
