#include "mainwindow.h"
#include "object.h"
#include <QTimer>
#include "map.h"
#include <QKeyEvent>

//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
//    ui->pushButton->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
//}
GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setGeometry(0, 0, 600, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    //ui->formLayout->set
    leftmap=new map(this);
    setFixedSize(600, 540);
    tim=new QTimer();
    tim->setInterval(5);
    connect(tim,SIGNAL(timeout()),leftmap,SLOT(onestep()));
    atim=new QTimer();
    atim->setInterval(30);
    connect(atim,SIGNAL(timeout()),leftmap,SLOT(oneeffect()));
    connect(leftmap,SIGNAL(dead()),this,SLOT(youaredead()));
    connect(this,SIGNAL(pressZ()),leftmap,SLOT(leftup()));
    connect(this,SIGNAL(pressM()),leftmap,SLOT(rightup()));
    connect(this,SIGNAL(releaseZ()),leftmap,SLOT(leftdown()));
    connect(this,SIGNAL(releaseM()),leftmap,SLOT(rightdown()));
    connect(leftmap,SIGNAL(scorechange(int,int)),this,SLOT(showscore()));
    connect(leftmap,&map::scorechange,this,on_scoreChanged);
    connect(this,&GameWindow::setMap,leftmap,&map::setmap);
    starttime();
}

void GameWindow::pause(){
    stoptime();
}
void GameWindow::resume(){
    starttime();
}
void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Z)  emit pressZ();
    if(event->key()==Qt::Key_M)  emit pressM();
    QWidget::keyPressEvent(event);
    // 发送按下信号
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    if(event->key()==Qt::Key_Z)  emit releaseZ();
    if(event->key()==Qt::Key_M)  emit releaseM();
    QWidget::keyReleaseEvent(event);
}

void GameWindow::starttime(){
    tim->start();
    atim->start();
}
void GameWindow::stoptime(){
    tim->stop();
    atim->stop();
}
GameWindow::~GameWindow()
{
    delete leftmap;
    delete tim;
    delete atim;
}
void GameWindow::youaredead(){
    stoptime();
    if(highest<leftmap->score){
        highest=leftmap->score;
    }
    emit gameOverRequest();
}

void GameWindow::newgame(){
    //qDebug()<<'a';
    leftmap->clearmap();
    leftmap->rebuildmap();
    starttime();
}

void GameWindow::showscore(){
    
}

void GameWindow::on_scoreChanged(int cur,int max){
    emit scoreChange(cur,max);
}

void GameWindow::on_mapSet(QList<EncodedMapElement> newmap,int gravity){
    leftmap->rebuildmap(newmap,gravity);
    starttime();
}
