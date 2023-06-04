#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>

#include "mdragcontainer.h"
#include "Headers/settingsmenu.h"

class MapEditor:public QWidget{
    Q_OBJECT
private:
    int _gravity=100;
    MDragContainer* _container;
    QLabel* _container_back;
    QList<QLabel*> _draggable_containers;
    QLabel* _coming_soon_label;
    QList<QPushButton*> _buttons;
    SwitchToMapConfirm* _switch_confirm;

    SettingsMenu* _settings_menu;
    QGraphicsBlurEffect *_blure;
    QList<QSoundEffect*> _sound_effects;
    QSoundEffect* _music;
    QWidget* _pMask;
public:
    MapEditor(QWidget* parent=nullptr);
    ~MapEditor();
    void paintEvent(QPaintEvent* event)override;
    void setSounds(QSoundEffect*,QList<QSoundEffect*>);
    void setUpMap(QList<EncodedMapElement>);
private slots:
    void on_pauseButtonClicked();
    void on_pauseMenuClosed();
    void on_exitRequested();

    void on_resetRequested();
    void on_gravityChanged(int);

    void on_switchButtonClicked();
    void on_switchConfirmClosed();
    void on_switchRequested();
signals:
    void exitRequest();
    void switchRequest(QList<EncodedMapElement>);
};

#endif