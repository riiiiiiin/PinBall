#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>

#include <Game/Headers/map.h>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    int highest;//最高分
    GameWindow(int&,QVector<ThemePack*>&,QWidget *parent = nullptr);
    ~GameWindow();
    void stoptime();//两个计时器停止
    void starttime();//两个计时器开始
public slots:
    void newgame();//恭喜分数窗口click之后开始新游戏
    void youaredead();//即gameover

    void pause();
    void resume();

    void on_scoreChanged(int,int);
    
    void on_mapSet(QVector<EncodedMapElement> newmap,int);

    void on_playSERequested(enumSoundEffect);
signals:
    void pressZ();
    void pressM();
    void releaseZ();
    void releaseM();

    void gameOverRequest();
    void scoreChange(int,int);
    void gamePauseRequest();

    void setMap(QVector<EncodedMapElement> newmap,int);
    void playSERequest(enumSoundEffect);
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    QTimer *tim,*atim;
    map *leftmap;

    int& _theme_index;
    QVector<ThemePack*>& _theme_packs;
};
#endif // MAINWINDOW_H
