#include "FrameWork/Headers/pausemenu.h"

PauseMenu::PauseMenu(QVector<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent)
    : MTab(parent),
      _music(msc),
      _sound_effects(se)
{
    // setup buttons
    _buttons.resize(4);
    _buttons[0] = new MCheckButton(125, "Mute_Music", "Mute Music:", this);
    _buttons[0]->setParent(this);
    connect(_buttons[0], SIGNAL(checked(bool)), this, SLOT(on_musicMuteButtonClicked(bool)));

    _buttons[1] = new MCheckButton(175, "Mute_SE", "Mute SE:", this);
    _buttons[1]->setParent(this);
    connect(_buttons[1], SIGNAL(checked(bool)), this, SLOT(on_seMuteButtonClicked(bool)));

    _buttons[2] = new MPushButton(225, "Resume", "Back To Game", this);
    _buttons[2]->setParent(this);
    connect(_buttons[2], SIGNAL(pushed()), this, SLOT(on_resumeButtonClicked()));

    _buttons[3] = new MPushButton(275, "Exit", "Exit", this);
    _buttons[3]->setParent(this);
    connect(_buttons[3], SIGNAL(pushed()), this, SLOT(on_exitButtonClicked()));

    // setup subdialog
    _exc = new ExitConfirm(this);
    connect(_exc, &ExitConfirm::accepted, this, &PauseMenu::on_exitRequested);

    // setup title
    _title = new QLabel(this);
    _title->setGeometry(375, 40, 200, 40);
    _title->setText("Game Paused");
    _title->setStyleSheet("color:white;font-family: \"Segoe UI Variable Small Semibol\";font-size:30px;font-weight: bold;");

    _white_bar = new QLabel(this);
    _white_bar->setGeometry(400, 85, 140, 2);
    _white_bar->setText("");
    _white_bar->setStyleSheet("background-color:white;");
}

PauseMenu::~PauseMenu()
{
    delete _exc;
}

void PauseMenu::setSounds(QSoundEffect *music, QVector<QSoundEffect *> se)
{
    _music = music;
    _sound_effects = se;
    auto _music_button = dynamic_cast<MCheckButton*>(_buttons[0]);
    _music_button->setChecked(_music->isMuted());
}

void PauseMenu::setButtons(){
    auto _music_button = dynamic_cast<MCheckButton*>(_buttons[0]);
    _music_button->setChecked(_music->isMuted());
    auto _se_button = dynamic_cast<MCheckButton*>(_buttons[1]);
    _se_button->setChecked(_sound_effects[0]->isMuted());
}

void PauseMenu::on_resumeButtonClicked()
{
    close();
}

void PauseMenu::on_exitButtonClicked()
{
    _exc->move(geometry().topLeft());
    _exc->raise();
    _exc->exec();
}

void PauseMenu::on_exitConfirmClosed()
{
}

void PauseMenu::on_exitRequested()
{
    emit exitRequest();
}

void PauseMenu::on_seMuteButtonClicked(bool checked)
{
    if (checked)
    {
        for (auto ptr : _sound_effects)
        {
            ptr->setMuted(true);
        }
    }
    else
    {
        for (auto ptr : _sound_effects)
        {
            ptr->setMuted(false);
        }
    }
}

void PauseMenu::on_musicMuteButtonClicked(bool checked)
{
    if (checked)
    {
        _music->setMuted(true);
    }
    else
    {
        _music->setMuted(false);
    }
}
