#include "loginwindow.h"
#include "loginwindow.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Tạo socket và kết nối tới server
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 8080);

    if (socket->waitForConnected()) {
        // Tạo JSON request
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;
        QJsonDocument doc(json);
        QByteArray data = doc.toJson();

        // Gửi yêu cầu
        socket->write("POST /api/signin HTTP/1.1\r\n");
        socket->write("Content-Type: application/json\r\n");
        socket->write(QString("Content-Length: %1\r\n").arg(data.size()).toUtf8());
        socket->write("\r\n");
        socket->write(data);
        socket->flush();

        // Nhận phản hồi
        socket->waitForReadyRead();
        QByteArray response = socket->readAll();

        // Phân tích phản hồi JSON
        QJsonDocument responseDoc = QJsonDocument::fromJson(response);
        if (responseDoc.isObject()) {
            QJsonObject responseObject = responseDoc.object();
            if (responseObject.contains("message")) {
                QMessageBox::information(this, "Success", responseObject["message"].toString());
            } else if (responseObject.contains("error")) {
                QMessageBox::warning(this, "Error", responseObject["error"].toString());
            }
        }
        socket->disconnectFromHost();
    }
}
