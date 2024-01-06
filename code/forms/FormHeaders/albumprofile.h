#ifndef ALBUMPROFILE_H
#define ALBUMPROFILE_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QListWidget>
#include <QEvent>
#include <QToolTip>
#include <QListWidgetItem>
#include "songCollectionHeaders/album.h"
#include "user.h"
#include "songprofile.h"

namespace Ui {
class AlbumProfile;
}

class AlbumProfile : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumProfile(User* user, Album album, QWidget* parent = nullptr);
    ~AlbumProfile();
    void fillSongsListWidget();
    void openSongProfile();

private:
    Ui::AlbumProfile *ui;
    User* user;
    Album album;
};

#endif // ALBUMPROFILE_H
