#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "mtab.h"

class PauseMenu : public MTab
{
    Q_OBJECT

public:
    explicit PauseMenu(QList<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent = nullptr);
    ~PauseMenu();
    void setSounds(QSoundEffect*,QList<QSoundEffect*>);
    void setButtons();
private:
    QSoundEffect *_music;
    ExitConfirm *_exc;
    QList<QSoundEffect *> _sound_effects;
signals:

protected:
private slots:
    void on_resumeButtonClicked();
    void on_exitButtonClicked();
    void on_seMuteButtonClicked(bool checked);
    void on_musicMuteButtonClicked(bool checked);
    void on_exitRequested();
    void on_exitConfirmClosed();
};

#endif // PAUSEMENU_H
