#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QVector>
#include "object.h"


class map : public QObject
{
    Q_OBJECT

public:
    map(QObject *parent=nullptr);
    ~map();
    int score;//游戏中分数
    int n;//vector的size

public slots:
    void onestep();
    void oneeffect();

signals:
    void dead();
    void scorechange();

private:
    double wup,wdo;//上行下行角速度
    double theleft,theright;//左右flipper的theta
    QVector<object*> cob;
    double t;
    ball* pb;
    object* pa;
};

#endif // MAP_H
