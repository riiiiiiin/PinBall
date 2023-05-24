
#include "mcheckbutton.h"

MCheckButton::MCheckButton(int height,QString name,QDialog* parent)
    :_height(height),_checked(false),_name(name)
{
    QFrame::setObjectName(name+"_Frame");
    QFrame::setMouseTracking(true);
    QFrame::setStyleSheet("#"+QFrame::objectName()+"{ background-color: rgba(255,255,255,0.01);border-radius:3px; }");
    QFrame::setGeometry(175, height, 610, 30);
    QFrame::setWindowFlags(Qt::FramelessWindowHint|windowFlags());

    _shadow = new QGraphicsDropShadowEffect();
    _shadow->setBlurRadius(20);
    _shadow->setColor(QColor("#ffffff"));
    _shadow->setOffset(0);
    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);

    _txtLabel = new QLabel(this);
    _txtLabel->setGeometry(15,3,200,20);
    _txtLabel->setObjectName(name+"_Label");
    _txtLabel->setText("AAAAAAAAAA");

    QFont font;
    font.setFamily("Segoe UI Variable Small Semibol");
    font.setBold(false);
    font.setPixelSize(20);
    _txtLabel->setFont(font);

    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#ffffff"));
    _txtLabel->setPalette(plt);

    _iconLabel = new QLabel(this);
    _iconLabel->setGeometry(570,3,24,24);
    _iconLabel->setText("");

    _ico_black = new QPixmap(":/icons/Box_Black_unChecked.png");
    _ico_white = new QPixmap(":/icons/Box_White_unChecked.png");
    _ico_black_checked = new QPixmap(":/icons/Box_Black_Checked.png");
    _ico_white_checked = new QPixmap(":/icons/Box_White_Checked.png");

    _iconLabel->setPixmap(*_ico_white);
    _iconLabel->setMask(_ico_white->mask());
}

MCheckButton::~MCheckButton(){
    delete _txtLabel;
    delete _iconLabel;
}

void MCheckButton::enterEvent(QEnterEvent* event){
    //QFrame::
    QFrame::setStyleSheet( "#"+QFrame::objectName()+"{ background-color: rgba(255,255,255,1.0);border-radius:3px; }");

    _shadow->setEnabled(true);
    this->setGraphicsEffect(_shadow);

    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#000000"));
    _txtLabel->setPalette(plt);
    if(_checked){
        _iconLabel->setPixmap(*_ico_black_checked);
        _iconLabel->setMask(_ico_white_checked->mask());
    }
    else{
        _iconLabel->setPixmap(*_ico_black);
        _iconLabel->setMask(_ico_white->mask());
    }



    Q_UNUSED(event);
}

void MCheckButton::leaveEvent(QEvent* event){
    QFrame::setStyleSheet("#"+QFrame::objectName()+" { background-color: rgba(255,255,255,0.01);border-radius:5px; }");

    _shadow->setEnabled(false);
    this->setGraphicsEffect(_shadow);

    QPalette plt = _txtLabel->palette();
    plt.setColor(QPalette::WindowText,QColor("#ffffff"));
    _txtLabel->setPalette(plt);

    if(_checked){
        _iconLabel->setPixmap(*_ico_white_checked);
        _iconLabel->setMask(_ico_white_checked->mask());
    }
    else{
        _iconLabel->setPixmap(*_ico_white);
        _iconLabel->setMask(_ico_white->mask());
    }



    Q_UNUSED(event);
}

void MCheckButton::mousePressEvent(QMouseEvent* event){
    Q_UNUSED(event);
    if(_checked){
        _iconLabel->setPixmap(*_ico_black);
        _iconLabel->setMask(_ico_white->mask());
        _checked = false;
    }
    else{
        _iconLabel->setPixmap(*_ico_black_checked);
        _iconLabel->setMask(_ico_white_checked->mask());
        _checked = true;
    }


}
