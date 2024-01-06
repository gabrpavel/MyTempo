#include "musicalcomposition.h"

MusicalComposition::MusicalComposition() {}
MusicalComposition::MusicalComposition(QString username, QString title,
                                       QString author, QString releaseDate)
    : username(username), title(title), author(author), releaseDate(releaseDate){}
MusicalComposition::MusicalComposition(const MusicalComposition& other)
    : title(other.title), author(other.author), releaseDate(other.releaseDate),
    username(other.username) {}
MusicalComposition::MusicalComposition(MusicalComposition&& other) noexcept
    : title(std::move(other.title)), author(std::move(other.author)),
    releaseDate(std::move(other.releaseDate)), username(std::move(other.username)) {}
void MusicalComposition::setTitle(const QString& title) {
    this->title = title;
}
void MusicalComposition::setAuthor(const QString& author) {
    this->author = author;
}
void MusicalComposition::setReleaseDate(const QString& releaseDate) {
    this->releaseDate = releaseDate;
}
void MusicalComposition::setUsername(const QString& username) {
    this->username = username;
}
QString MusicalComposition::getTitle() const {
    return this->title;
}
QString MusicalComposition::getAuthor() const {
    return this->author;
}
QString MusicalComposition::getReleaseDate() const {
    return this->releaseDate;
}
QString MusicalComposition::getUsername() const {
    return this->username;
}
bool MusicalComposition::compareTitle(const MusicalComposition& a,
                                      const MusicalComposition& b) {
    return const_cast<MusicalComposition&>(a).getTitle() < const_cast<MusicalComposition&>(b)
                                                                .getTitle();
}
bool MusicalComposition::compareAuthor(const MusicalComposition& a, const MusicalComposition& b) {
    return const_cast<MusicalComposition&>(a).getAuthor() < const_cast<MusicalComposition&>(b)
                                                                 .getAuthor();
}
bool MusicalComposition::compareReleaseDate(const MusicalComposition& a,
                                            const MusicalComposition& b) {
    QDate dateA = QDate::fromString(a.getReleaseDate(), "dd.MM.yyyy");
    QDate dateB = QDate::fromString(b.getReleaseDate(), "dd.MM.yyyy");

    return dateA > dateB;
}
std::ostream& operator<<(std::ostream& os, const MusicalComposition& musicalComposition) {
    os << musicalComposition.username.toStdString() << '|'
       << musicalComposition.title.toStdString() << '|'
       << musicalComposition.author.toStdString() << '|'
       << musicalComposition.releaseDate.toStdString();
    return os;
}
std::istream& operator>>(std::istream& is, MusicalComposition& musicalComposition) {
    std::string username, title, author, releaseDate;
    std::getline(is, username, '|');
    std::getline(is, title, '|');
    std::getline(is, author, '|');
    std::getline(is, releaseDate, '|');

    musicalComposition.setUsername(QString::fromStdString(username));
    musicalComposition.setTitle(QString::fromStdString(title));
    musicalComposition.setAuthor(QString::fromStdString(author));
    musicalComposition.setReleaseDate(QString::fromStdString(releaseDate));

    return is;
}
bool MusicalComposition::operator==(const MusicalComposition& other) const {
    return (title == other.title && author == other.author
            && releaseDate == other.releaseDate && username == other.username);
}
bool MusicalComposition::operator!=(const MusicalComposition& other) const {
    return !(*this == other);
}
bool MusicalComposition::operator>(const MusicalComposition& other) const {
    if (title != other.title) {
        return title > other.title;
    } else if (author != other.author) {
        return author > other.author;
    } else {
        return releaseDate > other.releaseDate;
    }
}
bool MusicalComposition::operator<(const MusicalComposition& other) const {
    return !(other > *this);
}
MusicalComposition& MusicalComposition::operator=(const MusicalComposition& other) {
    if (this != &other) {
        title = other.title;
        author = other.author;
        releaseDate = other.releaseDate;
        username = other.username;
    }
    return *this;
}
MusicalComposition& MusicalComposition::operator=(MusicalComposition&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        author = std::move(other.author);
        releaseDate = std::move(other.releaseDate);
        username = std::move(other.username);
    }
    return *this;
}
