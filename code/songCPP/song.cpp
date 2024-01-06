#include "songHeaders/song.h"

Song::Song() : MusicalComposition(nullptr, nullptr, nullptr, nullptr), genre() {}
Song::Song(QString username, QString title, QString author,
           QString releaseDate, QString genre)
    : MusicalComposition(username, title, author, releaseDate), genre(genre) {}
Song::Song(const Song& other)
    : MusicalComposition(other), genre(other.genre) {}
Song::Song(Song&& other) noexcept
    : MusicalComposition(std::move(other)), genre(std::move(other.genre)) {}
Song::~Song() {}
void Song::setGenre(const QString& genre) {
    this->genre = genre;
}
QString Song::getGenre() const {
    return this->genre;
}
bool Song::compareGenre(const Song& a, const Song& b) {
    return const_cast<Song&>(a).getGenre() < const_cast<Song&>(b).getGenre();
}
std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << static_cast<const MusicalComposition&>(song) << '|'
       << song.genre.toStdString();
    return os;
}
std::istream& operator>>(std::istream& is, Song& song) {
    MusicalComposition& baseSong = song;
    is >> baseSong;
    std::string genre;
    std::getline(is, genre, '|');
    song.setGenre(QString::fromStdString(genre));
    return is;
}
bool Song::operator ==(const Song& other) {
    return MusicalComposition::operator==(other) && genre == other.genre;
}
bool Song::operator !=(const Song& other) {
    return !(*this == other);
}
bool Song::operator>(const Song& other) const {
    const MusicalComposition& thisAsBase = *this;
    const MusicalComposition& otherAsBase = other;
    if (thisAsBase > otherAsBase) return true;
    else if (thisAsBase == otherAsBase && genre > other.genre) return true;
    return false;
}
bool Song::operator<(const Song& other) const {
    return !(other > *this);
}
Song& Song::operator=(const Song& other) {
    if (this != &other) {
        MusicalComposition::operator=(other);
        genre = other.genre;
    }
    return *this;
}
Song& Song::operator=(Song&& other) noexcept {
    if (this != &other) {
        MusicalComposition::operator=(std::move(other));
        genre = std::move(other.genre);
    }
    return *this;
}
