#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QTime>
#include <QRandomGenerator>

#include "FrameWork/Headers/gamewidgetmanager.h"

class MainWindow:public QMainWindow{
private:
    GameWidgetManager* _manager;
public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow();
};

#endif