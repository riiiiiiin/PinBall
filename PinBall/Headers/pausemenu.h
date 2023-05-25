#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QStyleOption>
#include <QtMultimedia>
#include <QKeyEvent>
#include <vector>

#include "exitconfirm.h"
#include "mcheckbutton.h"
#include "mpushbutton.h"


class PauseMenu : public QDialog
{
    Q_OBJECT

public:
    explicit PauseMenu(std::vector<QSoundEffect*> se,QSoundEffect* msc,QWidget *parent = nullptr);
    ~PauseMenu();
private:
    QSoundEffect* _music;
    ExitConfirm* _exc;
    QLabel* _title;
    QLabel* _white_bar;
    std::vector<QSoundEffect*> _sound_effects;
    std::vector<MCheckButton*> _check_buttons;
    std::vector<MPushButton*> _push_buttons;
signals:
    void closed();
    void exitRequest();
protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_resumeButtonClicked();
    void on_exitButtonClicked();
    void on_seMuteButtonClicked(bool checked);
    void on_musicMuteButtonClicked(bool checked);
    void on_exitRequested();
    void on_ExitConfirmClosed();
};

#endif // PAUSEMENU_H
