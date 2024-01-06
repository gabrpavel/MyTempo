#ifndef ALL_SONGS_CATALOG_H
#define ALL_SONGS_CATALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QListWidget>
#include <QEvent>
#include <QToolTip>
#include <QListWidgetItem>
#include <QDateTime>

#include "songprofile.h"

namespace Ui {
class AllSongsCatalog;
}

class AllSongsCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit AllSongsCatalog(User* user, QWidget *parent = nullptr);
    ~AllSongsCatalog();
    void loadAllSongsFromFile();
    void fillAllSongsCatalogListWidget(Ring<Song>& songs);
    bool eventFilter(QObject* object, QEvent* event);
    void openSongProfile();

private:
    Ui::AllSongsCatalog *ui;
    User* user;
    SongCollection allSongs;
private slots:
    void sorting(int index);
    void onSearchTextChanged(const QString& searchText);
};

#endif // ALL_SONGS_CATALOG_H
