#ifndef SKIPPABLEVIDEOWIDGET_H
#define SKIPPABLEVIDEOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QMediaPlayer>

#include <QApplication>

class SkippableVideoWidget : public QWidget
{
    Q_OBJECT

public:
    SkippableVideoWidget(QWidget *parent = nullptr);
    ~SkippableVideoWidget();

public slots:
    void closeOpeningVideo();

signals:
    void end();

protected:
    void mousePressEvent(QMouseEvent *event) override;


private:
    QHBoxLayout *layout;
    QVideoWidget *videoWidget;
    QAudioOutput *audioWidget;
    QMediaPlayer* player;
    
};
#endif // WIDGET_H
