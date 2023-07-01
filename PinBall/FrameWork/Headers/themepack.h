#ifndef THEMEPACK_H
#define THEMEPACK_H

#include <QPixmap>
#include <QFile>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

enum enumThemePicIndex{
    Cover,BG_Map_Editor,BG_Game,
    lFlipper,rFlipper,Ball,
    lKidney_game,lKidney_home,lKidney_placed,lKidney_valid,lKidney_invalid,
    rKidney_game,rKidney_home,rKidney_placed,rKidney_valid,rKidney_invalid,
    Drum_game,Drum_home,Drum_placed,Drum_valid,Drum_invalid,
    Bonus_Point_game,Bonus_Point_home,Bonus_Point_placed,Bonus_Point_valid,Bonus_Point_invalid
};

class ThemePack{
private:
    const static QVector<QString> s_PicNames;
    const static QVector<QString> s_PicPathsLegacy;
    const static int s_nPics;
    const static QVector<QSize> s_PicSizes;
    QFile m_jsonSource;
    QString m_ThemeTitle;
    QVector<QPixmap*> m_Pics;

public:
    ThemePack(QString _file_path);
    ThemePack();
    bool loadTheme();
    ~ThemePack()=default;
    QString const& themeTitle();
    QVector<QPixmap*> const& themePics();
};

const QVector<QString> ThemePack::s_PicNames{
    "Cover","BG_Map_Editor","BG_Game",
    "lFlipper","rFlipper","Ball",
    "lKidney_game","lKidney_home","lKidney_placed","lKidney_valid","lKidney_invalid",
    "rKidney_game","rKidney_home","rKidney_placed","rKidney_valid","rKidney_invalid",
    "Drum_game","Drum_home","Drum_placed","Drum_valid","Drum_invalid",
    "Bonus_Point_game","Bonus_Point_home","Bonus_Point_placed","Bonus_Point_valid","Bonus_Point_invalid"
};

const QVector<QSize> ThemePack::s_PicSizes{
    QSize(175,70),QSize(600,540),QSize(600,540),
    QSize(191,377),QSize(191,377),QSize(20,20),
    QSize(53,134),QSize(100,100),QSize(100,100),QSize(100,100),QSize(100,100),
    QSize(53,134),QSize(100,100),QSize(100,100),QSize(100,100),QSize(100,100),
    QSize(40,40),QSize(100,100),QSize(100,100),QSize(100,100),QSize(100,100),
    QSize(20,20),QSize(100,100),QSize(100,100),QSize(100,100),QSize(100,100)
};

const QVector<QString> ThemePack::s_PicPathsLegacy{
    ":/mapeditor/themes/Legacy_cover.png",
    ":/mapeditor/backgrounds/mapeditor_background.png",
    ":/map_items/background.png",

    ":/map_items/shifted_left_flipper.png",
    ":/map_items/shifted_right_flipper.png",
    ":/map_items/ball.png"

    ":/map_items/shifted_left_kidney.png",
    ":/mapeditor/draggables/home_pic.png",
    ":/mapeditor/draggables/static.png",
    ":/mapeditor/draggables/dragged_valid.png",
    ":/mapeditor/draggables/dragged_invalid.png",

    ":/map_items/shifted_right_kidney.png",
    ":/mapeditor/draggables/home_pic_2.png",
    ":/mapeditor/draggables/static_2.png",
    ":/mapeditor/draggables/dragged_valid_2.png",
    ":/mapeditor/draggables/dragged_invalid_2.png",

    ":/map_items/new_drum.png",
    ":/mapeditor/draggables/home_pic_3.png",
    ":/mapeditor/draggables/static_3.png",
    ":/mapeditor/draggables/dragged_valid_3.png",
    ":/mapeditor/draggables/dragged_invalid_3.png",

    ":/map_items/new_bonus_point.png",
    ":/mapeditor/draggables/home_pic_4.png",
    ":/mapeditor/draggables/static_4.png",
    ":/mapeditor/draggables/dragged_valid_4.png",
    ":/mapeditor/draggables/dragged_invalid_4.png"
};

const int ThemePack::s_nPics = 26;

#endif