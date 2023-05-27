#include "headers/mdraggable.h"

MDraggable::MDraggable(QPoint location_source, QWidget *parent)
    : QWidget(parent),_is_set_properly(false)
{
    _static_pic = new QPixmap(":/new/prefix2/static.png");
    _dragged_valid = new QPixmap(":/new/prefix2/dragged_valid.png");
    _dragged_invalid = new QPixmap(":/new/prefix2/dragged_invalid.png");

    _label = new QLabel(this);
    setMouseTracking(true);
    setGeometry(600, 300, 100, 100);
    move(location_source);
    _label->setText("");
    _label->setPixmap(*_static_pic);
    _label->setMask(_static_pic->mask());
    setVisible(true);
}

MDraggable::~MDraggable()
{

    disconnect(this);
    delete _label;
    delete _static_pic;
    delete _dragged_valid;
    delete _dragged_invalid;
}

bool MDraggable::IsPosValid()
{
    // note:relative postion to parent widget
    int cur_x = pos().x();
    // note:relative postion to parent widget
    int cur_y = pos().y();
    return (cur_x >= 50 && cur_x <= 550 && cur_y >= 40 && cur_y <= 500);
}

void MDraggable::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton && (event->modifiers() & Qt::ControlModifier) == 0)
    {
        _dragStartPos = event->globalPosition().toPoint();
        _dragLabelPos = pos();
        _banned_to_drag = false;
    }
    else
    {
        _banned_to_drag = true;
    }
    if(_is_set_properly && (event->modifiers() & Qt::ControlModifier) ){
        emit be_removed(this);
    }
}

void MDraggable::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() == Qt::LeftButton && _banned_to_drag == false && (event->modifiers() & Qt::ControlModifier) == false)
    {
        emit be_moved();
        QPoint delta = event->globalPosition().toPoint() - _dragStartPos;
        move(_dragLabelPos + delta);
        if (IsPosValid())
        {
            _label->setPixmap(*_dragged_valid);
        }
        else
        {
            _label->setPixmap(*_dragged_invalid);
        }
    }
    else
    {
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->pos(), event->globalPos(),
                                 Qt::LeftButton, Qt::NoButton, event->modifiers());
        QApplication::sendEvent(this, &releaseEvent);
    }
}

void MDraggable::mouseReleaseEvent(QMouseEvent *event)
{
    //setGeometry(600, 300, 100, 100);
    _label->setPixmap(*_static_pic);
    Q_UNUSED(event);
    if (IsPosValid())
    {
        _is_set_properly = true;
        emit be_released_validly();
    }
    else
    {
        _is_set_properly = false;
        emit be_released_invalidly();
        emit be_removed(this);
    }
}