#include "Headers/mmainwindow.h"

MMainWindow::MMainWindow(QWidget* parent):QMainWindow(parent){
    _manager = new GameWidgetManager(this);
    setCentralWidget(_manager->StackedWidget());
}

MMainWindow::~MMainWindow(){
    delete _manager;
}