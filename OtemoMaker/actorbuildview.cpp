#include "actorbuildview.h"

#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>
#include <QPainter>

ActorBuildView::ActorBuildView(QWidget *parent) : QGraphicsView(parent)
{
    frame = nullptr;

    isMoving = false;
    defaultFrameCount = 15;
    marign = 64;
}

void ActorBuildView::setFrame(AnimationFrame* frame)
{
    this->frame = frame;
    viewport()->repaint();
}

void ActorBuildView::setOffset(const QPoint &offset)
{
    if (frame != nullptr) {
        frame->setOffset(offset);
    }

    viewport()->repaint();

    if (frame != nullptr) {
        emit offsetMoved(frame->getOffset());
    }
}

void ActorBuildView::resetOffset()
{
    setOffset(QPoint(0, 0));
}

void ActorBuildView::setDefaultFrameCount(int frameCount)
{
    defaultFrameCount = frameCount;
}

void ActorBuildView::setActorImage(const ActorImageData &image)
{
    actorImage = image;
}

void ActorBuildView::dropEvent(QDropEvent *event)
{
    QByteArray bytes = event->mimeData()->data("application/x-om-cell");
    QDataStream s(&bytes, QIODevice::ReadOnly);

    int selectedCell = -1;
    s >> selectedCell;

    frame = new AnimationFrame(); //@@ リークしてる

    frame->setCell(selectedCell);
    frame->setFrameCount(defaultFrameCount);

    QPoint offset = QPoint(event->pos().x() - marign - 64, event->pos().y() - marign - 64);
    frame->setOffset(offset);

    viewport()->repaint();

    emit cellSelected(*frame);
}


void ActorBuildView::dragMoveEvent(QDragMoveEvent *)
{
//    offset = event->pos();
//    repaint();
}


void ActorBuildView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-om-cell")) {
        event->acceptProposedAction();
    }

}


void ActorBuildView::paintEvent(QPaintEvent*)
{
    QPainter painter(viewport());
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(marign, marign, actorImage.getActorSize().width(), actorImage.getActorSize().height());

    if (frame != nullptr) {
        if (!frame->isNull()) {
            QRect t(marign + frame->getOffset().x(), marign + frame->getOffset().y(), actorImage.getActorSize().width(), actorImage.getActorSize().height());
            actorImage.drawCell(painter, frame->getCell(), t);
        }
    }

}

void ActorBuildView::mousePressEvent(QMouseEvent *event)
{
    isMoving = true;
    prevMovePoint = event->pos();
}

void ActorBuildView::mouseReleaseEvent(QMouseEvent *)
{
    isMoving = false;
    if (frame != nullptr) {
        emit offsetMoved(frame->getOffset());
    }
}

void ActorBuildView::mouseMoveEvent(QMouseEvent *event)
{
    if (frame == nullptr) {
        return;
    }

    QPoint diff = event->pos() - prevMovePoint;
    QPoint offset = frame->getOffset();
    offset += diff;
    frame->setOffset(offset);
    prevMovePoint = event->pos();

    emit offsetCandidateMoving(offset);

    viewport()->repaint();

}

