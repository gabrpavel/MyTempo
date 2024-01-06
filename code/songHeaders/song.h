#ifndef SONG_H
#define SONG_H

#include "musicalcomposition.h"

class Song : public MusicalComposition {

private:

    QString genre;

public:

    Song();
    Song(QString username, QString title, QString author,
         QString releaseDate, QString genre);
    Song(const Song& other);
    Song(Song&& other) noexcept;
    ~Song();

    void setGenre(const QString& genre);
    QString getGenre() const;
    static bool compareGenre(const Song& a, const Song& b);

    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    friend std::istream& operator>>(std::istream& is, Song& song);
    bool operator ==(const Song& other);
    bool operator !=(const Song& other);
    bool operator>(const Song& other) const;
    bool operator<(const Song& other) const;
    Song& operator=(const Song& other);
    Song& operator=(Song&& other) noexcept;
};

#endif // SONG_H
