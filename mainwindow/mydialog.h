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
    explicit mydialog( QWidget *parent = nullptr);
    ~mydialog();
    void getscore(int _score);

signals:
    void new_game();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mydialog *ui;
    int score;
};

#endif // MYDIALOG_H
