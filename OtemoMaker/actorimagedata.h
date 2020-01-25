#ifndef ACTORIMAGEDATA_H
#define ACTORIMAGEDATA_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QFileInfo>
#include <QVector>

#include "animationmountpoint.h"
#include "actorimagecelldata.h"


class ActorImageData
{
public:
    ActorImageData();

    bool load(const QString &filename);

    inline bool isNull() const {
        return image.isNull();
    }


    int getCellNumber(int x, int y) const;
    QPoint getCellPosition(int x, int y) const;

    const QSize& getActorSize() const {
        return actorSize;
    }

    inline QString getName() const { return fileInfo.baseName(); }


    int getCellCount() const { return cellCount; }
    const QSize& getCellSize() const {
        return cellSize;
    }

    const QImage& getImage() const {
        return image;
    }

    bool drawCell(QPainter& painter, int cell, const QRect& rectDst) const;

    bool drawAll(QPainter& painter, QRect& rectDst) const;

    ActorImageCellData* getCellData(int cell);

    void setCellData(int cell, ActorImageCellData* data);

protected:
    QImage image;
    QSize actorSize;
    QSize cellSize;
    int cellCount;
    QFileInfo fileInfo;

    QVector<ActorImageCellData*> cellData;


};

#endif // ACTORIMAGEDATA_H
