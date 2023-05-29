#ifndef MDRAGCONTAINER_H
#define MDRAGCONTAINER_H

#include "headers/mdraggables.h"

#include <QList>

class MDragContainer : public QObject{
    Q_OBJECT
private:
    QPixmap* _static_pic;
    QPixmap* _dragged_valid;
    QPixmap* _dragged_invalid;
    QPixmap* _static_pic_2;
    QPixmap* _dragged_valid_2;
    QPixmap* _dragged_invalid_2;

    MDragKidney* _dragKidney_home;
    MDragDrum* _dragDrum_home;
    MDraggable* _draggable_buffer;

    QList<MDraggable*> _elements;
    QWidget* _parent;
    QPoint _location_kidney{QPoint(600,400)};
    QPoint _location_drum{QPoint(600,100)};
public:
    explicit MDragContainer(QWidget* parent = nullptr);
    ~MDragContainer();
public slots:
    void create_new_kidney();
    void create_new_drum();
    void trash_old();
    void move_old();
    void handle_remove_element(MDraggable*);
};

#endif