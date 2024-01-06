#ifndef ALL_ALBUMS_CATALOG_H
#define ALL_ALBUMS_CATALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <QToolTip>
#include "user.h"
#include <map>
#include "songCollectionHeaders/album.h"
#include "forms/FormHeaders/albumprofile.h"

namespace Ui {
class AllAlbumsCatalog;
}

class AllAlbumsCatalog : public QDialog
{
    Q_OBJECT

public:

    explicit AllAlbumsCatalog(User* user, QWidget *parent = nullptr);
    ~AllAlbumsCatalog();
    void loadAllAlbumsFromFile();
    void fillAllAlbumsCatalogListWidget();
    bool eventFilter(QObject* object, QEvent* event);
    void openAlbumProfile();
    void printAlbums();

private:
    Ui::AllAlbumsCatalog *ui;
    std::map<QString, Album> allAlbums;
    User* user;
};

#endif // ALL_ALBUMS_CATALOG_H
