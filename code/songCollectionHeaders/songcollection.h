#ifndef SONGCOLLECTION_H
#define SONGCOLLECTION_H

#include "musicalcomposition.h"
#include "songHeaders/song.h"
#include "D:\My projects\Ring\Ring\Ring.h"
#include "D:\My projects\Ring\Ring\Algorithm.h"

class SongCollection : public MusicalComposition {

private:

    Ring<Song> songs;

public:

    SongCollection();
    SongCollection(QString username, QString title, QString author, QString releaseDate);
    SongCollection(const SongCollection& other);
    SongCollection(SongCollection&& other) noexcept;

    void setSongs(const Ring<Song> songs);
    Ring<Song> getSongs() const;
    Ring<Song>& getSongsADRESS();

    void loadSongsFromFile(QString target, char* fileName);
    void viewSongs();
    void addSong(Song song);
    Ring<Song>::Iterator songsBeginning();

    bool operator==(const SongCollection& other) const;
    bool operator!=(const SongCollection& other) const;
    bool operator>(const SongCollection& other) const;
    bool operator<(const SongCollection& other) const;
    SongCollection& operator=(const SongCollection& other);
    SongCollection& operator=(SongCollection&& other) noexcept;
};
#endif // SONGCOLLECTION_H
