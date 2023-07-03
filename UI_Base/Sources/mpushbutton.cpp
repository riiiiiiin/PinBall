#include "UI_Base/Headers/mpushbutton.h"

MPushButton::MPushButton(int height, QString name, QString text, QDialog *parent)
    : MButton(height, name, text, parent)
{
    // setup Frame
}

MPushButton::~MPushButton()
{
}

void MPushButton::mousePressEvent(QMouseEvent *event)
{
    emit pushed();
    Q_UNUSED(event);
}
