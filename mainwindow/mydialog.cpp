#include "mydialog.h"
#include "ui_mydialog.h"

mydialog::mydialog(int _score,QWidget *parent) :
    QDialog(parent),score(_score),
    ui(new Ui::mydialog)
{
    ui->setupUi(this);
    ui->myscore->setNum(score);
}

mydialog::~mydialog()
{
    delete ui;
}
