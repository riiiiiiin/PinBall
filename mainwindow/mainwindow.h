#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <object.h>
#include <map.h>
#include <iostream>
#include <mydialog.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int highest;//最高分
    mydialog  *died;//恭喜分数窗口
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void stoptime();//两个计时器停止
    void starttime();//两个计时器开始
public slots:
    void newgame();//恭喜分数窗口click之后开始新游戏
    void youaredead();//死亡后弹出恭喜分数窗口
    void showscore();//游戏中每次分数变动后的重新显示

private:
    QTimer *tim,*atim;
    Ui::MainWindow *ui;
    map *leftmap;


//protected:
//void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
