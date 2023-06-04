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

    _dragLKidney_home = new MDragLKidney(LKidney, _static_pic, _dragged_valid, _dragged_invalid, _location_lKidney, _parent);
    _dragRKidney_home = new MDragRKidney(RKidney, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_rKidney, _parent);
    _dragDrum_home = new MDragDrum(Drum, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_drum, _parent);
    _dragBonusPoint_home = new MDragBonusPoint(BonusPoint, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_bonusPoint, _parent);
    _scene->addItem(_dragLKidney_home->shadow());
    _scene->addItem(_dragRKidney_home->shadow());
    _scene->addItem(_dragDrum_home->shadow());
    _scene->addItem(_dragBonusPoint_home->shadow());

    _draggable_buffer = nullptr;

    connect(_dragLKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_lKidney);
    connect(_dragRKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_rKidney);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_dragBonusPoint_home, &MDraggable::be_moved, this, &MDragContainer::create_new_bonusPoint);
    _map_elements.clear();
}

MDragContainer::~MDragContainer()
{
    disconnect(this);
    delete _dragLKidney_home;
    delete _dragRKidney_home;
    delete _dragDrum_home;
    delete _dragBonusPoint_home;
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    auto items = _scene->items();
    for (QGraphicsItem* item : items) {
        _scene->removeItem(item);
    }
    delete _scene;
    for (auto ptr : _map_elements)
    {
        delete ptr;
    }
    _map_elements.clear();
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

QList<EncodedMapElement> MDragContainer::encodeMap(){
    QList<EncodedMapElement> _encoded_elements;
    for(auto ptr:_map_elements){
        _encoded_elements.push_back({})
    } 



}

void MDragContainer::create_new_lKidney()
{
    _draggable_buffer = _dragLKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_lKidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragLKidney_home = nullptr;
    _dragLKidney_home = new MDragLKidney(LKidney, _static_pic, _dragged_valid, _dragged_invalid, _location_lKidney, _parent);
    connect(_dragLKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_lKidney);
    _draggable_buffer->raise();
    _scene->addItem(_dragLKidney_home->shadow());
}

void MDragContainer::create_new_rKidney()
{
    _draggable_buffer = _dragRKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_rKidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragRKidney_home = nullptr;
    _dragRKidney_home = new MDragRKidney(RKidney, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_rKidney, _parent);
    connect(_dragRKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_rKidney);
    _draggable_buffer->raise();
    _scene->addItem(_dragRKidney_home->shadow());
}

void MDragContainer::create_new_drum()
{
    _draggable_buffer = _dragDrum_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragDrum_home = nullptr;
    _dragDrum_home = new MDragDrum(Drum, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_drum, _parent);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    _draggable_buffer->raise();
    _scene->addItem(_dragDrum_home->shadow());
}

void MDragContainer::create_new_bonusPoint()
{
    _draggable_buffer = _dragBonusPoint_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_bonusPoint);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragBonusPoint_home = nullptr;
    _dragBonusPoint_home = new MDragBonusPoint(BonusPoint, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_bonusPoint, _parent);
    connect(_dragBonusPoint_home, &MDraggable::be_moved, this, &MDragContainer::create_new_bonusPoint);
    _draggable_buffer->raise();
    _scene->addItem(_dragBonusPoint_home->shadow());
}

void MDragContainer::trash_old()
{
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    if(_scene->items().contains(_draggable_buffer->shadow())){
        _scene->removeItem(_draggable_buffer->shadow());
    }
    
    _draggable_buffer = nullptr;
}

void MDragContainer::push_old()
{
    if (_draggable_buffer != nullptr)
    {
        disconnect(_draggable_buffer, nullptr, this, nullptr);
        if (not _map_elements.contains(_draggable_buffer))
        {
            _map_elements.push_back(_draggable_buffer);
            connect(_draggable_buffer, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
        }
        _draggable_buffer = nullptr;
    }
}

void MDragContainer::handle_remove_element(MDraggable *element_to_remove)
{
    if (element_to_remove != nullptr)
    {
        _map_elements.removeOne(element_to_remove);
        _scene->removeItem(element_to_remove->shadow());
        delete element_to_remove;
    }
}
