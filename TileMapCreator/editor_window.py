# editor_window.py
from PySide6.QtWidgets import QWidget, QHBoxLayout, QGraphicsView
from tile_palette import TilePalette
from tilemap_scene import TileMapScene

class EditorWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("TileMap Editor")

        self.scene = TileMapScene()
        self.view = QGraphicsView(self.scene)

        self.palette = TilePalette()
        self.palette.tile_selected_sig.connect(self.scene.set_active_tile)

        layout = QHBoxLayout()
        layout.addWidget(self.palette)
        layout.addWidget(self.view)
        self.setLayout(layout)
