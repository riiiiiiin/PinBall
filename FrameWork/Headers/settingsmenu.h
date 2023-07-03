#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "UI_Base/Headers/mtab.h"

class SettingsMenu : public MTab{
    Q_OBJECT
private:
    QSoundEffect* _music;
    ExitConfirm *_exc;
    QVector<QSoundEffect*> _sound_effects;
    int _gravity_rate;
    double const _default_gravity;
protected:
public:
    explicit SettingsMenu(int gravity,QVector<QSoundEffect*> se,QSoundEffect *msc,QWidget*parent=nullptr);
    ~SettingsMenu();
    void setSounds(QSoundEffect*,QVector<QSoundEffect*>);
    void setButtons();
signals:
    void resetMapRequest();
    void gravityChange(int);
private slots:
    void on_resumeButtonClicked();
    void on_exitButtonClicked();

    void on_seMuteButtonClicked(bool checked);
    void on_musicMuteButtonClicked(bool checked);

    void on_exitRequested();
    void on_exitConfirmClosed();

    void on_sliderNumberChange(int);
    void on_resetMapRequested();
};


#endif