#include "createexamroom.h"
#include "ui_createexamroom.h"

#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "config.h"
CreateExamRoom::CreateExamRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateExamRoom),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Kết nối nút "Lưu" với slot onSaveButtonClicked
    connect(ui->pushButton, &QPushButton::clicked, this, &CreateExamRoom::onSaveButtonClicked);

    // Kết nối các trường nhập liệu với hàm validateInputs để kiểm tra dữ liệu mỗi khi thay đổi
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_2, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_3, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_4, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->dateTimeEdit_2, &QDateTimeEdit::dateTimeChanged, this, &CreateExamRoom::validateInputs);

    // Gọi validateInputs để disable nút "Lưu" ban đầu nếu có trường trống
    validateInputs();
}

CreateExamRoom::~CreateExamRoom()
{
    delete ui;
}

// Hàm kiểm tra dữ liệu và disable nút "Lưu" nếu có trường trống
void CreateExamRoom::validateInputs()
{
    bool isValid = !ui->lineEdit->text().isEmpty() &&
                   !ui->lineEdit_2->text().isEmpty() &&
                   ui->spinBox->value() > 0 &&
                   ui->spinBox_2->value() > 0 &&
                   ui->spinBox_3->value() > 0 &&
                   ui->spinBox_4->value() > 0 &&
                   ui->dateTimeEdit->dateTime() < ui->dateTimeEdit_2->dateTime();

    ui->pushButton->setEnabled(isValid);
}

// Slot xử lý khi bấm nút "Lưu"
void CreateExamRoom::onSaveButtonClicked()
{
    handleCreateExamRoom();

    // Close the parent QDialog
    QDialog *dialog = qobject_cast<QDialog *>(this->parentWidget());
    if (dialog) {
        dialog->close();
    }

    QMessageBox::information(this, "Thông báo", "Phòng thi đã được tạo thành công!");
}

// "CONTROL CREATE_ROOM
// {
//   ""subject"": ""Mathematics"",
//   ""description"": ""Desc"",
//   ""number_of_easy_question"": 10,
//   ""number_of_medium_question"": 5,
//   ""number_of_hard_question"": 2,
//   ""time_limit"": 30,
//   ""start"": ""2024-12-05T10:00:00"",
//   ""end"": ""2024-12-05T10:30:00""
// }"
void CreateExamRoom::handleCreateExamRoom() {
    QJsonObject json;
    json["subject"] = ui->lineEdit->text();
    json["description"] = ui->lineEdit_2->text();
    json["number_of_easy_question"] = ui->spinBox->value();
    json["number_of_medium_question"] = ui->spinBox_2->value();
    json["number_of_hard_question"] = ui->spinBox_3->value();
    json["time_limit"] = ui->spinBox_4->value();

    // Adjust the year of the start and end times
    QDateTime startDateTime = ui->dateTimeEdit->dateTime();
    QDateTime endDateTime = ui->dateTimeEdit_2->dateTime();
    startDateTime = startDateTime.addYears(100);
    endDateTime = endDateTime.addYears(100);

    json["start"] = startDateTime.toString(Qt::ISODate);
    json["end"] = endDateTime.toString(Qt::ISODate);

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL CREATE_ROOM\n%1").arg(QString(jsonData));

    tcpSocket->connectToHost(IPADDRESS, 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket, &QTcpSocket::readyRead, this, &CreateExamRoom::handleCreateExamRoomResponse);
}

// NOTIFICATION CREATE_ROOM_SUCCESS Time
void CreateExamRoom::handleCreateExamRoomResponse() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    qDebug() << "Create exam room response from server:" << responseString;
    if (responseString.startsWith("NOTIFICATION CREATE_ROOM_SUCCESS")) {
        // Extract the question ID from the response
        qDebug() << "Create Question Success";
       
    } else {
        qDebug() << "Failed to create question";
    }
}
