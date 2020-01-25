#ifndef ANIMATIONMOUNTPOINT_H
#define ANIMATIONMOUNTPOINT_H

#include <QPoint>

class AnimationMountPoint
{
public:
    AnimationMountPoint();
    inline int getId() const { return id; }
    inline const QPoint& getOffset() const { return offset; }

    void setId(int id);
    void setOffset(const QPoint& offset);


protected:
    int id;
    QPoint offset;
};

#endif // ANIMATIONMOUNTPOINT_H
