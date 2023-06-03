#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QVector>
#include "object.h"
#include "ui_mainwindow.h"

class map : public QObject
{
    Q_OBJECT

public:
    map(Ui::MainWindow * mainwindow,QObject *parent=nullptr);
    ~map();
    int score,highest,n;

public slots:

    void onestep();
    void oneeffect();

private:
    Ui::MainWindow* m_mainwindow;
    double wup,wdo;//上行下行角速度
    double theleft,theright;//左右flipper的theta
    QVector<object*> cob;
    double t;
    ball* pb;
    object* pa;
};

#endif // MAP_H
