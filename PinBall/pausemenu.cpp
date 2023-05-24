#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(std::vector<QSoundEffect*> se,QWidget *parent,QApplication* app,QSoundEffect* msc) :
    QDialog(parent),
    ui(new Ui::PauseMenu),
    _app(app),
    _music(msc),
    _sound_effects(se)
{
    //setup translucent menu
    ui->setupUi(this);
    setWindowOpacity(1);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    //setup mute buttons
    _check_buttons.resize(2);
    _check_buttons[0] = new MCheckButton(150,"Mute_Music","Mute Music:",this);
    _check_buttons[0]->setParent(this);
    _check_buttons[1] = new MCheckButton(200,"Mute_SE","Mute SE:",this);
    _check_buttons[1]->setParent(this);
    QObject::connect(_check_buttons[0],SIGNAL(checked(bool)),this,SLOT(on_musicMuteButtonClicked(bool)));
    QObject::connect(_check_buttons[1],SIGNAL(checked(bool)),this,SLOT(on_seMuteButtonClicked(bool)));

    //setup exit buttons
    _push_buttons.resize(2);
    _push_buttons[0] = new MPushButton(250,"Resume","Back To Game",this);
    _push_buttons[0]->setParent(this);
    _push_buttons[1] = new MPushButton(300,"Exit","Exit",this);
    _push_buttons[1]->setParent(this);
    connect(_push_buttons[0],SIGNAL(pushed()),this,SLOT(on_resumeButtonClicked()));
    connect(_push_buttons[1],SIGNAL(pushed()),this,SLOT(on_exitButtonClicked()));
}

PauseMenu::~PauseMenu()
{
    delete ui;
    for(auto ptr:_sound_effects){
        delete ptr;
    }
    _sound_effects.clear();
    for(auto ptr:_push_buttons){
        delete ptr;
    }
    _push_buttons.clear();
}

void PauseMenu::closeEvent(QCloseEvent* event){
    emit closed();
    QDialog::closeEvent(event);
}

void PauseMenu::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Escape:{
        close();
        break;
    }
    default:{

    }
    }
}

void PauseMenu::on_resumeButtonClicked()
{
    close();
}

void PauseMenu::on_exitButtonClicked()
{
    ExitConfirm* exitc = new ExitConfirm(this,_app);
    exitc->show();
}

void PauseMenu::on_seMuteButtonClicked(bool checked)
{
    if(checked){
        for(auto ptr:_sound_effects){
            ptr->setMuted(true);
        }
    }
    else{
        for(auto ptr:_sound_effects){
            ptr->setMuted(false);
        }
    }
}


void PauseMenu::on_musicMuteButtonClicked(bool checked)
{
    if(checked){
        _music->setMuted(true);
    }
    else{
        _music->setMuted(false);
    }
}

