#ifndef MDRAGCONTAINER_H
#define MDRAGCONTAINER_H

#include "headers/mdraggables.h"

#include <QList>
#include <QGraphicsScene>

class MDragContainer : public QObject{
    Q_OBJECT
private:
    QPixmap* _static_pic;
    QPixmap* _dragged_valid;
    QPixmap* _dragged_invalid;
    QPixmap* _static_pic_2;
    QPixmap* _dragged_valid_2;
    QPixmap* _dragged_invalid_2;
    QPixmap* _static_pic_3;
    QPixmap* _dragged_valid_3;
    QPixmap* _dragged_invalid_3;
    QPixmap* _static_pic_4;
    QPixmap* _dragged_valid_4;
    QPixmap* _dragged_invalid_4;

    MDragKidney* _dragKidney_home;
    MDragDrum* _dragDrum_home;
    MDragAward* _dragAward_home;
    MDragCirWall* _dragCirWall_home;
    MDraggable* _draggable_buffer;

    QList<MDraggable*> _elements;
    QPoint _location_kidney{QPoint(670,180)};
    QPoint _location_drum{QPoint(670,60)};
    QPoint _location_award{QPoint(790,180)};
    QPoint _location_cirWall{QPoint(790,60)};

    QWidget* _parent;
    QGraphicsScene* _scene;
public:
    explicit MDragContainer(QWidget* parent = nullptr);
    ~MDragContainer();
    QList<MDraggable*> mapElements();
public slots:
    void create_new_kidney();
    void create_new_drum();
    void create_new_award();
    void create_new_cirWall();
    void trash_old();
    void push_old();
    void handle_remove_element(MDraggable*);
};

#endif