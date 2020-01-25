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
    QPixmap createIconPixmap(int cell);
    void enterDrag(int cell);

    QSize actorSize;
    QPoint getCellPosition(int x, int y);
    int getCellNumber(int x, int y);
    QPoint getCellXY(int cellNumber);

    int pressedCellNumber;
    bool isDragEntered;
    QPoint mousePressedPoint;

    ActorImageData image;

    int selectedCellNumber;


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

};

#endif // ACTORIMAGE_H
