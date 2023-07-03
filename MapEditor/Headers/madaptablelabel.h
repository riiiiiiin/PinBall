#ifndef MADAPTABLELABEL_H
#define MADAPTABLELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>

class MAdaptableLabel : public QLabel
{
public:
    MAdaptableLabel(QWidget *parent = nullptr);

    void setPixMap(const QPixmap &pixmap);

    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap _Pixmap;
    QPixmap _Mask;

    void updatePixmap();
};

#endif