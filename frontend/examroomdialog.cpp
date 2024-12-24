#include "examroomdialog.h"
#include "ui_examroomdialog.h"
#include "createquestion.h"

#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QThread>
#include <QMessageBox>

ExamRoomDialog::ExamRoomDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDialog),
    tcpSocket(new QTcpSocket(this)),
    tcpSocket1(new QTcpSocket(this)),
    tcpSocket2(new QTcpSocket(this)),
    tcpSocket3(new QTcpSocket(this)),
    tcpSocket4(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Make the header bold
    QHeaderView *header = ui->userTableWidget->horizontalHeader();
    QFont headerFont = header->font();
    headerFont.setBold(true);
    header->setFont(headerFont);

    // Optional: Adjust alignment and resize behavior
    header->setDefaultAlignment(Qt::AlignCenter); // Center alignment for the headers
    ui->userTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Adjust columns to fill the table width

    // CSS for exam result table
     // Make the header bold
    QHeaderView *headerExamResultTable = ui->examResultTableWidget->horizontalHeader();
    QFont headerFontExamResultTable = headerExamResultTable->font();
    headerFontExamResultTable.setBold(true);
    headerExamResultTable->setFont(headerFontExamResultTable);

    // Optional: Adjust alignment and resize behavior
    headerExamResultTable->setDefaultAlignment(Qt::AlignCenter); // Center alignment for the headers
    ui->examResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Adjust columns to fill the table width

    // Connect the close button signal to the slot
    // connect(ui->closeButton, &QPushButton::clicked, this, &ExamRoomDialog::onCloseButtonClicked);
    connect(ui->addQuestionButton, &QPushButton::clicked, this, &ExamRoomDialog::onAddQuestion);

    // handle start exam
    connect(ui->startExam, &QPushButton::clicked, this, &ExamRoomDialog::handleStartExam);

    // handle end exam
    connect(ui->endExam, &QPushButton::clicked, this, &ExamRoomDialog::handleEndExam);

    // Gọi hàm để tạo chart khi khởi tạo dialog
    setupScoreChart();
}

ExamRoomDialog::~ExamRoomDialog()
{
    delete ui;
}

void ExamRoomDialog::setRoomDetails(const QString &roomId, const QString &roomName, const QString &description, const QString &timeLimit, const QString &status, const QString &startTime, const QString &endTime)
{
    // ui->roomIdLabel->setText("Room ID: " + roomId);
    examRoomId = roomId.toInt();
    ui->roomName->setText(roomName);
    ui->description->setText(description);
    ui->timelimit->setText(timeLimit);
    ui->status->setText(status);
    ui->starttime->setText(startTime);
    ui->endtime->setText(endTime);

    if (status == "Not started") {
        ui->startExam->setEnabled(true);
        ui->endExam->setEnabled(false);
        ui->addQuestionButton->setEnabled(true);
        ui->addUser->setEnabled(true);
        // ui->tabExamResult->hide();  // Disable the tab
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabExamResult));
        // ui->tabExamResultChart->hide();  
        ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tabExamResultChart));
    } else if(status == "Finished") {
        ui->startExam->setEnabled(false);
        ui->endExam->setEnabled(false);
        ui->addQuestionButton->setEnabled(false);
        ui->addUser->setEnabled(false);
        ui->tabExamResult->setEnabled(true);  
        ui->tabExamResultChart->setEnabled(true);  
    } else {
        ui->startExam->setEnabled(false);
        ui->endExam->setEnabled(true);
        ui->addQuestionButton->setEnabled(false);
        ui->addUser->setEnabled(false);
        ui->tabExamResult->setEnabled(false);  // Disable the tab
        ui->tabExamResultChart->setEnabled(false);  // Disable the tab
    }

    handleGetQuestionBank(examRoomId);
    QThread::msleep(100);
    handleGetUserInRoom(examRoomId);
    QThread::msleep(100);
    handleGetExamResult(examRoomId);
}

// void ExamRoomDialog::onCloseButtonClicked()
// {
//     this->close();
// }

