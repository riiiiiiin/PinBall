#include "Headers/mslider.h"

MSlider::MSlider(int height, QString name, QString text, QDialog *parent)
    : MButton(height, name, text, parent)
{
    _slider = new QSlider(Qt::Horizontal, this);
    _slider->setGeometry(400, 5, 200, 30);
    _slider->setObjectName(name + "_Slider");
    _slider->setMinimum(1);
    _slider->setMaximum(200);
    _slider->setSingleStep(1);
    _slider->setTracking(true);
    _slider->setStyleSheet("QSlider{ min-height : 20px; max-height : 20px; }"
                           "QSlider::groove:horizontal{ height : 5px; background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal{ margin:-4px;height:20px ; width:20px;background-color:white;border:0px; }"
                           "QSlider::groove:horizontal:hover{height:5px;background-color:white;border:0px;left: 10px;right:10px;}"
                           "QSlider::handle:horizontal:hover{ margin:-4px;height:20px ; width:20px;background-color:white;border:0px; }");
    connect(_slider, QSlider::sliderReleased, this, MSlider::handle_number_change);
}

MSlider::~MSlider()
{
    delete _slider;
}

void MSlider::handle_number_change()
{
    emit number_changed(_slider->value());
    qDebug() << "s";
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