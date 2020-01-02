#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "animationdata.h"
#include "animationframe.h"
#include "actorimagedata.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->actorBuildView, SIGNAL(cellSelected(const AnimationFrame&)),
        this, SLOT(onImageCellSelected(const AnimationFrame&))
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
        ui->animationSelectListWidget, SIGNAL(animationUnselected(AnimationSelectListItem*)),
        this, SLOT(onAnimationUnselected(AnimationSelectListItem*))
    );

    connect(
        ui->animationTreeWidget, SIGNAL(animationDataChanged(AnimationData*)),
        ui->actorAnimationView, SLOT(setAnimaitonData(AnimationData*))
    );

    ActorImageData actorImage;
    bool isLoaded = actorImage.load("/Users/kysaeed/work/qt/OtemoMaker/otemo.png");
//    bool isLoaded = actorImage.load("/Users/kysaeed/work/qt/OtemoMaker/sprite_koneko.png");
    qDebug("MainWindow::MainWindow : img laod result = %d", isLoaded);

    ui->actorImgeView->setActorImage(actorImage);
    ui->animationSelectListWidget->addNewAnimation("Animation def");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onImageCellSelected(const AnimationFrame& frame)
{
    qDebug("MainWindow::onImageCellSelected() : entre");

    ui->animationTreeWidget->insertFrame(0, new AnimationFrame(frame)); //@
    setFrameOffset(frame.getOffset());

    AnimationData* data = ui->animationTreeWidget->createAnimationData();
    ui->actorAnimationView->setAnimaitonData(data);
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
//    item->setFrame(frame);

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

    qDebug("animation-ilst : count=%d", animationList.size());
    stream << static_cast<int32_t>(animationList.size());
    foreach (const AnimationData* animation, animationList) {
        animation->write(stream);
        qDebug(" frame count = %d", animation->getFrameCount());
    }
    file.close();
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
}

void MainWindow::onAnimationUnselected(AnimationSelectListItem* previousItem)
{
    qDebug("MainWindow::onAnimationUnselected: enter (data-count = %d)", previousItem->getAnimation()->getFrameCount());

//    previousItem->setAnimation(ui->animationTreeWidget->createAnimationData());
}

void MainWindow::commitFrames()
{
    AnimationData* animation = ui->animationTreeWidget->createAnimationData();
    ui->animationSelectListWidget->setAniamtionData(animation);
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
    ui->animationSelectListWidget->addNewAnimation("Animation!");
}