void ExamRoomDialog::onAddQuestion()
{
    // Create the parent dialog
    QDialog *parentDialog = new QDialog(this);
    parentDialog->setWindowTitle("Create Question");
    parentDialog->resize(900, 800);  // Set desired size for the dialog

    // Create and configure the custom widget
    CreateQuestion *createQuestion = new CreateQuestion(parentDialog);
    // CreateQuestion->setRoomDetails(roomId, roomName, description, timeLimit, status);
    createQuestion->setParent(parentDialog);

    qDebug() << "Exam room ID:" << examRoomId;
    createQuestion->setRoomId(examRoomId);  // Set the room ID for the question

    // Add the custom widget to the parent dialog's layout
    QVBoxLayout *layout = new QVBoxLayout(parentDialog);
    layout->addWidget(createQuestion);
    parentDialog->setLayout(layout);

    // Show the parent dialog as modal
    parentDialog->exec();
}

// build Exam Reult Charts
void ExamRoomDialog::setupScoreChart()
{
    // Tạo dữ liệu cho phổ điểm (điểm từ 1-10)
    QBarSet *set = new QBarSet("Phổ điểm");
    *set << 1 << 2 << 5 << 8 << 10 << 12 << 7 << 6 << 3 << 2;  // Ví dụ dữ liệu phổ điểm

    // Tạo series
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Tạo chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Phổ điểm phòng thi");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Tạo trục cho chart
    QStringList categories;
    for (int i = 1; i <= 10; ++i)
        categories << QString::number(i);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Số lượng");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Tạo chart view và gán chart vào tab
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Thêm chart vào layout của tabExamResultChart
    QVBoxLayout *layout = new QVBoxLayout(ui->tabExamResultChart);
    layout->addWidget(chartView);
    ui->tabExamResultChart->setLayout(layout);
}

void ExamRoomDialog::handleGetQuestionBank(int roomId){
    QJsonObject json;
    json["room_id"] = roomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_ROOM_QUESTION\n%1").arg(QString(jsonData));

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket, &QTcpSocket::readyRead, this, &ExamRoomDialog::handleGetQuestionBankResponse);
}

void ExamRoomDialog::handleGetQuestionBankResponse() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    qDebug() << "Get question bank response from server:" << responseString;

    if (responseString.startsWith("DATA JSON ROOM_QUESTION")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1 && jsonEndIndex > jsonStartIndex) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);

            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QJsonArray questionList = jsonObj["data"].toArray();

                // Clear the list widget before populating
                ui->listQuestionBankWidget->clear();

                for (int i = 0; i < questionList.size(); ++i) {
                    QJsonObject question = questionList[i].toObject();
                    QString id = QString::number(question["id"].toInt());
                    QString content = question["content"].toString();
                    QString difficulty = QString::number(question["difficulty"].toInt());

                    // Add the question to the list widget
                    QListWidgetItem *item = new QListWidgetItem(content);
                    item->setData(Qt::UserRole, id);
                    item->setData(Qt::UserRole + 1, difficulty);
                    ui->listQuestionBankWidget->addItem(item);
                }
            } else {
                qDebug() << "JSON Parse Error:" << parseError.errorString() << " at offset:" << parseError.offset;
                qDebug() << "Partial JSON data: " << jsonString;
            }
        } else {
            qDebug() << "Incomplete JSON detected. Response length:" << responseString.length();
        }
    } else {
        qDebug() << "Unexpected response format:" << responseString;
    }
}

// "CONTROL GET_USER_IN_ROOM
// {
//   ""room_id"":  1
// }"
void ExamRoomDialog::handleGetUserInRoom(int roomId) {
    QJsonObject json;
    json["room_id"] = roomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_USER_IN_ROOM\n%1").arg(QString(jsonData));

    tcpSocket1->connectToHost("localhost", 8080);
    if (tcpSocket1->waitForConnected()) {
        tcpSocket1->write(dataString.toUtf8());
        tcpSocket1->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket1, &QTcpSocket::readyRead, this, &ExamRoomDialog::handleGetUserInRoomResponse);
}

