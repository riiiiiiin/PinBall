#ifndef OBJECT_H
#define OBJECT_H

namespace natsume {
class object;
class obline;
class obcircle;
class ball;
class stwall;
class cirwall;
class drum;
class kidney;
}

class object
{
public:
    double coushu;
    object();
    virtual void jump(double t);
    virtual bool bounce(object* a);
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
};

class obline:public object{
protected:
    double x1,x2,y1,y2;
public:
    obline(double _x1,double _x2,double _y1,double _y2);
    bool judge(object* a);
    virtual bool bounce(object* a);
    virtual void effect();
};

class obcircle:public object{
protected:
    double x,y,r;
    bool full;
    double x1,x2,y1,y2;
public:
    obcircle(double _x,double _y,double _r,bool _full,double _x1=0,double _x2=0,double _y1=0,double _y2=0);
    bool judge(object* a);
    virtual void jump(double t);
    virtual bool bounce(object* a);
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
};

class ball:public obcircle
{
private:
    double vx,vy,g,t,alive;
public:
    ball(double _x, double _y, double _r, double _vx, double _vy,double _g);
    virtual void jump(double t);
    virtual bool bounce(object* a);
    virtual void effect();
    virtual double& getvx();
    virtual double& getvy();
    virtual double& getx();
    virtual double& gety();
    virtual double& getr();
    virtual bool isalive();
};

class stwall:public obline{
private:
    double coef;
public:
    stwall(double _x1,double _x2,double _y1,double _y2,double _coef);
    virtual bool bounce(object* a);
    virtual void effect();
};

class cirwall:public obcircle{
private:
    double coef;
public:
    cirwall(double _x,double _y,double _r,double _x1,double _x2,double _y1,double _y2,double _coef);
    virtual bool bounce(object* a);
    virtual void effect();
};

class drum:public obcircle{
private:
    double coef;
public:
    drum(double _x,double _y,double _r,double _coef);
    virtual bool bounce(object* a);
    virtual void effect();
};

class kidney:public obline{
private:
    double coef;
public:
    kidney(double _x1,double _x2,double _y1,double _y2,double _coef);
    bool bounce(object* a);
    void effect();
};
//class flipper{
//private:
//    double
//};

#endif // OBJECT_H
