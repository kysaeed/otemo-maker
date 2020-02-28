#ifndef ANIMATIONCELLVIEW_H
#define ANIMATIONCELLVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QPainter>
#include <QMouseEvent>

#include "actorimagedata.h"


class AnimationCellView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AnimationCellView(QWidget *parent = nullptr);

    inline int getCurrentCell() const { return cellNumber; }

signals:
    void currentCellChanged(int cell);

    void currentMountPointUpdated();

public slots:

    void setActorImage(ActorImageData* image);

    void setCell(int cell);

    void selectCurrentMountPoint(AnimationMountPoint* currrent);


    void setMountPoints(const QList<AnimationMountPoint*>& points);

protected:

    int cellNumber;
    ActorImageData* image;


    void drawPointMark(QPainter& painter, int id, const QPoint& position, bool isCurrent);

    ActorImageCellData* currentCellData;
    AnimationMountPoint* currentMountPoint;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ANIMATIONCELLVIEW_H
