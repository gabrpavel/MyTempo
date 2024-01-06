#ifndef REVIEW_H
#define REVIEW_H

#include <QString>
#include <QFile>

class Review {

private:

    QString reviewer;
    QString peerReviewedTitle;
    QString peerReviewedAuthor;
    QString review;

public:

    Review();
    Review(QString reviewer, QString peerReviewedTitle, QString peerReviewedAuthor,
           QString review);
    Review(const Review& other);
    Review(Review&& other) noexcept;

    QString getReviewer() const;
    void setReviewer(const QString& reviewer);
    QString getPeerReviewedTitle() const;
    void setPeerReviewedTitle(const QString& peerReviewedTitle);
    QString getPeerReviewedAuthor() const;
    void setPeerReviewedAuthor(const QString& peerReviewedTitle);
    QString getReviewText() const;
    void setReviewText(const QString& reviewText);

    friend std::ostream& operator<<(std::ostream& os, const Review& review);
    friend std::istream& operator>>(std::istream& is, Review& review);
    bool operator==(const Review& other) const;
    bool operator!=(const Review& other) const;
    Review& operator=(const Review& other);
    Review& operator=(Review&& other) noexcept;
};

#endif // REVIEW_H
