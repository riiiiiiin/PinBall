#ifndef ENCODEDMAP_H
#define ENCODEDMAP_H

#include <QString>
#include <QList>

enum e_MapElements{
    LKidney=1,
    RKidney=2,
    Drum=3,
    BonusPoint=4
};

struct EncodedMapElement{
    e_MapElements _element_type;
    double _x;
    double _y;
};

#endif