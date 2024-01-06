#include "exception.h"

Exception::Exception(int code, QString errorMessage) {
    this->code = code;
    this->errorMessage = errorMessage;
}
void Exception::generateErrorMessageBox(QString errorSolvingMessage) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Error: " + QString::number(code));
    msgBox.setText(errorMessage + ".\n" + errorSolvingMessage);
    msgBox.setFixedSize(800, 400);
    msgBox.exec();
}
Exception::~Exception(){}
