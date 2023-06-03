#include "Headers/settingsmenu.h"

SettingsMenu::SettingsMenu(int gravity,QList<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent)
: MTab(parent),
      _music(msc),
      _sound_effects(se),
      _gravity(gravity)
{
    //setup buttons
    _buttons.resize(6);
    _buttons[0] = new MSlider(125,"Change_Gravity","Gravity",this);
    _buttons[0]->setParent(this);
    connect(_buttons[0],SIGNAL(number_changed(int)),this,SLOT(on_sliderNumberChange(int)));
    auto _slider = dynamic_cast<MSlider*>(_buttons[0]);
    _slider->setDefault(_gravity);

    _buttons[1] = new MPushButton(175,"Reset_Map","Reset Map",this);
    _buttons[1]->setParent(this);
    connect(_buttons[1],SIGNAL(pushed()),this,SLOT(on_resetMapRequested()));

    _buttons[2] = new MCheckButton(225, "Mute_Music", "Mute Music:", this);
    _buttons[2]->setParent(this);
    connect(_buttons[2], SIGNAL(checked(bool)), this, SLOT(on_musicMuteButtonClicked(bool)));

    _buttons[3] = new MCheckButton(275, "Mute_SE", "Mute SE:", this);
    _buttons[3]->setParent(this);
    connect(_buttons[3], SIGNAL(checked(bool)), this, SLOT(on_seMuteButtonClicked(bool)));

    _buttons[4] = new MPushButton(325, "Resume", "Back To Map Editor", this);
    _buttons[4]->setParent(this);
    connect(_buttons[4], SIGNAL(pushed()), this, SLOT(on_resumeButtonClicked()));

    _buttons[5] = new MPushButton(375, "Exit", "Exit", this);
    _buttons[5]->setParent(this);
    connect(_buttons[5], SIGNAL(pushed()), this, SLOT(on_exitButtonClicked()));

    // setup subdialog
    _exc = new ExitConfirm(this);
    connect(_exc, &ExitConfirm::accepted, this, &SettingsMenu::on_exitRequested);

    // setup title
    _title = new QLabel(this);
    _title->setGeometry(392, 40, 200, 40);
    _title->setText("Map Editor");
    _title->setStyleSheet("color:white;font-family: \"Segoe UI Variable Small Semibol\";font-size:30px;font-weight: bold;");

    _white_bar = new QLabel(this);
    _white_bar->setGeometry(400, 85, 140, 2);
    _white_bar->setText("");
    _white_bar->setStyleSheet("background-color:white;");
}

SettingsMenu::~SettingsMenu(){
    delete _exc;
}

void SettingsMenu::setSounds(QSoundEffect *music, QList<QSoundEffect *> se)
{
    _music = music;
    _sound_effects = se;
    auto _music_button = dynamic_cast<MCheckButton*>(_buttons[2]);
    _music_button->setChecked(_music->isMuted());
}

void SettingsMenu::setButtons(){
    auto _music_button = dynamic_cast<MCheckButton*>(_buttons[2]);
    _music_button->setChecked(_music->isMuted());
    auto _se_button = dynamic_cast<MCheckButton*>(_buttons[3]);
    _se_button->setChecked(_sound_effects[0]->isMuted());
}

void SettingsMenu::on_exitButtonClicked(){
    _exc->move(geometry().topLeft());
    _exc->raise();
    _exc->exec();
}

void SettingsMenu::on_exitConfirmClosed()
{
}

void SettingsMenu::on_exitRequested()
{
    emit exitRequest();
}

void SettingsMenu::on_seMuteButtonClicked(bool checked)
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

void SettingsMenu::on_musicMuteButtonClicked(bool checked)
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

void SettingsMenu::on_resumeButtonClicked(){
    close();
}

void SettingsMenu::on_resetMapRequested(){
    emit resetMapRequest();
}

void SettingsMenu::on_sliderNumberChange(int value){
    _gravity = value;
    emit gravityChange(_gravity);
}