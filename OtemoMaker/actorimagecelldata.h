#ifndef ACTORIMAGECELLDATA_H
#define ACTORIMAGECELLDATA_H

#include <QList>
#include <QRect>


#include "animationmountpoint.h"


class ActorImageCellData
{
public:
    ActorImageCellData();

    inline const QRect& getBoundingBox() const { return boundingBox; }
    void setBoundingBox(const QRect& box);
    void addNewMountPoint(AnimationMountPoint* mountPoint);
    void clearMountPoints();
//    inline AnimationMountPoint* getMountPoint(int ) const { return ; }

protected:
    QList<AnimationMountPoint*> mountPoints;

    QRect boundingBox;
};

#endif // ACTORIMAGECELLDATA_H
