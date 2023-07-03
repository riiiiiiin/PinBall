
#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include "UI_Base/Headers/mbutton.h"

class MPushButton : public MButton
{
    Q_OBJECT

private:
public:
    MPushButton(int height, QString name, QString text, QDialog *parent = nullptr);
    ~MPushButton();

signals:
    void pushed();

protected:
    void mousePressEvent(QMouseEvent *event) override;

protected slots:
};

#endif // MPUSHBUTTON_H
