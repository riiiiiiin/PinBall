#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QVector>
#include "object.h"
#include <QTimer>
#include <QList>
#include "Headers/encodedmap.h"
#include <QLabel>
#include <QWidget>
#include <QPixmap>

class map : public QObject
{
    Q_OBJECT

public:
    map(QWidget *parent=nullptr);
    ~map();
    double gball;
    int score;//游戏中分数
    int highest;
    int n;//vector的size
    double t;
    void clearmap();
    void rebuildmap();
    void rebuildmap(QList<EncodedMapElement> newmap,int);
//    void drawmap();
    QWidget *pparent;
    QVector<QLabel*> which,changeable;
    QLabel *plabel;
    QPixmap pix;
    void updateball();
    void drawstatic();
    void drawscore();
    void clearstatic();
    void cleardynamic();
    void updateflipper();


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
    QVector<object*> cob;
    ball* pb;
    object* pa;
};

#endif // MAP_H
