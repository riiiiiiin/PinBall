
#include "headers/mainwindow.h"
#include "headers/mdragcontainer.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MDragContainer* d = new MDragContainer(this);
    //setStyleSheet("background-color:black");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e){

    QPixmap* bg = new QPixmap;
    bg->load(":/new/prefix1/Nebula.png");

    QPainter painter(this);
    painter.drawPixmap(0,0,*bg);
    QMainWindow::paintEvent(e);
}


