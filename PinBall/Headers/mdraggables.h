#ifndef MDRAGKIDNEY_H
#define MDRAGKIDNEY_H

#include "headers/mdraggable.h"

class MDragLKidney : public MDraggable
{
public:
    MDragLKidney(e_MapElements type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragLKidney();
};

class MDragRKidney : public MDraggable
{
public:
    MDragRKidney(e_MapElements type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragRKidney();
};

class MDragDrum : public MDraggable
{
public:
    MDragDrum(e_MapElements type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragDrum();
};

class MDragBonusPoint : public MDraggable{
public:
    MDragBonusPoint(e_MapElements type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragBonusPoint();
};

#endif