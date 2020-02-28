#ifndef ANIMATIONSELECTLIST_H
#define ANIMATIONSELECTLIST_H

#include <QObject>
#include <QListWidget>
#include <QList>

#include "animationlist.h"
#include "actor.h"
#include "animationselectlistitem.h"



class AnimationSelectList : public QListWidget
{
    Q_OBJECT
public:
    explicit AnimationSelectList(QWidget *parent = nullptr);

    void addNewAnimation(const QString &name = QString());
    QList<AnimationData*> createAnimationList();
    AnimationSelectListItem* getCurrentItem();
    AnimationData* getCurrentAnimation();

    AnimationList* getAnimationList();
    void setAnimations(AnimationList* animations);

public slots:
    void setAniamtionData(AnimationData* animation);

signals:
    void animationSelected(AnimationData* currentAnimation, AnimationData* previousAnimation);

protected slots:
    void onCurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

protected:
    void syncData();
    static AnimationData* getAnimationData(QListWidgetItem* item);
    AnimationList* animations;

};

#endif // ANIMATIONSELECTLIST_H
