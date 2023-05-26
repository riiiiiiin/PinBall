
#include "Headers/mcheckbutton.h"

MCheckButton::MCheckButton(int height,QString name,QString text,QDialog* parent)
    :MButton(height,name,text,parent)
{
    //setup icon
    _iconLabel = new QLabel(this);
    _iconLabel->setGeometry(570,3,24,24);
    _iconLabel->setText("");

    _ico_black = new QPixmap(":/icons/Box_Black_unChecked.png");
    _ico_white = new QPixmap(":/icons/Box_White_unChecked.png");
    _ico_black_checked = new QPixmap(":/icons/Box_Black_Checked.png");
    _ico_white_checked = new QPixmap(":/icons/Box_White_Checked.png");

    _iconLabel->setPixmap(*_ico_white);
    _iconLabel->setMask(_ico_white->mask());

    Q_UNUSED(parent);
}

MCheckButton::~MCheckButton(){
    delete _iconLabel;
    delete _ico_black;
    delete _ico_white;
    delete _ico_black_checked;
    delete _ico_white_checked;
}

void MCheckButton::enterEvent(QEnterEvent* event){
    //reset frame
    MButton::enterEvent(event);

    //reset icon
    if(_checked){
        _iconLabel->setPixmap(*_ico_black_checked);
        _iconLabel->setMask(_ico_white_checked->mask());
    }
    else{
        _iconLabel->setPixmap(*_ico_black);
        _iconLabel->setMask(_ico_white->mask());
    }
}

void MCheckButton::leaveEvent(QEvent* event){
    //reset frame
    MButton::leaveEvent(event);

    //reset icon
    if(_checked){
        _iconLabel->setPixmap(*_ico_white_checked);
        _iconLabel->setMask(_ico_white_checked->mask());
    }
    else{
        _iconLabel->setPixmap(*_ico_white);
        _iconLabel->setMask(_ico_white->mask());
    }
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
    emit checked(_checked);
}
