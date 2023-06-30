#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "UI_Base/Headers/mtab.h"

class PauseMenu : public MTab
{
    Q_OBJECT

public:
    explicit PauseMenu(QVector<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent = nullptr);
    ~PauseMenu();
    void setSounds(QSoundEffect*,QVector<QSoundEffect*>);
    void setButtons();
private:
    QSoundEffect *_music;
    ExitConfirm *_exc;
    QVector<QSoundEffect *> _sound_effects;
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
