#include "TilePalette.h"
#include "ClickableTile.h"
#include <QWidget>
#include <qpixmap.h>
#include <spdlog/spdlog.h>

TilePalette::TilePalette() : layout() {
    spdlog::debug("creating palette");
    setLayout(&layout);

    update_tilepalette();
}

void TilePalette::update_tilepalette() {
    for (int i = 0; i < tiles.size(); i++) {
        layout.addWidget(tiles[i].get());
    }
}

void TilePalette::select_tile(QPixmap pixmap) {
    emit tile_selected_sig(pixmap);
}

void TilePalette::add_tiles(QList<std::shared_ptr<QPixmap>> tile_images) {

    spdlog::debug("Debut de add tiles");
    for (int i = 0; i < tile_images.size(); i++) {
        spdlog::debug("Ajout d'une tile...");
        tiles.push_back(
            std::make_shared<ClickableTile>(*(tile_images[i].get())));
        connect(tiles[tiles.size() - 1].get(), &ClickableTile::clicked_sig,
                this, &TilePalette::select_tile);
    }
    spdlog::debug("Updating tile palette !");
    update_tilepalette();
}