#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <object.h>
#include <map.h>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void stoptime();
    void starttime();


private:
    QTimer *tim,*atim;
    Ui::MainWindow *ui;
    map *leftmap;
//protected:
//void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
