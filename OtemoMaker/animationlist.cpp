#include "animationlist.h"

AnimationList::AnimationList()
{

}

AnimationList::AnimationList(QList<AnimationData *> list)
{
    setAnimationList(list);
}

void AnimationList::addAnimationData(AnimationData* data)
{
    list.append(data);
}

void AnimationList::write(QDataStream &stream) const
{
    stream << static_cast<int32_t>(list.size());
    foreach (const AnimationData* animation, list) {
qDebug(" frame count = %d", animation->getFrameCount());
        animation->write(stream);
    }
}

void AnimationList::read(QDataStream &stream)
{
    int32_t listCount = 0;
    stream >> listCount;
qDebug("animation data count : %d", listCount);
    for (int i = 0; i < listCount; i++) {
        AnimationData* animation = new AnimationData();
        animation->read(stream);
    }
}

void AnimationList::setAnimationList(QList<AnimationData *> list)
{
    this->list = list;
}

