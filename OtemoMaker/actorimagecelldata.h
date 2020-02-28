#ifndef ACTORIMAGECELLDATA_H
#define ACTORIMAGECELLDATA_H

#include <QList>
#include <QRect>
#include <QDataStream>

#include "animationmountpoint.h"

//typedef QList<AnimationMountPoint*> AnimationMountPointList;

class ActorImageCellData
{
public:
    ActorImageCellData();

    inline const QRect& getBoundingBox() const { return boundingBox; }
    void setBoundingBox(const QRect& box);
    void addNewMountPoint(AnimationMountPoint* mountPoint);
    void clearMountPoints();
//    inline AnimationMountPoint* getMountPoint(int ) const { return ; }

    inline QList<AnimationMountPoint*>& getMountPoints() { return this->mountPoints; }
    void setMountPoints(const QList<AnimationMountPoint*>& points);

    void write(QDataStream& stream) const;
protected:
    QList<AnimationMountPoint*> mountPoints;

    QRect boundingBox;
};

#endif // ACTORIMAGECELLDATA_H
