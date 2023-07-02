#include <QTimer>
#include <QKeyEvent>

#include "Game/Headers/gamewindow.h"
#include "Game/Headers/object.h"
#include "Game/Headers/map.h"

GameWindow::GameWindow(int& theme_index,QVector<ThemePack*>& themes,QWidget *parent)
    : QWidget(parent),_theme_index(theme_index),_theme_packs(themes)
{
    setFocusPolicy(Qt::StrongFocus);
    setGeometry(0, 0, 600, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    //ui->formLayout->set
    leftmap=new map(_theme_index,_theme_packs,this);
    setFixedSize(600, 540);
    tim=new QTimer();
    tim->setInterval(2);
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
    // qDebug()<<"KeyPressed";
    switch(event->key()){
        case Qt::Key_Z:{
            emit pressZ();
            break;
        }
        case Qt::Key_M:{
            emit pressM();
            break;
        }
    }
    QWidget::keyPressEvent(event);
    // 发送按下信号
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    // qDebug()<<"KeyReleased";
    if(event->key()==Qt::Key_Z)  emit releaseZ();
    if(event->key()==Qt::Key_M)  emit releaseM();
    QWidget::keyReleaseEvent(event);
}

void GameWindow::starttime(){
    qDebug()<<"time started";
    activateWindow();
    tim->start();
    atim->start();
}
void GameWindow::stoptime(){
    qDebug()<<"time stopped";
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
        leftmap->highest=highest;
    }
    emit gameOverRequest();
}

void GameWindow::newgame(){
    leftmap->rebuild_map();
    leftmap->redraw_map();
    starttime();
}

void GameWindow::showscore(){
    
}

void GameWindow::on_scoreChanged(int cur,int max){
    emit scoreChange(cur,max);
}

void GameWindow::on_mapSet(QVector<EncodedMapElement> newmap,int gravity){
    leftmap->setmap(newmap,gravity);
    leftmap->rebuild_map();
    leftmap->redraw_map();
    starttime();
}
