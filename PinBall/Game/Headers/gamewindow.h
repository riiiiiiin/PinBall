#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QList>

#include <Game/Headers/map.h>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    int highest;//最高分
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void stoptime();//两个计时器停止
    void starttime();//两个计时器开始
public slots:
    void newgame();//恭喜分数窗口click之后开始新游戏
    
    void youaredead();//即gameover
    void showscore();//游戏中每次分数变动后的重新显示
    void pause();
    void resume();
    void on_scoreChanged(int,int);
    void on_mapSet(QList<EncodedMapElement> newmap,int);
signals:
    void pressZ();
    void pressM();
    void releaseZ();
    void releaseM();
    void gameOverRequest();
    void scoreChange(int,int);
    void setMap(QList<EncodedMapElement> newmap,int);
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    QTimer *tim,*atim;
    map *leftmap;


//protected:
//void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
