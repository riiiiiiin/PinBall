
#include "headers/mainwindow.h"
#include "headers/mdragcontainers.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MDragContainer* d = new MDragContainer(QPoint(600,300),this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


