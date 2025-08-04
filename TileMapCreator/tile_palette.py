# tile_palette.py
from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel, QScrollArea
from PySide6.QtGui import QPixmap, QMouseEvent
from PySide6.QtCore import Qt, Signal

class TilePalette(QWidget):
    tile_selected_sig = Signal(QPixmap)

    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.tiles = []

        self.update_tilepalette()


    def update_tilepalette(self):
        for t in self.tiles:
            self.layout.addWidget(t)

    def select_tile(self, pixmap):
        self.tile_selected_sig.emit(pixmap)

    def add_tiles(self, tile_images):
        for t in tile_images:
            tile = ClickableTile(t)
            tile.clicked_sig.connect(self.select_tile)
            self.tiles.append(tile)
        self.update_tilepalette()
            


class ClickableTile(QLabel):
    clicked_sig = Signal(QPixmap)

    def __init__(self, pixmap):
        super().__init__()
        self.setPixmap(pixmap)
        self.setFixedSize(pixmap.size())

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.clicked_sig.emit(self.pixmap())
