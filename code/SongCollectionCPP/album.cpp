#include "songCollectionHeaders/album.h"

Album::Album() {}
Album::Album(QString username, QString title, QString author,
             QString releaseDate, QString genre)
    : SongCollection(username, title, author, releaseDate), genre(genre) {}
Album::Album(const Album& other) : SongCollection(other), genre(other.genre) {}
Album::Album(Album&& other) noexcept : SongCollection(std::move(other)),
    genre(std::move(other.genre)) {}
Album::~Album() {}

QString Album::getGenre() const {
    return genre;
}
void Album::setGenre(const QString& newGenre) {
    genre = newGenre;
}

QTextStream& operator>>(QTextStream& stream, Album& album) {
    QString line = stream.readLine().trimmed();
    QStringList albumInfo = line.split("|");
    if (albumInfo.size() == 4) {
        QString title = albumInfo[0];
        QString author = albumInfo[1];
        QString releaseDate = albumInfo[2];
        QString genre = albumInfo[3];

        album.setTitle(title);
        album.setAuthor(author);
        album.setReleaseDate(releaseDate);
        album.setGenre(genre);

        while (!(line = stream.readLine().trimmed()).startsWith(">")) {
            if (!line.isEmpty()) {
                QString songTitle = line.remove(0, 1);
                Song song("", songTitle, author, releaseDate, genre);
                album.addSong(song);
            }
        }
    }
    return stream;
}

Album& Album::operator=(const Album& other) {
    if (this != &other) {
        SongCollection::operator=(other);
        genre = other.genre;
    }
    return *this;
}

Album& Album::operator=(Album&& other) noexcept {
    if (this != &other) {
        SongCollection::operator=(std::move(other));
        genre = std::move(other.genre);
    }
    return *this;
}
