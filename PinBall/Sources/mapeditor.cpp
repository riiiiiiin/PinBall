#include "headers/mapeditor.h"

MapEditor::MapEditor(QWidget *parent) : QWidget(parent)
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
    connect(_settings_menu,&SettingsMenu::resetMapRequest,this,&MapEditor::on_resetRequested);
    connect(_settings_menu, &SettingsMenu::exitRequest, this, &MapEditor::on_exitRequested);
    connect(_settings_menu, SIGNAL(gravityChange(int)), this, SLOT(on_gravityChanged(int)));
    
    // Setup Mask
    _pMask = new QWidget(this);
    _pMask->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    _pMask->hide();
    _pMask->setWindowOpacity(0.7);
    _pMask->setStyleSheet("background-color:black");
    _pMask->setFixedSize(this->width(), this->height());

    //setup container's background
    _container_back = new QLabel(this);
    _container_back->setText("");
    _container_back->setGeometry(650, 40, 260, 380);
    _container_back->setAutoFillBackground(true);
    _container_back->setFixedSize(260, 380);
    _container_back->setStyleSheet("background-color:rgba(255,255,255,128);border-radius:15px;border: 1px solid silver;");

    _draggable_containers.resize(6);
    for (int i = 0; i < 6; ++i)
    {
        _draggable_containers[i] = new QLabel(this);
        _draggable_containers[i]->setFixedSize(110, 110);
        _draggable_containers[i]->setText("");
        _draggable_containers[i]->setStyleSheet("background-color:rgba(255,255,255,154);border-radius: 10px;border: 1px solid royalblue;");
        _draggable_containers[i]->setAutoFillBackground(true);
    }
    _draggable_containers[0]->setGeometry(670 - 5, 60 - 5, 110, 110);
    _draggable_containers[1]->setGeometry(670 - 5, 180 - 5, 110, 110);
    _draggable_containers[2]->setGeometry(790 - 5, 60 - 5, 110, 110);
    _draggable_containers[3]->setGeometry(790 - 5, 180 - 5, 110, 110);
    _draggable_containers[4]->setGeometry(670 - 5, 300 - 5, 110, 110);
    _draggable_containers[5]->setGeometry(790 - 5, 300 - 5, 110, 110);

    QPixmap coming_soon(":/button_icons/coming_soon.png");
    _coming_soon_labels.resize(2);
    for(auto &plabel:_coming_soon_labels){
        plabel = new QLabel(this);
        plabel->setMinimumSize(100, 100);
        plabel->setText("");
        plabel->setPixmap(coming_soon);
        plabel->setMask(coming_soon.mask());
    }
    _coming_soon_labels[0]->move(675,300);
    _coming_soon_labels[1]->move(795, 300);

    //Setup map background
    QPixmap background(":/mapeditor/backgrounds/mapeditor_background.png");
    background = background.scaled(600,540, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _map_background = new QLabel(this);
    _map_background->setParent(this);
    _map_background->setGeometry(0,0,600,540);
    _map_background->setText("");
    _map_background->setPixmap(background);
    _map_background->setMask(background.mask());

    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setBlurRadius(70);
    _shadow->setColor(QColor("#ffffff"));
    _shadow->setOffset(0);
    _shadow->setEnabled(true);
    _map_background->setGraphicsEffect(_shadow);

    //Setup buttons
    _buttons.resize(2);
    for (int i = 0; i < 2; ++i)
    {
        _buttons[i] = new QPushButton(this);
        _buttons[i]->setParent(this);
    }

    _buttons[0]->setGeometry(665, 440, 110, 50);
    _buttons[0]->setText("Play");
    _buttons[0]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton{background-image: url(:/button_icons/play_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
                               "QPushButton{background-color:transparent;}"
                               "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton:hover{background-image: url(:/button_icons/play_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
                               "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[0],&QPushButton::clicked,this,MapEditor::on_switchButtonClicked);

    _buttons[1]->setGeometry(780, 442, 130, 50);
    _buttons[1]->setText("Menu");
    _buttons[1]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton{background-image: url(:/button_icons/menu_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
                               "QPushButton{background-color:transparent;}"
                               "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton:hover{background-image: url(:/button_icons/menu_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
                               "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[1], &QPushButton::clicked, this, MapEditor::on_pauseButtonClicked);

    _container = new MDragContainer(this);

    //setup confirm dialog
    _switch_confirm = new SwitchToMapConfirm(this);
    connect(_switch_confirm,&MConfirmation::accepted,this,MapEditor::on_switchRequested);
    connect(_switch_confirm,&MConfirmation::rejected,this,MapEditor::on_switchConfirmClosed);
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
    for(auto ptr:_coming_soon_labels){
        delete ptr;
    }
    delete _pMask;
    delete _settings_menu;
    delete _blure;
}

void MapEditor::paintEvent(QPaintEvent *e)
{
    QPixmap *bg = new QPixmap;
    bg->load(":/backgrounds/Dual_Quasar.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, *bg);
    QWidget::paintEvent(e);
}

void MapEditor::setSounds(QSoundEffect *music, QList<QSoundEffect *> se)
{
    _music = music;
    _sound_effects = se;
    _settings_menu->setSounds(music,se);
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

void MapEditor::on_switchButtonClicked(){
    _pMask->show();
    _blure->setEnabled(true);
    _switch_confirm->move(mapToGlobal(geometry().topLeft()));
    _switch_confirm->raise();
    _switch_confirm->exec();
    
}

void MapEditor::on_switchConfirmClosed(){
    _pMask->close();
    _blure->setEnabled(false);
}

void MapEditor::on_switchRequested(){
    _pMask->close();
    _blure->setEnabled(false);
    //convert map elements to map
    emit switchRequest(_container->encodeMap(),_gravity);
}

void MapEditor::setUpMap(QList<EncodedMapElement> encoded_map){
    _container->clear();
    _container->decodeMap(encoded_map);
}