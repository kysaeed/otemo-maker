#ifndef ACTORFRAMEVIEW_H
#define ACTORFRAMEVIEW_H

#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QTimer>
#include <QPoint>
#include <QList>
#include <QRect>

#include <QTimeLine>

#include "animationdata.h"
#include "actorimagedata.h"

class ActorFrameView : public QGraphicsView
{
    Q_OBJECT
public:
    ActorFrameView(QWidget *parent);
    inline const QRect& getBoundingBox() const { return boundingBox; }

signals:
    void boudingBoxResized(const QRect& box);

public slots:
    void setActorImage(const ActorImageData& image);
    void setAnimaitonData(AnimationData* data);
    void setAnimationPlayState(bool isPlaying);

protected slots:
    void onFrame();

protected:
    int cellIndex;

    QRect boundingBox;
    ActorImageData actorImage;

    QList<int> animationData;
    AnimationData animaitonData;

    void drawBoundingBox(QPainter& painter);

    bool isBoudingBoxResizing;
    void paintEvent(QPaintEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    QTimer timer;
    QTimeLine* timeLine;

};

#endif // ACTORFRAMEVIEW_H
