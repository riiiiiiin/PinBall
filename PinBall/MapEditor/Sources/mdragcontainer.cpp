#include "MapEditor/Headers/mdragcontainer.h"

MDragContainer::MDragContainer(int& theme_index,QVector<ThemePack*>& themes,QWidget *parent)
 : QObject(parent), _parent(parent),_theme_index(theme_index),_theme_packs(themes)
{
    // open pixmap
    _home_pic = _theme_packs[_theme_index]->themePics()[lKidney_home];
    _static_pic = _theme_packs[_theme_index]->themePics()[lKidney_placed];
    _dragged_valid = _theme_packs[_theme_index]->themePics()[lKidney_valid];
    _dragged_invalid = _theme_packs[_theme_index]->themePics()[lKidney_invalid];
    _home_pic_2 = _theme_packs[_theme_index]->themePics()[rKidney_home];
    _static_pic_2 = _theme_packs[_theme_index]->themePics()[rKidney_placed];
    _dragged_valid_2 = _theme_packs[_theme_index]->themePics()[rKidney_valid];
    _dragged_invalid_2 = _theme_packs[_theme_index]->themePics()[rKidney_invalid];
    _home_pic_3 = _theme_packs[_theme_index]->themePics()[Drum_home];
    _static_pic_3 = _theme_packs[_theme_index]->themePics()[Drum_placed];
    _dragged_valid_3 = _theme_packs[_theme_index]->themePics()[Drum_valid];
    _dragged_invalid_3 = _theme_packs[_theme_index]->themePics()[Drum_invalid];
    _home_pic_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_home];
    _static_pic_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_placed];
    _dragged_valid_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_valid];
    _dragged_invalid_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_invalid];

    _scratch_pic = new QPixmap(":/mapeditor/backgrounds/scratch.png");
    _scratch_shadow = new MDraggableShadow(_scratch_pic);
    _scratch_shadow->setPos(0,0);

    _scene = new QGraphicsScene();
    _scene->setSceneRect(0, 0, 960, 540);
    _scene->addItem(_scratch_shadow);

    _dragLKidney_home = new MDragLKidney(LKidney, _home_pic,_static_pic, _dragged_valid, _dragged_invalid, _location_lKidney, _parent);
    _dragRKidney_home = new MDragRKidney(RKidney,_home_pic_2, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_rKidney, _parent);
    _dragDrum_home = new MDragDrum(Drum, _home_pic_3,_static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_drum, _parent);
    _dragBonusPoint_home = new MDragBonusPoint(BonusPoint, _home_pic_4,_static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_bonusPoint, _parent);
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
}

QVector<EncodedMapElement> MDragContainer::encodeMap(){
    QVector<EncodedMapElement> _encoded_map;
    for(auto ptr:_map_elements){
        _encoded_map.push_back(EncodedMapElement{ptr->type(),(double)ptr->locatingPoint().x(),(double)ptr->locatingPoint().y()});
    } 
    return _encoded_map;
}

