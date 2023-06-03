#include "Headers/confirmations.h"

ExitConfirm::ExitConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(355, 190, 240, 50);
    _title->setText("Sure To Exit?");

    _acc_button->setGeometry(385, 260, 80, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(485, 260, 80, 30);
    _rej_button->setText("No");
}

ExitConfirm::~ExitConfirm()
{
}


SwitchToMapConfirm::SwitchToMapConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(340, 190, 300, 50);
    _title->setText("Save and Play?");

    _acc_button->setGeometry(385, 260, 80, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(485, 260, 80, 30);
    _rej_button->setText("Cancel");
}

SwitchToMapConfirm::~SwitchToMapConfirm()
{
}

SwitchToMapEditorConfirm::SwitchToMapEditorConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(340, 190, 300, 50);
    _title->setText("Edit The Map?");

    _acc_button->setGeometry(385, 260, 80, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(485, 260, 80, 30);
    _rej_button->setText("Cancel");
}

SwitchToMapEditorConfirm::~SwitchToMapEditorConfirm()
{
}