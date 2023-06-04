#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>
#include <QApplication>

#include "Natsume/mainwindow.h"
#include "pausemenu.h"

class GameMap : public QWidget
{
    Q_OBJECT
private:
    QList<QPushButton *> _buttons;
    QList<QLabel*> _score_display;
    GameWindow* _game_window;

    SwitchToMapEditorConfirm *_switch_confirm;
    NewGameConfirm *_new_game_confirm;
    PauseMenu *_pmenu;
    
    QList<QSoundEffect *> _sound_effects;
    QSoundEffect *_music;
    QWidget *_pMask;
    QGraphicsBlurEffect *_blure;

    int _score;
    
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
public slots:
    void on_newMapSet(QList<EncodedMapElement> newmap,int);

signals:
    void exitRequest();
    void switchRequest();
    void newGameRequest();
    void pauseRequest();
    void resumeRequest();
    void setMap(QList<EncodedMapElement> newmap,int);

protected:

};

#endif
