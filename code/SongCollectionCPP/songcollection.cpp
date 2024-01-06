#include "songCollectionHeaders/songcollection.h"

SongCollection::SongCollection() {}
SongCollection::SongCollection(QString username, QString title,
                               QString author, QString releaseDate)
    : MusicalComposition(username, title, author, releaseDate) {}
SongCollection::SongCollection(const SongCollection& other)
    : MusicalComposition(other), songs(other.songs) {
}
SongCollection::SongCollection(SongCollection&& other) noexcept
    : MusicalComposition(std::move(other)), songs(std::move(other.songs)) {
}
void SongCollection::setSongs(const Ring<Song> songs) {
    this->songs = songs;
}
Ring<Song> SongCollection::getSongs() const {
    return this->songs;
}
Ring<Song>& SongCollection::getSongsADRESS() {
    return songs;
}
bool SongCollection::operator==(const SongCollection& other) const {
    return static_cast<const MusicalComposition&>(*this) ==
           static_cast<const MusicalComposition&>(other);
}
bool SongCollection::operator!=(const SongCollection& other) const {
    return !(*this == other);
}
bool SongCollection::operator>(const SongCollection& other) const {
    return static_cast<const MusicalComposition&>(*this) >
           static_cast<const MusicalComposition&>(other);
}
bool SongCollection::operator<(const SongCollection& other) const {
    return static_cast<const MusicalComposition&>(*this) <
           static_cast<const MusicalComposition&>(other);
}
SongCollection& SongCollection::operator=(const SongCollection& other) {
    if (this != &other) {
        static_cast<MusicalComposition&>(*this) =
            static_cast<const MusicalComposition&>(other);
        songs = other.songs;
    }
    return *this;
}
SongCollection& SongCollection::operator=(SongCollection&& other) noexcept {
    if (this != &other) {
        static_cast<MusicalComposition&>(*this) =
            std::move(static_cast<MusicalComposition&>(other));
        songs = std::move(other.songs);
    }
    return *this;
}
void SongCollection::loadSongsFromFile(QString target, char* fileName) {
    Algorithm<Song>::loadFromFile(this->songs, fileName, target.toStdString());
}
void SongCollection::viewSongs() {
    std::cout << this->songs;
}
void SongCollection::addSong(Song song) {
    this->songs.push(song);
}
Ring<Song>::Iterator SongCollection::songsBeginning() {
    return songs.begin();
}
