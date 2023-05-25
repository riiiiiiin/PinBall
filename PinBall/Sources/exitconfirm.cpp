#include "Headers/exitconfirm.h"


ExitConfirm::ExitConfirm(QWidget *parent) :
    QDialog(parent)
{
    setGeometry(0,0,960,540);
    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    _background = new QLabel(this);
    _background->setGeometry(0,180,960,140);
    _background->setText("");
    _background->setObjectName("_background_");
    _background->setStyleSheet("QLabel#"+_background->objectName()+"{background-color:orange;}");
    _background->setParent(this);

    _title = new QLabel(this);
    _title->setGeometry(348,190,240,50);
    _title->setText("Sure To Exit?");
    _title->setStyleSheet("color:white;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 40px;");
    _title->setParent(this);

    _acc_button = new QPushButton(this);
    connect(_acc_button,&QPushButton::clicked,this,&ExitConfirm::on_Accepted);
    _acc_button->setObjectName("acc");
    _acc_button->setGeometry(385,260,60,30);
    _acc_button->setText("Yes");
    _acc_button->setStyleSheet("QPushButton#acc {background-color:orange; color:white ;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px; border:none;}"
                               "QPushButton#acc:hover {background-color:white;color:black;}");


    _rej_button = new QPushButton(this);
    connect(_rej_button,&QPushButton::clicked,this,&ExitConfirm::on_Rejected);
    _rej_button->setObjectName("rej");
    _rej_button->setGeometry(485,260,60,30);
    _rej_button->setText("No");
    _rej_button->setStyleSheet("QPushButton#rej {background-color:orange; color:white ;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px; border:none;}"
                               "QPushButton#rej:hover {background-color:white;color:black;}");
}

ExitConfirm::~ExitConfirm()
{
    delete _background;
    delete _title;
    delete _acc_button;
    delete _rej_button;
}

void ExitConfirm::closeEvent(QCloseEvent* event){
    emit closed();
    QDialog::closeEvent(event);
}

void ExitConfirm::on_Rejected(){
    close();
}

void ExitConfirm::on_Accepted(){
    emit exitReq();
}

void ExitConfirm::keyPressEvent(QKeyEvent *event)
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

