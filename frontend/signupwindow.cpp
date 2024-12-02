#include "signupwindow.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

SignupWindow::SignupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupWindow) {
    ui->setupUi(this);
}

SignupWindow::~SignupWindow() {
    delete ui;
}

void SignupWindow::on_signupButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString email = ui->emailLineEdit->text();

    // Tạo socket và kết nối tới server
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 8080);

    if (socket->waitForConnected()) {
        // Tạo JSON request
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;
        json["email"] = email;
        QJsonDocument doc(json);
        QByteArray data = doc.toJson();

        // Gửi yêu cầu
        socket->write("POST /api/signup HTTP/1.1\r\n");
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
