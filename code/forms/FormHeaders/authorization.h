#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "inputexception.h"
#include "fileexception.h"

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();
    bool checkCredentials(const QString &username, const QString &password);

private slots:

    void on_Sign_Up_clicked();

private:
    Ui::Authorization *ui;

signals:
    void userLoggedIn(const QString& username);
};

#endif // AUTHORIZATION_H
