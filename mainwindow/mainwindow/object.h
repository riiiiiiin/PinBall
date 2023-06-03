#ifndef OBJECT_H
#define OBJECT_H


#include <QObject>
class ball;
class object : public QObject
{
    Q_OBJECT
public:
    object();
    virtual ~object() {}
    double coushu;//不必在意
    bool ef;//判断是否需要特效
    int bonus=0;//加分
    virtual void jump(double t);
    virtual bool bounce(ball* a);
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
    virtual void pset(double theta,bool left);
};

class obline:public object{
protected:
    double x1,x2,y1,y2;//(x1,y1),(x2,y2)直线两端点
public:
    obline(double _x1,double _x2,double _y1,double _y2);
    bool judge(ball* a);//判断是否碰撞
    virtual bool bounce(ball* a);//虚
    virtual void effect();
    virtual void pset(double theta,bool left);
};

class obcircle:public object{
protected:
    double x,y,r;//(x,y)圆心，r是半径
    bool full;//是否是完整的圆
    double x1,x2,y1,y2;//圆弧的两个端点
public:
    obcircle(double _x,double _y,double _r,bool _full,double _x1=0,double _x2=0,double _y1=0,double _y2=0);
    bool judge(ball* a);//判断是否碰撞
    virtual void jump(double t);//虚
    virtual bool bounce(ball* a);//虚
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
    virtual void pset(double theta,bool left);
};

class ball:public obcircle
{
private:
    double vx,vy,g,t,alive;//t是时间间隔
public:
    ball(double _x, double _y, double _r, double _vx, double _vy,double _g);
    virtual void jump(double t);//计算球的自由落体
    virtual bool bounce(ball* a);//虚
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
};

class stwall:public obline{//直线墙
private:
    double coef;
public:
    stwall(double _x1,double _x2,double _y1,double _y2,double _coef);
    virtual bool bounce(ball* a);
    virtual void effect();
    void pset(double theta,bool left);
};

class cirwall:public obcircle{
private:
    double coef;
public:
    cirwall(double _x,double _y,double _r,double _x1,double _x2,double _y1,double _y2,double _coef);
    cirwall(double _x,double _y,double _r,double _coef);
    virtual bool bounce(ball* a);
    virtual void effect();
    void pset(double theta,bool left);
};

class drum:public obcircle{
private:
    double coef;
public:
    drum(double _x,double _y,double _r,double _coef);
    virtual bool bounce(ball* a);
    virtual void effect();
};

class kidney:public obline{
private:
    double coef;
public:
    kidney(double _x1,double _x2,double _y1,double _y2,double _coef);
    bool bounce(ball* a);
    void effect();
};



class award:public obcircle{
public:
    award(double _x,double _y,double _r);
    void effect();
    bool bounce(ball* a);
};




#endif // OBJECT_H
