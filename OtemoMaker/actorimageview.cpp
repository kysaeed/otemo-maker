#include "actorimageview.h"

#include <QApplication>
#include <QDir>
#include <QPixmap>
#include <QPainter>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>


ActorImageView::ActorImageView(QWidget *parent) : QGraphicsView(parent)
{
    qDebug("ActorImage::ActorImage");

    pressedCellNumber = -1;
    selectedCellNumber = 0;
}

void ActorImageView::paintEvent(QPaintEvent*)
{
    QPainter qPainter(viewport());
    QRect t(0, 0, image.getImage().width(), image.getImage().height());
    image.drawAll(qPainter, t);

    qPainter.setPen(QColor(0, 0, 255));
    qPainter.setBrush(Qt::BrushStyle::NoBrush);

    for (int y = 0; y <  image.getImage().height(); y += image.getActorSize().height()) {
        for (int x = 0; x <  image.getImage().width(); x += image.getActorSize().width()) {
            qPainter.drawRect(x, y, image.getActorSize().width(), image.getActorSize().height());
        }
    }

    qPainter.setPen(QPen(QColor(255, 0, 0), 2));
    qPainter.setBrush(Qt::BrushStyle::NoBrush);
    QPoint p = getCellXY(selectedCellNumber);
    QRect seletedMark(p.x() * image.getActorSize().width(), p.y() * image.getActorSize().height(), image.getActorSize().width(), image.getActorSize().height());
    qPainter.drawRect(seletedMark);

}

void ActorImageView::setActorImage(const ActorImageData &actorImage)
{
    this->image = actorImage;
    if (image.getCellCount() >= 0) {
        selectedCellNumber = 0;
    } else {
        selectedCellNumber = -1;
    }

    emit cellSelected(selectedCellNumber);
    emit actorImageChanged(this->image);
}

QPixmap ActorImageView::createIconPixmap(int cell)
{
    QPixmap pixmap(image.getActorSize().width() + 1, image.getActorSize().height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painer(&pixmap);

    QRect t(0, 0, image.getActorSize().width(), image.getActorSize().height());
    image.drawCell(painer, cell, t);
    painer.setPen(QColor(0x10, 0x10, 0xF0, 0x80));
    painer.drawRect(t);

    return pixmap;
}

void ActorImageView::enterDrag(int cell)
{

    this->pressedCellNumber = cell;
    QPixmap pixmap = createIconPixmap(pressedCellNumber);

    QDrag* drag = new QDrag(this);
    QMimeData* data = new QMimeData();

    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << cell;
    data->setData("application/x-om-cell", bytes);
    drag->setMimeData(data);
    drag->setHotSpot(QPoint(64, 64));
    drag->setPixmap(pixmap);
    drag->exec(Qt::CopyAction);

}

void ActorImageView::mousePressEvent(QMouseEvent *event)
{


    isDragEntered = false;
    mousePressedPoint = event->pos();
    pressedCellNumber = getCellNumber(event->x(), event->y());

    qDebug("ActorImageView::mousePressEvent : %d", pressedCellNumber);

}

void ActorImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!isDragEntered) {
        selectedCellNumber = pressedCellNumber;
        viewport()->repaint();
        emit cellSelected(selectedCellNumber);

    } else {
        isDragEntered = false;
    }

//    releaseMouse();
//    QApplication::restoreOverrideCursor();

//    emit droped(event->globalPos(), pressedCellNumber);

    int cell = getCellNumber(event->x(), event->y());


    if (cell != pressedCellNumber) {
        return;
    }

}

void ActorImageView::mouseMoveEvent(QMouseEvent *event)
{
    if (!isDragEntered) {
        QPoint diff = mousePressedPoint - event->pos();
        if (diff.manhattanLength() > 4) {
            isDragEntered = true;
            enterDrag(getCellNumber(event->x(), event->y()));
        }
    }

}

QPoint ActorImageView::getCellPosition(int x, int y)
{
    return QPoint(x / image.getActorSize().width(), y / image.getActorSize().height());
}

int ActorImageView::getCellNumber(int x, int y)
{
    QPoint cellPosition = getCellPosition(x, y);
    if (cellPosition.x() < 0) {
        return -1;
    }
    if (cellPosition.x() >= image.getCellSize().width()) {
        return -1;
    }

    if (cellPosition.y() < 0) {
        return -1;
    }
    if (cellPosition.y() >= image.getCellSize().height()) {
        return -1;
    }

    return cellPosition.x() + (cellPosition.y() * image.getCellSize().width());
}

QPoint ActorImageView::getCellXY(int cellNumber)
{
    return QPoint(cellNumber % image.getCellSize().width(), (cellNumber / image.getCellSize().width()));
}

void ActorImageView::dragMoveEvent(QDragMoveEvent *)
{
}

