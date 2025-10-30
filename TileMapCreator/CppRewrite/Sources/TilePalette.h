#ifndef TILEPALETTE_H
#define TILEPALETTE_H

#include "ClickableTile.h"
#include <QList>
#include <QWidget>
#include <memory>
#include <qlayout.h>
#include <qpixmap.h>

class TilePalette : public QWidget {
    Q_OBJECT
  public:
    TilePalette();
    void update_tilepalette();
    void select_tile(QPixmap pixmap);
    void add_tiles(QList<std::shared_ptr<QPixmap>> tile_images);

  private:
    QList<std::shared_ptr<ClickableTile>> tiles;
    QVBoxLayout layout;
  signals:
    void tile_selected_sig(QPixmap selected_tile);
};

#endif