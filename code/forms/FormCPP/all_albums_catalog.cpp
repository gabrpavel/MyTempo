#include "forms/FormHeaders/all_albums_catalog.h"
#include "ui_all_albums_catalog.h"

AllAlbumsCatalog::AllAlbumsCatalog(User* user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllAlbumsCatalog) {
    ui->setupUi(this);
    this->user = new User();
    this->user = user;

    this->setWindowTitle("Albums Catalog");
    this->setFixedSize(278, 430);

    loadAllAlbumsFromFile();
    fillAllAlbumsCatalogListWidget();
    openAlbumProfile();
}

AllAlbumsCatalog::~AllAlbumsCatalog()
{
    delete ui;
}
void AllAlbumsCatalog::loadAllAlbumsFromFile() {
    std::string fileName = "D:/My projects/Qt projects/MyTempo/Resources/albums.txt";
    QFile file(QString::fromStdString(fileName));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file:" << fileName;
        return;
    }

    QTextStream in(&file);
    QString line;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line == "<") {
            Album album;
            in >> album;
            album.viewSongs();
            QString key = album.getTitle() + " - " + album.getAuthor();
            allAlbums[key] = album;
            allAlbums[key].viewSongs();
        }
    }

    file.close();
}
void AllAlbumsCatalog::printAlbums() {
    for (auto it = allAlbums.begin(); it != allAlbums.end(); ++it) {
        std::cout << "Key: " << it->first.toStdString() << std::endl;
        std::cout << "Value: " << it->second.getSongsADRESS() << std::endl;
    }
}
void AllAlbumsCatalog::fillAllAlbumsCatalogListWidget() {
    if(!allAlbums.empty()) {
        for(auto it = allAlbums.begin(); it != allAlbums.end(); ++it) {
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2 (%3)")
                                                            .arg(it->second.getTitle(),
                                                                 it->second.getAuthor(),
                                                                 it->second.getGenre()));
            item->setData(Qt::UserRole, it->second.getReleaseDate());
            ui->allAlbumsCatalogListWidget->addItem(item);
        }
    }

}
bool AllAlbumsCatalog::eventFilter(QObject* object, QEvent* event) {
    if (object == ui->allAlbumsCatalogListWidget->viewport()) {
        if (event->type() == QEvent::ToolTip) {
            QListWidgetItem* currentItem = ui->allAlbumsCatalogListWidget->itemAt(
                ui->allAlbumsCatalogListWidget->mapFromGlobal(QCursor::pos()));
            if (currentItem) {
                QRect rect = ui->allAlbumsCatalogListWidget->visualItemRect(currentItem);
                QToolTip::showText(ui->allAlbumsCatalogListWidget->mapToGlobal(
                                       rect.bottomRight()),
                                   currentItem->data(Qt::UserRole).toString());
                return true;
            }
        }
    }
    return false;
}

void AllAlbumsCatalog::openAlbumProfile() {

    connect(ui->allAlbumsCatalogListWidget, &QListWidget::itemClicked, this,
            [=](QListWidgetItem* item) {
        if (item) {
            QString itemText = item->text();
            QStringList parts = itemText.split(" - ");

            if (parts.size() >= 2) {
                QString title = parts[0];
                QString authorWithGenre = parts[1];
                QString author = authorWithGenre.split(" (")[0];
                QString key = title + " - " + author;
                Album album(allAlbums.find(key)->second);
                AlbumProfile* albumProfile = new AlbumProfile(this->user, album, this);
                albumProfile->exec();
            }
        }
    });
}
