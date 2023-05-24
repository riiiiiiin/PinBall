
#include "mpushbutton.h"

MPushButton::MPushButton(int height,QString name,QString text,QDialog* parent)
    :_height(height),_name(name),_text(text)
{
    //setup Frame
    QFrame::setObjectName(name+"_Frame");
    QFrame::setMouseTracking(true);
    QFrame::setStyleSheet("#"+QFrame::objectName()+"{ background-color: rgba(255,255,255,0.01);border-radius:3px; }");
    QFrame::setGeometry(175, height, 610, 30);
    QFrame::setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    //setup ShadowEffect
    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setBlurRadius(20);
    _shadow->setColor(QColor("#ffffff"));
    _shadow->setOffset(0);
    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);
    //setup textLabel
    _txtLabel = new QLabel(this);
    _txtLabel->setGeometry(15,3,200,20);
    _txtLabel->setObjectName(name+"_Label");
    _txtLabel->setText(_text);
    //Font of textLabel
    QFont font;
    font.setFamily("Segoe UI Variable Small Semibol");
    font.setBold(false);
    font.setPixelSize(20);
    _txtLabel->setFont(font);
    //Plt of textLabel
    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#ffffff"));
    _txtLabel->setPalette(plt);

    Q_UNUSED(parent);
}

MPushButton::~MPushButton(){
    delete _txtLabel;
    delete _shadow;
}

void MPushButton::enterEvent(QEnterEvent* event){
    //reset frame
    QFrame::setStyleSheet( "#"+QFrame::objectName()+"{ background-color: rgba(255,255,255,1.0);border-radius:3px; }");
    _shadow->setEnabled(true);
    this->setGraphicsEffect(_shadow);
    //reset textLabel
    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#000000"));
    _txtLabel->setPalette(plt);
    Q_UNUSED(event);
}

void MPushButton::leaveEvent(QEvent* event){
    //reset frame
    QFrame::setStyleSheet("#"+QFrame::objectName()+" { background-color: rgba(255,255,255,0.01);border-radius:5px; }");
    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);

    //reset textLabel
    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#ffffff"));
    _txtLabel->setPalette(plt);

    Q_UNUSED(event);
}

void MPushButton::mousePressEvent(QMouseEvent* event){
    emit pushed();
    Q_UNUSED(event);
}
