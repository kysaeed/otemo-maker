#include "actorframeview.h"

ActorFrameView::ActorFrameView(QWidget *parent) : QGraphicsView(parent)
{
    timeLine = new QTimeLine(100, this);

    cellIndex = 0;
    isBoudingBoxResizing = false;


    connect(
        &timer, SIGNAL(timeout()),
        this, SLOT(onFrame())
    );
    timer.setInterval(16);
    setAnimationPlayState(true);
}

void ActorFrameView::setActorImage(const ActorImageData &image)
{
    this->actorImage = image;
    boundingBox = QRect(0, 0, actorImage.getActorSize().width() * 2,  actorImage.getActorSize().height() * 2);
}

void ActorFrameView::setAnimaitonData(AnimationData* data)
{
    setAnimationPlayState(false);

    this->animaitonData = *data;
    this->animaitonData.reset();
    setAnimationPlayState(true);
}

void ActorFrameView::setAnimationPlayState(bool isPlaying)
{
    if (isPlaying) {
        timer.start();
    } else {
        timer.stop();
    }
}

void ActorFrameView::onFrame()
{
//    qDebug("ActorFrameView::onFrame() : frame-count: %d", animaitonData.getFrameCount());

    if (animaitonData.getFrameCount() > 0) {
        animaitonData.moveNextFrame();
        AnimationFrame* f = animaitonData.getCurrentFrame();
        cellIndex = f->getCell();

//        qDebug("ActorFrameView::onFrame() : cellIndex: %d", cellIndex);
        viewport()->repaint();
    }
}

void ActorFrameView::paintEvent(QPaintEvent *)
{
    QPainter qPainter(viewport());


    if (animaitonData.getFrameCount() > 0) {
        AnimationFrame* frame = animaitonData.getCurrentFrame();
        QRect t(frame->getOffset().x() * 2, frame->getOffset().y() * 2, actorImage.getActorSize().width() * 2, actorImage.getActorSize().height() * 2);
        actorImage.drawCell(qPainter, frame->getCell(), t);

//        int idx = frame.getCell();
//        QPoint offset = frame.getOffset();
//        QRect f(actorSize.width() * idx, 0, actorSize.width(), actorSize.height());
//        QRect t(offset.x() * 2, offset.y() * 2, actorSize.width() * 2, actorSize.height() * 2);
//        qPainter.drawImage(t, image, f);
    }


    qPainter.setPen(QColor(255, 0, 0));
    qPainter.setBrush(Qt::BrushStyle::NoBrush);
    qPainter.drawRect(boundingBox);
}


void ActorFrameView::mousePressEvent(QMouseEvent *event)
{
    isBoudingBoxResizing = true;
    boundingBox.setX(event->x());
    boundingBox.setY(event->y());

    viewport()->repaint();
}

void ActorFrameView::mouseReleaseEvent(QMouseEvent *event)
{
    boundingBox.setWidth(event->x() - boundingBox.x());
    boundingBox.setHeight(event->y() - boundingBox.y());

    isBoudingBoxResizing = false;
    viewport()->repaint();
}

void ActorFrameView::mouseMoveEvent(QMouseEvent *event)
{
    if (isBoudingBoxResizing) {
        boundingBox.setWidth(event->pos().x() - boundingBox.x());
        boundingBox.setHeight(event->pos().y() - boundingBox.y());
        viewport()->repaint();
    }
}
