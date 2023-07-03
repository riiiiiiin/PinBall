#include "MapEditor/Headers/mdraggables.h"

MDragLKidney::MDragLKidney(enumMapElements type, QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(home_pic,static_pic,dragged_valid,dragged_invalid,location_source,parent,is_set_properly)
{
    
    _type = type;
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

MDragRKidney::MDragRKidney(enumMapElements type,QPixmap* home_pic, QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(home_pic,static_pic,dragged_valid,dragged_invalid,location_source,parent,is_set_properly)
{
    _type = type;
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

MDragDrum::MDragDrum(enumMapElements type, QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(home_pic,static_pic,dragged_valid,dragged_invalid,location_source,parent,is_set_properly){
    _type = type;
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

MDragBonusPoint::MDragBonusPoint(enumMapElements type,QPixmap* home_pic, QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent,bool is_set_properly):
MDraggable(home_pic,static_pic,dragged_valid,dragged_invalid,location_source,parent,is_set_properly){
    _type = type;
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