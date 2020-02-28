#include "actorimagedata.h"
#include <QDebug>

ActorImageData::ActorImageData()
{
    cellCount = 1;
    cellSize = QSize(1 ,1);
}


bool ActorImageData::load(const QString &filename)
{
    if (!image.load(filename)) {
        return false;
    }


    fileInfo = QFileInfo(filename);
    image = image.convertToFormat(QImage::Format_ARGB32);

    actorSize  = QSize(128, 128);
    cellSize = QSize(image.width() / actorSize.width(), image.height() / actorSize.height());
    cellCount = cellSize.width() * cellSize.height();

    cellData.fill(nullptr, getCellCount());

    return true;
}


bool ActorImageData::drawCell(QPainter& painter, int cell, const QRect& rectDst) const
{
    QRect r(actorSize.width() * (cell % cellSize.width()), actorSize.height() * static_cast<int>((cell / cellSize.width())), actorSize.width(), actorSize.height());
    painter.drawImage(rectDst, image, r);
    return true;
}

bool ActorImageData::drawAll(QPainter &painter, QRect &rectDst) const
{
    QRect r(0, 0, image.width(), image.height());
    painter.drawImage(rectDst, image, r);
    return true;
}

ActorImageCellData* ActorImageData::getCellData(int cell)
{
    if (cellData[cell] == nullptr) {
        cellData[cell] = new ActorImageCellData();
    }

    return cellData[cell];
}

bool ActorImageData::isEmptyCellData(int cell)
{
    if (cellData[cell] == nullptr) {
        return true;
    }

    return false;
}

void ActorImageData::setCellData(int cell, ActorImageCellData* data)
{
    if (cellData[cell] == data) {
        return;
    }

    cellData[cell] = data;
}

int ActorImageData::getCellNumber(int x, int y) const
{
    QPoint cellPosition = getCellPosition(x, y);
    if (cellPosition.x() < 0) {
        return -1;
    }
    if (cellPosition.x() >= cellSize.width()) {
        return -1;
    }

    if (cellPosition.y() < 0) {
        return -1;
    }
    if (cellPosition.y() >= cellSize.height()) {
        return -1;
    }

    return cellPosition.x() + (cellPosition.y() * cellSize.width());
}

QPoint ActorImageData::getCellPosition(int x, int y) const
{
    return QPoint(x / actorSize.width(), y / actorSize.height());
}

