#include "review.h"

Review::Review() {}
Review::Review(QString reviewer, QString peerReviewedTitle,
               QString peerReviewedAuthor, QString review)
    : reviewer(reviewer), peerReviewedTitle(peerReviewedTitle),
    peerReviewedAuthor(peerReviewedAuthor), review(review) {}
Review::Review(const Review& other)
    : reviewer(other.reviewer),
    peerReviewedTitle(other.peerReviewedTitle),
    peerReviewedAuthor(other.peerReviewedAuthor),
    review(other.review) {}
Review::Review(Review&& other) noexcept
    : reviewer(std::move(other.reviewer)),
    peerReviewedTitle(std::move(other.peerReviewedTitle)),
    peerReviewedAuthor(std::move(other.peerReviewedAuthor)),
    review(std::move(other.review)) {}
QString Review::getReviewer() const {
    return reviewer;
}
void Review::setReviewer(const QString& reviewer) {
    this->reviewer = reviewer;
}
QString Review::getPeerReviewedTitle() const {
    return peerReviewedTitle;
}
void Review::setPeerReviewedTitle(const QString& peerReviewedTitle) {
    this->peerReviewedTitle = peerReviewedTitle;
}
QString Review::getPeerReviewedAuthor() const {
    return peerReviewedAuthor;
}
void Review::setPeerReviewedAuthor(const QString& peerReviewedAuthor) {
    this->peerReviewedAuthor = peerReviewedAuthor;
}
QString Review::getReviewText() const {
    return review;
}
void Review::setReviewText(const QString& reviewText) {
    this->review = reviewText;
}
std::ostream& operator<<(std::ostream& os, const Review& review) {
    os << review.getReviewer().toStdString() << '|'
       << review.getPeerReviewedTitle().toStdString() << '|'
       << review.getPeerReviewedAuthor().toStdString() << '|'
       << review.getReviewText().toStdString();
    return os;
}
std::istream& operator>>(std::istream& is, Review& review) {
    std::string reviewer, peerReviewedTitle, peerReviewedAuthor, reviewText;
    std::getline(is, reviewer, '|');
    std::getline(is, peerReviewedTitle, '|');
    std::getline(is, peerReviewedAuthor, '|');
    std::getline(is, reviewText, '|');

    review.setReviewer(QString::fromStdString(reviewer));
    review.setPeerReviewedTitle(QString::fromStdString(peerReviewedTitle));
    review.setPeerReviewedAuthor(QString::fromStdString(peerReviewedAuthor));
    review.setReviewText(QString::fromStdString(reviewText));

    return is;
}
bool Review::operator==(const Review& other) const {
    return (
        reviewer == other.reviewer &&
        peerReviewedTitle == other.peerReviewedTitle &&
        peerReviewedAuthor == other.peerReviewedAuthor
        //review == other.review
        );
}
bool Review::operator!=(const Review& other) const {
    return !(*this == other);
}
Review& Review::operator=(const Review& other) {
    if (this != &other) {
        reviewer = other.reviewer;
        peerReviewedTitle = other.peerReviewedTitle;
        peerReviewedAuthor = other.peerReviewedAuthor;
        review = other.review;
    }
    return *this;
}
Review& Review::operator=(Review&& other) noexcept {
    if (this != &other) {
        reviewer = std::move(other.reviewer);
        peerReviewedTitle = std::move(other.peerReviewedTitle);
        peerReviewedAuthor = std::move(other.peerReviewedAuthor);
        review = std::move(other.review);
    }
    return *this;
}
