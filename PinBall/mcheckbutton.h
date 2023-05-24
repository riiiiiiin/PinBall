
#ifndef MCHECKBUTTON_H
#define MCHECKBUTTON_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

class MCheckButton : public QFrame
{
public:
    MCheckButton(int height,QString name,QDialog* parent = nullptr);
    ~MCheckButton()
        ;
private:
    int _height;
    bool _checked;
    QString _name;
    QLabel* _txtLabel;
    QLabel* _iconLabel;
    QGraphicsDropShadowEffect* _shadow;
    QPixmap* _ico_black;
    QPixmap* _ico_white;
    QPixmap* _ico_black_checked;
    QPixmap* _ico_white_checked;

protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // MCHECKBUTTON_H
