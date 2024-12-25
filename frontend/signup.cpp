// frontend/sources/signup.cpp
#include "signup.h"
#include "ui_signup.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "config.h"
Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Signup::onReadyRead);
}

Signup::~Signup() {
    delete ui;
}

void Signup::on_signupButton_clicked() {
    QJsonObject json;
    json["email"] = ui->emailLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();
    json["username"] = ui->usernameLineEdit->text();

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    tcpSocket->connectToHost(IPADDRESS, 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write("POST /signup ");
        tcpSocket->write(data);
        tcpSocket->flush();
    }
}

void Signup::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    ui->responseLabel->setText(response);
    emit showHome();
}
