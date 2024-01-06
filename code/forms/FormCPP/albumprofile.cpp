#include "forms/FormHeaders/albumprofile.h"
#include "ui_albumprofile.h"

AlbumProfile::AlbumProfile(User* user, Album album, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumProfile)
{
    ui->setupUi(this);
    this->setFixedSize(363, 736);
    this->setWindowTitle("Album Profile");
    this->user = new User();
    this->user = user;
    this->album = album;
    ui->albumTitle->setText(this->album.getTitle());
    ui->albumAuthor->setText(this->album.getAuthor());
    ui->albumGenre->setText(this->album.getGenre());
    ui->albumReleaseDate->setText(this->album.getReleaseDate());
    fillSongsListWidget();
    openSongProfile();

    QString imagePath = "D:\\My projects\\Qt projects\\MyTempo\\Resources\\album cover\\" + ui->albumTitle->text() + ".jpg";
    if (QFile::exists(imagePath)) {
        QPixmap albumPixmap(imagePath);
        ui->albumCover->setPixmap(albumPixmap.scaled(ui->albumCover->size(), Qt::KeepAspectRatio));
    } else {
        ui->albumCover->setText("Image not found");
    }
}

AlbumProfile::~AlbumProfile()
{
    delete ui;
}

void AlbumProfile::openSongProfile() {
    connect(ui->SongsListWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
        if (item) {
            QString fullTitle = item->text();
            QStringList parts = fullTitle.split(". ");
            if (parts.size() > 1) {
                QString titleWithoutNumber = parts[1];
                Song song(this->user->getUsername(), titleWithoutNumber, this->album.getAuthor(), this->album.getReleaseDate(), this->album.getGenre());
                SongProfile* songProfile = new SongProfile(this->user, song, this);
                songProfile->exec();
            }
        }
    });
}

void AlbumProfile::fillSongsListWidget() {

    //album.viewSongs();
    if(!album.getSongs().isEmpty()) {
        Ring<Song>::Iterator it = album.songsBeginning();
        int songNumber = 1;
        do {
            QString songTitle = it.current->data.getTitle();
            QListWidgetItem* item = new QListWidgetItem(QString("%1. %2")
                                                            .arg(songNumber)
                                                            .arg(songTitle));
            ui->SongsListWidget->addItem(item);
            ++songNumber;
            it++;
        } while(it != album.songsBeginning());
    }
}
