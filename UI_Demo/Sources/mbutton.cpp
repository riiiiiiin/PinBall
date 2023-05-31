#include "Headers/mbutton.h"

MButton::MButton(int height, QString objName, QString text, QWidget *parent)
    : _height(height), _name(objName), _text(text)
{
    // setup Frame
    QFrame::setObjectName(_name + "_Frame");
    QFrame::setMouseTracking(true);
    QFrame::setStyleSheet("#" + QFrame::objectName() + "{ background-color: rgba(255,255,255,0.01);border-radius:2px; }");
    QFrame::setGeometry(175, height, 610, 30);
    QFrame::setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // setup ShadowEffect
    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setBlurRadius(20);
    _shadow->setColor(QColor("#ffffff"));
    _shadow->setOffset(0);
    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);
    // setup textLabel
    _txtLabel = new QLabel(this);
    _txtLabel->setGeometry(15, 3, 200, 20);
    _txtLabel->setObjectName(_name + "_Label");
    _txtLabel->setText(_text);
    _txtLabel->setStyleSheet("#" + _txtLabel->objectName() + "{color:white;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px;}");

    Q_UNUSED(parent);
}

MButton::~MButton()
{
    delete _txtLabel;
    delete _shadow;
}

void MButton::enterEvent(QEnterEvent *event)
{
    // reset frame
    QFrame::setStyleSheet("#" + QFrame::objectName() + "{ background-color: rgba(255,255,255,1.0);border-radius:3px; }");
    _shadow->setEnabled(true);
    this->setGraphicsEffect(_shadow);
    // reset textLabel
    _txtLabel->setStyleSheet("#" + _txtLabel->objectName() + "{color:black;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px;}");
    Q_UNUSED(event);
}

void MButton::leaveEvent(QEvent *event)
{
    // reset frame
    QFrame::setStyleSheet("#" + QFrame::objectName() + " { background-color: rgba(255,255,255,0.01);border-radius:5px; }");
    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);

    // reset textLabel
    _txtLabel->setStyleSheet("#" + _txtLabel->objectName() + "{color:white;font-family: \"Segoe UI Variable Small Semibol\"; font-size: 20px;}");

    Q_UNUSED(event);
}

void MButton::setText(QString const& text){
    _txtLabel->setText(text);
}