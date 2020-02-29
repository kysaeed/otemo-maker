#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "animationdata.h"
#include "animationframe.h"
#include "actorimagedata.h"

#include "animationframeevent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->actorBuildView, SIGNAL(cellSelected(AnimationFrame*)),
        this, SLOT(onImageCellSelected(AnimationFrame*))
    );

    connect(
        ui->actorBuildView, SIGNAL(offsetMoved(const QPoint&)),
        this, SLOT(onOffsetMoved(const QPoint&))
    );

    connect(
        ui->animationTreeWidget, SIGNAL(frameSelected(AnimationFrame*)),
        this, SLOT(onAnimationTreeSelected(AnimationFrame*))
    );

    connect(
        ui->actorBuildView, SIGNAL(offsetCandidateMoving(const QPoint&)),
        this, SLOT(setFrameOffset(const QPoint&))
    );

    connect(
        ui->actorImgeView, SIGNAL(actorImageChanged(const ActorImageData&)),
        ui->actorBuildView, SLOT(setActorImage(const ActorImageData&))
    );

    connect(
        ui->actorImgeView, SIGNAL(actorImageChanged(const ActorImageData&)),
        ui->actorAnimationView, SLOT(setActorImage(const ActorImageData&))
    );

    connect(
        ui->animationSelectListWidget, SIGNAL(animationSelected(AnimationData*, AnimationData*)),
        this, SLOT(onAnimationSelected(AnimationData*, AnimationData*))
    );

    connect(
        ui->animationTreeWidget, SIGNAL(animationDataChanged(AnimationData*)),
        this, SLOT(onAnimationDataChanged(AnimationData*))
    );

    connect(
        ui->actorImgeView, SIGNAL(cellSelected(int)),
        ui->actorCellView, SLOT(setCell(int))
    );

    connect(
        ui->mountPointList, SIGNAL(mountPointListChanged(const QList<AnimationMountPoint*>&)),
        ui->actorCellView, SLOT(setMountPoints(const QList<AnimationMountPoint*>&))
    );

    connect(
        ui->mountPointList, SIGNAL(currentMountPointChanged(AnimationMountPoint*)),
        ui->actorCellView, SLOT(selectCurrentMountPoint(AnimationMountPoint*))
    );

    connect(
        ui->actorCellView,SIGNAL(currentMountPointUpdated()),
        this, SLOT(onCellViewMountPointUpdated())
    );

    connect(
        ui->actorImgeView, SIGNAL(cellSelected(int)),
        this, SLOT(onImageCellSelected(int))
    );


#if 0
    QString filename = "/Users/kysaeed/work/qt/otemo-maker/OtemoMaker/otemo.png";
#else
    QString filename = "/Users/kysaeed/work/qt/otemo-maker/OtemoMaker/sprite_koneko.png";
#endif

    ActorImageData actorImage;
    bool isLoaded = actorImage.load(filename);
    actor = Actor(actorImage);

