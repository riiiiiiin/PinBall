#include "headers/mdragcontainers.h"

MDragContainer::MDragContainer(QPoint location, QWidget *parent) : QObject(parent),_parent(parent), _location(location)
{
    _draggable_home = new MDraggable(location,parent);
    _draggable_buffer = nullptr;
    connect(_draggable_home,&MDraggable::be_moved,this,&MDragContainer::create_new);
    _elements.clear();
}

MDragContainer::~MDragContainer(){
    disconnect(this);
    delete _draggable_home;
    if(_draggable_buffer != nullptr){
        delete _draggable_buffer;
    }
    for (auto ptr : _elements)
    {
        delete ptr;
    }
    _elements.clear();
}

void MDragContainer::create_new(){
    _draggable_buffer = _draggable_home;
    disconnect(_draggable_buffer,&MDraggable::be_moved,this,&MDragContainer::create_new);
    connect(_draggable_buffer,&MDraggable::be_released_invalidly,this,&MDragContainer::trash_old);
    connect(_draggable_buffer,&MDraggable::be_released_validly,this,&MDragContainer::move_old);
    _draggable_home = nullptr;
    _draggable_home = new MDraggable(_location,_parent);
    connect(_draggable_home,&MDraggable::be_moved,this,&MDragContainer::create_new);
    _draggable_buffer->raise();
}

void MDragContainer::trash_old(){
    if(_draggable_buffer != nullptr){
        delete _draggable_buffer;
    }
    _draggable_buffer = nullptr;
}

void MDragContainer::move_old(){
    disconnect(_draggable_buffer,nullptr,this,nullptr);
    if (not _elements.contains(_draggable_buffer))
    {
        _elements.push_back(_draggable_buffer);
        connect(_draggable_buffer, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
    }
    _draggable_buffer = nullptr;
}

void MDragContainer::handle_remove_element(MDraggable *element_to_remove)
{
    _elements.removeOne(element_to_remove);
    delete element_to_remove;
}