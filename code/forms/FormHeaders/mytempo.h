#ifndef MYTEMPO_H
#define MYTEMPO_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyTempo; }
QT_END_NAMESPACE

class MyTempo : public QMainWindow
{
    Q_OBJECT

public:

    MyTempo(const QString& username, QWidget *parent = nullptr);
    ~MyTempo();
    void setUsername(const QString& username);

private slots:

    void on_exit_Button_clicked();
    void on_all_songs_Button_clicked();
    void on_my_catalog_Button_clicked();
    void on_all_albums_Button_clicked();

private:

    Ui::MyTempo *ui;
    User* user;

};
#endif // MYTEMPO_H
