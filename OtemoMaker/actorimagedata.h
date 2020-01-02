#ifndef ACTORIMAGEDATA_H
#define ACTORIMAGEDATA_H

#include <QObject>
#include <QImage>
#include <QPainter>

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

};

#endif // ACTORIMAGEDATA_H