void ExamRoomDialog::handleGetUserInRoomResponse() {
    QByteArray response = tcpSocket1->readAll();
    QString responseString(response);

    qDebug() << "Get user in room response from server:" << responseString;

    if (responseString.startsWith("DATA JSON USER_IN_ROOM")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1 && jsonEndIndex > jsonStartIndex) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);

            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QJsonArray userList = jsonObj["data"].toArray();

                // Clear the table widget before populating
                ui->userTableWidget->clearContents();

                for (int i = 0; i < userList.size(); ++i) {
                    QJsonObject user = userList[i].toObject();
                    QString userId = QString::number(user["id"].toInt());
                    QString name = user["name"].toString();
                    QString email = user["email"].toString();
                    QString dob = "N/A";  // Date of birth is not available in the response

                    // Add the user to the table widget
                    int row = ui->userTableWidget->rowCount();
                    ui->userTableWidget->insertRow(row);
                    ui->userTableWidget->setItem(row, 0, new QTableWidgetItem(userId));
                    ui->userTableWidget->setItem(row, 1, new QTableWidgetItem(name));
                    ui->userTableWidget->setItem(row, 2, new QTableWidgetItem(email));
                    ui->userTableWidget->setItem(row, 3, new QTableWidgetItem(dob));
                    ui->userTableWidget->setItem(row, 4, new QTableWidgetItem("Loại"));
                }
            } else {
                qDebug() << "JSON Parse Error:" << parseError.errorString() << " at offset:" << parseError.offset;
                qDebug() << "Partial JSON data: " << jsonString;
            }
        } else {
            qDebug() << "Incomplete JSON detected. Response length:" << responseString.length();
        }
    } else {
        qDebug() << "Unexpected response format:" << responseString;
    }
}

// "CONTROL GET_EXAM_RESULT_OF_ROOM
// {
//   ""room_id"":  1
// }"
void ExamRoomDialog::handleGetExamResult(int roomId) {
    QJsonObject json;
    json["room_id"] = roomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_EXAM_RESULT_OF_ROOM\n%1").arg(QString(jsonData));

    tcpSocket2->connectToHost("localhost", 8080);
    if (tcpSocket2->waitForConnected()) {
        tcpSocket2->write(dataString.toUtf8());
        tcpSocket2->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket2, &QTcpSocket::readyRead, this, &ExamRoomDialog::handleGetExamResultResponse);
}

void ExamRoomDialog::handleGetExamResultResponse() {
    QByteArray response = tcpSocket2->readAll();
    QString responseString(response);

    qDebug() << "Get exam result response from server:" << responseString;

    if (responseString.startsWith("DATA JSON EXAM_RESULT_OF_ROOM")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1 && jsonEndIndex > jsonStartIndex) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);

            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QJsonArray examResultList = jsonObj["data"].toArray();

                // Clear the table widget before populating
                ui->examResultTableWidget->clearContents();

                for (int i = 0; i < examResultList.size(); ++i) {
                    QJsonObject examResult = examResultList[i].toObject();
                    QString userId = QString::number(examResult["user_id"].toInt());
                    QString username = examResult["name"].toString();
                    QString email = examResult["email"].toString();
                    QString totalQuestions = QString::number(examResult["total_questions"].toInt());
                    QString correctAnswers = QString::number(examResult["correct_answers"].toInt());
                    QString score = QString::number(examResult["score"].toDouble());

                    qDebug() << "User ID:" << userId;
                    qDebug() << "Username:" << username;
                    qDebug() << "Email:" << email;
                    qDebug() << "Total Questions:" << totalQuestions;

                    // Add the exam result to the table widget
                    int row = ui->examResultTableWidget->rowCount();
                    ui->examResultTableWidget->insertRow(row);
                    ui->examResultTableWidget->setItem(row, 0, new QTableWidgetItem(userId));
                    ui->examResultTableWidget->setItem(row, 1, new QTableWidgetItem(username));
                    ui->examResultTableWidget->setItem(row, 2, new QTableWidgetItem(email));
                    ui->examResultTableWidget->setItem(row, 3, new QTableWidgetItem(totalQuestions));
                    ui->examResultTableWidget->setItem(row, 4, new QTableWidgetItem(correctAnswers));
                    ui->examResultTableWidget->setItem(row, 5, new QTableWidgetItem(score));
                }
            } else {
                qDebug() << "JSON Parse Error:" << parseError.errorString() << " at offset:" << parseError.offset;
                qDebug() << "Partial JSON data: " << jsonString;
            }
        } else {
            qDebug() << "Incomplete JSON detected. Response length:" << responseString.length();
        }
    } else {
        qDebug() << "Unexpected response format:" << responseString;
    }
}