void MDragContainer::decodeMap(QVector<EncodedMapElement> encoded_map){
    MDraggable* temp_ele;
    for(auto ele:encoded_map){
        temp_ele = nullptr;
        switch(ele.e_element_type){
            case enumMapElements::LKidney:{
                //offset to be determined
                temp_ele = new MDragLKidney(LKidney,_home_pic, _static_pic, _dragged_valid, _dragged_invalid, QPoint(int(ele.m_x),(int)(ele.m_y)), _parent);
                _map_elements.push_back(temp_ele);
                _scene->addItem(temp_ele->shadow());
                connect(temp_ele, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
                break;
            }
            case enumMapElements::RKidney:{
                //offset to be determined
                temp_ele = new MDragRKidney(RKidney, _home_pic_2,_static_pic_2, _dragged_valid_2, _dragged_invalid_2, QPoint(int(ele.m_x),(int)(ele.m_y)), _parent);
                _map_elements.push_back(temp_ele);
                _scene->addItem(temp_ele->shadow());
                connect(temp_ele, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
                break;
            }
            case enumMapElements::Drum:{
                //offset to be determined
                temp_ele = new MDragDrum(Drum,  _home_pic_3,_static_pic_3, _dragged_valid_3, _dragged_invalid_3, QPoint(int(ele.m_x),(int)(ele.m_y)), _parent);
                _map_elements.push_back(temp_ele);
                _scene->addItem(temp_ele->shadow());
                connect(temp_ele, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
                break;
            }
            case enumMapElements::BonusPoint:{
                //offset to be determined
                temp_ele = new MDragBonusPoint(BonusPoint,_home_pic_4, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, QPoint(int(ele.m_x),(int)(ele.m_y)), _parent);
                _map_elements.push_back(temp_ele);
                _scene->addItem(temp_ele->shadow());
                connect(temp_ele, &MDraggable::be_removed, this, &MDragContainer::handle_remove_element);
                break;
            }
        }
    }
}

void MDragContainer::clear(){
    if (_draggable_buffer != nullptr)
    {
        delete _draggable_buffer;
    }
    auto items = _scene->items();
    for (QGraphicsItem* item : items) {
        _scene->removeItem(item);
    }
    for (auto ptr : _map_elements)
    {
        delete ptr;
    }
    _map_elements.clear();

    _scene->addItem(_scratch_shadow);
    _scene->addItem(_dragLKidney_home->shadow());
    _scene->addItem(_dragRKidney_home->shadow());
    _scene->addItem(_dragDrum_home->shadow());
    _scene->addItem(_dragBonusPoint_home->shadow());
}

void MDragContainer::create_new_lKidney()
{
    _draggable_buffer = _dragLKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_lKidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragLKidney_home = nullptr;
    _dragLKidney_home = new MDragLKidney(LKidney,_home_pic, _static_pic, _dragged_valid, _dragged_invalid, _location_lKidney, _parent);
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
    _dragRKidney_home = new MDragRKidney(RKidney,_home_pic_2, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_rKidney, _parent);
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
    _dragDrum_home = new MDragDrum(Drum,  _home_pic_3,_static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_drum, _parent);
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
    _dragBonusPoint_home = new MDragBonusPoint(BonusPoint,  _home_pic_4,_static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_bonusPoint, _parent);
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

void MDragContainer::updateTheme(){
    qDebug()<<"update Theme";
    _home_pic = _theme_packs[_theme_index]->themePics()[lKidney_home];
    _static_pic = _theme_packs[_theme_index]->themePics()[lKidney_placed];
    _dragged_valid = _theme_packs[_theme_index]->themePics()[lKidney_valid];
    _dragged_invalid = _theme_packs[_theme_index]->themePics()[lKidney_invalid];
    _home_pic_2 = _theme_packs[_theme_index]->themePics()[rKidney_home];
    _static_pic_2 = _theme_packs[_theme_index]->themePics()[rKidney_placed];
    _dragged_valid_2 = _theme_packs[_theme_index]->themePics()[rKidney_valid];
    _dragged_invalid_2 = _theme_packs[_theme_index]->themePics()[rKidney_invalid];
    _home_pic_3 = _theme_packs[_theme_index]->themePics()[Drum_home];
    _static_pic_3 = _theme_packs[_theme_index]->themePics()[Drum_placed];
    _dragged_valid_3 = _theme_packs[_theme_index]->themePics()[Drum_valid];
    _dragged_invalid_3 = _theme_packs[_theme_index]->themePics()[Drum_invalid];
    _home_pic_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_home];
    _static_pic_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_placed];
    _dragged_valid_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_valid];
    _dragged_invalid_4 = _theme_packs[_theme_index]->themePics()[Bonus_Point_invalid];

    _dragLKidney_home->updatePics(_home_pic,_static_pic,_dragged_valid,_dragged_invalid);
    _dragRKidney_home->updatePics(_home_pic_2,_static_pic_2,_dragged_valid_2,_dragged_invalid_2);
    _dragDrum_home->updatePics(_home_pic_3,_static_pic_3,_dragged_valid_3,_dragged_invalid_3);
    _dragBonusPoint_home->updatePics(_home_pic_4,_static_pic_4,_dragged_valid_4,_dragged_invalid_4);

    for(auto ptr:_map_elements){
        switch(ptr->type()){
            case LKidney:{
                ptr->updatePics(_home_pic,_static_pic,_dragged_valid,_dragged_invalid);
                break;
            }
            case RKidney:{
                ptr->updatePics(_home_pic_2,_static_pic_2,_dragged_valid_2,_dragged_invalid_2);
                break;
            }
            case Drum:{
                ptr->updatePics(_home_pic_3,_static_pic_3,_dragged_valid_3,_dragged_invalid_3);
                break;
            }
            case BonusPoint:{
                ptr->updatePics(_home_pic_4,_static_pic_4,_dragged_valid_4,_dragged_invalid_4);
                break;
            }
        }
    }
}
