#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QAudioOutput>
#include <QVideoWidget>

#include <QApplication>

//#include "FrameWork/Headers/mainwindow.h"

class QMediaPlayer;
class QVideoWidget;


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE




class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QHBoxLayout *layout;
    QVideoWidget *videoWidget;
    QAudioOutput *audioWidget;
    QMediaPlayer* player;
    void mousePressEvent(QMouseEvent *event) override;
    void gameBegin();
public slots:
    void closeOpeningVideo();

signals:
    void clicked();
    void end();



private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
