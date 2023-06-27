#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QWidget>

#include <QTimer>

#include <QVector>
#include <QList>

#include <QLabel>
#include <QPixmap>
#include <QPainter>

#include <QTime>
#include <QRandomGenerator>
#include <QDebug>

#include <cmath>

#include "Headers/encodedmap.h"
#include "object.h"

class map : public QObject
{
    Q_OBJECT

public:
    map(QWidget *parent=nullptr);
    ~map();
    void rebuild_map();
    void redraw_map();
    int score;//游戏中分数
    int highest;

public slots:
    void onestep();
    void oneeffect();
    void leftup();
    void leftdown();
    void rightup();
    void rightdown();
    void setmap(QList<EncodedMapElement> newmap,int);//transform

signals:
    void dead();//
    void scorechange(int,int);

private:
    double wup,wdo;//上行下行角速度
    bool upleft,upright,moveupleft,moveupright;
    double theleft,theright;//左右flipper的theta
    double leftx,rightx,y;

    ball* pb;
    double gball;
    double t;

    QWidget *pparent;

    QList<object*> static_elements;
    QList<object*> dynamic_elements;
    QList<object*> dynamic_elements_default;
    QList<object*> map_eles;

    QList<EncodedMapElement> encoded_dynamic;
    QList<EncodedMapElement> encoded_dynamic_default;
    QList<EncodedMapElement>& encoded_elements;

    QList<QLabel*> map_pics;

    void updateball();
    void updateflipper();

    const double pi = acos(-1);
};

#endif // MAP_H
