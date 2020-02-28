#include "animationdata.h"

#include <QDebug>

AnimationData::AnimationData(const QString& name)
{
    this->name = name;
    reset();
}

AnimationData::~AnimationData()
{
    foreach (AnimationFrame* frame, frames) {
        delete frame;
    }
}

void AnimationData::setName(const QString &name)
{
    this->name = name;
}

void AnimationData::reset()
{
    counter = 0;
    frameIterator = frames.begin();
}

void AnimationData::moveNextData()
{
    if (frames.count() <= 1) {
        counter = 0;
        frameIterator = frames.begin();
        return;
    }

    frameIterator++;
    if (frameIterator == frames.end()) {
        counter = 0;
        frameIterator = frames.begin();
    }
}

void AnimationData::movePrevData()
{
    if (frames.count() <= 1) {
        counter = 0;
        frameIterator = frames.begin();
        return;
    }

    if (frameIterator == frames.begin()) {
        frameIterator = frames.end();
    }
    frameIterator--;
}

void AnimationData::moveNextFrame()
{
    if (frames.count() <= 1) {
        counter = 0;
        frameIterator = frames.begin();
        return;
    }

    counter++;
    if (counter >= (*frameIterator)->getFrameCount()) {
        counter = 0;
        moveNextData();
    }
}

AnimationFrame* AnimationData::getCurrentFrame()
{
    return (*frameIterator);
}

void AnimationData::addFrame(int position, AnimationFrame* frame)
{
    frames.insert(position, frame);
    reset();
}

void AnimationData::pushFrame(AnimationFrame* frame)
{
    frames.append(frame);
    reset();
}

void AnimationData::removeFramea(int position)
{
    frames.removeAt(position);
}

void AnimationData::write(QDataStream &stream) const
{
    QByteArray nameBytes = name.toUtf8();
    stream << nameBytes;
//    qDebug() << name << " / len=" << nameBytes.size() << " / " << nameBytes;

    stream << static_cast<int32_t>(frames.count());
    foreach (const AnimationFrame* frame, frames) {
        frame->write(stream);
    }
}

QByteArray AnimationData::toBytes() const
{
    QByteArray bytes;
    QDataStream stream(bytes);

    write(stream);
    return bytes;
}


