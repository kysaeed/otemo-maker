#include "animationcellview.h"

AnimationCellView::AnimationCellView(QWidget *parent) : QGraphicsView(parent)
{
    cellNumber = -1;

    mountPoint = QPoint(10, 10);
}

void AnimationCellView::setActorImage(const ActorImageData &image)
{
    this->image = image;
}

void AnimationCellView::setCell(int cell)
{
    cellNumber = cell;
    viewport()->repaint();
}

void AnimationCellView::drawPoint(QPainter &painter)
{
    const int PointSize = 5;
    QPen pen;

    pen.setColor(QColor(0xff, 0xff, 0xff));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(mountPoint.x() - PointSize, mountPoint.y(), mountPoint.x() + PointSize, mountPoint.y());
    painter.drawLine(mountPoint.x(), mountPoint.y() - PointSize, mountPoint.x(), mountPoint.y() + PointSize);

    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(mountPoint.x() - PointSize, mountPoint.y(), mountPoint.x() + PointSize, mountPoint.y());
    painter.drawLine(mountPoint.x(), mountPoint.y() - PointSize, mountPoint.x(), mountPoint.y() + PointSize);

}

void AnimationCellView::paintEvent(QPaintEvent*)
{
    QPainter painter(viewport());
    if (cellNumber >= 0) {
        image.drawCell(painter, cellNumber, QRect(0, 0, 128, 128));
    }


    drawPoint(painter);
}


void AnimationCellView::mousePressEvent(QMouseEvent *)
{
    //

}

void AnimationCellView::mouseReleaseEvent(QMouseEvent *event)
{
    mountPoint = event->pos();
    viewport()->repaint();
}
