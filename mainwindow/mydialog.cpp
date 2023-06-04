#include "mydialog.h"
#include "ui_mydialog.h"

mydialog::mydialog(QWidget *parent) :
    QDialog(parent),ui(new Ui::mydialog)
{
    ui->setupUi(this);
}

mydialog::~mydialog()
{
    delete ui;
}

void mydialog::on_pushButton_clicked()
{

    emit new_game();
}


void mydialog::getscore(int _score){
    score=_score;
    ui->myscore->setNum(score);
}
