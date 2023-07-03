#ifndef ENCODEDMAP_H
#define ENCODEDMAP_H

#include <QString>
#include <QVector>

enum enumMapElements{
    LKidney=1,
    RKidney=2,
    Drum=3,
    BonusPoint=4
};

struct EncodedMapElement{
    enumMapElements e_element_type;
    double m_x;
    double m_y;
};

#endif