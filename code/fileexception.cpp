#include "fileexception.h"

FileException::FileException(int code, QString errorMessage, QString errorSolvingMessage)
    : Exception(code, errorMessage), errorSolvingMessage(errorSolvingMessage){}
FileException::~FileException(){}
QString FileException::getErrorSolvingMessage() {
    return errorSolvingMessage;
}
bool FileException::exceptionFile(const QString& fileName) {
    QFile file(fileName);
    if(!file.exists(fileName))
        throw FileException(202, "File error", "File doesn't exist");
    if (!file.open(QIODevice::ReadOnly))
        throw FileException(201, "File error", "Cannot open file in read only mode");
    if(file.open(QIODevice::Append | QIODevice::Text))
        throw FileException(203, "File error", "Cannot open file in append mode");
    file.close();
    return true;
}
