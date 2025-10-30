#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <QGraphicsScene>
#include <QMouseEvent>
#include <qpixmap.h>

class TileMapScene : public QGraphicsScene {
    Q_OBJECT
  public:
    TileMapScene(int tile_size = 32);

    void set_active_tile(QPixmap selected_tile);
    void set_tile_size(int t);

  private:
    int tile_size;
    QPixmap active_tile;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif