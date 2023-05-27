#ifndef MDRAGCONTAINERS_H
#define MDRAGCONTAINERS_H

#include "headers/mdraggable.h"

#include <QList>

class MDragContainer : public QObject{
    Q_OBJECT
private:
    MDraggable* _draggable_home;
    MDraggable* _draggable_buffer;
    QList<MDraggable*> _elements;
    QWidget* _parent;
    QPoint _location;
public:
    explicit MDragContainer(QPoint location,QWidget* parent = nullptr);
    ~MDragContainer();
public slots:
    void create_new();
    void trash_old();
    void move_old();
    void handle_remove_element(MDraggable*);
};

#endif