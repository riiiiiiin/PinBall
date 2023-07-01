#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>
#include <QApplication>

#include "Game/Headers/gamewindow.h"
#include "FrameWork/Headers/pausemenu.h"

class GameMap : public QWidget
{
    Q_OBJECT
private:
    QVector<QPushButton *> _buttons;
    QVector<QLabel*> _score_display;
    GameWindow* _game_window;

    SwitchToMapEditorConfirm *_switch_confirm;
    NewGameConfirm *_new_game_confirm;
    PauseMenu *_pmenu;
    
    QVector<QSoundEffect *> _sound_effects;
    QSoundEffect *_music;
    QWidget *_pMask;
    QGraphicsBlurEffect *_blure;

    int _score;

    int& _theme_index;
    QVector<ThemePack>& _theme_packs;
    
public:
    GameMap(int&,QVector<ThemePack>&,QSoundEffect *, QVector<QSoundEffect *>,QWidget *parent = nullptr);
    ~GameMap();
    void paintEvent(QPaintEvent *e) override;

private slots:
    void on_pauseButtonClicked();
    void on_pauseMenuClosed();
    void on_exitRequested();

    void on_switchButtonClicked();
    void on_switchConfirmClosed();
    void on_switchRequested();

    void on_gameOver();
    void handle_setScore(int,int);
    void on_newGameRequested();
public slots:
    void on_newMapSet(QVector<EncodedMapElement> newmap,int);

signals:
    void exitRequest();
    void switchRequest();
    void newGameRequest();
    void pauseRequest();
    void resumeRequest();
    void setMap(QVector<EncodedMapElement> newmap,int);

protected:

};

#endif