//    ui->actorAnimationView->setAnimaitonData(&actor.getAnimaitons());
//            actor.getAnimaitons();

    if (isLoaded) {
        ui->actorImgeView->setActorImage(actorImage);
        ui->actorCellView->setActorImage(actor.getImage());
        ui->animationSelectListWidget->addNewAnimation(actor.getImage()->getName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onImageCellSelected(AnimationFrame* frame)
{
    qDebug("MainWindow::onImageCellSelected() : entre");

    ui->animationTreeWidget->insertFrame(0, frame); //@
    setFrameOffset(frame->getOffset());

    AnimationData* data = ui->animationTreeWidget->createAnimationData();
    ui->actorAnimationView->setAnimaitonData(data);
//    ui->mountPointList->setCellData(); ??????
}

void MainWindow::onOffsetMoved(const QPoint &offset)
{
qDebug("MainWindow::onOffsetMoved() : %d,%d", offset.x(), offset.y());

    setFrameOffset(offset);

    AnimationFrameTreeItem* item = dynamic_cast<AnimationFrameTreeItem*>(ui->animationTreeWidget->currentItem());
    if (item == nullptr) {
        return;
    }

    AnimationFrame* frame = item->getFrame();
    frame->setOffset(offset);

    ui->animationTreeWidget->setOffset(offset);

    AnimationData* ad = ui->animationTreeWidget->createAnimationData();
    ui->actorAnimationView->setAnimaitonData(ad); //@@

}

void MainWindow::onAnimationTreeSelected(AnimationFrame* frame)
{
    qDebug("MainWindow::onAnimationTreeSelected : frame..[%d]", frame->getCell());

    ui->spinBoxFrameCount->setValue(frame->getFrameCount());
    ui->actorBuildView->setFrame(frame);
    setFrameOffset(frame->getOffset());
}

void MainWindow::onAnimationDataChanged(AnimationData *animation)
{
    ui->actorBuildView->clear();
    ui->actorAnimationView->setAnimaitonData(animation);
}

void MainWindow::onImageCellSelected(int cell)
{
    qDebug("MainWindow::onImageCellSelected : %d ***********", cell);

    if (actor.getImage() != nullptr) {
        ui->mountPointList->setCellData(actor.getImage()->getCellData(cell));
    }
}

void MainWindow::setFrameOffset(const QPoint &offset)
{
    bool isBlocked = false;

    isBlocked = ui->spinBoxOffsetX->signalsBlocked();
    ui->spinBoxOffsetX->blockSignals(true);
    ui->spinBoxOffsetX->setValue(offset.x());
    ui->spinBoxOffsetX->blockSignals(isBlocked);

    isBlocked = ui->spinBoxOffsetY->signalsBlocked();
    ui->spinBoxOffsetY->blockSignals(true);
    ui->spinBoxOffsetY->setValue(offset.y());
    ui->spinBoxOffsetY->blockSignals(isBlocked);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug("write!");

    QList<AnimationData*> animationList = ui->animationSelectListWidget->createAnimationList();
    QFile file("/tmp/otemo.oan");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug(" write failed....");
        return;
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    actor.setBoudingBox(ui->actorAnimationView->getBoundingBox());


    actor.setAnimations(animationList);
    actor.write(stream);

    file.close();

    QMessageBox::information(this, tr("SAVE"), tr("animation data stored"));
}

void MainWindow::on_pushButtonResetOffset_clicked()
{
    ui->actorBuildView->resetOffset();
}

void MainWindow::on_spinBoxFrameCount_valueChanged(int frameCount)
{
    ui->animationTreeWidget->setFrameCount(frameCount);
    ui->actorBuildView->setDefaultFrameCount(frameCount);

    AnimationData* animation = ui->animationTreeWidget->createAnimationData();
    ui->actorAnimationView->setAnimaitonData(animation);

}

void MainWindow::onAnimationSelected(AnimationData* currentAnimation, AnimationData* previousAnimation)
{
#ifdef QT_DEBUG
    qDebug("MainWindow::onAnimationSelected: ");
    if (currentAnimation != nullptr) {
        qDebug("   currentAnimation : cur-count= %d", currentAnimation->getFrameCount());
    }
    if (previousAnimation != nullptr) {
        qDebug("   previousAnimation : prev-count= %d", previousAnimation->getFrameCount());
    }
#endif

    ui->actorAnimationView->setAnimationPlayState(false);
    ui->actorAnimationView->setAnimaitonData(currentAnimation);
    ui->animationTreeWidget->setAnimationData(currentAnimation);
    ui->actorAnimationView->setAnimationPlayState(true);

    ui->lineEditAnimationName->setText(currentAnimation->getName());
}

void MainWindow::commitFrames()
{
    AnimationData* animation = ui->animationTreeWidget->createAnimationData();
    ui->animationSelectListWidget->setAniamtionData(animation);
}

void MainWindow::onCellViewMountPointUpdated()
{
    ui->mountPointList->updateCurrentItemText();
}

void MainWindow::on_spinBoxOffsetX_valueChanged(int x)
{
    QPoint offset(x, ui->spinBoxOffsetY->value());
    ui->actorBuildView->setOffset(offset);
}

void MainWindow::on_spinBoxOffsetY_valueChanged(int y)
{
    QPoint offset(ui->spinBoxOffsetX->value(), y);
    ui->actorBuildView->setOffset(offset);
}


void MainWindow::on_pushButtonAddAnimation_clicked()
{
    QString name = ui->lineEditAnimationName->text();
    ui->animationSelectListWidget->addNewAnimation(name);
}

void MainWindow::on_pushButtonAddEvent_clicked()
{
    // TEST
    {
        AnimationFrameEvent* e = new AnimationFrameEvent();
        ui->animationTreeWidget->addEvent(e);
    }

}

void MainWindow::on_pushButtonAddMountPoint_clicked()
{
    int id = ui->spinBoxMoundPointId->value();
    if (ui->mountPointList->addNewMountPoint(id, QPoint(10, 10))) {
        int nextId = ui->mountPointList->getNextId();
        ui->spinBoxMoundPointId->setValue(nextId);
    }
}
