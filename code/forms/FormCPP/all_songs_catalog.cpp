#include "forms/FormHeaders/all_songs_catalog.h"
#include "ui_all_songs_catalog.h"

AllSongsCatalog::AllSongsCatalog(User* user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSongsCatalog)
{
    ui->setupUi(this);
    this->user = new User();
    this->user = user;

    this->setWindowTitle("Songs catalog");
    this->setFixedSize(278, 466);
    ui->sortOptions->addItem("By title");
    ui->sortOptions->addItem("By author");
    ui->sortOptions->addItem("By genre");
    ui->sortOptions->addItem("By release date");

    loadAllSongsFromFile();
    fillAllSongsCatalogListWidget(this->allSongs.getSongsADRESS());
    openSongProfile();

    connect(ui->sortOptions, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AllSongsCatalog::sorting);
    sorting(ui->sortOptions->currentIndex());
    connect(ui->searchLine, &QLineEdit::textChanged, this, &AllSongsCatalog::onSearchTextChanged);
}

AllSongsCatalog::~AllSongsCatalog()
{
    delete ui;
}
void AllSongsCatalog::loadAllSongsFromFile() {
    std::string fileName = "D:\\My projects\\Qt projects\\MyTempo\\Resources\\songs.txt";
    this->allSongs.loadSongsFromFile(QString::fromStdString("ALL"), fileName.data());
}
void AllSongsCatalog::fillAllSongsCatalogListWidget(Ring<Song>& songs) {
    if(!songs.isEmpty()) {
        Ring<Song>::Iterator it = songs.begin();
        do {
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2 (%3)").
                                                        arg((*it).getTitle(),
                                                            (*it).getAuthor(),
                                                            (*it).getGenre()));
            item->setData(Qt::UserRole, (*it).getReleaseDate());
            ui->allSongCatalogListWidget->addItem(item);
            it++;
        } while(it != songs.begin());
    }
}
bool AllSongsCatalog::eventFilter(QObject* object, QEvent* event) {
    if (object == ui->allSongCatalogListWidget->viewport()) {
        if (event->type() == QEvent::ToolTip) {
            QListWidgetItem* currentItem = ui->allSongCatalogListWidget->itemAt(
                ui->allSongCatalogListWidget->mapFromGlobal(QCursor::pos()));
            if (currentItem) {
                QRect rect = ui->allSongCatalogListWidget->visualItemRect(currentItem);
                QToolTip::showText(ui->allSongCatalogListWidget->mapToGlobal(
                                       rect.bottomRight()),
                                   currentItem->data(Qt::UserRole).toString());
                return true;
            }
        }
    }
    return false;
}
void AllSongsCatalog::openSongProfile() {

    connect(ui->allSongCatalogListWidget, &QListWidget::itemClicked, this,
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
                songProfile->exec();
            }
        }
});
}
void AllSongsCatalog::sorting(int index) {
    switch (index) {
    case 0:
        Algorithm<Song>::quickSort(this->allSongs.getSongsADRESS(),
                                   MusicalComposition::compareTitle);
        break;
    case 1:
        Algorithm<Song>::quickSort(this->allSongs.getSongsADRESS(),
                                   MusicalComposition::compareAuthor);
        break;
    case 2:
        Algorithm<Song>::quickSort(this->allSongs.getSongsADRESS(),
                                   Song::compareGenre);
        break;
    case 3:
        Algorithm<Song>::quickSort(this->allSongs.getSongsADRESS(),
                                   MusicalComposition::compareReleaseDate);
        break;
    default:
        break;
    }
    ui->allSongCatalogListWidget->clear();
    fillAllSongsCatalogListWidget(this->allSongs.getSongsADRESS());
    ui->allSongCatalogListWidget->viewport()->installEventFilter(this);
}
void AllSongsCatalog::onSearchTextChanged(const QString& searchText) {
    QString search = searchText.toLower();
    for (int i = 0; i < ui->allSongCatalogListWidget->count(); ++i) {
        QListWidgetItem *item = ui->allSongCatalogListWidget->item(i);
        QString itemText = item->text().toLower();
        if (itemText.contains(search)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}
