#include "object.h"

#include <QDebug>

object::object() : coushu(0), ef(false), noaward(false) {}
void object::jump() {}
bool object::bounce(ball *a) { return true; }
void object::effect() {}
void object::change(double _x1, double _x2, double _y1, double _y2, int _nocoef, bool go) {}

obcircle::obcircle(double _x, double _y, double _r, bool _full, double _x1, double _x2, double _y1, double _y2) : x(_x), y(_y), r(_r), full(_full), x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
void obcircle::jump() {}
bool obcircle::bounce(ball *a) { return true; }
void obcircle::effect() {}
bool obcircle::judge(ball *a)
{
    double xx = a->getx();
    double yy = a->gety();
    double rr = a->getr();
    if (sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy)) <= (r + rr) && sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy)) >= abs(r - rr))
    {
        double vx = a->getvx(), vy = a->getvy();
        double yl = y2 - y1, xl = x2 - x1;

        if (full)
        {
            if (((xx - x) * vx + (yy - y) * vy) > 0)
                return false; // 如果球的法向速度向外，就不进行变换了
            return true;
        }
        else
        {
            double xm = (x1 + x2) / 2 - x, ym = (y1 + y2) / 2 - y, c = (xx - x) * (xx - x) + (yy - y) * (yy - y);
            double xl = x1 - x, yl = y1 - y, L = sqrt(xl * xl + yl * yl);
            double xb = xx - x, yb = yy - y, B = sqrt(xb * xb + yb * yb);
            double cos1 = (xm * xb + ym * yb) / B, cos2 = (xm * xl + ym * yl) / L;
            if (cos1 >= cos2)
            {
                if ((c > r * r && ((xx - x) * vx + (yy - y) * vy) < 0) || (c <= r * r && ((xx - x) * vx + (yy - y) * vy) > 0))
                    return true;
            }
        }
    }
    return false;
    //    else{
    //        if(sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy))<=(r+rr)&&sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy))>=abs(r-rr)){
    //            if(((x1-x)*(y-yy)-(y1-y)*(x-xx))*((x2-x)*(y-yy)-(y2-y)*(x-xx))<0){
    //                return true;
    //            }
    //        }
    //    }
    return false;
}
void obcircle::change(double _x1, double _x2, double _y1, double _y2, int _nocoef, bool go) {}

obline::obline(double _x1, double _x2, double _y1, double _y2) : x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
bool obline::judge(ball *a)
{
    double x = a->getx(), y = a->gety(), min, max;
    min = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    max = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    if (min > max)
    {
        double tmp = max;
        max = min;
        min = tmp;
    }
    double l = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double cos = (min * min - max * max + l * l) / (2 * min * l);
    if (cos < 0)
        return false;
    double vx = a->getvx(), vy = a->getvy();
    double yl = y2 - y1, xl = x2 - x1;
    if (coushu == 0 && (yl * vx - xl * vy) * (yl * (x - x1) - xl * (y - y1)) > 0)
        return false; // 如果球的法向速度向外，就不进行变换了
    if (sqrt(1 - cos * cos) * min < a->getr())
        return true;
    else
        return false;
}
void obline::change(double _x1, double _x2, double _y1, double _y2, int _nocoef, bool go) {}
bool obline::bounce(ball *a) { return true; }
void obline::effect() {}

ball::ball(double _x, double _y, double _r, double _vx, double _vy, double _g)
    : obcircle(_x, _y, _r, true), vx(_vx), vy(_vy), g(_g), t(0.002), alive(1) {}
bool ball::bounce(ball *a) {}
void ball::effect() {}
double &ball::getvx() { return vx; }
double &ball::getvy() { return vy; }
double &ball::getx() { return x; }
double &ball::gety() { return y; }
double &ball::getr() { return r; }
void ball::jump()
{
    x = x + vx * t;
    y = y + vy * t + 0.5 * g * t * t;
    vy = vy + g * t;
    auto cur_speed = sqrt((vx * vx) + (vy * vy));
    if (cur_speed > 450)
    {
        vx /= (cur_speed / 450);
        vy /= (cur_speed / 450);
    }
    else if (cur_speed > 425)
    {
        vx /= ((cur_speed - 425) * 0.75 + 425) / 425;
        vy /= ((cur_speed - 425) * 0.75 + 425) / 425;
    }
    else if (cur_speed > 400)
    {
        vx /= ((cur_speed - 400) * 0.50 + 400) / 400;
        vy /= ((cur_speed - 400) * 0.50 + 400) / 400;
    }
    else if (cur_speed > 350)
    {
        vx /= ((cur_speed - 350) * 0.25 + 350) / 350;
        vy /= ((cur_speed - 350) * 0.25 + 350) / 350;
    }
    // qDebug()<<cur_speed;
    if (y > 540)
        alive = 0;
    if (y < 0 or x > 600 or x < 0)
        qDebug() << "超tm穿模了";
}
bool ball::isalive()
{
    return alive;
}

