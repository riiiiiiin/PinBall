#include "Headers/gamemap.h"

GameMap::GameMap(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 960, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setFixedSize(960, 540);

    // Setup blure effect
    _blure = new QGraphicsBlurEffect;
    _blure->setBlurRadius(5.0);
    this->setGraphicsEffect(_blure);
    _blure->setEnabled(false);

    // Setup PauseMenu
    _pmenu = new PauseMenu(_sound_effects, _music, this);
    connect(_pmenu, &PauseMenu::closed, this, &GameMap::on_pauseMenuClosed);
    connect(_pmenu, &PauseMenu::exitRequest, this, &GameMap::on_exitRequested);

    // Setup Mask
    _pMask = new QWidget(this);
    _pMask->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    _pMask->hide();
    _pMask->setWindowOpacity(0.7);
    _pMask->setStyleSheet("background-color:black");
    _pMask->setFixedSize(this->width(), this->height());

    _buttons.resize(2);
    for (int i = 0; i < 2; ++i)
    {
        _buttons[i] = new QPushButton(this);
    }

    _buttons[0]->setGeometry(675, 440, 110, 50);
    _buttons[0]->setText("Edit");
    _buttons[0]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton{background-image: url(:/button_icons/editor_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
                               "QPushButton{background-color:transparent;}"
                               "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton:hover{background-image: url(:/button_icons/editor_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
                               "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[0],&QPushButton::clicked,this,GameMap::on_switchButtonClicked);                           

    _buttons[1]->setGeometry(790, 442, 130, 50);
    _buttons[1]->setText("Menu");
    _buttons[1]->setStyleSheet("QPushButton {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton{background-image: url(:/button_icons/menu_button_inactive.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton{font-size:30px;color:#808080;font-family: \"Segoe UI\";}"
                               "QPushButton{background-color:transparent;}"
                               "QPushButton:hover {background-position: left;text-align: right;padding-right: 20px;padding-left: 0px;}"
                               "QPushButton:hover{background-image: url(:/button_icons/menu_button_active.png);background-origin: content;background-position: left;background-repeat: no-repeat;}"
                               "QPushButton:hover{font-size:30px;color:#fefefe;font-family: \"Segoe UI\";}"
                               "QPushButton:hover{background-color:transparent;}");
    connect(_buttons[1], &QPushButton::clicked, this, GameMap::on_pauseButtonClicked);

    //setup confirm dialog
    _switch_confirm = new SwitchToMapEditorConfirm(this);
    connect(_switch_confirm,&MConfirmation::accepted,this,GameMap::on_switchRequested);
    connect(_switch_confirm,&MConfirmation::rejected,this,GameMap::on_switchConfirmClosed);
}

GameMap::~GameMap()
{
    for (auto ptr : _buttons)
    {
        delete ptr;
    }
    delete _pMask;
    delete _pmenu;
    delete _blure;
}

void GameMap::paintEvent(QPaintEvent *e)
{
    QPixmap *bg = new QPixmap;
    bg->load(":/backgrounds/Nebula.png");

    QPainter painter(this);
    painter.drawPixmap(0, 0, *bg);
    QWidget::paintEvent(e);
}

void GameMap::setSounds(QSoundEffect *music, QList<QSoundEffect *> se)
{
    _music = music;
    _sound_effects = se;
    _pmenu->setSounds(music,se);
}

// enables blure while paused
void GameMap::on_pauseButtonClicked()
{
    _pMask->show();
    _pmenu->setButtons();
    _pmenu->show();
    _pmenu->move(mapToGlobal(geometry().topLeft()));
    _blure->setEnabled(true);
}

void GameMap::on_pauseMenuClosed()
{
    _pMask->close();
    _blure->setEnabled(false);
}

void GameMap::on_exitRequested()
{
    emit exitRequest();
}

void GameMap::on_switchButtonClicked(){
    _pMask->show();
    _blure->setEnabled(true);
    _switch_confirm->move(mapToGlobal(geometry().topLeft()));
    _switch_confirm->raise();
    _switch_confirm->exec();
    //pause
}

void GameMap::on_switchConfirmClosed(){
    _pMask->close();
    _blure->setEnabled(false);
    //resume
}

void GameMap::on_switchRequested(){
    _pMask->close();
    _blure->setEnabled(false);
    emit switchRequest();
}