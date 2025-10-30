#include "TileMapScene.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qnamespace.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <spdlog/spdlog.h>
#include <typeinfo>

TileMapScene::TileMapScene(int tile_size)
    : tile_size(tile_size), active_tile(QPixmap()) {
    setSceneRect(0, 0, 640, 480);
    setBackgroundBrush(Qt::lightGray);
}

void TileMapScene::set_active_tile(QPixmap pixmap) {
    spdlog::debug("Setting active tile...");
    active_tile = pixmap;
    spdlog::debug("Done");
}

void TileMapScene::set_tile_size(int t) { tile_size = t; }

void TileMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        spdlog::debug("Click sur la scene des pixmap avec bouton gauche");
        QPointF pos = event->scenePos();
        int x = ((int)pos.x() / tile_size) * tile_size;
        int y = ((int)pos.y() / tile_size) * tile_size;

        int i = 0;
        while (i < items(QPointF(x + 1, y + 1)).size()) {
            if (typeid(items(QPointF(x + 1, y + 1))[i]) ==
                typeid(QGraphicsPixmapItem)) {
                items(QPointF(x + 1, y + 1)).removeAt(i);
            } else {
                i++;
            }
        }

        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(active_tile);
        item->setPos(x, y);
        addItem(item);
    } else {
        spdlog::debug("Click sur la scene des pixmap");
    }
    QGraphicsScene::mousePressEvent(event);
}
