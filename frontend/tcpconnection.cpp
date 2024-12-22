// TcpConnection.cpp
#include "tcpconnection.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>


TcpConnection::TcpConnection(QObject* parent)
    : QObject(parent), tcpSocket(new QTcpSocket(this)) {
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpConnection::handleReadyRead);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TcpConnection::handleError);
}

TcpConnection& TcpConnection::instance() {
    static TcpConnection instance;
    return instance;
}

QTcpSocket* TcpConnection::getSocket() {
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        tcpSocket->connectToHost("localhost", 8080);
        if (!tcpSocket->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server:" << tcpSocket->errorString();
        }
    }
    return tcpSocket;
}

void TcpConnection::sendRequest(const QString& command, const QJsonObject& json) {
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(json);
        QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
        QString request = QString("%1\n%2").arg(command).arg(QString(jsonData));
        tcpSocket->write(request.toUtf8());
        tcpSocket->flush();
    } else {
        qDebug() << "Not connected to server.";
    }
}

void TcpConnection::disconnectFromServer() {
    tcpSocket->disconnectFromHost();
}

void TcpConnection::handleReadyRead() {
    QByteArray data = tcpSocket->readAll();
    QString responseString(data);

    // Phân tích dữ liệu từ server
    int jsonStartIndex = responseString.indexOf('{');
    if (jsonStartIndex != -1) {
        QString jsonString = responseString.mid(jsonStartIndex);
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
        if (parseError.error == QJsonParseError::NoError) {
            QString command = responseString.left(jsonStartIndex).trimmed();
            emit responseReceived(command, jsonDoc.object());
        } else {
            qDebug() << "Failed to parse JSON from server response.";
        }
    } else {
        qDebug() << "Invalid response from server:" << responseString;
    }
}

void TcpConnection::handleError(QAbstractSocket::SocketError socketError) {
    qDebug() << "Socket error:" << tcpSocket->errorString();
    // Tự động thử kết nối lại nếu mất kết nối
    
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "Reconnecting to server...";
        tcpSocket->connectToHost("localhost", 8080);
        if (!tcpSocket->waitForConnected(3000)) {
            qDebug() << "Failed to reconnect to server:" << tcpSocket->errorString();
        }
    }
}
