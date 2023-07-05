#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QVector>
#include "object.h"
#include <QTimer>
#include <QList>
//#include "encodedmap.h"
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
class map : public QObject
{
    Q_OBJECT

public:
    map(QWidget *parent=nullptr);
    ~map();
    double gball;//重力加速度
    int score;//游戏中分数
    int highest;//最高分
    bool ifsetmap;
    double t;
    void clearmapstatic();//清除不得分object
    void rebuildstatic();//重建不得分object
    void clearmapdynamic();//清除得分object
    void rebuilddynamic();//重建默认地图得分object
    QWidget *pparent;
    QVector<QLabel*> which,changeable;
    QLabel *plabel;
    QPixmap pix;
    void updateball();
    void drawstatic();//贴图
    void drawscore();//贴图
    void clearstatic();//清图
    void cleardynamic();//清图
    void updateflipper();

public slots:
    void onestep();
    void oneeffect();
    void leftup();
    void leftdown();
    void rightup();
    void rightdown();
    void changeballpic();
//    void setmap(QList<EncodedMapElement> newmap);//transform

signals:
    void dead();
    void scorechange(int,int);//现在的分数，最高分

private:
    QTimer *changeball;
    bool stateball;
    double wup,wdo;//上行下行角速度
    bool upleft,upright,moveupleft,moveupright;
    double theleft,theright;//左右flipper的theta
    double leftx,rightx,y;
    QVector<object*> cob;//不得分的object
    QVector<object*> cobd;//得分的object
    ball* pb;//小球的指针
    object* pa;//用来塞vector
};

#endif // MAP_H
