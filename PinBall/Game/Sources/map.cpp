#include "Game/Headers/map.h"

map::map(int &theme_index, QVector<ThemePack *> &themes, QWidget *parent)
    : pparent(parent), _theme_index(theme_index), _theme_packs(themes), encoded_elements(encoded_dynamic),
      _is_ball_alternated(false), _is_ball_alternated_buffer(false)
{
    pb = nullptr;
    _ball_alternate_timer.setInterval(1000);
    connect(&_ball_alternate_timer, &QTimer::timeout, this, handle_ballAlternate);
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
    dynamic_elements_default.push_back(new cirwall(210, 400, 10, 220, 210, 400, 410, 1));
    dynamic_elements_default.push_back(new cirwall(199.9, 377.55, 30, 180, 170, 400, 380, 1));
    // 11-16:RKidney
    dynamic_elements_default.push_back(new stwall(430, 430, 290, 380, 1));
    dynamic_elements_default.push_back(new kidney(410, 380, 290, 400, 1.5));
    dynamic_elements_default.push_back(new stwall(430, 390, 400, 410, 1));
    dynamic_elements_default.push_back(new cirwall(420, 294, 12, 1));
    dynamic_elements_default.push_back(new cirwall(390, 400, 10, 380, 390, 400, 410, 1));
    dynamic_elements_default.push_back(new cirwall(400.1, 377.55, 30, 420, 430, 400, 380, 1));

    encoded_dynamic_default.clear();

    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::BonusPoint, 175, 145});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::BonusPoint, 133, 64});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::Drum, 300, 90});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::Drum, 270, 150});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::Drum, 330, 150});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::LKidney, 220, 400});
    encoded_dynamic_default.push_back(EncodedMapElement{enumMapElements::RKidney, 380, 400});

    /////////////////////////////////////
    ////      留空动态地图元素部分     ////
    /////////////////////////////////////

    encoded_dynamic.clear();
    dynamic_elements.clear();
    updateMap();
}

void map::onestep()
{
    // qDebug()<<(double)clock()/CLOCKS_PER_SEC;
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
        if (obj->bounce(pb))
        { // 发生碰撞
            obj->ef = true;
            // qDebug()<<"bang!!!";
            // qDebug()<<i;
            if (obj->bonus != 0)
            {
                score += obj->bonus;
                highest = std::max(highest, score);
                emit scorechange(score, highest);
                if (obj->has_coolingdown)
                {
                    obj->bonus = 0;
                }
                if (not _is_ball_alternated)
                {
                    _is_ball_alternated = true;
                    _ball_alternate_timer.start();
                }
            }
            break;
        }
    }
    if (!pb->isalive())
    {
        emit dead();
    }
    // qDebug()<<(double)clock()/CLOCKS_PER_SEC;
}

