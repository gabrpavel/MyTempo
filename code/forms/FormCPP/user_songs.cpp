#include "forms/FormHeaders/user_songs.h"
#include "ui_user_songs.h"

UserSongs::UserSongs(User* user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSongs)
{
    ui->setupUi(this);
    this->user = new User();
    this->user = user;
    this->setWindowTitle("Added songs");
    this->setFixedSize(278, 466);
    ui->sortOptions->addItem("By title");
    ui->sortOptions->addItem("By author");
    ui->sortOptions->addItem("By genre");
    ui->sortOptions->addItem("By release date");

    fillUserSongsListWidget(this->user->getRingSongAdress());
    openSongProfile();
    connect(ui->sortOptions, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UserSongs::sorting);
    sorting(ui->sortOptions->currentIndex());
    connect(ui->searchLine, &QLineEdit::textChanged, this, &UserSongs::onSearchTextChanged);
}

UserSongs::~UserSongs()
{
    delete ui;
}
void UserSongs::fillUserSongsListWidget(Ring<Song>& songs) {

    if(!songs.isEmpty()) {
        Ring<Song>::Iterator it = songs.begin();
        do {
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2 (%3)")
                                                            .arg((*it).getTitle(),
                                                                 (*it).getAuthor(),
                                                                 (*it).getGenre()));
            item->setData(Qt::UserRole, (*it).getReleaseDate());
            ui->userSongsListWidget->addItem(item);
            it++;
        } while(it != songs.begin());
    }
}
bool UserSongs::eventFilter(QObject* object, QEvent* event) {

    if (object == ui->userSongsListWidget->viewport()) {
        if (event->type() == QEvent::ToolTip) {
            QListWidgetItem* currentItem = ui->userSongsListWidget->itemAt(
                ui->userSongsListWidget->mapFromGlobal(QCursor::pos()));
            if (currentItem) {
                QRect rect = ui->userSongsListWidget->visualItemRect(currentItem);
                QToolTip::showText(ui->userSongsListWidget->mapToGlobal(
                                       rect.bottomRight()),
                                   currentItem->data(Qt::UserRole).toString());
                return true;
            }
        }
    }
    return false;
}
void UserSongs::openSongProfile() {

    connect(ui->userSongsListWidget, &QListWidget::itemClicked, this,
            [=](QListWidgetItem* item) {
        if (item) {
            QString itemText = item->text();
            QStringList parts = itemText.split(" - ");

            if (parts.size() >= 2) {
                QString title = parts[0];
                QString authorWithGenre = parts[1];
                QString author = authorWithGenre.split(" (")[0];
                QString genre = authorWithGenre.section(" (", 1, 1).chopped(1);
                QString releaseDate = item->data(Qt::UserRole).toString();
                Song song(this->user->getUsername(), title, author, releaseDate, genre);
                SongProfile* songProfile = new SongProfile(this->user, song, this);
                songProfile->exec(); // Отображение модального диалога
            }
        }
    });
}
void UserSongs::sorting(int index) {
    switch (index) {
    case 0:
        Algorithm<Song>::quickSort(this->user->getRingSongAdress(),
                                   MusicalComposition::compareTitle);
        break;
    case 1:
        Algorithm<Song>::quickSort(this->user->getRingSongAdress(),
                                   MusicalComposition::compareAuthor);
        break;
    case 2:
        Algorithm<Song>::quickSort(this->user->getRingSongAdress(),
                                   Song::compareGenre);
        break;
    case 3:
        Algorithm<Song>::quickSort(this->user->getRingSongAdress(),
                                   MusicalComposition::compareReleaseDate);
        break;
    default:
        break;
    }
    ui->userSongsListWidget->clear();
    fillUserSongsListWidget(this->user->getRingSongAdress());
    ui->userSongsListWidget->viewport()->installEventFilter(this);
}
void UserSongs::onSearchTextChanged(const QString& searchText) {
    QString search = searchText.toLower();
    for (int i = 0; i < ui->userSongsListWidget->count(); ++i) {
        QListWidgetItem *item = ui->userSongsListWidget->item(i);
        QString itemText = item->text().toLower();
        if (itemText.contains(search)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}
