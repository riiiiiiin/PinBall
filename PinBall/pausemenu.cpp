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

    //setup one button(example)
    QPixmap* pix = new QPixmap;
    pix->load(":/icons/cat_cool.png");
    *pix = pix->scaled(32,32);

    ui->resumeButton->setIconSize(pix->size());
    ui->resumeButton->setMask(pix->mask());
    ui->resumeButton->setStyleSheet("background-image: url(:/icons/cat_cool.png)");

    ui->seMuteButton->setCheckable(true);
    ui->musicMuteButton->setCheckable(true);
}

PauseMenu::~PauseMenu()
{
    delete ui;
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

void PauseMenu::paintEvent(QPaintEvent *e){
    QPixmap* bder = new QPixmap;
    bder->load(":/backgrounds/border.png");
    resize(bder->size());
    QPainter painter(this);
    painter.drawPixmap(0,0,*bder);
    QWidget::paintEvent(e);
}

void PauseMenu::on_resumeButton_clicked()
{
    close();
}

void PauseMenu::on_exitButton_clicked()
{
    ExitConfirm* exitc = new ExitConfirm(this,_app);
    exitc->show();
}

void PauseMenu::on_seMuteButton_clicked(bool checked)
{
    if(checked){
        ui->seMuteButton->setText("seMuted!");
        for(auto ptr:_sound_effects){
            ptr->setMuted(true);
        }
    }
    else{
        ui->seMuteButton->setText(("seMute"));
        for(auto ptr:_sound_effects){
            ptr->setMuted(false);
        }
    }
}


void PauseMenu::on_musicMuteButton_clicked(bool checked)
{
    if(checked){
        ui->musicMuteButton->setText("musicMuted!");
        _music->setMuted(true);
    }
    else{
        ui->musicMuteButton->setText("musicMute");
        _music->setMuted(false);
    }
}

