#ifndef MCONFIRMATION_H
#define MCONFIRMATION_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>

class MConfirmation : public QDialog
{
    Q_OBJECT
private:
    QLabel *_background;

protected:
    QLabel *_title;
    QPushButton *_acc_button;
    QPushButton *_rej_button;

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
protected slots:
    virtual void on_Rejected();
    virtual void on_Accepted();
signals:
    void accepted();
    void rejected();

public:
    explicit MConfirmation(QWidget *parent = nullptr);
    virtual ~MConfirmation();
};

#endif
