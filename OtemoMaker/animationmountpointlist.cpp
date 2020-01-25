#include "animationmountpointlist.h"

AnimationMountPointList::AnimationMountPointList(QWidget *parent) : QListWidget(parent)
{

}

void AnimationMountPointList::addNewMountPoint(const QPoint &position)
{
    AnimationMountPoint* mp = new AnimationMountPoint();
    AnimationMountPointListItem* item = new AnimationMountPointListItem(this, mp);
}
