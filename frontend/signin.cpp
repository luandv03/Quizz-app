// frontend/sources/signin.cpp
#include "signin.h"
#include "ui_signin.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>

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
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL LOGIN\n%1").arg(QString(jsonData));

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    }
}

void Signin::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    if (responseString.startsWith("NOTIFICATION LOGIN_FAILURE")) {
        ui->responseLabel->setText("Đăng nhập thất bại");
        ui->responseLabel->setStyleSheet("QLabel { color : red; }");
    } else if (responseString.startsWith("NOTIFICATION LOGIN_SUCCESS")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        if (jsonStartIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                int userId = jsonObj["user_id"].toInt();
                // Handle the user ID if needed
                emit showExamRoomList();
            }
        }
    } else {
        ui->responseLabel->setText("Unknown response from server");
        ui->responseLabel->setStyleSheet("QLabel { color : orange; }");
    }
}