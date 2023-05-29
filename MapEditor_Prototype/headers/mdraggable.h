#ifndef MDRAGGABLE_H
#define MDRAGGABLE_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QApplication>
#include <QObject>

enum e_MDraggables{
    kidney = 1,
    drum = 2
};

class MDraggable : public QWidget
{
    Q_OBJECT
private:
    
    QPoint _dragStartPos;
    QPoint _dragLabelPos;
    bool _banned_to_drag;
    bool _is_set_properly;
protected:
    QLabel *_label;
    e_MDraggables _type;
    QPixmap* _static_pic;
    QPixmap* _dragged_valid;
    QPixmap* _dragged_invalid;
public:
    MDraggable(QPoint location_source,QWidget *parent = nullptr);
    virtual ~MDraggable();

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