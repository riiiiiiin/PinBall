#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <object.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void playnow();

private:
    object* cob[50];
    int num;
    double t;
    object* pb;
    Ui::MainWindow *ui;

protected:
//void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
