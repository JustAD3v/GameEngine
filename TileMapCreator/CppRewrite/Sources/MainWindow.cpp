// The main window of the App

#include "MainWindow.h"
#include "ImportWindow.h"
#include "TileMapScene.h"
#include "TilePalette.h"
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <iostream>
#include <optional>
#include <qboxlayout.h>
#include <qmainwindow.h>
#include <qpixmap.h>
#include <qscrollarea.h>
#include <qwindowdefs.h>
#include <spdlog/spdlog.h>

MainWindow::MainWindow()
    : newAct(tr("&New"), this), openAct(tr("&Open"), this),
      saveAct(tr("&Save"), this) {

    spdlog::debug("Creating main window...");
    scene = new TileMapScene(32);
    scene->setParent(this);
    view = new QGraphicsView(scene, this);
    QObject::connect(&newAct, &QAction::triggered, this, &MainWindow::newFile);
    QObject::connect(&openAct, &QAction::triggered, this,
                     &MainWindow::launchImportWindow);
    QObject::connect(&saveAct, &QAction::triggered, this,
                     &MainWindow::saveTileMap);

    window = new QWidget(this);
    layout = new QHBoxLayout(window);
    scrollPalette = new QScrollArea(this);
    palette = new TilePalette();
    palette->setParent(scrollPalette);

    setWindowTitle("TileMap Editor");

    window->setLayout(layout);

    scrollPalette->setWidgetResizable(true);
    scrollPalette->setWidget(palette);
    layout->addWidget(scrollPalette);
    layout->addWidget(view);
    connect(palette, &TilePalette::tile_selected_sig, scene,
            &TileMapScene::set_active_tile);

    // std::cout << "Appel à la création de la classe" << std::endl;

    setCentralWidget(window);
    // Create the menu with MainWindow as parent, then add it to the menubar.
    fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(&newAct);
    fileMenu->addAction(&openAct);
    fileMenu->addAction(&saveAct);
}

void MainWindow::newFile() { std::cout << "Coucou 1" << std::endl; }
void MainWindow::open() { std::cout << "Coucou 2" << std::endl; }

void MainWindow::launchImportWindow() {

    impW = std::make_unique<ImportWindow>();
    impW->setGeometry(QRect(100, 100, 400, 200));
    mainWPos = pos();
    impW->setGeometry(mainWPos->x() + 100, mainWPos->y() + 100, 400, 200);
    connect(impW.get(), &ImportWindow::image_cut_sig, this,
            &MainWindow::endImport);
    impW->show();
}
int MainWindow::saveTileMap() {
    spdlog::info("Saving tilemap...");
    return 0;
};
void MainWindow::endImport(QList<std::shared_ptr<QPixmap>> tile_images,
                           int tile_size) {
    spdlog::debug("Debut de end of import");
    scene->set_tile_size(tile_size);

    palette->add_tiles(tile_images);

    spdlog::debug("End of import.");
}
