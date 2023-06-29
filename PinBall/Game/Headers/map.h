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
#include <QGraphicsDropShadowEffect>

#include <QTime>
#include <QRandomGenerator>
#include <QDebug>

#include <cmath>

#include "FrameWork/Headers/encodedmap.h"
#include "Game/Headers/object.h"

class map : public QObject
{
    Q_OBJECT

public:
    map(QWidget *parent=nullptr);
    ~map();
    void rebuild_map();
    void redraw_map();
    int score=0;//游戏中分数
    int highest=0;

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
    double gball=200;
    double t=0.002;

    QWidget *pparent;

    QList<object*> static_elements;
    QList<object*> dynamic_elements;
    QList<object*> dynamic_elements_default;
    QList<object*> map_eles;

    QList<EncodedMapElement> encoded_dynamic;
    QList<EncodedMapElement> encoded_dynamic_default;
    QList<EncodedMapElement>& encoded_elements;

    QList<QLabel*> map_pics;
    QGraphicsDropShadowEffect* _shadow;

    void updateball();
    void updateflipper();

    const double pi = acos(-1);
};

#endif // MAP_H