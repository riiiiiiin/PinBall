#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "object.h"
#include <QTimer>
#include "mydialog.h"
#include "ui_mydialog.h"
#include "map.h"
//#include <QMouseEvent>

//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
//    ui->pushButton->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
//}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    leftmap=new map(ui);
    setFixedSize(960, 540);
    tim=new QTimer();
    tim->setInterval(12);
    connect(*tim,SIGNAL(timeout()),leftmap,SLOT(onestep()));
    atim=new QTimer();
    atim->setInterval(30);
    connect(*atim,SIGNAL(timeout()),leftmap,SLOT(oneeffect()));

    ui->setupUi(this);

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




