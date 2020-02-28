#include "animationcellview.h"

AnimationCellView::AnimationCellView(QWidget *parent) : QGraphicsView(parent)
{
    cellNumber = -1;
    image = nullptr;
    currentCellData = nullptr;
    currentMountPoint = nullptr;

}

void AnimationCellView::setActorImage(ActorImageData* image)
{
    this->image = image;
    setCell(0);
}

void AnimationCellView::setCell(int cell)
{
    cellNumber = cell;

    currentCellData = nullptr;
    currentMountPoint = nullptr;
    if (cellNumber >= 0) {
        if (image != nullptr) {
//            if (image->isEmptyCellData(cellNumber)) {
                currentCellData = image->getCellData(cellNumber);
                currentMountPoint = nullptr;
//            }
        }
    }

    emit currentCellChanged(cellNumber);

    viewport()->repaint();
}

void AnimationCellView::selectCurrentMountPoint(AnimationMountPoint *currrent)
{
qDebug("AnimationCellView::selectCurrentMountPoint : %p  , currentCellData=%p", currrent, currentCellData);
    if (currentCellData == nullptr) {  // TODO: set currentCellData befor select point !
        return;
    }
qDebug("  count = %d", currentCellData->getMountPoints().count());

    currentMountPoint = nullptr;
    foreach (AnimationMountPoint* m, currentCellData->getMountPoints()) {
qDebug("  m:%p", m);
        if (m == currrent) {
qDebug("  finded!!!");
            currentMountPoint = m;
            break;
        }
    }

    viewport()->repaint();
}

void AnimationCellView::setMountPoints(const QList<AnimationMountPoint *> &points)
{
    qDebug("AnimationCellView::setMountPoints : %d", points.size());

    if (currentCellData != nullptr) {
        currentCellData->setMountPoints(points);
    }

    viewport()->repaint();
}

void AnimationCellView::drawPointMark(QPainter &painter, int id, const QPoint& position, bool isCurrent)
{
    const int PointSize = 5;
    QPen pen;

    pen.setWidth(3);
    pen.setColor(QColor(0xff, 0xff, 0xff));
    painter.setPen(pen);
    painter.drawLine(position.x() - PointSize, position.y(), position.x() + PointSize, position.y());
    painter.drawLine(position.x(), position.y() - PointSize, position.x(), position.y() + PointSize);

    pen.setWidth(1);
    if (isCurrent) {
        pen.setColor(QColor(0xff, 0x00, 0x00));
    } else {
        pen.setColor(QColor(0x00, 0x00, 0x00));
    }
    painter.setPen(pen);
    painter.drawLine(position.x() - PointSize, position.y(), position.x() + PointSize, position.y());
    painter.drawLine(position.x(), position.y() - PointSize, position.x(), position.y() + PointSize);

    QString caption;
    caption.sprintf("%d", id);
    painter.drawText(position.x() + 10, position.y() - 2, caption);

}

void AnimationCellView::paintEvent(QPaintEvent*)
{
    QPainter painter(viewport());
    if (image != nullptr) {
        if (cellNumber >= 0) {
            image->drawCell(painter, cellNumber, QRect(0, 0, 128, 128));
        }
    }

    if (currentCellData != nullptr) {
        foreach (const AnimationMountPoint* p, currentCellData->getMountPoints()) {
            bool isCurrent = false;
            if (currentMountPoint == p) {
                isCurrent = true;
            }
            drawPointMark(painter, p->getId(), p->getOffset(), isCurrent);
        }
    }
}


void AnimationCellView::mousePressEvent(QMouseEvent *)
{
    //

}

void AnimationCellView::mouseReleaseEvent(QMouseEvent *event)
{
    if (currentCellData != nullptr) {
        if (currentMountPoint != nullptr) {
            currentMountPoint->setOffset(event->pos());
            emit currentMountPointUpdated();
        }
    }

    viewport()->repaint();
}
