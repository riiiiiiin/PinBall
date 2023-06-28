#include "map.h"

map::map(QWidget *parent) : pparent(parent), encoded_elements(encoded_dynamic)
{
    highest = 0;
    score = 0;
    t = 0.002;
    pb=nullptr;

    //////////////////////////////////
    ////      静态地图元素部分     ////
    /////////////////////////////////

    static_elements.clear();
    // 0-4:左flipper,对应theleft
    static_elements.push_back(new stwall(210, 234.3, 459, 464.9, 1));
    static_elements.push_back(new stwall(234.3, 258.6, 464.9, 470.9, 1));
    static_elements.push_back(new stwall(282.8, 258.6, 476.8, 470.9, 1));
    static_elements.push_back(new cirwall(280.8, 484.3, 7.8, 1));
    static_elements.push_back(new stwall(206, 278.8, 479, 491.8, 1));
    // 5-9:右flipper,对应theright
    static_elements.push_back(new stwall(390, 365.7, 459, 464.9, 1));
    static_elements.push_back(new stwall(365.7, 341.4, 464.9, 470.9, 1));
    static_elements.push_back(new stwall(317.2, 341.4, 476.8, 470.9, 1));
    static_elements.push_back(new cirwall(319.2, 484.3, 7.8, 1));
    static_elements.push_back(new stwall(394, 321.2, 479, 491.8, 1));
    // 10-13:右上角的四边形墙
    static_elements.push_back(new stwall(453, 390, 74, 117, 1));
    static_elements.push_back(new stwall(430, 390, 150, 117, 1));
    static_elements.push_back(new stwall(430, 484, 150, 114, 1));
    static_elements.push_back(new stwall(484, 453, 114, 74, 1));
    // 14:左下直线墙
    static_elements.push_back(new stwall(67, 210, 424, 459, 0.7));
    // 15:右下直线墙
    static_elements.push_back(new stwall(533, 390, 424, 459, 0.7));
    // 16:圆弧顶
    static_elements.push_back(new cirwall(300, 814.6, 800, 100, 500, 40, 40, 1));
    // 17-18:轨道
    static_elements.push_back(new cirwall(343.326, 136.22, 180, 173, 181, 78, 214, 1));
    static_elements.push_back(new cirwall(339.835, 144.28, 150, 205, 200, 210, 90, 1));
    // 19:左壁
    static_elements.push_back(new stwall(100, 67, 40, 424, 1));
    // 20:右壁
    static_elements.push_back(new stwall(500, 533, 40, 424, 1));

    /////////////////////////////////////
    ////      默认动态地图元素部分     ////
    /////////////////////////////////////

    dynamic_elements_default.clear();
    // 0-1:BonusPoint*2
    dynamic_elements_default.push_back(new award(175, 145, 10));
    dynamic_elements_default.push_back(new award(133, 64, 10));
    // 2-4:Drum*3
    dynamic_elements_default.push_back(new drum(300, 90, 20, 1.5));
    dynamic_elements_default.push_back(new drum(270, 150, 20, 1.5));
    dynamic_elements_default.push_back(new drum(330, 150, 20, 1.5));
    // 5-10:LKidney
    dynamic_elements_default.push_back(new stwall(170, 170, 290, 380, 1));
    dynamic_elements_default.push_back(new kidney(190, 220, 290, 400, 1.5));
    dynamic_elements_default.push_back(new stwall(180, 210, 400, 410, 1));
    dynamic_elements_default.push_back(new cirwall(180, 294, 12, 1));
    dynamic_elements_default.push_back(new cirwall(210, 400, 10,220,210,400,410, 1));
    dynamic_elements_default.push_back(new cirwall(199.9, 377.55, 30,180,170,400,380, 1));
    // 11-16:RKidney
    dynamic_elements_default.push_back(new stwall(430, 430, 290, 380, 1));
    dynamic_elements_default.push_back(new kidney(410, 380, 290, 400, 1.5));
    dynamic_elements_default.push_back(new stwall(430, 390, 400, 410, 1));
    dynamic_elements_default.push_back(new cirwall(420, 294, 12, 1));
    dynamic_elements_default.push_back(new cirwall(390, 400, 10,380,390,400,410, 1));
    dynamic_elements_default.push_back(new cirwall(400.1, 377.55, 30,420,430,400,380, 1));

    encoded_dynamic_default.clear();

    encoded_dynamic_default.push_back(EncodedMapElement{BonusPoint, 175, 145});
    encoded_dynamic_default.push_back(EncodedMapElement{BonusPoint, 133, 64});
    encoded_dynamic_default.push_back(EncodedMapElement{Drum, 300, 90});
    encoded_dynamic_default.push_back(EncodedMapElement{Drum, 270, 150});
    encoded_dynamic_default.push_back(EncodedMapElement{Drum, 330, 150});
    encoded_dynamic_default.push_back(EncodedMapElement{LKidney, 220, 400});
    encoded_dynamic_default.push_back(EncodedMapElement{RKidney, 380, 400});

    /////////////////////////////////////
    ////      留空动态地图元素部分     ////
    /////////////////////////////////////

    encoded_dynamic.clear();
    dynamic_elements.clear();
    rebuild_map();
    redraw_map();
}

