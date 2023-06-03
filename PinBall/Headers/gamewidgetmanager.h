#ifndef GAMEWIDGETMANAGER_H
#define GAMEWIDGETMANAGER_H

#include <QStackedWidget>
#include <QtMultimedia>
#include <QApplication>

#include "Headers/gamemap.h"
#include "Headers/mapeditor.h"

class GameWidgetManager : public QObject{
    Q_OBJECT
private:
    QStackedWidget* _stacked_widget;
    GameMap* _map;
    MapEditor* _map_editor;
    QSoundEffect* _music;
    QList<QSoundEffect*> _sound_effects;
public:
    GameWidgetManager(QWidget* parent=nullptr);
    ~GameWidgetManager();
    QStackedWidget* StackedWidget();
signals:
private slots:
    void switch_to_map();
    void switch_to_mapEditor();
    void on_exit_requested();
};

#endif