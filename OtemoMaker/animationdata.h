#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

#include <QList>
#include <QByteArray>
#include <QDataStream>
#include "animationframe.h"


class AnimationData
{
public:
    AnimationData(const QString& name = "Animation");
    virtual ~AnimationData();

    inline void clear() {
        frames.clear();
    }

    inline const QString& getName() const {
        return name;
    }

    void setName(const QString& name);

    void reset();
    void moveNextData();
    void movePrevData();

    void moveNextFrame();

    AnimationFrame* getCurrentFrame();

    void removeFramea(int position);
    void addFrame(int position, AnimationFrame* frame);
    void pushFrame(AnimationFrame* frame);

    inline int getFrameCount() const {
        return frames.count();
    }

    void write(QDataStream& stream) const;
    QByteArray toBytes() const;

protected:
    QString name;
    QList<AnimationFrame*> frames;
    QList<AnimationFrame*>::iterator frameIterator;
    int counter;
};

#endif // ANIMATIONDATA_H
