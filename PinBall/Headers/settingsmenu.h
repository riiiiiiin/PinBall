#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "mtab.h"

class SettingsMenu : public MTab{
    Q_OBJECT
private:
    QSoundEffect* _music;
    ExitConfirm *_exc;
    QList<QSoundEffect*> _sound_effects;
    int _gravity;
protected:
public:
    explicit SettingsMenu(int gravity,QList<QSoundEffect*> se,QSoundEffect *msc,QWidget*parent=nullptr);
    ~SettingsMenu();
    void setSounds(QSoundEffect*,QList<QSoundEffect*>);
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