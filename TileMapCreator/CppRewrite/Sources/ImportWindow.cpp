#include "ImportWindow.h"

#include <QObject>
#include <QWidget>
#include <iostream>
#include <optional>
#include <qcombobox.h>
#include <qpixmap.h>
#include <qpushbutton.h>

#include <QFileDialog>
#include <qvarlengtharray.h>

ImportWindow::ImportWindow()
    : image_pixmap(std::nullopt), tiles({}), main_layout(QVBoxLayout(this)),
      import_button(QPushButton(tr("&Choose a file"))), size_selector(),
      cut_button("Cut"), label_image(tr("No image loaded")) {
    setWindowTitle(tr("Import tilesheet"));

    connect(&import_button, &QPushButton::clicked, this,
            &ImportWindow::import_file);
    main_layout.addWidget(&import_button);
    size_label.setText("Select tile size");
    size_label.setAlignment(Qt::AlignCenter);
    main_layout.addWidget(&size_label);

    size_selector.addItem("16x16", 16);
    size_selector.addItem("32x32", 32);
    size_selector.addItem("48x48", 48);
    main_layout.addWidget(&size_selector);

    connect(&cut_button, &QPushButton::clicked, this, &ImportWindow::cut_image);
    main_layout.addWidget(&cut_button);

    main_layout.addWidget(&label_image);
}

int ImportWindow::import_file() {
    file_path = QFileDialog::getOpenFileName(this, tr("&Choose a file"), "",
                                             "Images (*.png)");
    if (!file_path.isEmpty()) {
        image_pixmap = std::make_optional<QPixmap>(file_path);
        if (image_pixmap->isNull()) {
            std::cerr << "Erreur : impossible de charger l'image" << std::endl;
            return -1;
        } else {
            label_image.setPixmap(image_pixmap.value());
            label_image.setFixedSize(image_pixmap->size());
        }
    }
    return 0;
}

int ImportWindow::cut_image() {
    if (!file_path.isEmpty()) {
        tiles = {};
        int index = size_selector.currentIndex();
        tile_size = size_selector.itemData(index);
        int col_size = image_pixmap->height() / tile_size.toInt();
        int row_size = image_pixmap->width() / tile_size.toInt();

        // tiles.reserve(col_size * row_size);
        for (int i = 0; i < row_size; i++) {
            for (int j = 0; j < col_size; j++) {
                tiles.push_back(std::make_shared<QPixmap>(image_pixmap->copy(
                    i * tile_size.toInt(), j * tile_size.toInt(),
                    tile_size.toInt(), tile_size.toInt())));
            }
        }
        emit image_cut_sig(tiles, tile_size.toInt());
    } else {
        std::cerr << "No tiles !" << std::endl;
        return 0;
    }

    return 0;
}