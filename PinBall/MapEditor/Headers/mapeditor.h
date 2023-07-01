#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QPushButton>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QtMultimedia>

#include "MapEditor/Headers/mdragcontainer.h"
#include "FrameWork/Headers/settingsmenu.h"

class MapEditor:public QWidget{
    Q_OBJECT
private:
    int _gravity=200;

    MDragContainer* _container;

    QLabel* _container_back;
    QVector<QLabel*> _draggable_containers;
    QLabel* _map_background;

    QVector<QPushButton*> _buttons;
    QVector<QPushButton*> _page_change_buttons;

    SwitchToMapConfirm* _switch_confirm;
    SettingsMenu* _settings_menu;

    QGraphicsDropShadowEffect* _shadow;
    QGraphicsBlurEffect *_blure;
    QWidget* _pMask;

    QVector<QSoundEffect*> _sound_effects;
    QSoundEffect* _music;
    // 待重写
    int _theme_index{0};
    int _theme_count{1};
    const QVector<QString> _theme_titles{"Legacy"};
    QVector<QPixmap*> _theme_covers;

    QLabel* _theme_title_display;
    QLabel* _theme_cover_display;

    void updateTheme();
    
public:
    MapEditor(QWidget* parent=nullptr);
    ~MapEditor();
    void paintEvent(QPaintEvent* event)override;
    void setSounds(QSoundEffect*,QVector<QSoundEffect*>);
    void setUpMap(QVector<EncodedMapElement>);
private slots:
    void on_pauseButtonClicked();
    void on_pauseMenuClosed();
    void on_exitRequested();

    void on_resetRequested();
    void on_gravityChanged(int);

    void on_switchButtonClicked();
    void on_switchConfirmClosed();
    void on_switchRequested();

    void on_themeIndexIncrease();
    void on_themeIndexDecrease();
signals:
    void exitRequest();
    void switchRequest(QVector<EncodedMapElement>,int);
};

#endif