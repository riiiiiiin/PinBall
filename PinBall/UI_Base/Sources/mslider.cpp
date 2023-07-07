#include "UI_Base/Headers/mslider.h"

MSlider::MSlider(int height, QString name, QString text, QDialog *parent)
    : MButton(height, name, text, parent),_text(text)
{
    _slider = new QSlider(Qt::Horizontal, this);
    _slider->setGeometry(400, 5, 200, 30);
    _slider->setObjectName(name + "_Slider");
    _slider->setMinimum(50);
    _slider->setMaximum(300);
    _slider->setSingleStep(1);
    _slider->setTracking(true);
    _slider->setStyleSheet("QSlider{ min-height : 20px; max-height : 20px; }"
                           "QSlider::groove:horizontal{ height : 5px; background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal{ margin:-4px;height:20px ; width:20px;background-color:white;border:0px; }"
                           "QSlider::groove:horizontal:hover{height:5px;background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal:hover{ margin:-4px;height:20px ; width:20px;background-color:white;border:0px; }");
    connect(_slider, &QSlider::sliderReleased, this, &MSlider::handle_number_change);
}

MSlider::~MSlider()
{
    delete _slider;
}

void MSlider::handle_number_change()
{
    emit number_changed(_slider->value());
    setText(_text+" : "+QString::number(_slider->value())+"%");
}

void MSlider::enterEvent(QEnterEvent *event)
{
    _slider->setStyleSheet("QSlider{min-height: 20px;max-height: 20px;}"
                           "QSlider::groove:horizontal{height:5px;background-color:black;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal{ margin:-4px;height:20px ; width:20px;background-color:black;border:0px; }"
                           "QSlider::groove:horizontal:hover{height:5px;background-color:black;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal:hover{ margin:-4px;height:20px ; width:20px;background-color:black;border:0px; }");
    MButton::enterEvent(event);
}

void MSlider::leaveEvent(QEvent *event)
{
    _slider->setStyleSheet("QSlider{min-height: 20px;max-height: 20px;}"
                           "QSlider::groove:horizontal{height:5px;background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal{ margin:-4px;height:20px ; width:20px;background-color:white; border:0px;}"
                           "QSlider::groove:horizontal:hover{height:5px;background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal:hover{ margin:-4px;height:20px ; width:20px;background-color:white;border:0px; }");
    MButton::leaveEvent(event);
}

void MSlider::setMinimum(int n){
    _slider->setMinimum(n);
}

void MSlider::setMaximum(int n){
    _slider->setMaximum(n);
}

bool MSlider::setDefault(int n){
    if(n<=_slider->maximum()&&n>=_slider->minimum()){
        _slider->setValue(n);
        setText(_text+" : "+QString::number(_slider->value())+"%");
        return true;
    }
    else{
        return false;
    }
}