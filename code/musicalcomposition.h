#ifndef MUSICALCOMPOSITION_H
#define MUSICALCOMPOSITION_H

#pragma once

#include <QString>
#include <set>
#include <QFile>
#include <QDate>

class MusicalComposition {

protected:

    QString title;
    QString author;
    QString releaseDate;
    QString username;

public:

    MusicalComposition();
    MusicalComposition(QString username, QString title, QString author, QString releaseDate);
    MusicalComposition(const MusicalComposition& other);
    MusicalComposition(MusicalComposition&& other) noexcept;
    virtual ~MusicalComposition() = default;

    void setTitle(const QString& title);
    void setAuthor(const QString& author);
    void setReleaseDate(const QString& releaseDate);
    void setUsername(const QString& releaseDate);
    QString getTitle() const;
    QString getAuthor() const;
    QString getReleaseDate() const;
    QString getUsername() const;

    static bool compareTitle(const MusicalComposition& a, const MusicalComposition& b);
    static bool compareAuthor(const MusicalComposition& a, const MusicalComposition& b);
    static bool compareReleaseDate(const MusicalComposition& a, const MusicalComposition& b);

    friend std::ostream& operator<<(std::ostream& os, const MusicalComposition& musicalComposition);
    friend std::istream& operator>>(std::istream& is, MusicalComposition& musicalComposition);
    bool operator==(const MusicalComposition& other) const;
    bool operator!=(const MusicalComposition& other) const;
    bool operator>(const MusicalComposition& other) const;
    bool operator<(const MusicalComposition& other) const;
    MusicalComposition& operator=(const MusicalComposition& other);
    MusicalComposition& operator=(MusicalComposition&& other) noexcept;
};

#endif // MUSICALCOMPOSITION_H
