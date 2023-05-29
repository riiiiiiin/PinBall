#include "headers/mdragcontainer.h"

MDragContainer::MDragContainer(QWidget *parent) : QObject(parent), _parent(parent)
{
    qDebug()<<this;
    // open pixmap
    _static_pic = new QPixmap(":/new/prefix2/static.png");
    _dragged_valid = new QPixmap(":/new/prefix2/dragged_valid.png");
    _dragged_invalid = new QPixmap(":/new/prefix2/dragged_invalid.png");
    _static_pic_2 = new QPixmap(":/new/prefix2/static_2.png");
    _dragged_valid_2 = new QPixmap(":/new/prefix2/dragged_valid_2.png");
    _dragged_invalid_2 = new QPixmap(":/new/prefix2/dragged_invalid_2.png");

    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, parent);
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, parent);
    _draggable_buffer = nullptr;

    connect(_dragKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    _elements.clear();
}

MDragContainer::~MDragContainer()
{
    disconnect(this);
    delete _dragKidney_home;
    delete _dragDrum_home;
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    for (auto ptr : _elements)
    {
        delete ptr;
    }
    _elements.clear();
    delete _static_pic ;
    delete _dragged_valid ;
    delete _dragged_invalid ;
    delete _static_pic_2 ;
    delete _dragged_valid_2 ;
    delete _dragged_invalid_2;
}

void MDragContainer::create_new_kidney()
{
    _draggable_buffer = _dragKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::move_old);
    _dragKidney_home = nullptr;
    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, _parent);
    connect(_dragKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    _draggable_buffer->raise();
}

void MDragContainer::create_new_drum()
{
    _draggable_buffer = _dragDrum_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::move_old);
    _dragDrum_home = nullptr;
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, _parent);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    _draggable_buffer->raise();
}

void MDragContainer::trash_old()
{
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    _draggable_buffer = nullptr;
}

void MDragContainer::move_old()
{
    if (_draggable_buffer != nullptr)
    {
        disconnect(_draggable_buffer, nullptr, this, nullptr);
        if (not _elements.contains(_draggable_buffer))
        {
            _elements.push_back(_draggable_buffer);
            connect(_draggable_buffer, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
        }
        _draggable_buffer = nullptr;
    }
}

void MDragContainer::handle_remove_element(MDraggable *element_to_remove)
{
    if (element_to_remove != nullptr)
    {
        _elements.removeOne(element_to_remove);
        delete element_to_remove;
    }
}