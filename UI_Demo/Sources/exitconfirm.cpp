#include "Headers/exitconfirm.h"

ExitConfirm::ExitConfirm(QWidget *parent) : MConfirmation(parent)
{
    _title->setGeometry(348, 190, 240, 50);
    _title->setText("Sure To Exit?");

    _acc_button->setGeometry(385, 260, 60, 30);
    _acc_button->setText("Yes");

    _rej_button->setGeometry(485, 260, 60, 30);
    _rej_button->setText("No");
}

ExitConfirm::~ExitConfirm()
{
}
