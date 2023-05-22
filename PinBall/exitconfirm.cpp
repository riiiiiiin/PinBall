#include "exitconfirm.h"
#include "ui_exitconfirm.h"

ExitConfirm::ExitConfirm(QWidget *parent,QApplication* app) :
    QDialog(parent),
    ui(new Ui::ExitConfirm),
    _app(app)
{
    ui->setupUi(this);
    this->setModal(true);
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags());

}

ExitConfirm::~ExitConfirm()
{
    delete ui;
}

void ExitConfirm::on_buttonBox_accepted()
{
    _app->quit();
}


void ExitConfirm::on_buttonBox_rejected()
{
    close();
}

