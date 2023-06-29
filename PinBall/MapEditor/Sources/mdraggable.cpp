#include "MapEditor/Headers/mdraggable.h"

MDraggable::MDraggable(QPixmap* static_pic,QPoint location_source, QWidget *parent,bool is_set_properly)
    : _static_pic(static_pic),QWidget(parent),_is_set_properly(is_set_properly)
{
    _label = new MAdaptableLabel(this);
    resize(100,100);
    setMouseTracking(true);
    _label->resize(100,100);
    move(location_source);
    _label->setText("");
    setVisible(true);

    _shadow = new MDraggableShadow(static_pic);
    _shadow->setPos(location_source);
    raise();
}

MDraggable::~MDraggable()
{
    disconnect(this);
    delete _label;
    delete _shadow;
}

MDraggableShadow * MDraggable::shadow(){
    return _shadow;
}

e_MapElements MDraggable::type()const{
    return _type;
}

bool MDraggable::IsPosValid()
{
    // note:relative postion to parent widget
    int cur_x = pos().x();
    // note:relative postion to parent widget
    int cur_y = pos().y();
    bool pos_valid = ((cur_x >= 50 && cur_x <= 550 && cur_y >= 40 && cur_y <= 500)and not(cur_x>150 and cur_x < 210 and cur_y>60 and cur_y<220));
    if(pos_valid && _shadow->collidingItems().empty()){
        return true;
    }
    return false;
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
        _shadow->setPos(_dragLabelPos+delta);
        resize(_dragged_valid->size());
        _label->resize(_dragged_valid->size());
        if (IsPosValid())
        {
            _label->setPixMap(*_dragged_valid);
        }
        else
        {
            _label->setPixMap(*_dragged_invalid);
        }
    }
    else if(event->buttons() & Qt::LeftButton)
    {
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->pos(), event->globalPos(),
                                 Qt::LeftButton, Qt::NoButton, event->modifiers());
        QApplication::sendEvent(this, &releaseEvent);
    }
}

void MDraggable::mouseReleaseEvent(QMouseEvent *event)
{
    _label->resize(_static_pic->size());
    _label->setPixMap(*_static_pic);
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
