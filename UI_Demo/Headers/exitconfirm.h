#ifndef EXITCOMFIRM_H
#define EXITCOMFIRM_H

#include "Headers/mconfirmation.h"

class ExitConfirm : public MConfirmation
{
    Q_OBJECT

public:
    explicit ExitConfirm(QWidget *parent = nullptr);
    ~ExitConfirm();

signals:
protected slots:
protected:
private:
};

#endif // EXITCOMFIRM_H
