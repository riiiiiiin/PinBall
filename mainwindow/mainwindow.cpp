#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
//#include <QMouseEvent>

//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
//    ui->pushButton->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
//}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    num=3;//object除小球，数目
    t=0.05;
    pb=new ball(1,1,1,1,1,1);//小球指针
    cob[0]=new stwall(20,10,40,50,0.1);
    cob[1]=new stwall(20,10,40,50,0.1);
    cob[2]=new cirwall(2,2,2,1,1,1,1,0.1);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    for(int i=0;i<num;i++){
        if(cob[i]) delete cob[i];
    }
    if(pb) delete pb;
    delete ui;
}

void MainWindow::playnow(){
    while(pb->isalive()){
        ui->zuobiao->setNum(pb->getx());
        pb->jump(t);//小球斜抛运动
        for(int i=0;i<num;i++){
            if(cob[i]->bounce(pb)){//发生碰撞
                cob[i]->effect();//画面&声音特效+分数变化
                break;
            }
        }
    }
    //弹出分数结算窗口，如何重新调用构造函数？两个error？分数怎么弄？
}
