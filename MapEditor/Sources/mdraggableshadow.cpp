#include "MapEditor/Headers/mdraggableshadow.h"

MDraggableShadow::MDraggableShadow(QPixmap* pixmap,QGraphicsItem *parent)
    : QGraphicsPixmapItem(*pixmap, parent)
{
    setShapeMode(QGraphicsPixmapItem::MaskShape);
}

MDraggableShadow::~MDraggableShadow(){}

void MDraggableShadow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(), pixmap());
}