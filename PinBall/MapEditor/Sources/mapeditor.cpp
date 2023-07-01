#include "MapEditor/Headers/mapeditor.h"

MapEditor::MapEditor(int& theme_index,QVector<ThemePack*>& themes,QSoundEffect* music,QVector<QSoundEffect*> se,QWidget *parent) 
: QWidget(parent),_theme_index(theme_index),_theme_packs(themes),_music(music),_sound_effects(se)
{
    setGeometry(0, 0, 960, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setFixedSize(960, 540);

    // Setup blure effect
    _blure = new QGraphicsBlurEffect;
    _blure->setBlurRadius(5.0);
    this->setGraphicsEffect(_blure);
    _blure->setEnabled(false);

    // Setup SettingsMenu
    _settings_menu = new SettingsMenu(_gravity, _sound_effects, _music, this);
    connect(_settings_menu, &SettingsMenu::closed, this, &MapEditor::on_pauseMenuClosed);
    connect(_settings_menu, &SettingsMenu::resetMapRequest, this, &MapEditor::on_resetRequested);
    connect(_settings_menu, &SettingsMenu::exitRequest, this, &MapEditor::on_exitRequested);
    connect(_settings_menu, SIGNAL(gravityChange(int)), this, SLOT(on_gravityChanged(int)));

    // Setup Mask
    _pMask = new QWidget(this);
    _pMask->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    _pMask->hide();
    _pMask->setWindowOpacity(0.7);
    _pMask->setStyleSheet("background-color:black");
    _pMask->setFixedSize(this->width(), this->height());

    // setup container's background
    _container_back = new QLabel(this);
    _container_back->setText("");
    _container_back->setGeometry(650, 40, 260, 380);
    _container_back->setAutoFillBackground(true);
    _container_back->setFixedSize(260, 380);
    _container_back->setStyleSheet("background-color:rgba(255,255,255,96);border-radius:15px;border: 1px solid silver;");

    _draggable_containers.resize(5);
    for (int i = 0; i < 5; ++i)
    {
        _draggable_containers[i] = new QLabel(this);
        _draggable_containers[i]->setText("");
        _draggable_containers[i]->setStyleSheet("background-color:rgba(255,255,255,96);border-radius: 10px;border: 1px solid royalblue;");
        _draggable_containers[i]->setAutoFillBackground(true);
    }
    _draggable_containers[4] = new QLabel(this);
    _draggable_containers[4]->setText("");
    _draggable_containers[4]->setStyleSheet("background-color:rgba(255,255,255,64);border-radius: 10px;border: 1px solid indianred;");
    _draggable_containers[4]->setAutoFillBackground(true);

    _draggable_containers[0]->setGeometry(670 - 5, 60 - 5, 110, 110);
    _draggable_containers[1]->setGeometry(670 - 5, 180 - 5, 110, 110);
    _draggable_containers[2]->setGeometry(790 - 5, 60 - 5, 110, 110);
    _draggable_containers[3]->setGeometry(790 - 5, 180 - 5, 110, 110);
    _draggable_containers[4]->setGeometry(670 - 5, 300 - 5, 230, 110);

    // Setup map background
    _map_background = new QLabel(this);
    _map_background->setParent(this);
    _map_background->setGeometry(0, 0, 600, 540);
    _map_background->setText("");
    _map_background->setPixmap(*_theme_packs[_theme_index]->themePics()[BG_Map_Editor]);
    _map_background->setMask(_theme_packs[_theme_index]->themePics()[BG_Map_Editor]->mask());

    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setBlurRadius(70);
    _shadow->setColor(QColor("#ffffff"));
    _shadow->setOffset(0);
    _shadow->setEnabled(true);
    _map_background->setGraphicsEffect(_shadow);

    // Setup buttons
    _buttons.resize(2);
    for (int i = 0; i < 2; ++i)
    {
        _buttons[i] = new QPushButton(this);
        _buttons[i]->setParent(this);
    }

    _buttons[0]->setGeometry(665, 440, 110, 50);
    _buttons[0]->setText("Play");
    _buttons[0]->setStyleSheet(
        "QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
        "QPushButton{background-image: url(:/button_icons/play_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
        "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
        "QPushButton{background-color:transparent;}"
        "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
        "QPushButton:hover{background-image: url(:/button_icons/play_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
        "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
        "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[0], &QPushButton::clicked, this,&MapEditor::on_switchButtonClicked);

    _buttons[1]->setGeometry(780, 442, 130, 50);
    _buttons[1]->setText("Menu");
    _buttons[1]->setStyleSheet(
        "QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
        "QPushButton{background-image: url(:/button_icons/menu_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
        "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
        "QPushButton{background-color:transparent;}"
        "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
        "QPushButton:hover{background-image: url(:/button_icons/menu_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
        "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
        "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[1], &QPushButton::clicked, this, &MapEditor::on_pauseButtonClicked);

    // Setup themes
    _page_change_buttons.resize(2);
    for (int i = 0; i < 2; ++i)
    {
        _page_change_buttons[i] = new QPushButton(this);
        _page_change_buttons[i]->setParent(this);
        _page_change_buttons[i]->setText("");
    }
    _page_change_buttons[0]->setStyleSheet(
        "QPushButton{icon: url(:/mapeditor/themes/next_page_inactive.png);}"
        "QPushButton{background-color:transparent;}"
        "QPushButton:hover{icon: url(:/mapeditor/themes/next_page_active.png);}"
        "QPushButton:hover{background-color:transparent;}");
    _page_change_buttons[0]->setGeometry(867, 300, 32, 64);
    _page_change_buttons[1]->setStyleSheet(
        "QPushButton{icon: url(:/mapeditor/themes/previous_page_inactive.png);}"
        "QPushButton{background-color:transparent;}"
        "QPushButton:hover{icon: url(:/mapeditor/themes/previous_page_active.png);}"
        "QPushButton:hover{background-color:transparent;}");
    _page_change_buttons[1]->setGeometry(660, 299, 32, 64);
    connect(_page_change_buttons[0],&QPushButton::clicked,this,&MapEditor::on_themeIndexIncrease);
    connect(_page_change_buttons[1],&QPushButton::clicked,this,&MapEditor::on_themeIndexDecrease);

    _theme_title_display=new QLabel(this);
    _theme_title_display->setParent(this);
    _theme_title_display->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _theme_title_display->setStyleSheet("color:honeydew;font-family: \"Segoe UI Variable Display Light\"; font-size: 25px;");
    _theme_title_display->setGeometry(680,360,200,40);

    _theme_cover_display=new QLabel(this);
    _theme_cover_display->setParent(this);
    _theme_cover_display->setText("");
    _theme_cover_display->setGeometry(695,300,175,70);
    
    _container = new MDragContainer(_theme_index,_theme_packs,this);

    updateTheme();

    // Setup confirm dialogs
    _switch_confirm = new SwitchToMapConfirm(this);
    connect(_switch_confirm, &MConfirmation::accepted, this, &MapEditor::on_switchRequested);
    connect(_switch_confirm, &MConfirmation::rejected, this, &MapEditor::on_switchConfirmClosed);
}

MapEditor::~MapEditor()
{
    delete _container_back;
    for (auto ptr : _draggable_containers)
    {
        delete ptr;
    }
    for (auto ptr : _buttons)
    {
        delete ptr;
    }
    for (auto ptr : _page_change_buttons)
    {
        delete ptr;
    }
    delete _pMask;
    delete _settings_menu;
    delete _blure;
    delete _theme_title_display;
    delete _theme_cover_display;
}

void MapEditor::paintEvent(QPaintEvent *e)
{
    QPixmap *bg = new QPixmap;
    bg->load(":/backgrounds/Dual_Quasar.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, *bg);
    QWidget::paintEvent(e);
}

void MapEditor::on_pauseButtonClicked()
{
    _pMask->show();
    _settings_menu->setButtons();
    _settings_menu->show();
    _settings_menu->move(mapToGlobal(geometry().topLeft()));
    _blure->setEnabled(true);
}

void MapEditor::on_pauseMenuClosed()
{
    _pMask->close();
    _blure->setEnabled(false);
}

void MapEditor::on_exitRequested()
{
    emit exitRequest();
}

void MapEditor::on_resetRequested()
{
    _container->clear();
    // resets the map
}

void MapEditor::on_gravityChanged(int gravity)
{
    _gravity = gravity;
}

void MapEditor::on_switchButtonClicked()
{
    _pMask->show();
    _blure->setEnabled(true);
    _switch_confirm->move(mapToGlobal(geometry().topLeft()));
    _switch_confirm->raise();
    _switch_confirm->exec();
}

void MapEditor::on_switchConfirmClosed()
{
    _pMask->close();
    _blure->setEnabled(false);
}

void MapEditor::on_switchRequested()
{
    _pMask->close();
    _blure->setEnabled(false);
    // convert map elements to map
    emit switchRequest(_container->encodeMap(), _gravity);
}

void MapEditor::setUpMap(QVector<EncodedMapElement> encoded_map)
{
    _container->clear();
    _container->decodeMap(encoded_map);
}

void MapEditor::on_themeIndexIncrease(){
    ++_theme_index;
    updateTheme();
}

void MapEditor::on_themeIndexDecrease(){
    --_theme_index;
    updateTheme();
}

void MapEditor::updateTheme(){
    _theme_index=_theme_index%_theme_packs.size();
    _theme_index=_theme_index>=0?_theme_index:_theme_index+_theme_packs.size();
    
    _theme_title_display->setText(_theme_packs[_theme_index]->themeTitle());
    _theme_cover_display->setPixmap(*_theme_packs[_theme_index]->themePics()[Cover]);

    _map_background->setPixmap(*_theme_packs[_theme_index]->themePics()[BG_Map_Editor]);
    _map_background->setMask(_theme_packs[_theme_index]->themePics()[BG_Map_Editor]->mask());
    
    _container->updateTheme();
}