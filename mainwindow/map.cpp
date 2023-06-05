#include <QVector>
#include "map.h"
#include "mydialog.h"
#include <QObject>
#include <cmath>
#include <QTimer>
//#include "encodedmap.h"
#include <QLabel>
#include <QWidget>
#include <QPainter>
map::map(QWidget *parent):pparent(parent)
{
    highest=0;
    score=0;
    ifsetmap=false;
    t=0.005;
    rebuildstatic();
    rebuilddynamic();
    drawstatic();
    drawscore();
}


void map::onestep(){
    int lc=0,rc=0;
    moveupleft=false;//是否在上升
    moveupright=false;
    double rx,ry;
    pb->jump();//小球斜抛运动
    //qDebug()<<pb->getx()<<' '<<pb->gety();
    if(theleft>-0.78&&upleft==true){
        theleft-=t*wup;
        if(theleft<-0.78) theleft=-0.78;
        lc=1;
        moveupleft=true;
    }
    else if(theleft<0.24&&upleft==false){
        theleft+=t*wdo;
        if(theleft>0.24) theleft=0.24;
        lc=1;
    }
    if(theright>-0.78&&upright==true){
        theright-=t*wup;
        if(theright<-0.78) theright=-0.78;
        rc=1;
        moveupright=true;
    }
    else if(theright<0.24&&upright==false){
        theright+=t*wdo;
        if(theright>0.24) theright=0.24;
        rc=1;
    }
    if(lc){
        rx=25*cos(theleft);
        ry=25*sin(theleft);
        cob[0]->change(leftx,leftx+rx,y,y+ry,int(upleft),moveupleft);
        cob[1]->change(leftx+rx,leftx+2*rx,y+ry,y+2*ry,int(upleft)*2,moveupleft);
        cob[2]->change(leftx+2*rx,leftx+3*rx,y+2*ry,y+3*ry,int(upleft)*3,moveupleft);
        cob[4]->change(leftx+3*rx-2,y+3*ry+7.5,0,0,int(upleft),moveupleft);
        cob[5]->change(leftx-4,leftx+3*rx-4,y+20,y+3*ry+15,0,moveupleft);
    }
    if(rc){
        rx=25*cos(theright);
        ry=25*sin(theright);
        cob[6]->change(rightx,rightx-rx,y,y+ry,int(upright),moveupright);
        cob[7]->change(rightx-rx,rightx-2*rx,y+ry,y+2*ry,int(upright)*2,moveupright);
        cob[8]->change(rightx-2*rx,rightx-3*rx,y+2*ry,y+3*ry,int(upright)*3,moveupright);
        cob[10]->change(rightx-3*rx+2,y-3*ry+7.5,0,0,int(upright),moveupright);
        cob[11]->change(rightx+4,rightx-3*rx+4,y+20,y+3*ry+15,0,moveupright);
    }
    int n=cob.size();
    int m=cobd.size();
    for(int i=0;i<n;i++){
        if(cob[i]->bounce(pb)){
            break;
        }
    }
    for(int i=0;i<m;i++){
        if(cobd[i]->bounce(pb)&(!cobd[i]->noaward)){//发生碰撞
            //qDebug()<<"bang!!!";
            //qDebug()<<i;
            if(cobd[i]->bonus!=0){
                score+=cobd[i]->bonus;
                emit scorechange(score,highest);
            }
            break;
        }
    }
    if(!pb->isalive()) {

        emit dead();
    }
}

void map::oneeffect(){
    int m=cobd.size();
    for(int i=0;i<m;i++){
        if(cobd[i]->ef){//发生碰撞
            cobd[i]->effect();//画面&声音特效+分数变化
            cobd[i]->ef=false;
        }
    }
    updateball();
    updateflipper();
}

map::~map(){
    clearmapdynamic();
    clearmapstatic();
    clearstatic();
    cleardynamic();
}

void map::leftup(){
    upleft=true;
}

void map::leftdown(){
    upleft=false;
}

void map::rightdown(){
    upright=false;
}

void map::rightup(){
    upright=true;
}

