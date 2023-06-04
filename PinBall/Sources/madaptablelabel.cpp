#include "Headers/madaptablelabel.h"

MAdaptableLabel::MAdaptableLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
}

void MAdaptableLabel::setPixMap(const QPixmap &pixmap)
{
    _Pixmap = pixmap;
    _Mask = pixmap.mask();
    updatePixmap();
}

void MAdaptableLabel::resizeEvent(QResizeEvent *event)
{
    updatePixmap();
    QLabel::resizeEvent(event);
}

void MAdaptableLabel::updatePixmap()
{
    if (_Pixmap.isNull() || _Mask.isNull())
        return;

    QPixmap scaledPixmap = _Pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap scaledMask = _Mask.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap maskedPixmap(size());
    maskedPixmap.fill(Qt::transparent);
    
    QPainter painter(&maskedPixmap);
    painter.drawPixmap((width() - scaledMask.width()) / 2, (height() - scaledMask.height()) / 2, scaledMask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap((width() - scaledPixmap.width()) / 2, (height() - scaledPixmap.height()) / 2, scaledPixmap);
    painter.end();

    QLabel::setPixmap(maskedPixmap);
    QLabel::setMask(maskedPixmap.mask());
}
