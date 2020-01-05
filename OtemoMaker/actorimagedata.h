#ifndef ACTORIMAGEDATA_H
#define ACTORIMAGEDATA_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QFileInfo>

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

    bool drawAll(QPainter& painter, QRect& rectDst);

protected:
    QImage image;
    QSize actorSize;
    QSize cellSize;
    int cellCount;
    QFileInfo fileInfo;

};

#endif // ACTORIMAGEDATA_H