void map::rebuildstatic(){
    score=0;
    emit scorechange(score,highest);
    upleft=false;//Z按键状态
    upright=false;//M按键状态
    moveupleft=false;//是否在上升
    moveupright=false;
    theleft=0.24;
    theright=0.24;//初始角
    wup=3;//上升角速度
    wdo=1;//下降角速度
    y=459;
    leftx=210;
    rightx=390;
    gball=200;

    pb=new ball(300,270,10,30,-300,gball);//小球指针
    pa=new stwall(210,234.3,459,464.9,1);
    cob.push_back(pa);//0
    pa=0;
    pa=new stwall(234.3,258.6,464.9,470.9,1);
    cob.push_back(pa);//1
    pa=0;
    pa=new stwall(282.8,258.6,476.8,470.9,1);
    cob.push_back(pa);//2
    pa=0;
    pa=new cirwall(208,469,10.2,1);
    cob.push_back(pa);//3
    pa=0;
    pa=new cirwall(280.8,484.3,7.8,1);
    cob.push_back(pa);//4
    pa=0;
    pa=new stwall(206,278.8,479,491.8,1);
    cob.push_back(pa);//5
    pa=0;//左flipper,对应theleft
    pa=new stwall(390,365.7,459,464.9,1);
    cob.push_back(pa);//6
    pa=0;
    pa=new stwall(365.7,341.4,464.9,470.9,1);
    cob.push_back(pa);//7
    pa=0;
    pa=new stwall(317.2,341.4,476.8,470.9,1);
    cob.push_back(pa);//8
    pa=0;
    pa=new cirwall(392,469,10.2,1);
    cob.push_back(pa);//9
    pa=0;
    pa=new cirwall(319.2,484.3,7.8,1);
    cob.push_back(pa);//10
    pa=0;
    pa=new stwall(394,321.2,479,491.8,1);
    cob.push_back(pa);//11
    pa=0;//右flipper,对应theright
    pa=new stwall(453,390,74,117,1);
    cob.push_back(pa);//12
    pa=0;
    pa=new stwall(430,390,150,117,1);
    cob.push_back(pa);//13
    pa=0;
    pa=new stwall(430,484,150,114,1);
    cob.push_back(pa);//14
    pa=0;
    pa=new stwall(484,453,114,74,1);
    cob.push_back(pa);//15
    pa=0;//右上角的四边形墙
    pa=new stwall(67,210,424,459,0.7);
    cob.push_back(pa);//16
    pa=0;//左下直线墙
    pa=new stwall(533,390,424,459,0.7);
    cob.push_back(pa);//17
    pa=0;//右下直线墙
    pa=new cirwall(300,814.6,800,100,500,40,40,1);
    cob.push_back(pa);//18
    pa=0;//圆弧顶
    pa=new cirwall(343.326,136.22,180,173,181,78,214,1);
    cob.push_back(pa);//19
    pa=0;//轨道
    pa=new cirwall(339.835,144.28,150,205,200,210,90,1);
    cob.push_back(pa);//20
    pa=0;//轨道
    pa=new stwall(100,67,40,424,1);
    cob.push_back(pa);//21
    pa=0;//左壁
    pa=new stwall(500,533,40,424,1);
    cob.push_back(pa);//22
    pa=0;//右壁
}
void map::rebuilddynamic(){
    pa=new award(175,145,10);
    cobd.push_back(pa);//37
    pa=0;//奖励点
    pa=new award(133,64,10);
    cobd.push_back(pa);//12
    pa=0;
    pa=new drum(300,90,20,1.5);
    cobd.push_back(pa);//13
    pa=0;
    pa=new drum(270,150,20,1.5);
    cobd.push_back(pa);//14
    pa=0;
    pa=new drum(330,150,20,1.5);
    cobd.push_back(pa);//15
    pa=0;//3个drum
    pa=new stwall(170,170,290,380,1);
    cobd.push_back(pa);//16
    pa=0;
    pa=new kidney(190,220,290,400,1.5);
    cobd.push_back(pa);//17
    pa=0;
    pa=new stwall(180,210,400,410,1);
    cobd.push_back(pa);//18
    pa=0;
    pa=new cirwall(180,294,12,1);
    cobd.push_back(pa);//19
    pa=0;
    pa=new cirwall(210,400,10,1);
    cobd.push_back(pa);//20
    pa=0;
    pa=new cirwall(199.9,377.55,30,1);
    cobd.push_back(pa);//21
    pa=0;//左腰子
    pa=new stwall(430,430,290,380,1);
    cobd.push_back(pa);//22
    pa=0;
    pa=new kidney(410,380,290,400,1.5);
    cobd.push_back(pa);//23
    pa=0;
    pa=new stwall(430,390,400,410,1);
    cobd.push_back(pa);//24
    pa=0;
    pa=new cirwall(420,294,12,1);
    cobd.push_back(pa);//25
    pa=0;
    pa=new cirwall(390,400,10,1);
    cobd.push_back(pa);//26
    pa=0;
    pa=new cirwall(400.1,377.55,30,1);
    cobd.push_back(pa);//27
    pa=0;//右腰子
}
void map::clearmapstatic(){
    int n=cob.size();
    for(int i=0;i<n;i++){
        if(cob[i]) delete cob[i];
    }
    cob.clear();
}
void map::clearmapdynamic(){
    int m=cobd.size();
    for(int i=0;i<m;i++){
        if(cobd[i]) delete cobd[i];
    }
    cobd.clear();
}
void map::clearstatic(){
    int m=which.size();
    for(int i=0;i<m;i++) delete which[i];
    which.clear();
}

