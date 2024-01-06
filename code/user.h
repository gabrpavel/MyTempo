#ifndef USER_H
#define USER_H

#include "review.h"
#include "songCollectionHeaders/playlist.h"
#include <QMessageBox>
#include <QInputDialog>

class User {

public:

    User();
    User(const QString& username);
    User(const User& other);
    User(User&& other) noexcept;
    void setUsername(const QString& username);
    QString getUsername();
    Playlist getAddedSongs();
    Ring<Song> getRingSong();
    Ring<Song>& getRingSongAdress();
    Ring<Review> getReviews();
    void fillAddedSongs();
    void viewAddedSongs();
    void loadReviewsFromFile();
    void viewReviews();
    void addSong(Song song);
    void removeSong(Song song);
    void addReview(Review review);
    void removeReview(Review review);
    Ring<Song>::Iterator getSongsBeginning();
    User& operator =(const User& other);
    User& operator =(User&& other) noexcept;

private:

    QString username;
    Playlist addedSongs;
    Ring<Review> reviews;
};

#endif // USER_H
