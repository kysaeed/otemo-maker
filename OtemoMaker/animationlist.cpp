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

void AnimationList::setAnimationList(QList<AnimationData *> list)
{
    this->list = list;
}
