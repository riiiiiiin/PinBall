#include "Headers/pausemenu.h"

PauseMenu::PauseMenu(std::vector<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent)
    : QDialog(parent),
      _music(msc),
      _sound_effects(se)
{
    // setup translucent menu
    setGeometry(0, 0, 960, 540);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    // setup mute buttons
    _check_buttons.resize(2);
    _check_buttons[0] = new MCheckButton(125, "Mute_Music", "Mute Music:", this);
    _check_buttons[0]->setParent(this);
    _check_buttons[1] = new MCheckButton(175, "Mute_SE", "Mute SE:", this);
    _check_buttons[1]->setParent(this);
    connect(_check_buttons[0], SIGNAL(checked(bool)), this, SLOT(on_musicMuteButtonClicked(bool)));
    connect(_check_buttons[1], SIGNAL(checked(bool)), this, SLOT(on_seMuteButtonClicked(bool)));

    // setup exit buttons
    _push_buttons.resize(2);
    _push_buttons[0] = new MPushButton(225, "Resume", "Back To Game", this);
    _push_buttons[0]->setParent(this);
    _push_buttons[1] = new MPushButton(275, "Exit", "Exit", this);
    _push_buttons[1]->setParent(this);
    connect(_push_buttons[0], SIGNAL(pushed()), this, SLOT(on_resumeButtonClicked()));
    connect(_push_buttons[1], SIGNAL(pushed()), this, SLOT(on_exitButtonClicked()));

    // setup subdialog
    _exc = new ExitConfirm(this);
    connect(_exc, &ExitConfirm::accepted, this, &PauseMenu::on_exitRequested);

    // setup title
    _title = new QLabel(this);
    _title->setGeometry(412, 40, 200, 40);
    _title->setText("Settings");

    QFont font;
    font.setFamily("Segoe UI Variable Small Semibol");
    font.setBold(true);
    font.setPixelSize(30);
    _title->setFont(font);
    QPalette plt = _title->palette();
    plt.setColor(QPalette::WindowText, QColor("#ffffff"));
    _title->setPalette(plt);

    _white_bar = new QLabel(this);
    _white_bar->setGeometry(398, 85, 140, 2);
    _white_bar->setText("");
    _white_bar->setPixmap(QPixmap(":/others/White_140_2.png"));
}

PauseMenu::~PauseMenu()
{
    for (auto ptr : _check_buttons)
    {
        delete ptr;
    }
    _check_buttons.clear();
    for (auto ptr : _push_buttons)
    {
        delete ptr;
    }
    _push_buttons.clear();
    delete _exc;
    delete _title;
    delete _white_bar;
}

void PauseMenu::closeEvent(QCloseEvent *event)
{
    emit closed();
    QDialog::closeEvent(event);
}

void PauseMenu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
    {
        close();
        break;
    }
    default:
    {
    }
    }
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

void PauseMenu::on_ExitConfirmClosed()
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
