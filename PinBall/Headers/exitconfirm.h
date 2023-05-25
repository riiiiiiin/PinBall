#ifndef EXITCOMFIRM_H
#define EXITCOMFIRM_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>

class ExitConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit ExitConfirm(QWidget *parent = nullptr);
    ~ExitConfirm();

signals:
    void exitReq();
    void closed();

private slots:
    void on_Rejected();
    void on_Accepted();
protected:
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    QLabel* _background;
    QLabel* _title;
    QPushButton* _acc_button;
    QPushButton* _rej_button;
};

#endif // EXITCOMFIRM_H
