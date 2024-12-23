#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QObject>

class TcpConnection : public QObject {
    Q_OBJECT

public:
    static TcpConnection& instance();
    QTcpSocket* getSocket();

    // Hàm tiện ích
    void sendRequest(const QString& command, const QJsonObject& json);
    void disconnectFromServer();

private:
    explicit TcpConnection(QObject* parent = nullptr);
    QTcpSocket* tcpSocket;

    TcpConnection(const TcpConnection&) = delete;
    TcpConnection& operator=(const TcpConnection&) = delete;

private slots:
    void handleReadyRead();
    void handleError(QAbstractSocket::SocketError socketError);

signals:
    void responseReceived(const QString& command, const QJsonObject& response);
};

#endif // TCPCONNECTION_H