void ExamRoomDialog::handleStartExam() {
    QJsonObject json;
    json["room_id"] = examRoomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL START_EXAM\n%1").arg(QString(jsonData));

    tcpSocket3->connectToHost("localhost", 8080);
    if (tcpSocket3->waitForConnected()) {
        tcpSocket3->write(dataString.toUtf8());
        tcpSocket3->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket3, &QTcpSocket::readyRead, this, &ExamRoomDialog::handleStartExamResponse);
}


// NOTIFICATION START_EXAM_FAIL Time
// NOTIFICATION START_EXAM_SUCCESS Time
void ExamRoomDialog::handleStartExamResponse() {
    QByteArray response = tcpSocket3->readAll();
    QString responseString(response);

    qDebug() << "Start exam response from server:" << responseString;

    if (responseString.startsWith("NOTIFICATION START_EXAM_SUCCESS")) {
        // Update the status label
        ui->status->setText("Ongoing");
        ui->startExam->setEnabled(false);
        ui->endExam->setEnabled(true);  
        ui->addQuestionButton->setEnabled(false);
        ui->addUser->setEnabled(false);

        qDebug() << "Exam started successfully";
        QMessageBox::information(this, "Start Exam Success", "Exam started successfully.");
    } else if (responseString.startsWith("NOTIFICATION START_EXAM_FAIL")) {
        // Display an error message
        qDebug() << "Failed to start the exam";

        QMessageBox::critical(this, "Start Exam Failed", "Failed to start the exam. Please try again later.");
    } else {
        qDebug() << "Unexpected response format:" << responseString;
    }
}

// "CONTROL END_EXAM
// {
//   ""room_id"": 1
// }"
void ExamRoomDialog::handleEndExam() {
    QJsonObject json;
    json["room_id"] = examRoomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL END_EXAM\n%1").arg(QString(jsonData));

    tcpSocket4->connectToHost("localhost", 8080);
    if (tcpSocket4->waitForConnected()) {
        tcpSocket4->write(dataString.toUtf8());
        tcpSocket4->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket4, &QTcpSocket::readyRead, this, &ExamRoomDialog::handleEndExamResponse);
}

// "NOTIFICATION END_EXAM_SUCCESS 2024-12-24T21:10:34
// {
//   ""message"": ""Exam ended successfully""
// }
// "
void ExamRoomDialog::handleEndExamResponse() {
    QByteArray response = tcpSocket4->readAll();
    QString responseString(response);

    qDebug() << "End exam response from server:" << responseString;

    if (responseString.startsWith("NOTIFICATION END_EXAM_SUCCESS")) {
        // Update the status label
        ui->status->setText("Finished");
        ui->startExam->setEnabled(false);
        ui->endExam->setEnabled(false);
        ui->addQuestionButton->setEnabled(false);
        ui->addUser->setEnabled(false);
        ui->tabExamResult->setEnabled(true);  
        ui->tabExamResultChart->setEnabled(true);  

        qDebug() << "Exam ended successfully";
        QMessageBox::information(this, "End Exam Success", "Exam ended successfully.");
    } else {
        qDebug() << "Unexpected response format:" << responseString;
    }
}