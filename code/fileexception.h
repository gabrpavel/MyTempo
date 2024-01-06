#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <QFile>
#include "exception.h"

class FileException : public Exception
{
private:
    QString errorSolvingMessage;
public:
    FileException(int, QString, QString);
    ~FileException();
    QString getErrorSolvingMessage();
    static bool exceptionFile(const QString& fileName);
};

#endif // FILEEXCEPTION_H
