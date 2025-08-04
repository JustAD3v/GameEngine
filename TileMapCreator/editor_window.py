from PySide6.QtWidgets import *
from PySide6.QtGui import QPixmap, QTransform
from PySide6.QtCore import QRect, Qt, Signal
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

        menu_bar = QWidget()
        menu_layout = QHBoxLayout()
        menu_bar.setLayout(menu_layout)

        bouton_import = QPushButton("Import")
        bouton_import.clicked.connect(self.import_window)
        menu_layout.addWidget(bouton_import)

        bouton_save = QPushButton("Save")
        bouton_save.clicked.connect(self.save)
        menu_layout.addWidget(bouton_save)


        main_layout = QVBoxLayout(self)
        main_layout.addWidget(menu_bar)

        content_layout = QHBoxLayout()
        scrollPalette = QScrollArea()
        scrollPalette.setWidgetResizable(True)
        scrollPalette.setWidget(self.palette)
        content_layout.addWidget(scrollPalette)
        content_layout.addWidget(self.view)
        main_layout.addLayout(content_layout)

    def import_window(self):
        print("Opening a new popup window...")
        self.imp_w = ImportWindow()
        self.imp_w.setGeometry(QRect(100, 100, 400, 200))
        main_pos = self.pos()
        print(main_pos)
        self.imp_w.setGeometry(main_pos.x() + 100, main_pos.y() + 100, 400, 200)
        self.imp_w.image_cut_sig.connect(self.end_of_import)
        self.imp_w.show()

    def save(self):
        print("saving tilemap...")

    def end_of_import(self, tile_images, tileSize):
        self.scene.tile_size = tileSize
        self.palette.add_tiles(tile_images)

class ImportWindow(QWidget):
    image_cut_sig = Signal(list, int)

    def __init__(self):
        super().__init__()

        self.imagePixmap = None
        self.Tiles = None

        self.setWindowTitle("Import tilesheet")
        main_layout = QVBoxLayout(self)

        import_button = QPushButton("choose a file")
        import_button.clicked.connect(self.import_file)
        main_layout.addWidget(import_button)

        size_label = QLabel()
        size_label.setText("<b>Select tile size</b>")
        size_label.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(size_label)

        self.size_selector = QComboBox()
        self.size_selector.addItem("16x16", 16)
        self.size_selector.addItem("32x32", 32)
        self.size_selector.addItem("48x48", 48)
        main_layout.addWidget(self.size_selector)

        cut_button = QPushButton("Cut")
        cut_button.clicked.connect(self.cut_image)
        main_layout.addWidget(cut_button)

        self.label_image = QLabel("No image loaded")
        main_layout.addWidget(self.label_image)


    def import_file(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Choose a file",
            "",
            "Images (*.png)"
        )

        if file_path:
            self.imagePixmap = QPixmap(file_path)
            if self.imagePixmap.isNull():
                print("Erreur : impossible de charger l'image")
                return

            self.label_image.setPixmap(self.imagePixmap)
            self.label_image.setFixedSize(self.imagePixmap.size())

    def cut_image(self):
        if self.imagePixmap:
            self.tiles = []
            index = self.size_selector.currentIndex()
            self.tileSize = self.size_selector.itemData(index)
            colSize = int(self.imagePixmap.height()//self.tileSize)
            rowSize = int(self.imagePixmap.width()//self.tileSize)

            for i in range(rowSize):
                for j in range(colSize):
                    self.tiles.append(self.imagePixmap.copy(i*self.tileSize, j*self.tileSize, self.tileSize, self.tileSize))

            self.image_cut_sig.emit(self.tiles, self.tileSize)