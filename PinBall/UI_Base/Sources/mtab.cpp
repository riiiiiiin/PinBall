#include "UI_Base/Headers/mtab.h"

MTab::MTab(QWidget *parent) : QDialog(parent)
{
    // setup translucent menu
    setGeometry(0, 0, 960, 540);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
}

MTab::~MTab()
{
    delete _title;
    delete _white_bar;
    for (auto&ptr : _buttons)
    {
        delete ptr;
    }
    _buttons.clear();
}

void MTab::closeEvent(QCloseEvent *event)
{
    emit closed();
    QDialog::closeEvent(event);
}

void MTab::keyPressEvent(QKeyEvent *event)
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