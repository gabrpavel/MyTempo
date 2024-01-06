#include "forms/FormHeaders/mytempo.h"
#include "ui_mytempo.h"
#include "forms/FormHeaders/all_songs_catalog.h"
#include "forms/FormHeaders/user_songs.h"
#include "forms/FormHeaders/all_albums_catalog.h"

MyTempo::MyTempo(const QString& username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyTempo) {
    ui->setupUi(this);
    this->setFixedSize(337, 469);
    this->user = new User();
    this->user->setUsername(username);
    this->user->fillAddedSongs();
    this->user->loadReviewsFromFile();
}
MyTempo::~MyTempo() {
    delete ui;
}
void MyTempo::on_exit_Button_clicked() {
    this->close();
}
void MyTempo::on_all_songs_Button_clicked(){
    AllSongsCatalog* allSongsCatalog = new AllSongsCatalog(this->user, this);
    allSongsCatalog->setModal(1);
    allSongsCatalog->show();
}
void MyTempo::on_my_catalog_Button_clicked() {
    if(user->getRingSong().isEmpty())
        QMessageBox::warning(this, "My songs catalog", "You don't have any songs");
    else {
        UserSongs* userSongs = new UserSongs(this->user, this);
        userSongs->setModal(1);
        userSongs->show();
    }
}
void MyTempo::on_all_albums_Button_clicked() {
    AllAlbumsCatalog* allAlbumsCatalog = new AllAlbumsCatalog(this->user, this);
    allAlbumsCatalog->setModal(1);
    allAlbumsCatalog->show();
}

