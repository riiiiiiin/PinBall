#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>

#include "pausemenu.h"

class GameMap : public QWidget
{
    Q_OBJECT
private:
    QList<QPushButton *> _buttons;
    QList<QLabel*> _score_display;

    SwitchToMapEditorConfirm *_switch_confirm;
    NewGameConfirm *_new_game_confirm;
    PauseMenu *_pmenu;
    
    QList<QSoundEffect *> _sound_effects;
    QSoundEffect *_music;
    QWidget *_pMask;
    QGraphicsBlurEffect *_blure;

public:
    GameMap(QWidget *parent = nullptr);
    ~GameMap();
    void paintEvent(QPaintEvent *e) override;
    void setSounds(QSoundEffect *, QList<QSoundEffect *>);
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

signals:
    void exitRequest();
    void switchRequest();
    void newGameRequest();
};

#endif