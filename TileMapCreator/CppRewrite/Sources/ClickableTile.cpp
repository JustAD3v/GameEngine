#include "ClickableTile.h"
#include <QMouseEvent>
#include <qnamespace.h>
#include <qpixmap.h>
#include <spdlog/spdlog.h>

ClickableTile::ClickableTile(QPixmap &pixmap) : own_pixmap(pixmap.copy()) {
    setPixmap(own_pixmap);
    setFixedSize(own_pixmap.size());
}

void ClickableTile::mousePressEvent(QMouseEvent *event) {
    spdlog::debug("Mouse event !");
    if (event->button() == Qt::LeftButton) {
        spdlog::debug("type : bouton gauche");
        emit clicked_sig(pixmap());
    }
}