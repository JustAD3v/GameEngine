#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ImportWindow.h"
#include "TileMapScene.h"
#include "TilePalette.h"
#include <QAction>
#include <QGraphicsView>
#include <QList>
#include <QMainWindow>
#include <QMenu>
#include <QPoint>
#include <QToolBar>
#include <memory>
#include <optional>
#include <qboxlayout.h>
#include <qwidget.h>

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow();
    //~MainWindow();

  private:
    // #ifndef QT_NO_CONTEXTMENU
    //     void contextMenuEvent(QContextMenuEvent *event) override;
    // #endif // QT_NO_CONTEXTMENU
    // méthodes privées
    void newFile();
    void open();
    int saveTileMap();
    void launchImportWindow();
    void endImport(QList<std::shared_ptr<QPixmap>> tile_images, int tile_size);
    // attributs privés
    QMenu *fileMenu;
    QAction newAct;
    QAction openAct;
    QAction saveAct;
    std::optional<QPoint> mainWPos;
    std::unique_ptr<ImportWindow> impW;
    QGraphicsView *view;
    TileMapScene *scene;
    TilePalette *palette;
    QScrollArea *scrollPalette;
    QWidget *window;
    QHBoxLayout *layout;
};

#endif
