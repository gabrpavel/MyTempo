#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QMessageBox>
#include <QLineEdit>

class Exception {
private:
    QString errorMessage;
    int code;
public:
    Exception(int code, QString errorMessage);
    virtual ~Exception();
    void generateErrorMessageBox(QString errorSolvingMessage);
};

#endif // EXCEPTION_H
