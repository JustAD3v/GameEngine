#ifndef CLICKABLETILE_H
#define CLICKABLETILE_H

#include <QLabel>
#include <qpixmap.h>

class ClickableTile : public QLabel {
    Q_OBJECT
  public:
    ClickableTile(QPixmap &pixmap);

  private:
    QPixmap own_pixmap;
    void mousePressEvent(QMouseEvent *event) override;

  signals:
    void clicked_sig(QPixmap image);
};

#endif