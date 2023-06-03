#include "object.h"
#include <math.h>


object::object():coushu(0),ef(false){}
void object::jump(double t){}
bool object::bounce(ball* a){return true;}
void object::effect(){}
double& object::getvx(){return coushu;}
double& object::getvy(){return coushu;}
double& object::getx(){return coushu;}
double& object::gety(){return coushu;}
double& object::getr(){return coushu;}
bool object::isalive(){return true;}
void object::pset(double theta,bool left){}


obcircle::obcircle(double _x,double _y,double _r,bool _full,double _x1,double _x2,double _y1,double _y2):
    x(_x),y(_y),r(_r),full(_full),x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
void obcircle::jump(double t){}
bool obcircle::bounce(ball* a){return true;}
void obcircle::effect(){}
double& obcircle::getvx(){return coushu;}
double& obcircle::getvy(){return coushu;}
double& obcircle::getx(){return coushu;}
double& obcircle::gety(){return coushu;}
double& obcircle::getr(){return coushu;}
bool obcircle::isalive(){return coushu;}
bool obcircle::judge(ball* a){
    double xx=a->getx();
    double yy=a->gety();
    double rr=a->getr();
    if(full){
        if(sqrt(x-xx)*(x-xx)+sqrt(y-yy)*(y-yy)<=(r+rr)) return true;
    }
    else{
        if(sqrt(x-xx)*(x-xx)+sqrt(y-yy)*(y-yy)<=(r+rr)&&sqrt(x-xx)*(x-xx)+sqrt(y-yy)*(y-yy)>=r-rr){
            if(((x1-x)*(y-yy)-(y1-y)*(x-xx))*((x2-x)*(y-yy)-(y2-y)*(x-xx))<0){
                return true;
            }
        }
    }
    return false;
}
void obcircle::pset(double theta,bool left){}

obline::obline(double _x1, double _x2, double _y1, double _y2):x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
bool obline::judge(ball* a){
    double x=a->getx(),y=a->gety(),min,max;
    min=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    max=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
    if(min>max) {
        double tmp=max;
        max=min;
        min=tmp;
    }
    double l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    double cos=min*min-max*max+l*l;
    if(cos<0) return false;
    if(sqrt(1-cos*cos)*min<a->getr()) return true;
    else return false;
}

bool obline::bounce(ball* a){return true;}
void obline::effect(){}
void obline::pset(double theta,bool left){}

ball::ball(double _x, double _y, double _r, double _vx, double _vy, double _g):obcircle(_x,_y,_r, true),vx(_vx),vy(_vy),g(_g),t(0.05),alive(1){}
bool ball::bounce(ball* a){}
void ball::effect(){}
double& ball::getvx(){return vx;}
double& ball::getvy(){return vy;}
double& ball::getx(){return x;}
double& ball::gety(){return y;}
double& ball::getr(){return r;}
void ball::jump(double t){
    x=x+vx*t;
    y=y+vy*t+0.5*g*t*t;
    vy=vy-g*t;
    if(y>540) alive=0;
}
bool ball::isalive(){
    return alive;
}

stwall::stwall(double _x1,double _x2,double _y1,double _y2,double _coef):obline(_x1,_x2,_y1,_y2),coef(_coef){object::bonus=0;}
bool stwall::bounce(ball* a){
    if(obline::judge(a)){
        double ax=a->getvx(),ay=a->getvy();
        double A=y2-y1;
        double B=x1-x2;
        double C=A*A+B*B;
        double vx=-(ax-(coef+1)*A*(A*ax+B*ay)/C);
        double vy=-(ay-(coef+1)*B*(A*ax+B*ay)/C);

        a->getvx()=vx;
        a->getvy()=vy;
        this->effect();
        return true;
    }
    return false;
}
void stwall::effect(){}
void stwall::pset(double theta,bool left){

}

cirwall::cirwall(double _x,double _y,double _r,double _x1,double _x2,double _y1,double _y2,double _coef):obcircle(_x,_y,_r,0,_x1,_x2,_y1,_y2),coef(_coef){object::bonus=0;}
cirwall::cirwall(double _x,double _y,double _r,double _coef):obcircle(_x,_y,_r,1),coef(_coef){object::bonus=0;}
void cirwall::effect(){}
bool cirwall::bounce(ball* a){
    if(obcircle::judge(a)){
        double ax=a->getvx(),ay=a->getvy();
        double A=y-a->gety(),B=a->getx()-x,C=A*A+B*B;
        double vx=(ax-(coef+1)*A*(A*ax+B*ay)/C),vy=(ay-(coef+1)*B*(A*ax+B*ay)/C);

        a->getvx()=vx;
        a->getvy()=vy;
        this->effect();
        return true;
    }
    return false;
}
void cirwall::pset(double theta,bool left){

}


drum::drum(double _x, double _y, double _r, double _coef):obcircle(_x,_y,_r, true),coef(_coef){object::bonus=99;}
void drum::effect(){}
bool drum::bounce(ball* a){
    if(obcircle::judge(a)){
        double ax=a->getvx(),ay=a->getvy();
        double A=y-a->gety(),B=a->getx()-x,C=A*A+B*B;
        double vx=coef*(ax-2*A*(A*ax+B*ay)/C),vy=coef*(ay-2*B*(A*ax+B*ay)/C);
        a->getvx()=vx;
        a->getvy()=vy;
        this->effect();
        return true;
    }
    return false;
}

kidney::kidney(double _x1,double _x2,double _y1,double _y2,double _coef):obline(_x1,_x2,_y1,_y2),coef(_coef){object::bonus=99;}
bool kidney::bounce(ball* a){
    if(obline::judge(a)){
        double ax=a->getvx(),ay=a->getvy();
        double A=y2-y1;
        double B=x1-x2;
        double C=A*A+B*B;
        double vx=-(ax-(coef+1)*A*(A*ax+B*ay)/C);
        double vy=-(ay-(coef+1)*B*(A*ax+B*ay)/C);

        a->getvx()=vx;
        a->getvy()=vy;
        this->effect();
        return true;
    }
    return false;
}
void kidney::effect(){

}

award::award(double _x, double _y,double _r):obcircle(_x,_y,_r, true){object::bonus=1999;}

void award::effect(){

}

bool award::bounce(ball* a){
    if(obcircle::judge(a)) {
        this->effect();
        return true;
    }
    return false;
}



//按下按键，flipper,向上匀速（很快）旋转，按住按键flipper保持位置；松掉按键，flipper匀速（较慢）旋转回到初始位置
//flipper::flipper():{}