void map::oneeffect()
{
    // qDebug()<<(double)clock()/CLOCKS_PER_SEC;
    for (auto obj : map_eles)
    {
        if (obj->ef)
        { // 发生碰撞
            emit playse(obj->e_obse);
            obj->ef = false;
        }
    }
    updateball();
    updateflipper();
    // qDebug()<<(double)clock()/CLOCKS_PER_SEC;
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
    for (auto &e : map_pic_labels)
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

void map::_rebuild_map()
{
    qDebug() << "rebuild called";
    score = 0;
    emit scorechange(0, highest);
    upleft = false;     // Z按键状态
    upright = false;    // M按键状态
    moveupleft = false; // 是否在上升
    moveupright = false;
    theleft = 0.24;
    theright = 0.24; // 初始角

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
    qDebug() << gball;
}

void map::_redraw_map()
{
    qDebug() << "redraw called";
    for (auto &l : map_pic_labels)
    {
        if (l != nullptr)
        {
            delete l;
        }
    }
    map_pic_labels.clear();

    QLabel *plabel = new QLabel(pparent);
    plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[BG_Game]);
    plabel->setMask(_theme_packs[_theme_index]->themePics()[BG_Game]->mask());
    plabel->setGeometry(0, 0, 600, 540);
    plabel->setFixedSize(600, 540);
    plabel->show();
    map_pic_labels.push_back(plabel);

    // _shadow = new QGraphicsDropShadowEffect();
    // _shadow->setBlurRadius(70);
    // _shadow->setColor(QColor("#ffffff"));
    // _shadow->setOffset(0);
    // _shadow->setEnabled(true);
    // plabel->setGraphicsEffect(_shadow);

    plabel = nullptr;

    plabel = new QLabel(pparent);
    plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[Ball]);
    plabel->setMask(_theme_packs[_theme_index]->themePics()[Ball]->mask());
    plabel->setGeometry(pb->getx() - 10, pb->gety() - 10, 20, 20);
    plabel->setFixedSize(20, 20);
    plabel->show();
    map_pic_labels.push_back(plabel);

    plabel = nullptr;

    plabel = new QLabel(pparent);
    _lflipper_pixmap = _theme_packs[_theme_index]->themePics()[lFlipper];
    plabel->setPixmap(*_lflipper_pixmap);
    plabel->setGeometry(98, 294, 191, 377);
    plabel->show();
    map_pic_labels.push_back(plabel);

    plabel = nullptr;

    plabel = new QLabel(pparent);
    _rflipper_pixmap = _theme_packs[_theme_index]->themePics()[rFlipper];
    plabel->setPixmap(*_rflipper_pixmap);
    plabel->setGeometry(305, 295, 191, 377);
    plabel->show();
    map_pic_labels.push_back(plabel);

    plabel = nullptr;

    for (auto const &e : encoded_elements)
    {
        switch (e.e_element_type)
        {
        case enumMapElements::LKidney:
        {
            plabel = new QLabel(pparent);
            plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[lKidney_game]);
            plabel->setMask(_theme_packs[_theme_index]->themePics()[lKidney_game]->mask());
            plabel->setGeometry(e.m_x - 50, e.m_y - 120, 53, 134);
            plabel->setFixedSize(53, 134);
            plabel->show();
            map_pic_labels.push_back(plabel);

            plabel = nullptr;
            break;
        }
        case enumMapElements::RKidney:
        {
            plabel = new QLabel(pparent);
            plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[rKidney_game]);
            plabel->setMask(_theme_packs[_theme_index]->themePics()[rKidney_game]->mask());
            plabel->setGeometry(e.m_x - 3, e.m_y - 120, 53, 134);
            plabel->setFixedSize(53, 134);
            plabel->show();
            map_pic_labels.push_back(plabel);

            plabel = nullptr;
            break;
        }
        case enumMapElements::Drum:
        {
            plabel = new QLabel(pparent);
            plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[Drum_game]);
            plabel->setMask(_theme_packs[_theme_index]->themePics()[Drum_game]->mask());
            plabel->setGeometry(e.m_x - 20, e.m_y - 20, 40, 40);
            plabel->setFixedSize(40, 40);
            plabel->show();
            map_pic_labels.push_back(plabel);

            plabel = nullptr;
            break;
        }
        case enumMapElements::BonusPoint:
        {
            plabel = new QLabel(pparent);
            plabel->setPixmap(*_theme_packs[_theme_index]->themePics()[Bonus_Point_game]);
            plabel->setMask(_theme_packs[_theme_index]->themePics()[Bonus_Point_game]->mask());
            plabel->setGeometry(e.m_x - 10, e.m_y - 10, 20, 20);
            plabel->setFixedSize(20, 20);
            plabel->show();
            map_pic_labels.push_back(plabel);

            plabel = nullptr;
            break;
        }
        }
    }
    map_pic_labels[1]->raise();
}

void map::updateball()
{
    if (_is_ball_alternated != _is_ball_alternated_buffer)
    {
        if (_is_ball_alternated)
        {
            map_pic_labels[1]->setPixmap(*_theme_packs[_theme_index]->themePics()[Ball_alter]);
        }
        else
        {
            map_pic_labels[1]->setPixmap(*_theme_packs[_theme_index]->themePics()[Ball]);
        }
        _is_ball_alternated_buffer = _is_ball_alternated;
    }
    map_pic_labels[1]->move(pb->getx() - 10, pb->gety() - 10);
}

