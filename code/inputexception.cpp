#include "inputexception.h"

InputException::InputException(int code, QString errorMessage, QString errorSolvingMessage) :
    Exception(code, errorMessage), errorSolvingMessage(errorSolvingMessage) {}
QString InputException::getErrorSolvingMessage() {
    return errorSolvingMessage;
}
bool InputException::exceptionUsername(QLineEdit* usernameField) {
    QString username = usernameField->text();
    if (username.isEmpty())
        throw InputException(101, "Username field is empty", "Please enter a username");
    if (username.length() < 4)
        throw InputException(102, "Username is too short",
                             "Username should be at least 4 characters long");
    if (username.contains('|'))
        throw InputException(102, "Incorrect username", "Username cannot contain '|'");
    return true;
}
bool InputException::exceptionPassword(QLineEdit* passwordField) {
    QString password = passwordField->text();
    if (password.isEmpty())
        throw InputException(101, "Password field is empty", "Please enter a password");
    if (password.length() < 4)
        throw InputException(102, "Password is too short",
                             "Password should be at least 4 characters long");
    if (password.contains('|') || password.contains(' '))
        throw InputException(102, "Incorrect password", "Password cannot contain '|' and spaces");
    return true;
}
bool InputException::exceptionReview(QString review) {
    if (review.isEmpty()) {
        throw InputException(101, "Review field is empty", "Please enter a username");
        return false;
    }
    if (review.contains('|'))
        throw InputException(102, "Incorrect review", "Review cannot contain '|'");
    return true;
}
InputException::~InputException(){}
