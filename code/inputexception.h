#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H

#include "exception.h"

class InputException : public Exception {
private:
    QString errorSolvingMessage;
public:
    explicit InputException(int, QString, QString);
    ~InputException();
    QString getErrorSolvingMessage();
    static bool exceptionUsername(QLineEdit*);
    static bool exceptionPassword(QLineEdit*);
    static bool exceptionReview(QString);
};

#endif // INPUTEXCEPTION_H
