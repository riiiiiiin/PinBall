#ifndef MBUTTON_H
#define MBUTTON_H

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QObject>

class MButton : public QFrame
{
    Q_OBJECT

private:
    int _height;
    QString _name;
    QString _text;
    QLabel *_txtLabel;
    QGraphicsDropShadowEffect *_shadow;

protected:
    void setText(QString const&);
signals:

protected slots:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

public:
    MButton(int height, QString objName, QString text, QWidget *parent = nullptr);
    virtual ~MButton();
};

#endif