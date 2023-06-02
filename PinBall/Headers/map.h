#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>

#include "pausemenu.h"

class Map : public QWidget

{
    Q_OBJECT
private:
    QList<QPushButton*> _buttons;
    SwitchToMapEditorConfirm* _switch_confirm;

    PauseMenu *_pmenu;
    QGraphicsBlurEffect *_blure;
    QList<QSoundEffect*> _sound_effects;
    QSoundEffect* _music;
    QWidget* _pMask;
public:
    Map(QWidget *parent = nullptr);
    ~Map();
    void paintEvent(QPaintEvent *e) override;
    void setSounds(QSoundEffect*,QList<QSoundEffect*>);
private slots:
    void on_pauseButtonClicked();
    void on_pauseMenuClosed();
    void on_exitRequested();

    void on_switchButtonClicked();
    void on_switchConfirmClosed();
    void on_switchRequested();

signals:
    void exitRequest();
    void switchRequest();
};

#endif 
