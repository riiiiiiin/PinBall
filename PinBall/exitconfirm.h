#ifndef EXITCOMFIRM_H
#define EXITCOMFIRM_H

#include <QDialog>
#include <QApplication>

namespace Ui {
class ExitConfirm;
}

class ExitConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit ExitConfirm(QWidget *parent = nullptr,QApplication* app=nullptr);
    ~ExitConfirm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ExitConfirm *ui;
    QApplication* _app;
};

#endif // EXITCOMFIRM_H
