#ifndef ALBUM_H
#define ALBUM_H

#include "songcollection.h"

class Album : public SongCollection {

private:

    QString genre;

public:

    Album();
    Album(QString username, QString title, QString author, QString releaseDate, QString genre);
    Album(const Album& other);
    Album(Album&& other) noexcept;
    ~Album();

    QString getGenre() const;
    void setGenre(const QString& newGenre);

    friend QTextStream& operator>>(QTextStream& stream, Album& album);
    Album& operator=(const Album& other);
    Album& operator=(Album&& other) noexcept;
};

#endif // ALBUM_H
