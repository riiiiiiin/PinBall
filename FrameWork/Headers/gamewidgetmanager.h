#ifndef GAMEWIDGETMANAGER_H
#define GAMEWIDGETMANAGER_H

#include <QStackedWidget>
#include <QtMultimedia>
#include <QApplication>

#include "Game/Headers/gamemap.h"
#include "MapEditor/Headers/mapeditor.h"
#include "Video/Headers/widget.h"

class GameWidgetManager : public QObject{
    Q_OBJECT
private:
    QStackedWidget* _stacked_widget;
    Widget* _video;
    GameMap* _map;
    MapEditor* _map_editor;
    QSoundEffect* _music;
    QVector<QSoundEffect*> _sound_effects;
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
    void init_map();
};

#endif
