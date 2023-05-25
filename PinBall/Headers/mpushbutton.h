
#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QGraphicsDropShadowEffect>


class MPushButton : public QFrame
{
    Q_OBJECT

public:
    MPushButton(int height,QString name,QString text,QDialog* parent = nullptr);
    ~MPushButton();
private:
    int _height;
    QString _name;
    QString _text;
    QLabel* _txtLabel;
    QGraphicsDropShadowEffect* _shadow;

signals:
    void pushed();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // MPUSHBUTTON_H
