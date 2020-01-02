#ifndef ANIMATIONSELECTITEM_H
#define ANIMATIONSELECTITEM_H

#include <QListWidgetItem>

#include "animationdata.h"

class AnimationSelectListItem : public QListWidgetItem
{
public:
    AnimationSelectListItem(AnimationData* animation, QListWidget* parent = nullptr);

    void setAnimation(AnimationData* animation);

    inline AnimationData* getAnimation() const {
        return animation;
    }

protected:
    void updateTexts();

    AnimationData* animation;
};

#endif // ANIMATIONSELECTITEM_H
