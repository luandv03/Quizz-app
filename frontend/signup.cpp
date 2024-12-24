// frontend/sources/signup.cpp
#include "signup.h"
#include "ui_signup.h"
#include <QJsonDocument>
#include <QJsonObject>

Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Signup::onReadyRead);

    connect(ui->signinButton, &QPushButton::clicked, [this]() {
        emit showSignin();
    });
}

Signup::~Signup() {
    delete ui;
}

void Signup::on_signupButton_clicked() {
    QJsonObject json;
    json["email"] = ui->emailLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();
    json["username"] = ui->usernameLineEdit->text();

}

void Signup::onReadyRead() {
    
}
