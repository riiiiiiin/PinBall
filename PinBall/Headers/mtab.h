#ifndef MTAB_H
#define MTAB_H

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

class MTab : public QDialog
{
    Q_OBJECT

protected:
    QLabel *_title;
    QLabel *_white_bar;
    std::vector<MButton *> _buttons;

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void closed();
    void exitRequest();

protected slots:

public:
    explicit MTab(QWidget *parent = nullptr);
    virtual ~MTab();
};

#endif