#ifndef ACTORIMAGE_H
#define ACTORIMAGE_H

#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>

#include "actorimagedata.h"


class ActorImageView : public QGraphicsView
{
    Q_OBJECT
public:
    ActorImageView(QWidget *parent);
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void setActorImage(const ActorImageData& actorImage);

signals:
    void cellSelected(int cellNumber);
    void droped(const QPoint& positoin, int cellNumber);
    void actorImageChanged(const ActorImageData& actorImage);

protected:
    QSize actorSize;
    QPoint getCellPosition(int x, int y);
    int getCellNumber(int x, int y);

    int pressedCellNumber;

    ActorImageData image;


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

};

#endif // ACTORIMAGE_H
