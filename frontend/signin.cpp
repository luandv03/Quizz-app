// frontend/sources/signin.cpp
#include "signin.h"
#include "ui_signin.h"
#include <QJsonDocument>
#include <QJsonObject>

Signin::Signin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signin)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Signin::onReadyRead);
}

Signin::~Signin() {
    delete ui;
}

void Signin::on_signinButton_clicked() {
    QJsonObject json;
    json["email"] = ui->emailLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write("POST /signin ");
        tcpSocket->write(data);
        tcpSocket->flush();
    }
}

void Signin::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    ui->responseLabel->setText(response);
    emit showHome();
}
