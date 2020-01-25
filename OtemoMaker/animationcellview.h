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

signals:

public slots:

    void setActorImage(const ActorImageData& image);

    void setCell(int cell);

protected:

    int cellNumber;
    ActorImageData image;

    QPoint mountPoint;

    void drawPoint(QPainter& painter);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ANIMATIONCELLVIEW_H