stwall::stwall(double _x1, double _x2, double _y1, double _y2, double _coef) : obline(_x1, _x2, _y1, _y2), coef(_coef) { object::bonus = 0; }
bool stwall::bounce(ball *a)
{
    if (obline::judge(a))
    {
        double vx = a->getvx(), vy = a->getvy();
        double yl = y2 - y1, xl = x2 - x1;
        double c = yl * yl + xl * xl;
        double c1 = (vx * xl + vy * yl) / c;
        double c2 = -coef * (vy * xl - vx * yl) / c;
        vx = c1 * xl - yl * c2;
        vy = c1 * yl + c2 * xl;

        a->getvx() = vx;
        a->getvy() = vy - coushu * 90;
        this->effect();
        return true;
    }
    return false;
}
void stwall::effect() {}
void stwall::change(double _x1, double _x2, double _y1, double _y2, int _nocoef, bool go)
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
    coef = 1;
    if (_nocoef > 0 && go == true)
        coushu = _nocoef;
    else
        coushu = 0;
}

cirwall::cirwall(double _x, double _y, double _r, double _x1, double _x2, double _y1, double _y2, double _coef) : obcircle(_x, _y, _r, 0, _x1, _x2, _y1, _y2), coef(_coef) { object::bonus = 0; }
cirwall::cirwall(double _x, double _y, double _r, double _coef) : obcircle(_x, _y, _r, 1), coef(_coef) { object::bonus = 0; }
void cirwall::effect() {}
bool cirwall::bounce(ball *a)
{
    if (obcircle::judge(a))
    {
        double vx = a->getvx(), vy = a->getvy();
        double ax = a->getx(), ay = a->gety();
        double yl = x - ax, xl = ay - y;
        double c = yl * yl + xl * xl;
        double c1 = (vx * xl + vy * yl) / c;
        double c2 = -coef * (vy * xl - vx * yl) / c;
        vx = c1 * xl - yl * c2;
        vy = c1 * yl + c2 * xl;

        a->getvx() = vx;
        a->getvy() = vy;
        this->effect();
        return true;
    }
    return false;
}
void cirwall::change(double _x1, double _x2, double _y1, double _y2, int _nocoef, bool go)
{
    x = _x1;
    y = _y1;
}

drum::drum(double _x, double _y, double _r, double _coef) : obcircle(_x, _y, _r, true), coef(_coef) { object::bonus = 99; }
void drum::effect() {}
bool drum::bounce(ball *a)
{
    if (obcircle::judge(a))
    {
        double vx = a->getvx(), vy = a->getvy();
        double ax = a->getx(), ay = a->gety();
        double yl = x - ax, xl = ay - y;
        double c = yl * yl + xl * xl;
        double c1 = (vx * xl + vy * yl) / c;
        double c2 = -coef * (vy * xl - vx * yl) / c;
        vx = c1 * xl - yl * c2;
        vy = c1 * yl + c2 * xl;

        a->getvx() = vx;
        a->getvy() = vy;
        this->effect();
        return true;
    }
    return false;
}

kidney::kidney(double _x1, double _x2, double _y1, double _y2, double _coef) : obline(_x1, _x2, _y1, _y2), coef(_coef) { object::bonus = 99; }
bool kidney::bounce(ball *a)
{
    if (obline::judge(a))
    {
        double vx = a->getvx(), vy = a->getvy();
        double yl = y2 - y1, xl = x2 - x1;
        double c = yl * yl + xl * xl;
        double c1 = (vx * xl + vy * yl) / c;
        double c2 = -coef * (vy * xl - vx * yl) / c;
        vx = c1 * xl - yl * c2;
        vy = c1 * yl + c2 * xl;

        a->getvx() = vx;
        a->getvy() = vy;
        this->effect();
        return true;
    }
    return false;
}
void kidney::effect()
{
}

award::award(double _x, double _y, double _r) : obcircle(_x, _y, _r, true)
{
    object::bonus = 1999;
    noaward = false;
    ifaward = new QTimer();
    ifaward->setInterval(1000);
    connect(ifaward, SIGNAL(timeout()), this, SLOT(deleteaward()));
    connect(this, SIGNAL(getaward()), this, SLOT(dealaward()));
}

void award::effect()
{
}

bool award::judge(ball *a)
{
    auto distance = sqrt((a->getx() - x) * (a->getx() - x) + (a->gety() - y) * (a->gety() - y));
    return (distance < r);
}

bool award::bounce(ball *a)
{
    if (judge(a))
    {
        this->effect();
        emit getaward();
        return true;
    }
    return false;
}
void award::deleteaward()
{
    ifaward->stop();
    noaward = false;
    // qDebug()<<'b';
}
void award::dealaward()
{
    if (noaward)
        return;
    else
    {
        ifaward->start();
        noaward = true;
        // qDebug()<<'a';
    }

} // 后面可做图片消失与重新出现

// 按下按键，flipper,向上匀速（很快）旋转，按住按键flipper保持位置；松掉按键，flipper匀速（较慢）旋转回到初始位置
// flipper::flipper():{}
