#include "FrameWork/Headers/openingvideowidget.h"

#include <QDebug>

SkippableVideoWidget::SkippableVideoWidget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(0, 0, 960, 540);
    player = new QMediaPlayer;
    player->setSource(QUrl("qrc:/opening_video/opening.mp4"));// i hate this silly path format!
    qDebug()<<player->error();

    videoWidget = new QVideoWidget;
    audioWidget = new QAudioOutput;
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioWidget);

    layout = new QHBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 设置布局的边缘

    connect(player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(closeOpeningVideo()));
    player->play();
}

SkippableVideoWidget::~SkippableVideoWidget()
{
    layout->removeWidget(videoWidget);
    delete videoWidget;
    videoWidget = nullptr;
    delete audioWidget;
    audioWidget = nullptr;
}

void SkippableVideoWidget::closeOpeningVideo()
{
    if (videoWidget == nullptr)
        return;
    emit end();
}

void SkippableVideoWidget::mousePressEvent(QMouseEvent *event)
{
    player->stop();
    QWidget::mousePressEvent(event);
}

