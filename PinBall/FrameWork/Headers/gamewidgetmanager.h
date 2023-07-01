#ifndef GAMEWIDGETMANAGER_H
#define GAMEWIDGETMANAGER_H

#include <QStackedWidget>
#include <QtMultimedia>
#include <QApplication>

#include "Game/Headers/gamemap.h"
#include "MapEditor/Headers/mapeditor.h"
#include "FrameWork/Headers/themepack.h"

class GameWidgetManager : public QObject{
    Q_OBJECT
private:
    QStackedWidget* _stacked_widget;
    GameMap* _map;
    MapEditor* _map_editor;

    QSoundEffect* _music;
    QVector<QSoundEffect*> _sound_effects;

    int _theme_index{0};
    QVector<ThemePack> _theme_packs;
public:
    GameWidgetManager(QWidget* parent=nullptr);
    ~GameWidgetManager();
    QStackedWidget* StackedWidget();
signals:
    void setMap(QVector<EncodedMapElement> newmap,int);
private slots:
    void switch_to_map(QVector<EncodedMapElement>,int gravity);
    void switch_to_mapEditor();
    void on_exit_requested();
};

#endif