void map::cleardynamic(){
    int m=changeable.size();
    for(int i=0;i<m;i++) delete changeable[i];
    changeable.clear();
}

void map::updateball()
{
    which[1]->setGeometry(pb->getx()-10,pb->gety()-10,20, 20);
}
void map::updateflipper(){
    plabel=which[2];
//    delete plabel;
//    plabel = new QLabel();
    QTransform transform;
    transform.translate(40, 20);
    transform.rotate(-(0.24-theleft)/3.1416*180);
    pix.load(":/new/prefix1/shifted_left_flipper.png");
    pix = pix.transformed(transform);
    transform.translate(40, 10);
    pix = pix.scaled( 198,39);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(92,454, 198,39);
    plabel->setFixedSize(198,39);
    plabel->show();
    plabel=which[3];
    //    delete plabel;
    //    plabel = new QLabel();
    QTransform transform1;
    transform1.translate(40, 20);
    transform1.rotate((0.24-theright)/3.1416*180);
    pix.load(":/new/prefix1/shifted_right_flipper.png");
    pix = pix.transformed(transform1);
    transform1.translate(40, 10);
    pix = pix.scaled( 198,39);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(306,454, 198,39);
    plabel->setFixedSize(198,39);
    plabel->show();
//    QPainter painter;
//    pix.load(":/new/prefix1/shifted_left_flipper.png");
//    painter.translate(-40,-20);
//    painter.rotate(-(0.24-theleft)/3.1416*180);
//    painter.translate(40,20);
//    painter.drawPixmap(191, 454, 99, 39, pix);
//    plabel=which[2];
////    delete plabel;
////    plabel = new QLabel();
//    plabel->setPixmap(pix);
//    plabel->setMask(pix.mask());
//    plabel->setGeometry(191,454, 99,39);
//    plabel->setFixedSize(99,39);
//    plabel->show();

}
void map::drawstatic(){
    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/background.png");
    pix = pix.scaled(600, 540);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(0, 0, 600, 540);
    plabel->setFixedSize(600, 540);
    plabel->show();
    which.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/ball.png");
    pix = pix.scaled(20, 20);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(pb->getx()-10, pb->gety()-10, 20, 20);
    plabel->setFixedSize(20, 20);
    plabel->show();
    which.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/shifted_left_flipper.png");
    pix = pix.scaled( 198,39);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(92,454, 198,39);
    plabel->setFixedSize( 198,39);
    plabel->show();
    which.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/shifted_right_flipper.png");
    pix = pix.scaled( 198,39);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(306,454, 198,39);
    plabel->setFixedSize( 198,39);
    plabel->show();
    which.push_back(plabel);
    plabel=0;

}

