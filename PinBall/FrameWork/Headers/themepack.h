#ifndef THEMEPACK_H
#define THEMEPACK_H

#include <QPixmap>
#include <QFile>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>

enum enumThemePicIndex{
    Cover,BG_Map_Editor,BG_Game,
    lFlipper,rFlipper,Ball,
    lKidney_game,lKidney_home,lKidney_placed,lKidney_valid,lKidney_invalid,
    rKidney_game,rKidney_home,rKidney_placed,rKidney_valid,rKidney_invalid,
    Drum_game,Drum_home,Drum_placed,Drum_valid,Drum_invalid,
    Bonus_Point_game,Bonus_Point_home,Bonus_Point_placed,Bonus_Point_valid,Bonus_Point_invalid,
    count
};

class ThemePack{
private:
    const static QVector<QString> s_PicNames;
    const static QVector<QString> s_PicPathsLegacy;
    const static QVector<QSize> s_PicSizes;
    QString m_packDir;
    QString m_ThemeTitle;
    QVector<QPixmap*> m_Pics;

public:
    ThemePack(QString);
    ThemePack(ThemePack &&);
    ThemePack();
    ~ThemePack();
    bool loadTheme();
    QString const& themeTitle();
    QVector<QPixmap*> const& themePics() const;
};

#endif