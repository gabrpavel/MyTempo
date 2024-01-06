#include "user.h"

User::User(){}
User::User(const QString& username) : username(username) {}
User::User(const User& other) {
    if (this != &other) {
        username = other.username;
        addedSongs = other.addedSongs;
        reviews = other.reviews;
    }
}
User::User(User&& other) noexcept {
    if (this != &other) {
        username = std::move(other.username);
        addedSongs = std::move(other.addedSongs);
        reviews = std::move(other.reviews);
    }
}
void User::setUsername(const QString& username) {
    this->username = username;
}
QString User::getUsername() {
    return this->username;
}
Playlist User::getAddedSongs() {
    return this->addedSongs;
}
Ring<Review> User::getReviews() {
    return this->reviews;
}
Ring<Song> User::getRingSong() {
    return this->addedSongs.getSongs();
}
Ring<Song>& User::getRingSongAdress() {
    return this->addedSongs.getSongsADRESS();
}
void User::fillAddedSongs() {
    std::string fileName = "D:\\My projects\\Qt projects\\MyTempo\\Resources\\addedSongs.txt";
    this->addedSongs.fillPlaylist(this->username, fileName.data());
}
void User::viewAddedSongs() {
    this->addedSongs.viewSongs();
}
void User::loadReviewsFromFile() {
    std::string fileName = "D:\\My projects\\Qt projects\\MyTempo\\Resources\\reviews.txt";
    Algorithm<Review>::loadFromFile(this->reviews, fileName.data(), this->username.toStdString());
}
void User::viewReviews() {
    std::cout << this->reviews << std::endl;
}
void User::addSong(Song song) {
    if(!this->addedSongs.getPlaylistSongs().isEmpty()) {
        if (addedSongs.getPlaylistSongs().exist(song)) {
            QMessageBox::warning(nullptr, "Adding song", "You've already added this song!");
        } else {
            addedSongs.addSongToPlaylist(song);
            std::ofstream file("D:\\My projects\\Qt projects\\MyTempo\\Resources\\addedSongs.txt",
                               std::ios::app);
            if (file.is_open()) {
                file << song << std::endl;
                file.close();
                QMessageBox::information(nullptr, "Add song", "Song added!");
            } else {
                QMessageBox::warning(nullptr, "File", "File not found!");
            }
        }
    }
    else {
        addedSongs.addSongToPlaylist(song);
        std::ofstream file("D:\\My projects\\Qt projects\\MyTempo\\Resources\\addedSongs.txt",
                           std::ios::app);
        if (file.is_open()) {
            file << song << std::endl;
            file.close();
            QMessageBox::information(nullptr, "Add song", "Song added!");
        } else {
            QMessageBox::warning(nullptr, "File", "File not found!");
        }
    }

}
void User::addReview(Review review) {
    Ring<Review>::Iterator it = reviews.find(review);
    if (!reviews.isEmpty() && *it == review) {

        QMessageBox msgBox;
        msgBox.setText("You already have a review for this song. Would you like to replace it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        int choice = msgBox.exec();
        if (choice == QMessageBox::Yes) {
            *it = review;
            Algorithm<Review>::removeFromFile(
                "D:\\My projects\\Qt projects\\MyTempo\\Resources\\reviews.txt", review);
        } else{
            return;
        }
    } else {
        reviews.push(review);
    }

    std::ofstream file("D:\\My projects\\Qt projects\\MyTempo\\Resources\\reviews.txt",
                       std::ios::app);
    if (file.is_open()) {
        file << review << std::endl;
        file.close();

        if (*it == review) {
            QMessageBox::information(nullptr, "Review replaced", "The review has been successfully replaced!");
        } else {
            QMessageBox::information(nullptr, "Adding review", "Review has been successfully added!");
        }
    } else {
        if (*it == review) {
            QMessageBox::warning(nullptr, "Review replaced", "File not found!");
        } else {
            QMessageBox::warning(nullptr, "Adding review", "File not found!");
        }
    }
}
void User::removeSong(Song song) {
    if (addedSongs.getPlaylistSongs().isEmpty() || !addedSongs.getPlaylistSongs().exist(song)) {
        QMessageBox::critical(nullptr, "Remove error", "You didn't add this song.");
        return;
    }
    addedSongs.getPlaylistSongs().deleteElement(song);
    Algorithm<Song>::removeFromFile(
        "D:\\My projects\\Qt projects\\MyTempo\\Resources\\addedSongs.txt", song);
    QMessageBox::information(nullptr, "Remove error", "Song successfully deleted.");
}
void User::removeReview(Review review) {

    if (reviews.isEmpty() || !reviews.exist(review)) {
        QMessageBox::critical(nullptr, "Remove error", "You don't have a review for this song.");
        return;
    }
    reviews.deleteElement(review);
    Algorithm<Review>::removeFromFile(
        "D:\\My projects\\Qt projects\\MyTempo\\Resources\\reviews.txt", review);
    QMessageBox::information(nullptr, "Remove error", "Review successfully deleted.");
}

Ring<Song>::Iterator User::getSongsBeginning() {
    return this->addedSongs.songsBeginning();
}
User& User::operator=(const User& other) {
    if (this != &other) {
        username = other.username;
        addedSongs = other.addedSongs;
        reviews = other.reviews;
    }
    return *this;
}
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        username = std::move(other.username);
        addedSongs = std::move(other.addedSongs);
        reviews = std::move(other.reviews);
    }
    return *this;
}
