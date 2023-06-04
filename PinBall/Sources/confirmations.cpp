#include "Headers/confirmations.h"

ExitConfirm::ExitConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(365, 190, 240, 50);
    _title->setText("Sure To Exit?");

    _acc_button->setGeometry(360, 260, 120, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(490, 260, 120, 30);
    _rej_button->setText("No");
}

ExitConfirm::~ExitConfirm()
{
}


SwitchToMapConfirm::SwitchToMapConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(350, 190, 300, 60);
    _title->setText("Save and Play?");

    _acc_button->setGeometry(360, 260, 120, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(490, 260, 120, 30);
    _rej_button->setText("Cancel");
}

SwitchToMapConfirm::~SwitchToMapConfirm()
{
}

SwitchToMapEditorConfirm::SwitchToMapEditorConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(352, 190, 300, 50);
    _title->setText("Edit The Map?");

    _acc_button->setGeometry(360, 260, 120, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(490, 260, 120, 30);
    _rej_button->setText("Cancel");
}

SwitchToMapEditorConfirm::~SwitchToMapEditorConfirm()
{
}

NewGameConfirm::NewGameConfirm(QWidget *parent) : MConfirmation(parent){
    _title->setGeometry(230, 190, 500, 50);
    _title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _title->setText("🎉Your Score : 99 🎉");

    _acc_button->setGeometry(360, 260, 120, 30);
    _acc_button->setText("Try Again!");

    _rej_button->setGeometry(490, 260, 120, 30);
    _rej_button->setText("Exit");
}

NewGameConfirm::~NewGameConfirm(){}

void NewGameConfirm::setScore(int score){
    _title->setText("🎉Your Score : "+QString::number(score)+" 🎉");
}