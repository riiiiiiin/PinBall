#ifndef MDRAGKIDNEY_H
#define MDRAGKIDNEY_H

#include "headers/mdraggable.h"

class MDragKidney : public MDraggable
{
public:
    MDragKidney(e_MDraggables type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragKidney();
};

class MDragDrum : public MDraggable
{
public:
    MDragDrum(e_MDraggables type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragDrum();
};

class MDragAward : public MDraggable
{
public:
    MDragAward(e_MDraggables type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragAward();
};

class MDragCirWall : public MDraggable{
public:
    MDragCirWall(e_MDraggables type, QPixmap *staitc_pic, QPixmap *dragged_valid, QPixmap *dragged_invalid, QPoint location_source, QWidget *parent = nullptr);
    ~MDragCirWall();
};

#endif