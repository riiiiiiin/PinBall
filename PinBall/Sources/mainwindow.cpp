#include "Headers/mainwindow.h"

MainWindow::MainWindow(QWidget* parent):QMainWindow(parent){
    _manager = new GameWidgetManager(this);
    setCentralWidget(_manager->StackedWidget());
}

MainWindow::~MainWindow(){
    delete _manager;
}