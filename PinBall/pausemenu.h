#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDialog>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QStyleOption>
#include <QtMultimedia>
#include <vector>

#include "exitconfirm.h"
#include "mcheckbutton.h"
#include "mpushbutton.h"

namespace Ui {
class PauseMenu;
}

class PauseMenu : public QDialog
{
    Q_OBJECT

public:
    explicit PauseMenu(std::vector<QSoundEffect*> se,QWidget *parent = nullptr,QApplication* app = nullptr,QSoundEffect* msc=nullptr);
    ~PauseMenu();
private:
    Ui::PauseMenu *ui;
    QApplication* _app;
    QSoundEffect* _music;
    std::vector<QSoundEffect*> _sound_effects;
    std::vector<MCheckButton*> _check_buttons;
    std::vector<MPushButton*> _push_buttons;
signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_resumeButtonClicked();
    void on_exitButtonClicked();
    void on_seMuteButtonClicked(bool checked);
    void on_musicMuteButtonClicked(bool checked);
};

#endif // PAUSEMENU_H
