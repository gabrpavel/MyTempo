#include <QApplication>
#include "forms/FormHeaders/mytempo.h"
#include "forms/FormHeaders/authorization.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Authorization authorization;
    MyTempo *myTempo = nullptr;

    QObject::connect(&authorization, &Authorization::userLoggedIn,
                     [&myTempo](const QString& username) {
        myTempo = new MyTempo(username);
        myTempo->show();
    });

    authorization.show();
    return a.exec();
}
