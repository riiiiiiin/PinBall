#include <FrameWork/Headers/themepack.h>

ThemePack::ThemePack():m_ThemeTitle("Legacy"){
    for(int i=0;i<s_nPics;++i){
        m_Pics[i]=new QPixmap(s_PicPathsLegacy[i]);
        *m_Pics[i] = m_Pics[i]->scaled(s_PicSizes[i], Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
}

ThemePack::ThemePack(QString _file_path) : m_jsonSource(QFile(_file_path))
{
}

bool ThemePack::loadTheme()
{
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
    for (int i = 0; i < s_nPics; ++i)
    {
        if(not jsonObj.contains(s_PicNames[i])){
            qWarning()<<"Incomplete theme.json!";
            return false;
        }
        QFile file(jsonObj.value(s_PicNames[i]).toString());
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Failed to open image file";
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
    return m_ThemeTitle;
}

QVector<QPixmap *> const &ThemePack::themePics()
{
    return m_Pics;
}