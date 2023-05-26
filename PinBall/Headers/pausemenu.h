#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "mtab.h"

class PauseMenu : public MTab
{
    Q_OBJECT

public:
    explicit PauseMenu(std::vector<QSoundEffect *> se, QSoundEffect *msc, QWidget *parent = nullptr);
    ~PauseMenu();

private:
    QSoundEffect *_music;
    ExitConfirm *_exc;
    std::vector<QSoundEffect *> _sound_effects;
signals:

protected:
private slots:
    void on_resumeButtonClicked();
    void on_exitButtonClicked();
    void on_seMuteButtonClicked(bool checked);
    void on_musicMuteButtonClicked(bool checked);
    void on_exitRequested();
    void on_ExitConfirmClosed();
};

#endif // PAUSEMENU_H