void map::updateflipper()
{
    QLabel *plabel = map_pic_labels[2];

    QPixmap rotatedPixmap(_lflipper_pixmap->size());
    rotatedPixmap.fill(Qt::transparent);
    QPainter painter(&rotatedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);                                                          // 设置抗锯齿
    painter.translate(rotatedPixmap.width() / 2, rotatedPixmap.height() / 2);                               // 将坐标系移动到图像中心
    painter.rotate(-(0.24 - theleft) / pi * 180);                                                           // 旋转
    painter.drawPixmap(-_lflipper_pixmap->width() / 2, -_lflipper_pixmap->height() / 2, *_lflipper_pixmap); // 绘制旋转后的图像
    plabel->setPixmap(rotatedPixmap);

    plabel = nullptr;

    plabel = map_pic_labels[3];

    QPixmap rotatedPixmap1(_rflipper_pixmap->size());
    rotatedPixmap1.fill(Qt::transparent);
    QPainter painter1(&rotatedPixmap1);
    painter1.setRenderHint(QPainter::Antialiasing);                                                          // 设置抗锯齿
    painter1.translate(rotatedPixmap1.width() / 2, rotatedPixmap1.height() / 2);                             // 将坐标系移动到图像中心
    painter1.rotate((0.24 - theright) / pi * 180);                                                           // 旋转
    painter1.drawPixmap(-_rflipper_pixmap->width() / 2, -_rflipper_pixmap->height() / 2, *_rflipper_pixmap); // 绘制旋转后的图像
    plabel->setPixmap(rotatedPixmap1);
}

void map::setmap(QVector<EncodedMapElement> newmap, int gg)
{
    qDebug() << "setmap called";
    for (auto ptr : dynamic_elements)
    {
        if (ptr)
        {
            delete ptr;
        }
    }
    dynamic_elements.clear();
    highest = 0;
    encoded_dynamic = newmap;
    gball = gg;
    for (auto const &e : newmap)
    {
        switch (e.e_element_type)
        {
        case enumMapElements::LKidney:
        {
            dynamic_elements.push_back(new stwall(e.m_x - 50, e.m_x - 50, e.m_y - 110, e.m_y - 20, 1));
            dynamic_elements.push_back(new kidney(e.m_x - 30, e.m_x, e.m_y - 110, e.m_y, 1.3));
            dynamic_elements.push_back(new stwall(e.m_x - 40, e.m_x - 10, e.m_y, e.m_y + 10, 1));
            dynamic_elements.push_back(new cirwall(e.m_x - 40, e.m_y - 106, 12, 1));
            dynamic_elements.push_back(new cirwall(e.m_x - 10, e.m_y, 10, e.m_x, e.m_x - 10, e.m_y, e.m_y + 10, 1));
            dynamic_elements.push_back(new cirwall(e.m_x - 20.1, e.m_y - 22.45, 30, e.m_x - 40, e.m_x - 50, e.m_y, e.m_y - 20, 1));

            break;
        }
        case enumMapElements::RKidney:
        {
            dynamic_elements.push_back(new stwall(e.m_x + 50, e.m_x + 50, e.m_y - 110, e.m_y - 20, 1));
            dynamic_elements.push_back(new kidney(e.m_x + 30, e.m_x, e.m_y - 110, e.m_y, 1.3));
            dynamic_elements.push_back(new stwall(e.m_x + 50, e.m_x + 10, e.m_y, e.m_y + 10, 1));
            dynamic_elements.push_back(new cirwall(e.m_x + 40, e.m_y - 106, 12, 1));
            dynamic_elements.push_back(new cirwall(e.m_x + 10, e.m_y, 10, e.m_x, e.m_x + 10, e.m_y, e.m_y + 10, 1));
            dynamic_elements.push_back(new cirwall(e.m_x + 20.1, e.m_y - 22.45, 30, e.m_x + 40, e.m_x + 50, e.m_y, e.m_y - 20, 1));

            break;
        }
        case enumMapElements::Drum:
        {
            dynamic_elements.push_back(new drum(e.m_x, e.m_y, 20, 1.2));

            break;
        }
        case enumMapElements::BonusPoint:
        {
            dynamic_elements.push_back(new award(e.m_x, e.m_y, 10));

            break;
        }
        }
    }
}

void map::updateMap()
{
    _rebuild_map();
    _redraw_map();
    updateflipper();
}

void map::handle_ballAlternate()
{
    _is_ball_alternated = false;
}