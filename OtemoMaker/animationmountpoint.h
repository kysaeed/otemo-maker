#ifndef ANIMATIONMOUNTPOINT_H
#define ANIMATIONMOUNTPOINT_H

#include <QPoint>
#include <QDataStream>

class AnimationMountPoint
{
public:
    AnimationMountPoint();
    AnimationMountPoint(int id, const QPoint& offset);

    inline int getId() const { return id; }
    inline const QPoint& getOffset() const { return offset; }

    void setId(int id);
    void setOffset(const QPoint& offset);

    void write(QDataStream& stream) const;
    void read(QDataStream& stream);

protected:
    int id;
    QPoint offset;
};

#endif // ANIMATIONMOUNTPOINT_H
