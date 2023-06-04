#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "Headers/gamewidgetmanager.h"

class MMainWindow:public QMainWindow{
private:
    GameWidgetManager* _manager;
public:
    MMainWindow(QWidget* parent=nullptr);
    ~MMainWindow();
};

#endif