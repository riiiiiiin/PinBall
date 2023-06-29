#include "UI_Base/Headers/mconfirmation.h"

MConfirmation::MConfirmation(QWidget *parent) : QDialog(parent)
{
    // setup background
    setGeometry(0, 0, 960, 540);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    _background = new QLabel(this);
    _background->setGeometry(0, 180, 960, 140);
    _background->setText("");
    _background->setObjectName("_background_");
    _background->setStyleSheet("QLabel#" + _background->objectName() + "{background-color:orange;}");
    _background->setParent(this);

    // setup title
    _title = new QLabel(this);
    _title->setStyleSheet("color:white;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 40px;font-weight: bold;");
    _title->setParent(this);

    // setup accept button
    _acc_button = new QPushButton(this);
    connect(_acc_button, &QPushButton::clicked, this, &MConfirmation::on_Accepted);
    _acc_button->setObjectName("acc");
    _acc_button->setStyleSheet("QPushButton#acc {background-color:orange; color:white ;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px; border:none;}"
                               "QPushButton#acc:hover {background-color:white;color:black;}");

    // setup reject button
    _rej_button = new QPushButton(this);
    connect(_rej_button, &QPushButton::clicked, this, &MConfirmation::on_Rejected);
    _rej_button->setObjectName("rej");
    _rej_button->setStyleSheet("QPushButton#rej {background-color:orange; color:white ;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px; border:none;}"
                               "QPushButton#rej:hover {background-color:white;color:black;}");

    Q_UNUSED(parent);
}

MConfirmation::~MConfirmation()
{
    delete _background;
    delete _title;
    delete _acc_button;
    delete _rej_button;
}

void MConfirmation::closeEvent(QCloseEvent *event)
{
    
    QDialog::closeEvent(event);
}

void MConfirmation::on_Rejected()
{
    emit rejected();
    close();
}

void MConfirmation::on_Accepted()
{
    emit accepted();
    close();
}

void MConfirmation::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
    {
        emit rejected();
        close();
        break;
    }
    case Qt::Key_Enter:
    {
        emit accepted();
        close();
        break;
    }
    default:
    {
    }
    }
}
