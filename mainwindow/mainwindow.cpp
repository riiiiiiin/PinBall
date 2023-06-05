#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
#include <QTimer>
#include "mydialog.h"
#include "ui_mydialog.h"
#include "map.h"
#include <QKeyEvent>

//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
//    ui->pushButton->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
//}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->formLayout->set
    died=new mydialog();
    leftmap=new map(this);
    setFixedSize(960, 540);
    tim=new QTimer();
    tim->setInterval(5);
    connect(tim,SIGNAL(timeout()),leftmap,SLOT(onestep()));
    atim=new QTimer();
    atim->setInterval(30);
    connect(atim,SIGNAL(timeout()),leftmap,SLOT(oneeffect()));
    connect(leftmap,SIGNAL(dead()),this,SLOT(youaredead()));
    connect(died,SIGNAL(new_game()),this,SLOT(newgame()));
    connect(this,SIGNAL(pressZ()),leftmap,SLOT(leftup()));
    connect(this,SIGNAL(pressM()),leftmap,SLOT(rightup()));
    connect(this,SIGNAL(releaseZ()),leftmap,SLOT(leftdown()));
    connect(this,SIGNAL(releaseM()),leftmap,SLOT(rightdown()));
    connect(leftmap,SIGNAL(scorechange(int,int)),this,SLOT(showscore()));
    ui->setupUi(this);
    starttime();
}

void MainWindow::pause(){
    stoptime();
}

void MainWindow::resume(){
    starttime();
}
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Z)  emit pressZ();
    if(event->key()==Qt::Key_M)  emit pressM();
    QWidget::keyPressEvent(event);
    // 发送按下信号
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if(event->key()==Qt::Key_Z)  emit releaseZ();
    if(event->key()==Qt::Key_M)  emit releaseM();
    QWidget::keyReleaseEvent(event);
}

void MainWindow::starttime(){
    tim->start();
    atim->start();
}
void MainWindow::stoptime(){
    tim->stop();
    atim->stop();
}
MainWindow::~MainWindow()
{

    delete ui;
}
void MainWindow::youaredead(){
    stoptime();
    ui->score->setNum(leftmap->score);
    if(highest<leftmap->score){
        highest=leftmap->score;
        leftmap->highest=highest;
        ui->highest->setNum(highest);
    }
    died->getscore(leftmap->score);
    died->show();
}

void MainWindow::newgame(){
    //qDebug()<<'a';
    died->close();
    leftmap->clearstatic();
    leftmap->cleardynamic();
    leftmap->clearmapdynamic();
    leftmap->clearmapstatic();
    leftmap->rebuildstatic();
    leftmap->drawstatic();
    if(!(leftmap->ifsetmap)){//如果进行了setmap
        leftmap->rebuilddynamic();
        leftmap->drawscore();

    }
    leftmap->ifsetmap=false;
    starttime();
}

void MainWindow::showscore(){
    ui->score->setNum(leftmap->score);
}


