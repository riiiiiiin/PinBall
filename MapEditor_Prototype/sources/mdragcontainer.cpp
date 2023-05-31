#include "headers/mdragcontainer.h"

MDragContainer::MDragContainer(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 960, 540);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    _big_back = new QLabel(this);
    _big_back->setText("");
    _big_back->setGeometry(650, 40, 260, 380);
    _big_back->setAutoFillBackground(true);
    _big_back->setFixedSize(260, 380);
    _big_back->setStyleSheet("background-color:rgba(255,255,255,128);border-radius:15px;border: 1px solid silver;");

    _small_backs.resize(6);
    for (int i = 0; i < 6; ++i)
    {
        _small_backs[i] = new QLabel(this);
        _small_backs[i]->setFixedSize(110, 110);
        // _small_backs[i]->setContentsMargins(10,10,10,10);
        _small_backs[i]->setText("");
        _small_backs[i]->setStyleSheet("background-color:rgba(255,255,255,154);border-radius: 10px;border: 1px solid royalblue;");
        _small_backs[i]->setAutoFillBackground(true);
    }

    _small_backs[0]->setGeometry(670-5, 60-5, 110, 110);
    _small_backs[1]->setGeometry(670-5, 180-5, 110, 110);
    _small_backs[2]->setGeometry(790-5, 60-5, 110, 110);
    _small_backs[3]->setGeometry(790-5, 180-5, 110, 110);
    _small_backs[4]->setGeometry(670-5,300-5,110,110);
    _small_backs[5]->setGeometry(790-5,300-5,110,110);

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

    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, this);
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, this);
    _dragAward_home = new MDragAward(award, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_award, this);
    _dragCirWall_home = new MDragCirWall(cirwall, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_cirWall, this);

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

    delete _big_back;
    for (auto ptr : _small_backs)
    {
        delete ptr;
    }
}

void MDragContainer::create_new_kidney()
{
    _draggable_buffer = _dragKidney_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragKidney_home = nullptr;
    _dragKidney_home = new MDragKidney(kidney, _static_pic, _dragged_valid, _dragged_invalid, _location_kidney, this);
    connect(_dragKidney_home, &MDraggable::be_moved, this, &MDragContainer::create_new_kidney);
    _draggable_buffer->raise();
}

void MDragContainer::create_new_drum()
{
    _draggable_buffer = _dragDrum_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragDrum_home = nullptr;
    _dragDrum_home = new MDragDrum(drum, _static_pic_2, _dragged_valid_2, _dragged_invalid_2, _location_drum, this);
    connect(_dragDrum_home, &MDraggable::be_moved, this, &MDragContainer::create_new_drum);
    _draggable_buffer->raise();
}

void MDragContainer::create_new_award()
{
    _draggable_buffer = _dragAward_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_award);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragAward_home = nullptr;
    _dragAward_home = new MDragAward(award, _static_pic_3, _dragged_valid_3, _dragged_invalid_3, _location_award, this);
    connect(_dragAward_home, &MDraggable::be_moved, this, &MDragContainer::create_new_award);
    _draggable_buffer->raise();
}

void MDragContainer::create_new_cirWall()
{
    _draggable_buffer = _dragCirWall_home;
    disconnect(_draggable_buffer, &MDraggable::be_moved, this, &MDragContainer::create_new_cirWall);
    connect(_draggable_buffer, &MDraggable::be_released_invalidly, this, &MDragContainer::trash_old);
    connect(_draggable_buffer, &MDraggable::be_released_validly, this, &MDragContainer::push_old);
    _dragCirWall_home = nullptr;
    _dragCirWall_home = new MDragCirWall(cirwall, _static_pic_4, _dragged_valid_4, _dragged_invalid_4, _location_cirWall, this);
    connect(_dragCirWall_home, &MDraggable::be_moved, this, &MDragContainer::create_new_cirWall);
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
        delete element_to_remove;
    }
}
