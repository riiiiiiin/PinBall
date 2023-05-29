#ifndef MSLIDER_H
#define MSLIDER_H

#include <QSlider>

#include "Headers/mbutton.h"

class MSlider : public MButton{
    Q_OBJECT
private:
    QSlider* _slider;
public:
    MSlider(int height,QString name,QString text,QDialog* parent = nullptr);
    ~MSlider();
signals:
    void number_changed(int);
protected slots:
    void handle_number_change();
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};


#endif