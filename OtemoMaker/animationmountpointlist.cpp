#include "animationmountpointlist.h"

AnimationMountPointList::AnimationMountPointList(QWidget *parent) : QListWidget(parent)
{
    cellData = nullptr;

    connect(
        this, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
        this, SLOT(onItemSelected(QListWidgetItem*, QListWidgetItem*))
    );
}

QList<AnimationMountPoint*> AnimationMountPointList::createMountPointList()
{
    QList<AnimationMountPoint*> mountPoints;

    for (int i = 0; i < count(); i++) {
        AnimationMountPointListItem* item = getMountPointItem(i);
        if (item != nullptr) {
            mountPoints.append(item->getMountPoint());
        }
    }

    return mountPoints;
}

AnimationMountPointListItem *AnimationMountPointList::getMountPointItem(int index)
{
    return dynamic_cast<AnimationMountPointListItem*>(item(index));
}

bool AnimationMountPointList::hasId(int id)
{
    for (int i = 0; i < count(); i++) {
        AnimationMountPointListItem* item = getMountPointItem(i);
        if (item != nullptr) {
            if (item->getMountPoint()->getId() == id) {
                return true;
            }
        }
    }
    return false;
}

int AnimationMountPointList::getNextId()
{
    int id = 0;

    for (int i = 0; i < count(); i++) {
        AnimationMountPointListItem* item = getMountPointItem(i);
        if (item != nullptr) {
            if (item->getMountPoint()->getId() >= id) {
                id = (item->getMountPoint()->getId() + 1);
            }
        }
    }

    return id;
}

bool AnimationMountPointList::addNewMountPoint(int id, const QPoint &position)
{
    if (hasId(id)) {
        return false;
    }

    AnimationMountPoint* m = new AnimationMountPoint(id, position);

    AnimationMountPointListItem* item = new AnimationMountPointListItem(this, m);
    item->setSelected(true);

    cellData->setMountPoints(createMountPointList());

    emit mountPointListChanged(cellData->getMountPoints());
    emit currentMountPointChanged(m);

    return true;
}

void AnimationMountPointList::setCellData(ActorImageCellData *data)
{
    qDebug("AnimationMountPointList::setCellData : %p", data);

    clear();
    cellData = data;
    if (cellData != nullptr) {
        qDebug("  count=%d", cellData->getMountPoints().size());
        foreach (AnimationMountPoint* m, cellData->getMountPoints()) {
            new AnimationMountPointListItem(this, m);
        }
    }


}

void AnimationMountPointList::updateCurrentItemText()
{
    AnimationMountPointListItem* item = dynamic_cast<AnimationMountPointListItem*>(currentItem());
    if (item == nullptr) {
        return;
    }
    item->updateText();
}

void AnimationMountPointList::onItemSelected(QListWidgetItem *current, QListWidgetItem * /*previous*/)
{
    AnimationMountPointListItem* item = dynamic_cast<AnimationMountPointListItem*>(current);
    if (item == nullptr) {
        return;
    }

    emit currentMountPointChanged(item->getMountPoint());
}
