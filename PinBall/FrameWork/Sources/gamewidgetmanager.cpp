#include "FrameWork/Headers/gamewidgetmanager.h"

GameWidgetManager::GameWidgetManager(QWidget* parent)
:QObject(parent){
    //setup se
    auto _se = new QSoundEffect();
    _se->setSource(QUrl::fromLocalFile(":/se/APPLAUSE.WAV"));
    _se->setVolume(0.25f);
    _sound_effects.push_back(_se);
    //setup music
    _music = new QSoundEffect();
    _music->setSource(QUrl::fromLocalFile(":/music/The_Wild_Side.wav"));
    _music->setLoopCount(QSoundEffect::Infinite);
    _music->setVolume(0.25f);
    _music->play();
    //Setup ThemePacks
    auto legacy_pack= new ThemePack();
    _theme_packs.push_back(legacy_pack);
    QString executablePath = QCoreApplication::applicationDirPath();
    QString initialDirectory = QDir(executablePath).filePath("Themepacks");
    QDir directory(initialDirectory);
    QStringList subdirectories = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto const & subdirectory : subdirectories) {
        QString subdirPath = directory.absoluteFilePath(subdirectory);
        QString filePath = QDir(subdirPath).filePath("theme.json");
        if(QFile::exists(filePath)){
            auto customized_pack=new ThemePack(subdirPath);
            if(customized_pack->loadTheme()){
                _theme_packs.push_back(customized_pack);
            }
        }
    }
    //Setup Widgets
    _stacked_widget = new QStackedWidget(parent);
    _map = new GameMap(_theme_index,_theme_packs,_music,_sound_effects,parent);
    _map_editor = new MapEditor(_theme_index,_theme_packs,_music,_sound_effects,parent);
    _stacked_widget->addWidget(_map);
    _stacked_widget->addWidget(_map_editor);

    connect(_map,&GameMap::switchRequest,this,&GameWidgetManager::switch_to_mapEditor);
    connect(_map_editor,&MapEditor::switchRequest,this,&GameWidgetManager::switch_to_map);
    connect(_map,&GameMap::exitRequest,this,&GameWidgetManager::on_exit_requested);
    connect(_map_editor,&MapEditor::exitRequest,this,&GameWidgetManager::on_exit_requested);
    connect(this,&GameWidgetManager::setMap,_map,&GameMap::on_newMapSet);
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

void GameWidgetManager::switch_to_map(QVector<EncodedMapElement> encoded_map,int gravity){
    //set up map
    emit setMap(encoded_map,gravity);
    _map->activateWindow();
    _stacked_widget->setCurrentWidget(_map);
    _music->setSource(QUrl::fromLocalFile(":/music/The_Wild_Side.wav"));
    _music->setLoopCount(QSoundEffect::Infinite);
    _music->setVolume(0.25f);
    _music->play();
}

void GameWidgetManager::switch_to_mapEditor(){
    _map_editor->activateWindow();
    _stacked_widget->setCurrentWidget(_map_editor);
    _music->setSource(QUrl::fromLocalFile(":/music/The_Unexplored.wav"));
    _music->setLoopCount(QSoundEffect::Infinite);
    _music->setVolume(0.25f);
    _music->play();
}

QStackedWidget* GameWidgetManager::StackedWidget(){
    return _stacked_widget;
}