#include <QVector>
#include "map.h"
#include "mydialog.h"
#include <QObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
map::map(Ui::MainWindow *mainwindow,QObject *parent):m_mainwindow(mainwindow),QObject{parent}
{

    t=0.01;
    pb=new ball(300,540,2,0,-30,5);//小球指针
    pa=new stwall(210,234.3,459,464.9,1);
    cob.push_back(pa);//0
    pa=0;
    pa=new stwall(234.3,258.6,464.9,470.9,1);
    cob.push_back(pa);//1
    pa=0;
    pa=new stwall(282.8,258.6,476.8,470.9,1);
    cob.push_back(pa);//1
    pa=0;
    pa=new cirwall(208,469,10.2,1);
    cob.push_back(pa);//2
    pa=0;
    pa=new cirwall(280.8,484.3,7.8,1);
    cob.push_back(pa);//3
    pa=0;
    pa=new stwall(206,278.8,479,491.8,1);
    cob.push_back(pa);//4
    pa=0;//左flipper,对应theleft
    pa=new stwall(390,365.7,459,464.9,1);
    cob.push_back(pa);//0
    pa=0;
    pa=new stwall(365.7,341.4,464.9,470.9,1);
    cob.push_back(pa);//1
    pa=0;
    pa=new stwall(317.2,341.4,476.8,470.9,1);
    cob.push_back(pa);//1
    pa=0;
    pa=new cirwall(392,469,10.2,1);
    cob.push_back(pa);//2
    pa=0;
    pa=new cirwall(319.2,484.3,7.8,1);
    cob.push_back(pa);//3
    pa=0;
    pa=new stwall(394,321.2,479,491.8,1);
    cob.push_back(pa);//4
    pa=0;//右flipper,对应theright
    pa=new drum(133,64,10,2);
    cob.push_back(pa);//8
    pa=0;
    pa=new drum(300,90,20,2);
    cob.push_back(pa);//9
    pa=0;
    pa=new drum(270,150,20,2);
    cob.push_back(pa);//10
    pa=0;
    pa=new drum(330,150,20,2);
    cob.push_back(pa);//11
    pa=0;//4个drum
    pa=new stwall(170,170,290,380,1);
    cob.push_back(pa);//12
    pa=0;
    pa=new kidney(190,220,290,400,2);
    cob.push_back(pa);//13
    pa=0;
    pa=new stwall(180,210,400,410,1);
    cob.push_back(pa);//14
    pa=0;
    pa=new cirwall(180,294,12,170,190,290,290,1);
    cob.push_back(pa);//15
    pa=0;
    pa=new cirwall(210,400,10,220,210,400,410,1);
    cob.push_back(pa);//16
    pa=0;
    pa=new cirwall(199.9,377.55,30,180,170,400,380,1);
    cob.push_back(pa);//17
    pa=0;//左腰子
    pa=new stwall(430,430,290,380,1);
    cob.push_back(pa);//18
    pa=0;
    pa=new kidney(410,380,290,400,2);
    cob.push_back(pa);//19
    pa=0;
    pa=new stwall(430,390,400,410,1);
    cob.push_back(pa);//20
    pa=0;
    pa=new cirwall(420,294,12,410,430,290,290,1);
    cob.push_back(pa);//21
    pa=0;
    pa=new cirwall(390,400,10,380,390,400,410,1);
    cob.push_back(pa);//22
    pa=0;
    pa=new cirwall(400.1,377.55,30,420,430,400,380,1);
    cob.push_back(pa);//23
    pa=0;//右腰子
    pa=new stwall(453,390,74,117,1);
    cob.push_back(pa);//24
    pa=0;
    pa=new stwall(430,390,150,117,1);
    cob.push_back(pa);//25
    pa=0;
    pa=new stwall(430,484,150,114,1);
    cob.push_back(pa);//26
    pa=0;
    pa=new stwall(484,453,114,74,1);
    cob.push_back(pa);//27
    pa=0;//右上角的四边形墙
    pa=new stwall(67,210,424,459,1);
    cob.push_back(pa);//28
    pa=0;//左下直线墙
    pa=new stwall(533,390,424,459,1);
    cob.push_back(pa);//29
    pa=0;//右下直线墙
    pa=new cirwall(300,1274.6,800,100,500,500,500,1);
    cob.push_back(pa);//30
    pa=0;//圆弧顶
    pa=new cirwall(343.326,136.22,180,173,181,78,214,1);
    cob.push_back(pa);//31
    pa=0;//轨道
    pa=new cirwall(339.835,144.28,150,205,200,210,90,1);
    cob.push_back(pa);//32
    pa=0;//轨道
    pa=new award(175,145,10);
    cob.push_back(pa);//33
    pa=0;//奖励点
    pa=new stwall(100,67,40,424,1);
    cob.push_back(pa);//34
    pa=0;//左壁
    pa=new stwall(500,533,40,424,1);
    cob.push_back(pa);//35
    pa=0;//右壁
    n=cob.size();
}


void map::onestep(){

    pb->jump(t);//小球斜抛运动
    for(int i=0;i<4;i++){
        cob[i]->pset(theleft,1);
    }
    for(int i=0;i<n;i++){
        if(cob[i]->bounce(pb)){//发生碰撞
            cob[i]->ef=true;
            score+=cob[i]->bonus;
            //m_mainwindow->
            break;
        }
    }
    if(!pb->isalive()) {
        m_mainwindow->stoptime();
        mydialog con(score);
        con.show();
    }
}

void map::oneeffect(){
    for(int i=0;i<n;i++){
        if(cob[i]->ef){//发生碰撞
            cob[i]->effect();//画面&声音特效+分数变化
            cob[i]->ef=false;

        }
    }
}

map::~map(){
    for(int i=0;i<n;i++){
        if(cob[i]) delete cob[i];
    }
    if(pb) delete pb;
}