void map::onestep()
{
    int lc = 0, rc = 0;
    moveupleft = false; // 是否在上升
    moveupright = false;
    double rx, ry;
    pb->jump(); // 小球斜抛运动
    // qDebug()<<pb->getx()<<' '<<pb->gety();
    if (theleft > -0.78 && upleft == true)
    {
        theleft -= t * wup;
        if (theleft < -0.78)
            theleft = -0.78;
        lc = 1;
        moveupleft = true;
    }
    else if (theleft < 0.24 && upleft == false)
    {
        theleft += t * wdo;
        if (theleft > 0.24)
            theleft = 0.24;
        lc = 1;
    }
    if (theright > -0.78 && upright == true)
    {
        theright -= t * wup;
        if (theright < -0.78)
            theright = -0.78;
        rc = 1;
        moveupright = true;
    }
    else if (theright < 0.24 && upright == false)
    {
        theright += t * wdo;
        if (theright > 0.24)
            theright = 0.24;
        rc = 1;
    }
    if (lc)
    {
        rx = 25 * cos(theleft);
        ry = 25 * sin(theleft);
        map_eles[0]->change(leftx, leftx + rx, y, y + ry, int(upleft), moveupleft);
        map_eles[1]->change(leftx + rx, leftx + 2 * rx, y + ry, y + 2 * ry, int(upleft) * 2, moveupleft);
        map_eles[2]->change(leftx + 2 * rx, leftx + 3 * rx, y + 2 * ry, y + 3 * ry, int(upleft) * 3, moveupleft);
        map_eles[3]->change(leftx + 3 * rx - 2, y + 3 * ry + 7.5, 0, 0, int(upleft), moveupleft);
        map_eles[4]->change(leftx - 4, leftx + 3 * rx - 4, y + 20, y + 3 * ry + 15, 0, moveupleft);
    }
    if (rc)
    {
        rx = 25 * cos(theright);
        ry = 25 * sin(theright);
        map_eles[5]->change(rightx, rightx - rx, y, y + ry, int(upright), moveupright);
        map_eles[6]->change(rightx - rx, rightx - 2 * rx, y + ry, y + 2 * ry, int(upright) * 2, moveupright);
        map_eles[7]->change(rightx - 2 * rx, rightx - 3 * rx, y + 2 * ry, y + 3 * ry, int(upright) * 3, moveupright);
        map_eles[8]->change(rightx - 3 * rx + 2, y - 3 * ry + 7.5, 0, 0, int(upright), moveupright);
        map_eles[9]->change(rightx + 4, rightx - 3 * rx + 4, y + 20, y + 3 * ry + 15, 0, moveupright);
    }
    for (auto obj : map_eles)
    {
        if (obj->bounce(pb) and (!obj->noaward))
        { // 发生碰撞
            obj->ef = true;
            // qDebug()<<"bang!!!";
            // qDebug()<<i;
            if (obj->bonus != 0 and (not obj->noaward))
            {
                score += obj->bonus;
                highest = std::max(highest, score);
                emit scorechange(score, highest);
            }
            break;
        }
    }
    if (!pb->isalive())
    {
        emit dead();
    }
}

void map::oneeffect()
{
    for (auto obj : map_eles)
    {
        if (obj->ef)
        {                  // 发生碰撞
            obj->effect(); // 画面&声音特效+分数变化
            obj->ef = false;
        }
    }
    updateball();
    updateflipper();
}

map::~map()
{
    encoded_dynamic.clear();
    encoded_dynamic_default.clear();
    encoded_elements.clear();
    map_eles.clear();
    for (auto &e : static_elements)
    {
        if (e)
        {
            delete e;
        }
    }
    static_elements.clear();
    for (auto &e : dynamic_elements)
    {
        if (e)
        {
            delete e;
        }
    }
    dynamic_elements.clear();
    for (auto &e : dynamic_elements_default)
    {
        if (e)
        {
            delete e;
        }
    }
    dynamic_elements_default.clear();
    if (pb)
    {
        delete pb;
    }
}

void map::leftup()
{
    upleft = true;
}

void map::leftdown()
{
    upleft = false;
}

void map::rightdown()
{
    upright = false;
}

void map::rightup()
{
    upright = true;
}

