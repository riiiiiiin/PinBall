#include "headers/mdraggables.h"

MDragKidney::MDragKidney(e_MDraggables type, QPixmap* staitc_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent):
MDraggable(location_source,parent)
{
    
    _type = type;
    _static_pic = staitc_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;

    _label->setPixmap(*_static_pic);
    _label->setMask(_static_pic->mask());
    setVisible(true);
}

MDragKidney::~MDragKidney(){}

MDragDrum::MDragDrum(e_MDraggables type, QPixmap* staitc_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget* parent):
MDraggable(location_source,parent)
{
    _type = type;
    _static_pic = staitc_pic;
    _dragged_valid = dragged_valid;
    _dragged_invalid = dragged_invalid;

    _label->setPixmap(*_static_pic);
    _label->setMask(_static_pic->mask());
    setVisible(true);
}

MDragDrum::~MDragDrum(){}