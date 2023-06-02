#include "headers/mdragcontainer.h"

MDragContainer::MDragContainer(QWidget *parent) : QObject(parent), _parent(parent)
{
    // open pixmap
    _static_pic = new QPixmap(":/new/prefix2/static.png");
    _dragged_valid = new QPixmap(":/new/prefix2/dragged_valid.png");
    _dragged_invalid = new QPixmap(":/new/prefix2/dragged_invalid.png");
    _static_pic_2 = new QPixmap(":/new/prefix2/static_2.png");
    _dragged_valid_2 = new QPixmap(":/new/prefix2/dragged_valid_2.png");
    _dragged_invalid_2 = new QPixmap(":/new/prefix2/dragged_invalid_2.png");
    _static_pic_3 = new QPixmap(":/new/prefix2/static_3.png");
    _dragged_valid_3 = new QPixmap(":/new/prefix2/dragged_valid_3.png");
    _dragged_invalid_3 = new QPixmap(":/new/prefix2/dragged_invalid_3.png");
    _static_pic_4 = new QPixmap(":/new/prefix2/static_4.png");
    _dragged_valid_4 = new QPixmap(":/new/prefix2/dragged_valid_4.png");
    _dragged_invalid_4 = new QPixmap(":/new/prefix2/dragged_invalid_4.png");

    _scene = new QGraphicsScene();
    _scene->setSceneRect(0, 0, 960, 540);

    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, _parent);
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, _parent);
    _dragAward_home = new MDragAward(award, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_award, _parent);
    _dragCirWall_home = new MDragCirWall(cirwall, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_cirWall, _parent);
    _scene->addItem(_dragKidney_home->shadow());
    _scene->addItem(_dragDrum_home->shadow());
    _scene->addItem(_dragAward_home->shadow());
    _scene->addItem(_dragCirWall_home->shadow());

    _draggable_buffer = nullptr;

    connect(_dragKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_dragAward_home, &MDraggable::be_moved, this, &MDragContainer::create_new_award);
    connect(_dragCirWall_home, &MDraggable::be_moved, this, &MDragContainer::create_new_cirWall);
    _elements.clear();
}

MDragContainer::~MDragContainer()
{
    disconnect(this);
    delete _dragKidney_home;
    delete _dragDrum_home;
    delete _dragAward_home;
    delete _dragCirWall_home;
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    auto items = _scene->items();
    for (QGraphicsItem* item : items) {
        _scene->removeItem(item);
    }
    delete _scene;
    for (auto ptr : _elements)
    {
        delete ptr;
    }
    _elements.clear();
    delete _static_pic;
    delete _dragged_valid;
    delete _dragged_invalid;
    delete _static_pic_2;
    delete _dragged_valid_2;
    delete _dragged_invalid_2;
    delete _static_pic_3;
    delete _dragged_valid_3;
    delete _dragged_invalid_3;
    delete _static_pic_4;
    delete _dragged_valid_4;
    delete _dragged_invalid_4;
    
}

void MDragContainer::create_new_kidney()
{
    _draggable_buffer = _dragKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragKidney_home = nullptr;
    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, _parent);
    connect(_dragKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    _draggable_buffer->raise();
    _scene->addItem(_dragKidney_home->shadow());
}

void MDragContainer::create_new_drum()
{
    _draggable_buffer = _dragDrum_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragDrum_home = nullptr;
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, _parent);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    _draggable_buffer->raise();
    _scene->addItem(_dragDrum_home->shadow());
}

void MDragContainer::create_new_award()
{
    _draggable_buffer = _dragAward_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_award);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragAward_home = nullptr;
    _dragAward_home = new MDragAward(award, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_award, _parent);
    connect(_dragAward_home, &MDraggable::be_moved, this, &MDragContainer::create_new_award);
    _draggable_buffer->raise();
    _scene->addItem(_dragAward_home->shadow());
}

void MDragContainer::create_new_cirWall()
{
    _draggable_buffer = _dragCirWall_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_cirWall);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragCirWall_home = nullptr;
    _dragCirWall_home = new MDragCirWall(cirwall, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_cirWall, _parent);
    connect(_dragCirWall_home, &MDraggable::be_moved, this, &MDragContainer::create_new_cirWall);
    _draggable_buffer->raise();
    _scene->addItem(_dragCirWall_home->shadow());
}

void MDragContainer::trash_old()
{
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    _scene->removeItem(_draggable_buffer->shadow());
    _draggable_buffer = nullptr;
}

void MDragContainer::push_old()
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
        _scene->removeItem(element_to_remove->shadow());
        delete element_to_remove;
    }
}
