
#ifndef MCHECKBUTTON_H
#define MCHECKBUTTON_H

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QObject>

class MCheckButton : public QFrame
{
    Q_OBJECT

public:
    MCheckButton(int height,QString objname,QString text,QDialog* parent = nullptr);
    ~MCheckButton();
private:
    int _height;
    bool _checked;
    QString _name;
    QString _text;
    QLabel* _txtLabel;
    QLabel* _iconLabel;
    QGraphicsDropShadowEffect* _shadow;
    QPixmap* _ico_black;
    QPixmap* _ico_white;
    QPixmap* _ico_black_checked;
    QPixmap* _ico_white_checked;

signals:
    void checked(bool);
protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // MCHECKBUTTON_H
