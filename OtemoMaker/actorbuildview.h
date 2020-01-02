#ifndef ACTORBUILDVIEW_H
#define ACTORBUILDVIEW_H

#include <QGraphicsView>
#include <QPoint>
#include <QList>
//#include <QSize>
#include "actorimagedata.h"
#include "actorframeview.h"

class ActorBuildView : public QGraphicsView
{
    Q_OBJECT
public:
    ActorBuildView(QWidget *parent);

    void setImage(const QImage& image);
    void setFrame(AnimationFrame* frame);

signals:
    void cellSelected(const AnimationFrame& frame);
    void offsetCandidateMoving(const QPoint& offset);
    void offsetMoved(const QPoint& offset);

public slots:
    void setActorImage(const ActorImageData& image);
    void setOffset(const QPoint& offset);
    void resetOffset();
    void setDefaultFrameCount(int frameCount);

protected:

    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

    virtual void paintEvent(QPaintEvent *event) override;

    ActorImageData actorImage;
    int marign;
    int defaultFrameCount;

    AnimationFrame* frame;

    bool isMoving;
    QPoint prevMovePoint;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // ACTORBUILDVIEW_H
