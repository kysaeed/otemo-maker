#ifndef ANIMATIONSELECTLIST_H
#define ANIMATIONSELECTLIST_H

#include <QObject>
#include <QListWidget>
#include <QList>

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

public slots:
    void setAniamtionData(AnimationData* animation);

signals:
    void animationSelected(AnimationData* currentAnimation, AnimationData* previousAnimation);
    void animationUnselected(AnimationSelectListItem* previousItem);

protected slots:
    void onCurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

protected:
    static AnimationData* getAnimationData(QListWidgetItem* item);

};

#endif // ANIMATIONSELECTLIST_H
