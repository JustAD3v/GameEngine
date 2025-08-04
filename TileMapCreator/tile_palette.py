# tile_palette.py
from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel
from PySide6.QtGui import QPixmap, QMouseEvent
from PySide6.QtCore import Qt, Signal

class TilePalette(QWidget):
    tile_selected_sig = Signal(QPixmap)

    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.setLayout(layout)

        # Exemple : deux tuiles (bleu et rouge)
        self.tiles = []

        for color in [Qt.blue, Qt.red]:
            pixmap = QPixmap(32, 32)
            pixmap.fill(color)
            label = ClickableTile(pixmap)
            label.clicked_sig.connect(self.select_tile)
            layout.addWidget(label)
            self.tiles.append(label)

    def select_tile(self, pixmap):
        self.tile_selected_sig.emit(pixmap)

class ClickableTile(QLabel):
    clicked_sig = Signal(QPixmap)

    def __init__(self, pixmap):
        super().__init__()
        self.setPixmap(pixmap)
        self.setFixedSize(pixmap.size())

    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.LeftButton:
            self.clicked_sig.emit(self.pixmap())
