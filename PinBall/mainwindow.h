
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QApplication>
#include <QGraphicsBlurEffect>
#include <QtMultimedia>

#include "pausemenu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QApplication* app = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e) override;

private slots:
    void on_pauseButton_clicked();
    void on_pauseMenu_closed();

private:
    Ui::MainWindow *ui;
    PauseMenu *pmenu;
    QApplication* main_app;
    QGraphicsBlurEffect *blure;
    std::vector<QSoundEffect*> sound_effects;
    QSoundEffect* music;
    QWidget* m_pMask;
};

#endif // MAINWINDOW_H