void map::rebuild_map()
{
    score = 0;
    emit scorechange(0, highest);
    upleft = false;     // Z按键状态
    upright = false;    // M按键状态
    moveupleft = false; // 是否在上升
    moveupright = false;
    theleft = 0.24;
    theright = 0.24; // 初始角
    wup = 3;         // 上升角速度
    wdo = 1;         // 下降角速度
    y = 459;
    leftx = 210;
    rightx = 390;

    if (pb)
    {
        delete pb;
    }
    pb = nullptr;
    pb = new ball(300, 270, 10, QRandomGenerator::global()->bounded(-200, 200), QRandomGenerator::global()->bounded(-300, -150), gball);

    map_eles.clear();
    if (dynamic_elements.empty())
    {
        map_eles = static_elements + dynamic_elements_default;
    }
    else
    {
        map_eles = static_elements + dynamic_elements;
    }

    if (encoded_dynamic.empty())
    {
        encoded_elements = encoded_dynamic_default;
    }
    else
    {
        encoded_elements = encoded_dynamic;
    }
}

void map::redraw_map()
{
    for(auto&l:map_pics){
        if(l!=nullptr){
            delete l;
        }
    }
    map_pics.clear();

    QLabel *plabel = new QLabel(pparent);
    QPixmap *ppix = new QPixmap(":/new/prefix1/background.png");
    *ppix = ppix->scaled(600, 540, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plabel->setPixmap(*ppix);
    plabel->setMask(ppix->mask());
    plabel->setGeometry(0, 0, 600, 540);
    plabel->setFixedSize(600, 540);
    plabel->show();
    map_pics.push_back(plabel);

    plabel = nullptr;
    ppix = nullptr;

    plabel = new QLabel(pparent);
    ppix= new QPixmap(":/new/prefix1/ball.png");
    *ppix = ppix->scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plabel->setPixmap(*ppix);
    plabel->setMask(ppix->mask());
    plabel->setGeometry(pb->getx() - 10, pb->gety() - 10, 20, 20);
    plabel->setFixedSize(20, 20);
    plabel->show();
    map_pics.push_back(plabel);

    plabel = nullptr;
    ppix = nullptr;

    plabel = new QLabel(pparent);
    ppix= new QPixmap(":/new/prefix1/shifted_left_flipper.png");
    *ppix = ppix->scaled(527, 198, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plabel->setPixmap(*ppix);
    // plabel->setMask(ppix->mask());
    plabel->setGeometry(98, 338, 527, 198);
    plabel->show();
    map_pics.push_back(plabel);

    plabel = nullptr;
    ppix = nullptr;

    plabel = new QLabel(pparent);
    ppix= new QPixmap(":/new/prefix1/shifted_right_flipper.png");
    *ppix = ppix->scaled(527, 198, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plabel->setPixmap(*ppix);
    // plabel->setMask(ppix->mask());
    plabel->setGeometry(305, 339, 527, 198);
    plabel->show();
    map_pics.push_back(plabel);

    plabel = nullptr;
    ppix = nullptr;

    for (auto const &e : encoded_elements)
    {
        switch (e._element_type)
        {
        case LKidney:
        {
            plabel = new QLabel(pparent);
            ppix= new QPixmap(":/new/prefix1/shifted_left_kidney.png");
            *ppix = ppix->scaled(53, 134, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            plabel->setPixmap(*ppix);
            plabel->setMask(ppix->mask());
            plabel->setGeometry(e._x - 50, e._y - 120, 53, 134);
            plabel->setFixedSize(53, 134);
            plabel->show();
            map_pics.push_back(plabel);

            plabel = nullptr;
            ppix = nullptr;
            break;
        }
        case RKidney:
        {
            plabel = new QLabel(pparent);
            ppix= new QPixmap(":/new/prefix1/shifted_right_kidney.png");
            *ppix = ppix->scaled(53, 134, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            plabel->setPixmap(*ppix);
            plabel->setMask(ppix->mask());
            plabel->setGeometry(e._x - 3, e._y - 120, 53, 134);
            plabel->setFixedSize(53, 134);
            plabel->show();
            map_pics.push_back(plabel);

            plabel = nullptr;
            ppix = nullptr;
            break;
        }
        case Drum:
        {
            plabel = new QLabel(pparent);
            ppix= new QPixmap(":/new/prefix1/new_drum.png");
            *ppix = ppix->scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            plabel->setPixmap(*ppix);
            plabel->setMask(ppix->mask());
            plabel->setGeometry(e._x - 20, e._y - 20, 40, 40);
            plabel->setFixedSize(40, 40);
            plabel->show();
            map_pics.push_back(plabel);

            plabel = nullptr;
            ppix = nullptr;
            break;
        }
        case BonusPoint:
        {
            plabel = new QLabel(pparent);
            ppix= new QPixmap(":/new/prefix1/new_bonus_point.png");
            *ppix = ppix->scaled(20,20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            plabel->setPixmap(*ppix);
            plabel->setMask(ppix->mask());
            plabel->setGeometry(e._x - 10, e._y - 10, 20, 20);
            plabel->setFixedSize(20, 20);
            plabel->show();
            map_pics.push_back(plabel);

            plabel = nullptr;
            ppix = nullptr;
            break;
        }
        }
    }
}

void map::updateball()
{
    map_pics[1]->setGeometry(pb->getx() - 10, pb->gety() - 10, 20, 20);
}

void map::updateflipper()
{
    QLabel* plabel = map_pics[2];

    QPixmap* ppix=new QPixmap(":/new/prefix1/shifted_left_flipper.png");
    QPixmap* rotatedPixmap=new QPixmap(ppix->size());
    rotatedPixmap->fill(Qt::transparent);
    QPainter* painter=new QPainter(rotatedPixmap);
    painter->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
    painter->translate(rotatedPixmap->width() / 2, rotatedPixmap->height() / 2);// 将坐标系移动到图像中心
    painter->rotate(-(0.24-theleft)/pi*180);//旋转
    painter->drawPixmap(-ppix->width() / 2, -ppix->height() / 2, *ppix);// 绘制旋转后的图像
    plabel->setPixmap(*rotatedPixmap);

    plabel=nullptr;
    ppix = nullptr;

    plabel = map_pics[3];

    ppix=new QPixmap(":/new/prefix1/shifted_right_flipper.png");
    rotatedPixmap=new QPixmap(ppix->size());
    rotatedPixmap->fill(Qt::transparent);
    painter=new QPainter(rotatedPixmap);
    painter->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
    painter->translate(rotatedPixmap->width() / 2, rotatedPixmap->height() / 2);// 将坐标系移动到图像中心
    painter->rotate((0.24-theright)/pi*180);//旋转
    painter->drawPixmap(-ppix->width() / 2, -ppix->height() / 2, *ppix);// 绘制旋转后的图像
    plabel->setPixmap(*rotatedPixmap);
}

void map::setmap(QList<EncodedMapElement> newmap, int gg)
{
    highest=0;
    encoded_dynamic = newmap;
    gball=gg;
    dynamic_elements.clear();
    for (auto const &e : newmap)
    {
        switch (e._element_type)
        {
        case LKidney:
        {
            dynamic_elements.push_back(new stwall(e._x - 50, e._x - 50, e._y - 110, e._y - 20, 1));
            dynamic_elements.push_back(new kidney(e._x - 30, e._x, e._y - 110, e._y, 1.3));
            dynamic_elements.push_back(new stwall(e._x - 40, e._x - 10, e._y, e._y + 10, 1));
            // dynamic_elements.push_back(new cirwall(e._x - 40, e._y - 106, 12, e._x - 50, e._x - 30, e._y - 110, e._y - 110, 1));
            dynamic_elements.push_back(new cirwall(e._x - 40, e._y - 106, 12, 1));
            dynamic_elements.push_back(new cirwall(e._x - 10, e._y, 10, e._x, e._x - 10, e._y, e._y + 10, 1));
            dynamic_elements.push_back(new cirwall(e._x - 20.1, e._y - 22.45, 30, e._x - 40, e._x - 50, e._y, e._y - 20, 1));

            break;
        }
        case RKidney:
        {
            dynamic_elements.push_back(new stwall(e._x + 50, e._x + 50, e._y - 110, e._y - 20, 1));
            dynamic_elements.push_back(new kidney(e._x + 30, e._x, e._y - 110, e._y, 1.3));
            dynamic_elements.push_back(new stwall(e._x + 50, e._x + 10, e._y, e._y + 10, 1));
            // dynamic_elements.push_back(new cirwall(e._x + 40, e._y - 106, 12, e._x + 10, e._x + 30, e._y - 110, e._y - 110, 1));
            dynamic_elements.push_back(new cirwall(e._x + 40, e._y - 106, 12, 1));
            dynamic_elements.push_back(new cirwall(e._x + 10, e._y, 10, e._x, e._x + 10, e._y, e._y+10, 1));
            dynamic_elements.push_back(new cirwall(e._x + 20.1, e._y - 22.45, 30, e._x + 40, e._x + 50, e._y, e._y - 20, 1));

            break;
        }
        case Drum:
        {
            dynamic_elements.push_back(new drum(e._x, e._y, 20, 1.2));

            break;
        }
        case BonusPoint:
        {
            dynamic_elements.push_back(new award(e._x, e._y, 10));

            break;
        }
        }
    }
}