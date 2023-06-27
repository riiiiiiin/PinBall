#include "headers/mdraggables.h"

MDragLKidney::MDragLKidney(e_MapElements type, QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(static_pic,location_source,parent,is_set_properly)
{
    
    _type = type;
    _static_pic = static_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;
    _label->resize(100,100);
    _label->setPixmap(*home_pic);
    _label->setMask(home_pic->mask());
    setVisible(true);
}
//note:offset to be determined
QPoint MDragLKidney::locatingPoint()const{
    return QPoint((pos().x()+50),(pos().y())+120);
}

MDragLKidney::~MDragLKidney(){}

MDragRKidney::MDragRKidney(e_MapElements type,QPixmap* home_pic, QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(static_pic,location_source,parent,is_set_properly)
{
    _type = type;
    _static_pic = static_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;
    _label->resize(100,100);
    _label->setPixmap(*home_pic);
    _label->setMask(home_pic->mask());
    setVisible(true);
}
//note:offset to be determined
QPoint MDragRKidney::locatingPoint()const{
    return QPoint((pos().x()+3),(pos().y()+120));
}

MDragRKidney::~MDragRKidney(){}

MDragDrum::MDragDrum(e_MapElements type, QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(static_pic,location_source,parent,is_set_properly){
    _type = type;
    _static_pic = static_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;
    _label->resize(100,100);
    _label->setPixmap(*home_pic);
    _label->setMask(home_pic->mask());
    setVisible(true);
}
//note:offset to be determined
QPoint MDragDrum::locatingPoint()const{
    return QPoint((pos().x()+20),(pos().y())+20);
}

MDragDrum::~MDragDrum(){}

MDragBonusPoint::MDragBonusPoint(e_MapElements type,QPixmap* home_pic, QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(static_pic,location_source,parent,is_set_properly){
    _type = type;
    _static_pic = static_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;
    _label->resize(100,100);
    _label->setPixmap(*home_pic);
    _label->setMask(home_pic->mask());
    setVisible(true);
}
//note:offset to be determined
QPoint MDragBonusPoint::locatingPoint()const{
    return QPoint((pos().x()+10),(pos().y())+10);
}

MDragBonusPoint::~MDragBonusPoint(){}