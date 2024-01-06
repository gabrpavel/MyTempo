#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "songCollectionHeaders/songcollection.h"

class Playlist : public SongCollection {

private:

    QString curator;

public:

    Playlist();
    Playlist(QString username, QString title, QString author,
             QString releaseDate, QString curator);
    Playlist(const Playlist& other);
    Playlist(Playlist&& other) noexcept;

    void setCurator(const QString& username);
    QString getCurator() const;
    Ring<Song>& getPlaylistSongs();
    void fillPlaylist(QString curator, char* fileName);
    void addSongToPlaylist(Song song);

    bool operator==(const Playlist& other) const;
    bool operator!=(const Playlist& other) const;
    bool operator>(const Playlist& other) const;
    bool operator<(const Playlist& other) const;
    Playlist& operator=(const Playlist& other);
    Playlist& operator=(Playlist&& other) noexcept;
};

#endif // PLAYLIST_H
