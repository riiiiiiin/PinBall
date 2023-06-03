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


signals:
    void new_game();
private slots:
    void on_pushButton_clicked();

private:
    Ui::mydialog *ui;
    int score;
};

#endif // MYDIALOG_H
