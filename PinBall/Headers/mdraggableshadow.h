#ifndef MDRAGGABLESHADOW_H
#define MDRAGGABLESHADOW_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

class MDraggableShadow : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
private:
public:
    MDraggableShadow(QPixmap* pixmap,QGraphicsItem* parent=nullptr);
    ~MDraggableShadow();
signals:
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};


#endif