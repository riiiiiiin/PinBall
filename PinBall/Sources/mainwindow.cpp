
#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setup blure effect
    blure = new QGraphicsBlurEffect;
    blure->setBlurRadius(5.0);
    this->setGraphicsEffect(blure);
    blure->setEnabled(false);
    //Setup music
    music = new QSoundEffect();
    music->setSource(QUrl::fromLocalFile(":/music/a.wav"));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.25f);
    music->play();
    //Setup se
    QSoundEffect* sound_effect=new QSoundEffect();
    sound_effect->setSource((QUrl::fromLocalFile(":/se/APPLAUSE.WAV")));
    sound_effect->setVolume(0.25f);
    sound_effects.push_back(sound_effect);
    //Setup PauseMenu
    pmenu = new PauseMenu(sound_effects,music,this);
    connect(pmenu,&PauseMenu::closed,this,&MainWindow::on_pauseMenuClosed);
    connect(pmenu,&PauseMenu::exitRequest,this,&MainWindow::on_exitRequested);
    //Setup Mask
    m_pMask = new QWidget(this);
    m_pMask->setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    m_pMask->hide();
    m_pMask->setWindowOpacity(0.7);
    m_pMask->setStyleSheet("background-color:black");
    m_pMask->setFixedSize(this->width(),this->height());
}

MainWindow::~MainWindow()
{
    music->stop();
    delete music;
    for(auto ptr:sound_effects){
        ptr->stop();
        delete ptr;
    }
    sound_effects.clear();
    delete m_pMask;
    delete ui;
    delete pmenu;
    delete blure;
}

void MainWindow::paintEvent(QPaintEvent *e){

    QPixmap* bg = new QPixmap;
    bg->load(":/backgrounds/Nebula.png");

    QPainter painter(this);
    painter.drawPixmap(0,0,*bg);
    QMainWindow::paintEvent(e);
}

//enables blure while paused
void MainWindow::on_pauseButton_clicked()
{
    m_pMask->show();
    pmenu->show();
    pmenu->move(geometry().topLeft());
    blure->setEnabled(true);
}

void MainWindow::on_pauseMenuClosed(){
    m_pMask->close();
    blure->setEnabled(false);
}

void MainWindow::on_exitRequested(){
    QCoreApplication::quit();
}
