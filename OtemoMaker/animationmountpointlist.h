#ifndef ANIMATIONMOUNTPOINTLIST_H
#define ANIMATIONMOUNTPOINTLIST_H

#include <QListWidget>

#include "actorimagecelldata.h"
#include "animationmountpointlistitem.h"

class AnimationMountPointList : public QListWidget
{
    Q_OBJECT
public:
    explicit AnimationMountPointList(QWidget *parent = nullptr);
    QList<AnimationMountPoint*> createMountPointList();
    AnimationMountPointListItem* getMountPointItem(int index);

    bool hasId(int id);
    int getNextId();
    bool addNewMountPoint(int id, const QPoint& position);

public slots:
    void setCellData(ActorImageCellData *data);
    void updateCurrentItemText();

protected slots:
    void onItemSelected(QListWidgetItem *current, QListWidgetItem *previous);

signals:
    void mountPointListChanged(const QList<AnimationMountPoint*>& mountPoints);

    void currentMountPointChanged(AnimationMountPoint* mountPoint);

protected:
    ActorImageCellData* cellData;

};

#endif // ANIMATIONMOUNTPOINTLIST_H
