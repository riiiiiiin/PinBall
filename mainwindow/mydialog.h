#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class mydialog;
}

class mydialog : public QDialog
{
    Q_OBJECT

public:
    explicit mydialog( int _score,QWidget *parent = nullptr);
    ~mydialog();

private:
    Ui::mydialog *ui;
    int score;
};

#endif // MYDIALOG_H
