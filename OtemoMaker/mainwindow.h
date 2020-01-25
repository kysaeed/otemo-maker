#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

#include "animationselectlistitem.h"
#include "animationframe.h"
#include "actor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void onImageCellSelected(AnimationFrame* frame);
    void onOffsetMoved(const QPoint& offset);
    void onAnimationTreeSelected(AnimationFrame* frame);
    void onAnimationDataChanged(AnimationData* animation);

    void setFrameOffset(const QPoint& offset);

    void onAnimationSelected(AnimationData *currentAnimation, AnimationData* previousAnimation);
//    void onAnimationUnselected(AnimationSelectListItem* previousItem);

    void commitFrames();

private slots:
    void on_pushButton_clicked();
    void on_pushButtonResetOffset_clicked();
    void on_spinBoxFrameCount_valueChanged(int frameCount);



    void on_spinBoxOffsetX_valueChanged(int x);

    void on_spinBoxOffsetY_valueChanged(int y);

    void on_pushButtonAddAnimation_clicked();

    void on_pushButtonAddEvent_clicked();

protected:
    Actor actor;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
