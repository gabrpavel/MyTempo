#include "songCollectionHeaders/playlist.h"

Playlist::Playlist() {}
Playlist::Playlist(QString username, QString title, QString author,
                   QString releaseDate, QString curator)
    : SongCollection(username, title, author, releaseDate), curator(curator){}
Playlist::Playlist(const Playlist& other)
    : SongCollection(other), curator(other.curator) {
}
Playlist::Playlist(Playlist&& other) noexcept
    : SongCollection(std::move(other)), curator(std::move(other.curator)) {
}
void Playlist::setCurator(const QString& curator) {
    this->curator = curator;
}
QString Playlist::getCurator() const {
    return curator;
}
Ring<Song>& Playlist::getPlaylistSongs() {
    return this->getSongsADRESS();
}
void Playlist::fillPlaylist(QString curator, char* fileName) {
    this->loadSongsFromFile(curator, fileName);
}
void Playlist::addSongToPlaylist(Song song) {
    this->addSong(song);
}
bool Playlist::operator==(const Playlist& other) const {
    return static_cast<const SongCollection&>(*this) ==
               static_cast<const SongCollection&>(other) &&
           curator == other.curator;
}
bool Playlist::operator!=(const Playlist& other) const {
    return !(*this == other);
}
bool Playlist::operator>(const Playlist& other) const {
    if (static_cast<const SongCollection&>(*this) !=
        static_cast<const SongCollection&>(other)) {
        return static_cast<const SongCollection&>(*this) >
               static_cast<const SongCollection&>(other);
    } else {
        return curator > other.curator;
    }
}
bool Playlist::operator<(const Playlist& other) const {
    return !(other > *this);
}
Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        static_cast<SongCollection&>(*this) = other;
        curator = other.curator;
    }
    return *this;
}
Playlist& Playlist::operator=(Playlist&& other) noexcept {
    if (this != &other) {
        static_cast<SongCollection&>(*this) = std::move(other);
        curator = std::move(other.curator);
    }
    return *this;
}
