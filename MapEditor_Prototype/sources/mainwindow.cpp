
#include "headers/mainwindow.h"
#include "headers/mdragcontainer.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MDragContainer* d = new MDragContainer(this);
    setStyleSheet("background-color:green");
}

MainWindow::~MainWindow()
{
    delete ui;
}


