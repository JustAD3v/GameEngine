# tilemap_scene.py
from PySide6.QtWidgets import QGraphicsScene, QGraphicsPixmapItem
from PySide6.QtGui import QPixmap
from PySide6.QtCore import Qt, QPointF

class TileMapScene(QGraphicsScene):
    def __init__(self, tile_size=32):
        super().__init__()
        self.tile_size = tile_size
        self.active_tile = None  # Tuile sélectionnée
        self.setSceneRect(0, 0, 640, 480)
        self.setBackgroundBrush(Qt.lightGray)

    def set_active_tile(self, pixmap: QPixmap):
        self.active_tile = pixmap

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton and self.active_tile:
            pos = event.scenePos()
            x = int(pos.x() // self.tile_size) * self.tile_size
            y = int(pos.y() // self.tile_size) * self.tile_size

            # Supprimer une tuile existante à cet emplacement
            for item in self.items(QPointF(x + 1, y + 1)):
                if isinstance(item, QGraphicsPixmapItem):
                    self.removeItem(item)

            # Placer la nouvelle tuile
            item = QGraphicsPixmapItem(self.active_tile)
            item.setPos(x, y)
            self.addItem(item)
