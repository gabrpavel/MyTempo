#ifndef SONGPROFILE_H
#define SONGPROFILE_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QEvent>
#include <QToolTip>

#include <QUrl>
#include <QStyle>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>

#include "user.h"
#include "inputexception.h"

namespace Ui {
class SongProfile;
}

class SongProfile : public QDialog
{
    Q_OBJECT

protected:

    void closeEvent(QCloseEvent *event) override;

public:

    explicit SongProfile(User* user, Song song, QWidget* parent = nullptr);
    ~SongProfile();
    void loadReviewsFromFile();
    void fillReviewsListWidget();

private slots:

    void on_addSongButton_clicked();
    void on_addReviewButton_clicked();
    void on_removeSongButton_clicked();
    void on_removeReviewButton_clicked();

    void setPosition(int position);
    void updateSliderPosition();
    void updateDurationInfo(qint64 duration);
    void updatePositionInfo(qint64 position);


    void on_playAndPauseButton_clicked();

private:

    Ui::SongProfile *ui;
    QMediaPlayer* player;
    User* user;
    Song song;
    Ring<Review> reviews;
};

#endif // SONGPROFILE_H