void map::drawscore(){

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/new_drum.png");
    pix = pix.scaled(40,40);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(280,70, 40,40);
    plabel->setFixedSize(40,40);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/new_drum.png");
    pix = pix.scaled(40,40);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(250,130, 40,40);
    plabel->setFixedSize(40,40);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/new_drum.png");
    pix = pix.scaled(40,40);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(310,130, 40,40);
    plabel->setFixedSize(40,40);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/shifted_left_kidney.png");
    pix = pix.scaled(51,134);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(170,280, 40,40);
    plabel->setFixedSize(51,134);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/shifted_right_kidney.png");
    pix = pix.scaled(51,134);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(375,280, 40,40);
    plabel->setFixedSize(51,134);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/new_bonus_point.png");
    pix = pix.scaled(20,20);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(123,54, 20,20);
    plabel->setFixedSize(20,20);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

    plabel=new QLabel(pparent);
    pix.load(":/new/prefix1/new_bonus_point.png");
    pix = pix.scaled(20,20);
    plabel->setPixmap(pix);
    plabel->setMask(pix.mask());
    plabel->setGeometry(165,135, 20,20);
    plabel->setFixedSize(20,20);
    plabel->show();
    changeable.push_back(plabel);
    plabel=0;

}

//void setmap(QList<EncodedMapElement> newmap,int gg){
//    clearmapstatic();
//    clearmapdynamic();
//    clearstatic();
//    cleardynamic();
//    rebuildstatic();
//    drawstatic();
//    QList<EncodedMapElement>::const_iterator m=newmap.begin();
//    double x,y;
//    for(;m!=newmap.end();m++){
//        x1=m->_x;
//        y1=m->_y;
//        switch(m->_element_type){
//        case 1:
//            x=x1-220;
//            y=y1-400;
//            pa=new stwall(170+x,170+x,290+y,380+y,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new kidney(190+x,220+x,290+y,400+y,1.3);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new stwall(180+x,210+x,400+y,410+y,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(180+x,294+y,12,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(210+x,400+y,10,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(199.9+x,377.55+y,30,1);
//            cobd.push_back(pa);
//            pa=0;//左腰子
//            plabel=new QLabel(pparent);
//            pix.load(":/new/prefix1/shifted_left_kidney.png");
//            pix = pix.scaled(51,134);
//            plabel->setPixmap(pix);
//            plabel->setMask(pix.mask());
//            plabel->setGeometry(x1-50,y1-110, 51,134);
//            plabel->setFixedSize(51,134);
//            plabel->show();
//            changeable.push_back(plabel);
//            plabel=0;
//        case 2:
//            x=x1-380;
//            y=y1-400;
//            pa=new stwall(430+x,430+x,290+y,380+y,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new kidney(410+x,380+x,290+y,400+y,1.3);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new stwall(430+x,390+x,400+y,410+y,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(420+x,294+y,12,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(390+x,400+y,10,1);
//            cobd.push_back(pa);
//            pa=0;
//            pa=new cirwall(400.1+x,377.55+y,30,1);
//            cobd.push_back(pa);
//            pa=0;//右腰子
//            plabel=new QLabel(pparent);
//            pix.load(":/new/prefix1/shifted_right_kidney.png");
//            pix = pix.scaled(51,134);
//            plabel->setPixmap(pix);
//            plabel->setMask(pix.mask());
//            plabel->setGeometry(x1-3,y1-110, 51,134);
//            plabel->setFixedSize(51,134);
//            plabel->show();
//            changeable.push_back(plabel);
//            plabel=0;
//        case 3:
//            pa=new drum(x1,y1,20,1.2);
//            cobd.push_back(pa);
//            pa=0;
//            plabel=new QLabel(pparent);
//            pix.load(":/new/prefix1/new_drum.png");
//            pix = pix.scaled(40,40);
//            plabel->setPixmap(pix);
//            plabel->setMask(pix.mask());
//            plabel->setGeometry(x1-20,y1-20, 40,40);
//            plabel->setFixedSize(40,40);
//            plabel->show();
//            changeable.push_back(plabel);
//            plabel=0;
//        case 4:
//            pa=new award(x1,y1,10);
//            cobd.push_back(pa);
//            pa=0;
//            plabel=new QLabel(pparent);
//            pix.load(":/new/prefix1/new_bonus_point.png");
//            pix = pix.scaled(20,20);
//            plabel->setPixmap(pix);
//            plabel->setMask(pix.mask());
//            plabel->setGeometry(x1-10,y1-10, 20,20);
//            plabel->setFixedSize(20,20);
//            plabel->show();
//            changeable.push_back(plabel);
//            plabel=0;
//        }
//    }
//ifsetmap=true;
//pb=new ball(300,270,10,30,-300,gg);//小球指针
//}





