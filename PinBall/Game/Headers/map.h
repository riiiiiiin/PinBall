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
#include "FrameWork/Headers/themepack.h"

class map : public QObject
{
    Q_OBJECT

public:
    map(int&,QVector<ThemePack*>&,QWidget *parent=nullptr);
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
    void setmap(QVector<EncodedMapElement> newmap,int);//transform

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

    QVector<object*> static_elements;
    QVector<object*> dynamic_elements;
    QVector<object*> dynamic_elements_default;
    QVector<object*> map_eles;

    QVector<EncodedMapElement> encoded_dynamic;
    QVector<EncodedMapElement> encoded_dynamic_default;
    QVector<EncodedMapElement>& encoded_elements;

    QVector<QLabel*> map_pic_labels;
    QGraphicsDropShadowEffect* _shadow;

    int& _theme_index;
    QVector<ThemePack*>& _theme_packs;

    void updateball();
    void updateflipper();

    const double pi = acos(-1);
};

#endif // MAP_H
