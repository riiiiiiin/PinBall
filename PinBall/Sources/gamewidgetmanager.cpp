#include "Headers/gamewidgetmanager.h"

GameWidgetManager::GameWidgetManager(QWidget* parent)
:QObject(parent){
    _stacked_widget = new QStackedWidget(parent);
    _map = new Map(parent);
    _map_editor = new MapEditor(parent);
    //setup se
    //setup music
    _music = new QSoundEffect();
    _music->setSource(QUrl::fromLocalFile(":/music/a.wav"));
    _music->setLoopCount(QSoundEffect::Infinite);
    _music->setVolume(0.25f);
    _music->play();

    _map->setSounds(_music,_sound_effects);
    _map_editor->setSounds(_music,_sound_effects);
    _stacked_widget->addWidget(_map);
    _stacked_widget->addWidget(_map_editor);

    connect(_map,&Map::switchRequest,this,&GameWidgetManager::switch_to_mapEditor);
    connect(_map_editor,&MapEditor::switchRequest,this,&GameWidgetManager::switch_to_map);
    connect(_map,&Map::exitRequest,this,&GameWidgetManager::on_exit_requested);
    connect(_map_editor,&MapEditor::exitRequest,this,&GameWidgetManager::on_exit_requested);
}

GameWidgetManager::~GameWidgetManager(){
    delete _map;
    delete _map_editor;
    delete _stacked_widget;
    delete _music;
    for(auto ptr:_sound_effects){
        delete ptr;
    }
}

void GameWidgetManager::on_exit_requested(){
    QCoreApplication::quit();
}

void GameWidgetManager::switch_to_map(){
    _stacked_widget->setCurrentWidget(_map);
}

void GameWidgetManager::switch_to_mapEditor(){
    qDebug()<<'a';
    _stacked_widget->setCurrentWidget(_map_editor);
}

QStackedWidget* GameWidgetManager::StackedWidget(){
    return _stacked_widget;
}