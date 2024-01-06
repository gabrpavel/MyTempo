#include "forms/FormHeaders/authorization.h"
#include "ui_authorization.h"
#include <QMessageBox>
#include <QPushButton>

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
    connect(ui->Login, &QPushButton::clicked, this, [=]() {
        try {
            if(!(InputException::exceptionUsername(ui->lineUsername) &&
                 InputException::exceptionPassword(ui->linePassword)));
            else {
                QString username = ui->lineUsername->text();
                QString password = ui->linePassword->text();

                if(checkCredentials(username, password)) {
                    emit userLoggedIn(username);
                    this->hide();
                } else {
                    ui->lineUsername->clear();
                    ui->linePassword->clear();
                    QMessageBox::critical(nullptr, "Authorization", "Account not found");
                }
            }
        } catch (InputException& ie) {
            ui->lineUsername->clear();
            ui->linePassword->clear();
            ie.generateErrorMessageBox(ie.getErrorSolvingMessage());
        }
    });
}
Authorization::~Authorization()
{
    delete ui;
}
bool Authorization::checkCredentials(const QString &username, const QString &password) {
    QString fileName("D:\\My projects\\Qt projects\\MyTempo\\Resources\\authorization.txt");
    try {
        if(!(FileException::exceptionFile(fileName)));
        else {
            QFile file(fileName);
            if(file.isOpen()) file.close();
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QString token = username + '|' + password;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.compare(token) == 0) {
                    file.close();
                    return 1;
                }
            }
            file.close();
            return 0;
        }
    } catch (FileException& fe) {
        ui->lineUsername->clear();
        ui->linePassword->clear();
        fe.generateErrorMessageBox(fe.getErrorSolvingMessage());
        return 0;
    }
}
void Authorization::on_Sign_Up_clicked()
{
    QString fileName("D:\\My projects\\Qt projects\\MyTempo\\Resources\\authorization.txt");
    try {
        if(!(InputException::exceptionUsername(ui->lineUsername)
              && InputException::exceptionPassword(ui->linePassword)));
        else if(!(FileException::exceptionFile(fileName)));
        else {
            QString username = ui->lineUsername->text();
            QString password = ui->linePassword->text();
            ui->lineUsername->clear();
            ui->linePassword->clear();
            if(checkCredentials(username, password)) {
                QMessageBox::critical(nullptr, "Registration", "Account already exist!");
                return;
            }
            QFile file(fileName);
            file.open(QIODevice::Append | QIODevice::Text);
            QString token = username + '|' + password;
            QTextStream out(&file);
            out << token << '\n';
            file.close();
            QMessageBox::information(nullptr, "Registration", "Account created!");
        }
    } catch (InputException& ie) {
        ui->lineUsername->clear();
        ui->linePassword->clear();
        ie.generateErrorMessageBox(ie.getErrorSolvingMessage());
    } catch (FileException& fe) {
        ui->lineUsername->clear();
        ui->linePassword->clear();
        fe.generateErrorMessageBox(fe.getErrorSolvingMessage());
    }
}
