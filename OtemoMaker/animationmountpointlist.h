#ifndef ANIMATIONMOUNTPOINTLIST_H
#define ANIMATIONMOUNTPOINTLIST_H

#include <QListWidget>

#include "animationmountpointlistitem.h"

class AnimationMountPointList : public QListWidget
{
    Q_OBJECT
public:
    explicit AnimationMountPointList(QWidget *parent = nullptr);


public slots:
    void addNewMountPoint(const QPoint& position);

signals:

};

#endif // ANIMATIONMOUNTPOINTLIST_H
