#ifndef CONFIRMATIONS_H
#define CONFIRMATIONS_H

#include "UI_Base/Headers/mconfirmation.h"

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

class SwitchToMapConfirm:public MConfirmation{
    Q_OBJECT
public:
    explicit SwitchToMapConfirm(QWidget* parent = nullptr);
    ~SwitchToMapConfirm();
};

class SwitchToMapEditorConfirm:public MConfirmation{
    Q_OBJECT
public:
    explicit SwitchToMapEditorConfirm(QWidget* parent = nullptr);
    ~SwitchToMapEditorConfirm();
};

class NewGameConfirm:public MConfirmation{
    Q_OBJECT
public:
    explicit NewGameConfirm(QWidget* parent=nullptr);
    ~NewGameConfirm();
    void setScore(int);
};

#endif 
