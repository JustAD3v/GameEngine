#include "MainWindow.h"
#include <QApplication>
#include <QPushButton>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
#ifdef MAP
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HugoBR");
    QCoreApplication::setApplicationName("Tile Map Creator");
    QCoreApplication::setApplicationVersion("0.0.1");
    MainWindow w;
    w.show();
    return a.exec();
}
