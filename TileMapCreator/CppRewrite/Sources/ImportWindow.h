#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QList>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <optional>
#include <qpushbutton.h>
#include <qscrollarea.h>

class ImportWindow : public QWidget {
    Q_OBJECT

  public:
    ImportWindow();
    int import_file();
    int cut_image();

  private:
    QVBoxLayout main_layout;
    QLabel size_label;
    QPushButton import_button;
    QPushButton cut_button;
    QComboBox size_selector;
    QLabel label_image;
    std::optional<QPixmap> image_pixmap;
    QString file_path;
    QList<std::shared_ptr<QPixmap>> tiles;
    QVariant tile_size;

  signals:
    void image_cut_sig(QList<std::shared_ptr<QPixmap>> tiles, int tile_size);
};

#endif
