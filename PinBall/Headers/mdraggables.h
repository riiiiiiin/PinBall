#ifndef MDRAGKIDNEY_H
#define MDRAGKIDNEY_H

#include "headers/mdraggable.h"

class MDragLKidney : public MDraggable
{
public:
    MDragLKidney(e_MapElements type, QPixmap* home_pic,QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr,bool is_set_properly=false);
    ~MDragLKidney();
    QPoint locatingPoint()const override;
};

class MDragRKidney : public MDraggable
{
public:
    MDragRKidney(e_MapElements type, QPixmap* home_pic,QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr,bool is_set_properly=false);
    ~MDragRKidney();
    QPoint locatingPoint()const override;
};

class MDragDrum : public MDraggable
{
public:
    MDragDrum(e_MapElements type, QPixmap* home_pic,QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr,bool is_set_properly=false);
    ~MDragDrum();
    QPoint locatingPoint()const override;
};

class MDragBonusPoint : public MDraggable{
public:
    MDragBonusPoint(e_MapElements type, QPixmap* home_pic,QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr,bool is_set_properly=false);
    ~MDragBonusPoint();
    QPoint locatingPoint()const override;
};

#endif