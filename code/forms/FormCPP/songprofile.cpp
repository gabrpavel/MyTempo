#include "forms/FormHeaders/songprofile.h"
#include "ui_songprofile.h"

SongProfile::SongProfile(User* user, Song song, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SongProfile)
{
    ui->setupUi(this);
    this->setWindowTitle("Song Profile");
    this->setFixedSize(363, 712);
    this->user = new User();
    this->user = user;
    this->song = song;
    ui->songTitle->setText(this->song.getTitle());
    ui->songAuthor->setText(this->song.getAuthor());
    ui->songGenre->setText(this->song.getGenre());
    ui->songReleaseDate->setText(this->song.getReleaseDate());
    loadReviewsFromFile();
    fillReviewsListWidget();

    connect(ui->songSlider, &QSlider::sliderMoved, this, &SongProfile::setPosition);

    this->player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    QString filePath = "D:\\My projects\\Qt projects\\MyTempo\\Resources\\song\\"
                                              + this->song.getAuthor() + " - " + this->song.getTitle() + ".mp3";
    player->setSource(QUrl::fromLocalFile(filePath));
    audioOutput->setVolume(15);

    if(!QFile::exists(filePath)) {
        ui->playAndPauseButton->setVisible(0);
        ui->songSlider->setVisible(0);
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SongProfile::updateSliderPosition);
    timer->start(1000);
    ui->playAndPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

SongProfile::~SongProfile()
{
    delete ui;
}

void SongProfile::on_addSongButton_clicked() {

    Song addedSong(song.getUsername(), song.getTitle(), song.getAuthor(),
                   song.getReleaseDate(), song.getGenre());
    this->user->addSong(addedSong);
}
void SongProfile::loadReviewsFromFile() {

    if(!reviews.isEmpty()) reviews.clear();
    QString reviewsFilePath =
        "D:\\My projects\\Qt projects\\MyTempo\\Resources\\reviews.txt";
    QFile file(reviewsFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open a file with reviews.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');

        if (parts.size() == 4 && parts[1] == song.getTitle() && parts[2] ==
                                                                    song.getAuthor()) {
            Review review(parts[0], parts[1], parts[2], parts[3]);
            reviews.push(review);
        }
    }

    file.close();
}
void SongProfile::fillReviewsListWidget() {
    ui->ReviewListWidget->clear();
    if(reviews.isEmpty()) return;
    Ring<Review>::Iterator it = reviews.begin();
    do {
        QString reviewText = it.current->data.getReviewer() + ": " +
                             it.current->data.getReviewText();
        QListWidgetItem *item = new QListWidgetItem(reviewText);
        ui->ReviewListWidget->addItem(item);
        it++;
    } while (it != reviews.begin());
}
void SongProfile::on_addReviewButton_clicked() {
    QString newReviewText = QInputDialog::getText(nullptr,
                                                  "New review", "Input rewiew:");
    try {
        if(!(InputException::exceptionReview(newReviewText)));
        else {

            Review newReview(user->getUsername(), song.getTitle(), song.getAuthor(),
                             newReviewText);
            this->user->addReview(newReview);
            loadReviewsFromFile();
            fillReviewsListWidget();

        }
    } catch (InputException& e) {

        e.generateErrorMessageBox(e.getErrorSolvingMessage());
    }
}

void SongProfile::on_removeSongButton_clicked()
{
    Song removedSong(song.getUsername(), song.getTitle(), song.getAuthor(),
                   song.getReleaseDate(), song.getGenre());
    this->user->removeSong(removedSong);
    ui->ReviewListWidget->clear();
    fillReviewsListWidget();
}


void SongProfile::on_removeReviewButton_clicked() {
    Review review(user->getUsername(), song.getTitle(), song.getAuthor(), "");
    this->user->removeReview(review);
    loadReviewsFromFile();
    fillReviewsListWidget();
}

void SongProfile::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question(
        this, "Closing a window", "Are you sure you want to close the window?",
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes
        );

    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        player->pause();
        event->accept();
    }
}

void SongProfile::updateSliderPosition() {
    qint64 duration = player->duration();
    if (duration > 0) {
        qint64 position = player->position();
        ui->songSlider->setMaximum(static_cast<int>(duration));
        ui->songSlider->setValue(static_cast<int>(position));

        updatePositionInfo(position);
        updateDurationInfo(duration);
    }
}

void SongProfile::setPosition(int position) {
    player->setPosition(position);
}

void SongProfile::updateDurationInfo(qint64 duration) {

    QTime totalTime(0, (duration / 60000) % 60, (duration / 1000) % 60);
    ui->durationLabel->setText(totalTime.toString("mm:ss"));
}

void SongProfile::updatePositionInfo(qint64 position) {

    QTime currentTime(0, (position / 60000) % 60, (position / 1000) % 60);
    ui->currentTimeLable->setText(currentTime.toString("mm:ss"));
}

void SongProfile::on_playAndPauseButton_clicked() {

    static bool isPlaying = false;
    if(isPlaying) {
        player->pause();
        ui->playAndPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->playAndPauseButton->setStyleSheet(
            "QPushButton {"
            "background-color: #55aaff; "
            "color: #fff;"
            "font-weight: 600;"
            "border-radius: 20px;"
            "border: 2px solid #0055ff;"
            "padding: 5px 15px;"
            "margin-top: 10px;"
            "outline: 0px;"
            "}"
            "QPushButton:hover {"
            "background-color: white;"
            "color: black"
            "}"
            "QPushButton"
            "  }");
        isPlaying = !isPlaying;
    } else {
        player->play();
        ui->playAndPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        ui->playAndPauseButton->setStyleSheet(
            "QPushButton {"
            "background-color: white; "
            "color: black;"
            "font-weight: 600;"
            "border-radius: 20px;"
            "border: 2px solid #0055ff;"
            "padding: 5px 15px;"
            "margin-top: 10px;"
            "outline: 0px;"
            "}"
            "QPushButton:hover {"
            "background-color: #55aaff;"
            "color: black"
            "}"
            "QPushButton"
            "  }");
        isPlaying = !isPlaying;
        }
}

