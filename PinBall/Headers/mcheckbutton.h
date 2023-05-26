
#ifndef MCHECKBUTTON_H
#define MCHECKBUTTON_H

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QObject>

#include "Headers/mbutton.h"

class MCheckButton : public MButton
{
    Q_OBJECT

private:
    bool _checked;
    QLabel *_iconLabel;
    QPixmap *_ico_black;
    QPixmap *_ico_white;
    QPixmap *_ico_black_checked;
    QPixmap *_ico_white_checked;

signals:
    void checked(bool);

protected:
    void mousePressEvent(QMouseEvent *event) override;

protected slots:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

public:
    MCheckButton(int height, QString objname, QString text, QDialog *parent = nullptr);
    ~MCheckButton();
};

#endif // MCHECKBUTTON_H
