#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "animationframe.h"
#include "actorimagedata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->actorBuildView, SIGNAL(cellSelected(int, const QPoint&)),
        this, SLOT(onImageCellSelected(int, const QPoint&))
    );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onImageCellSelected(int cellNumber, const QPoint& offset)
{
    qDebug("MainWindow::onImageCellSelected() : entre");

    qDebug("cell : %d,%d", offset.x(), offset.y());

    animation.push_front(cellNumber);

    AnimationFrame frame;
    frame.setCell(cellNumber);
    frame.setOffset(offset);

    ui->treeWidget->addFrame(0, frame);

    ui->actorAnimationView->setAnimaitonData(animation);

//    ui->actorBuildView->setAnimaitonData(animation)

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButtonResetOffset_clicked()
{
    ui->actorBuildView->resetOffset();
}
