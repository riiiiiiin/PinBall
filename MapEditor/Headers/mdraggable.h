#ifndef MDRAGGABLE_H
#define MDRAGGABLE_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QApplication>
#include <QObject>

#include "MapEditor/Headers/mdraggableshadow.h"
#include "FrameWork/Headers/encodedmap.h"
#include "MapEditor/Headers/madaptablelabel.h"

class MDraggable : public QWidget
{
    Q_OBJECT
private:
    QPoint _dragStartPos;
    QPoint _dragLabelPos;
    bool _banned_to_drag;
    bool _is_set_properly;
protected:
    MAdaptableLabel *_label;
    enumMapElements _type;
    QPixmap* _home_pic;
    QPixmap* _static_pic;
    QPixmap* _dragged_valid;
    QPixmap* _dragged_invalid;
    MDraggableShadow* _shadow;
public:
    MDraggable(QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid,QPoint location_source,QWidget *parent = nullptr,bool is_set_properly=false);
    virtual ~MDraggable();
    void updatePics(QPixmap* home_pic,QPixmap* static_pic,QPixmap* dragged_valid,QPixmap* dragged_invalid);
    MDraggableShadow * shadow();
    enumMapElements type()const;
    virtual QPoint locatingPoint()const =0;
protected:
    inline bool IsPosValid();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public slots:

signals:
    void be_moved();
    void be_released_invalidly();
    void be_released_validly();
    void be_removed(MDraggable*);
};

#endif