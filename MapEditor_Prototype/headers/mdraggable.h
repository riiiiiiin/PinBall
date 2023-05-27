#ifndef MDRAGGABLE_H
#define MDRAGGABLE_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QApplication>
#include <QObject>

class MDraggable : public QWidget
{
    Q_OBJECT
private:
    QLabel *_label;
    QPoint _dragStartPos;
    QPoint _dragLabelPos;
    QPixmap* _static_pic;
    QPixmap* _dragged_valid;
    QPixmap* _dragged_invalid;
    bool _banned_to_drag;
    bool _is_set_properly;
public:
    MDraggable(QPoint location_source,QWidget *parent = nullptr);
    ~MDraggable();

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