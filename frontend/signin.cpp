// frontend/sources/signin.cpp
#include "signin.h"
#include "ui_signin.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>
#include <QDebug>
#include <QThread>

Signin::Signin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signin)
    , tcpSocket(new QTcpSocket(this))
    , tcpSocket2(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Signin::onReadyRead);
    connect(tcpSocket2, &QTcpSocket::readyRead, this, &Signin::onProfile);
    connect(tcpSocket, &QTcpSocket::connected, this, &Signin::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Signin::onDisconnected);

    // tcpSocket->connectToHost("localhost", 8080);
    // if (!tcpSocket->waitForConnected(3000)) {
    //     qDebug() << "Không thể kết nối tới server trong constructor.";
    // }
}

Signin::~Signin() {
    delete ui;
}

void Signin::on_signinButton_clicked() {
    // if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
    //     qDebug() << "Socket chưa kết nối. Không thể gửi yêu cầu đăng nhập.";
    //     return;
    // }

    QJsonObject json;
    json["email"] = ui->emailLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    QString dataString = QString("CONTROL LOGIN\n%1").arg(QString(jsonData));

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    }
}

void Signin::getProfile() {
    // if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
    //     qDebug() << "Socket chưa kết nối. Không thể gửi yêu cầu lấy hồ sơ.";
    //     return;
    // }

    QJsonObject json;
    json["user_id"] = UserData::instance().getUserId();

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    QString dataString = QString("CONTROL GET_PROFILE_BY_ID\n%1").arg(QString(jsonData));

    tcpSocket2->connectToHost("localhost", 8080);
    if (tcpSocket2->waitForConnected()) {
        tcpSocket2->write(dataString.toUtf8());
        tcpSocket2->flush();
    }
    qDebug() << "Get Profile Request:" << dataString;
}

void Signin::onProfile() {
    qDebug () << "onProfile nhu concac";
    QByteArray response = tcpSocket2->readAll();
    QString responseString(response);

    qDebug() << "Response:" << responseString;

    if (responseString.startsWith("DATA JSON GET_PROFILE_BY_ID")) {
        int jsonStartIndex = responseString.indexOf('{');
        if (jsonStartIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QString userName = jsonObj["name"].toString();
                QString email = jsonObj["email"].toString();
                QString dob = jsonObj["dob"].toString();
                UserData::instance().setUserName(userName);
                UserData::instance().setEmail(email);
                UserData::instance().setDob(dob);

                qDebug() << "User Name:" << UserData::instance().getUserName();
                qDebug() << "Email:" << UserData::instance().getEmail();
                qDebug() << "DOB:" << UserData::instance().getDob();

                QString role = UserData::instance().getRole();
                qDebug() << "Role:" << role;

                if (role == "admin") {
                    emit showUserManagement();
                } else {
                    emit showExamRoomList();
                }

                // reset sign form value
                ui->emailLineEdit->setText("");
                ui->passwordLineEdit->setText("");
            }
        }
    }
}

void Signin::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    if (responseString.startsWith("NOTIFICATION LOGIN_FAILURE")) {
        ui->responseLabel->setText("Đăng nhập thất bại");
        ui->responseLabel->setStyleSheet("QLabel { color : red; }");
        qDebug() << "Login Response:" << responseString;
    } else if (responseString.startsWith("NOTIFICATION LOGIN_SUCCESS")) {
        qDebug() << "Login Response:" << responseString;

        int jsonStartIndex = responseString.indexOf('{');
        if (jsonStartIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                int userId = jsonObj["user_id"].toInt();
                UserData::instance().setUserData(jsonObj);

                qDebug() << "User ID:" << UserData::instance().getUserId();

                getProfile();
            }
        }
    } else {
        ui->responseLabel->setText("Unknown response from server");
        ui->responseLabel->setStyleSheet("QLabel { color : orange; }");
    }
}

void Signin::onConnected() {
    qDebug() << "Connected to server.";
}

void Signin::onDisconnected() {
    qDebug() << "Disconnected from server.";
}
