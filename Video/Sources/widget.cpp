#include "Video/Headers/widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QHBoxLayout>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QTransform>

class CustomVideoWidget : public QVideoWidget
{
    //    Q_OBJECT
public:
    CustomVideoWidget() : QVideoWidget() {}

signals:
    void clicked() {}
    void end() {}

public:
    void mousePressEvent(QMouseEvent *event) override
    {
        QWidget::mousePressEvent(event);
        emit clicked();
        // 发送clicked信号
    }
};

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setGeometry(0, 0, 950, 535);
    player = new QMediaPlayer;
    player->setSource(QUrl("qrc:/new/prefix1/opening.mp4"));

    videoWidget = new CustomVideoWidget;
    audioWidget = new QAudioOutput;
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioWidget);

    layout = new QHBoxLayout(this);
    layout->addWidget(videoWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 设置布局的边缘

    // set up the signal to close the player after the video end, qt version = 6.5.1
    player->play();
    connect(player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(closeOpeningVideo()));
    // press any part of the window to close the video
    connect(this, SIGNAL(clicked()), this, SLOT(closeOpeningVideo()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeOpeningVideo()
{
    if (videoWidget == nullptr)
        return;
    layout->removeWidget(videoWidget);
    delete videoWidget;
    videoWidget = nullptr;
    delete audioWidget;
    audioWidget = nullptr;
    emit end();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

   // 发送clicked信号
//    emit end();
    emit clicked();
}

//void Widget::gameBegin()
//{
//    emit end();
//}
