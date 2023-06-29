#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QtMultimedia>

#include "mdragcontainer.h"
#include "Headers/settingsmenu.h"

class MapEditor:public QWidget{
    Q_OBJECT
private:
    int _gravity=200;

    MDragContainer* _container;

    QLabel* _container_back;
    QList<QLabel*> _draggable_containers;
    QList<QLabel*> _coming_soon_labels;
    QLabel* _map_background;

    QList<QPushButton*> _buttons;

    SwitchToMapConfirm* _switch_confirm;
    SettingsMenu* _settings_menu;

    QGraphicsDropShadowEffect* _shadow;
    QGraphicsBlurEffect *_blure;
    QWidget* _pMask;

    QList<QSoundEffect*> _sound_effects;
    QSoundEffect* _music;
    
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
    void switchRequest(QList<EncodedMapElement>,int);
};

#endif