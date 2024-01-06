#ifndef USER_SONGS_H
#define USER_SONGS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QListWidget>
#include <QEvent>
#include <QToolTip>

#include "user.h"
#include "songprofile.h"


namespace Ui {
class UserSongs;
}

class UserSongs : public QDialog
{
    Q_OBJECT

public:
    explicit UserSongs(User* user, QWidget *parent = nullptr);
    ~UserSongs();
    void fillUserSongsListWidget(Ring<Song>& songs);
    void openSongProfile();
    void setUsername(const QString& username);
    bool eventFilter(QObject* object, QEvent* event);

private:
    Ui::UserSongs *ui;
    User* user;

private slots:
    void sorting(int index);
    void onSearchTextChanged(const QString& searchText);
};

#endif // USER_SONGS_H
