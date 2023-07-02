#include <FrameWork/Headers/themepack.h>

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
    QSize(53,134),QSize(100,100),QSize(53,134),QSize(53,134),QSize(53,134),
    QSize(53,134),QSize(100,100),QSize(53,134),QSize(53,134),QSize(53,134),
    QSize(40,40),QSize(100,100),QSize(40,40),QSize(40,40),QSize(40,40),
    QSize(20,20),QSize(100,100),QSize(20,20),QSize(20,20),QSize(20,20)
};

const QVector<QString> ThemePack::s_PicPathsLegacy{
    ":/mapeditor/themes/Legacy_cover.png",
    ":/mapeditor/backgrounds/mapeditor_background.png",
    ":/map_items/background.png",

    ":/map_items/shifted_left_flipper.png",
    ":/map_items/shifted_right_flipper.png",
    ":/map_items/ball.png",

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

ThemePack::ThemePack():m_ThemeTitle("Legacy"){
    m_Pics.resize((int)count);
    for(int i=0;i<(int)count;++i){
        m_Pics[i]=new QPixmap(s_PicPathsLegacy[i]);
        *m_Pics[i] = m_Pics[i]->scaled(s_PicSizes[i], Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
}

ThemePack::ThemePack(QString _dir) : m_packDir(_dir)
{
}

ThemePack::ThemePack(ThemePack&& other)
:m_packDir(std::move(other.m_packDir)),m_ThemeTitle(std::move(other.m_ThemeTitle)),m_Pics(std::move(other.m_Pics))
{
    qDebug()<<"moved";
}

bool ThemePack::loadTheme()
{
    qDebug()<<"loadTheme";
    QFile m_jsonSource(QDir(m_packDir).filePath("theme.json"));
    if (!m_jsonSource.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open JSON file";
        return false;
    }

    QByteArray jsonData = m_jsonSource.readAll();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError)
    {
        qWarning() << "Failed to parse JSON:" << error.errorString();
        return false;
    }

    // 检查 JSON 是否为对象
    if (!jsonDoc.isObject())
    {
        qWarning() << "JSON is not an object";
        return false;
    }

    // 将 JSON 转换为对象
    QJsonObject jsonObj = jsonDoc.object();
    m_ThemeTitle = jsonObj.value("Theme_Title").toString();
    QDir currentDir(m_packDir);
    m_Pics.resize((int)count);
    for (int i = 0; i < (int)count; ++i)
    {
        if(not jsonObj.contains(s_PicNames[i])){
            qWarning()<<"Incomplete theme.json!";
            return false;
        }
        QString picPath = QDir(m_packDir).filePath(jsonObj.value(s_PicNames[i]).toString());
        QFile file(picPath);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Failed to open image file,file name below:"<<Qt::endl<<picPath;
            return false;
        }
        // 读取文件数据
        QByteArray imageData = file.readAll();
        // 创建 QImage 对象并加载图片数据
        QImage image;

        if (image.loadFromData(imageData))
        {
            m_Pics[i] = new QPixmap();
            *m_Pics[i] = QPixmap::fromImage(image);
            *m_Pics[i] = m_Pics[i]->scaled(s_PicSizes[i], Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        else
        {
            qWarning() << "Invalid Image";
            return false;
        }
    }
    return true;
}

ThemePack::~ThemePack()
{
    for (auto ptr : m_Pics)
    {
        if (ptr)
        {
            delete ptr;
        }
    }
}

QString const &ThemePack::themeTitle()
{
    qDebug()<<"Theme title called";
    return m_ThemeTitle;
}

QVector<QPixmap *> const &ThemePack::themePics() const
{
    qDebug()<<"Theme pic called";
    return m_Pics;
}