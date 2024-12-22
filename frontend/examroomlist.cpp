// frontend/sources/examroomlist.cpp
#include "examroomlist.h"
#include "ui_examroomlist.h"
#include <userdata.h>

#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ExamRoomList::ExamRoomList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomList),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &ExamRoomList::onReadyRead);
    connect(tcpSocket, &QTcpSocket::connected, this, &ExamRoomList::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ExamRoomList::onDisconnected);

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListAction = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *userManagementAction = new QAction("User Management", this);
    QAction *examRoomManagementAction = new QAction("Exam Room Management", this);
    QAction *practicesAction = new QAction("Logout", this);

    menu->addAction(examRoomListAction);
    menu->addAction(profileAction);
    menu->addAction(userManagementAction);
    menu->addAction(examRoomManagementAction);
    menu->addAction(practicesAction);

    ui->avatarButton->setMenu(menu);

    connect(profileAction, &QAction::triggered, [this]() {
        emit showProfile();
    });

    connect(userManagementAction, &QAction::triggered, [this]() {
        emit showUserManagement();
    });

    connect(examRoomManagementAction, &QAction::triggered, [this]() {
        qDebug() << "showExamRoomManagement";
        emit showExamRoomManagement();
    });

}

ExamRoomList::~ExamRoomList()
{
    delete ui;
}

void ExamRoomList::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    // reset prev UI
    ui->examRoomList->clear();

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_ROOM_LIST\n%1");

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }
}

void ExamRoomList::on_searchButton_clicked()
{
    // Implement search functionality here
}

void ExamRoomList::on_avatarButton_clicked()
{
    // Implement avatar button functionality here
}

void ExamRoomList::handleJoinButtonClicked(int roomId)
{
    // Implement join button functionality here
    // For example, you can display a message box with the item text
    // QMessageBox::information(this, "Join Exam Room", "Joining " + item->text());
    // Emit signal to show Exam Room Detail UI
    emit showExamRoomDetail(roomId);
}

void ExamRoomList::populateExamRoomList(const QJsonArray &examRooms)
{
    qDebug() << "Populating exam rooms. Number of rooms:" << examRooms.size();
    foreach (const QJsonValue &value, examRooms) {
        QJsonObject examRoom = value.toObject();
        qDebug() << "Creating item for subject:" << examRoom["subject"].toString();
        createExamRoomItem(examRoom);
    }
    qDebug() << "Finished populating. Total items in list:" << ui->examRoomList->count();
}

void ExamRoomList::createExamRoomItem(const QJsonObject &examRoom)
{
    qDebug() << "Adding exam room:" << examRoom["subject"].toString();

    QListWidgetItem *item = new QListWidgetItem(ui->examRoomList);
    QWidget *itemWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(itemWidget);

    QFont subjectFont;
    subjectFont.setPointSize(14); // Set font size
    subjectFont.setBold(true);    // Set font weight to bold


    QLabel *subjectLabel = new QLabel(examRoom["subject"].toString());
    subjectLabel->setFont(subjectFont);
    qDebug() << "Subject label created with text:" << subjectLabel->text();

    QLabel *descriptionLabel = new QLabel(examRoom["description"].toString());
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setMaximumHeight(40);

    QLabel *numberOfEasyQuestionLabel = new QLabel("Số câu dễ: " + QString::number(examRoom["number_of_easy_question"].toInt()));
    QLabel *numberOfMediumQuestionLabel = new QLabel("Số câu trung bình: " + QString::number(examRoom["number_of_medium_question"].toInt()));
    QLabel *numberOfHardQuestionLabel = new QLabel("Số câu khó: " + QString::number(examRoom["number_of_hard_question"].toInt()));
    QLabel *timeLimitLabel = new QLabel("Time Limit: " + QString::number(examRoom["time_limit"].toInt()) + " minutes");
    QLabel *startTimeLabel = new QLabel("Start Time: " + examRoom["start"].toString());
    QLabel *endTimeLabel = new QLabel("End Time: " + examRoom["end"].toString());
    QLabel *statusLabel = new QLabel("Status: " + examRoom["status"].toString());
    QLabel *statusUserLabel = new QLabel(this);

    // status : Not Started, Ongoing, Finished
    // Not Started: Chưa bắt đầu => Users joined => Marked Joined On Button Join => Button: "View"
    // Ongoing: Đang diễn ra => Users joined => Can view ; Users not joined => Can't join
    // Finished: Đã kết thúc => Users joined => Marked Joined On Button Join => Button: "View"; 
    // Users not joined => Can't join
    int userId = UserData::instance().getUserId();

    QPushButton *joinButton = new QPushButton(this);
    joinButton->setCursor(Qt::PointingHandCursor);
    QJsonArray userIds = examRoom["user_ids"].toArray();
    bool userJoined = false;
    for (const QJsonValue &value : userIds) {
        if (value.toInt() == userId) {
            userJoined = true;
            break;
        }
    }

    if (userJoined) {
        joinButton->setText("View");
        joinButton->setStyleSheet("background-color: #007bff; color: white; font-weight: bold;");

        statusUserLabel->setText("Joined");
        statusUserLabel->setStyleSheet("color: green; font-weight: bold;");
    } else {
        statusUserLabel->setText("Not Joined");
        statusUserLabel->setStyleSheet("color: green; font-weight: bold;");

        QString status = examRoom["status"].toString();
        if (status == "Not started") {
            joinButton->setText("Join");
            joinButton->setStyleSheet("background-color: #007bff; color: white; font-weight: bold;");
        } else {
            joinButton->setText("Can't Join");
            joinButton->setEnabled(false);
            joinButton->setStyleSheet("background-color: #6c757d; color: white; font-weight: bold;");
        }
    }

    layout->addWidget(subjectLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(numberOfEasyQuestionLabel);
    layout->addWidget(numberOfMediumQuestionLabel);
    layout->addWidget(numberOfHardQuestionLabel);
    layout->addWidget(timeLimitLabel);
    layout->addWidget(startTimeLabel);
    layout->addWidget(endTimeLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(statusUserLabel);
    layout->addWidget(joinButton);
    itemWidget->setLayout(layout);

    item->setSizeHint(itemWidget->sizeHint());  // Ensure the item has the correct size
    ui->examRoomList->addItem(item);
    ui->examRoomList->setItemWidget(item, itemWidget);

    connect(joinButton, &QPushButton::clicked, [this, item, examRoom, userJoined, userId]() {
        // join exam room 
        QString status = examRoom["status"].toString();
        int roomId = examRoom["id"].toInt();
        if (!userJoined && status == "Not started") {
            callApiJoinExamRoom(userId, roomId);
        }

        handleJoinButtonClicked(roomId);
    });
}

void ExamRoomList::callApiJoinExamRoom(int userId, int roomId) {
    qDebug() << "Join button clicked for room ID:" << roomId;

    // Construct the JSON object for the request
    QJsonObject json;
    json["user_id"] = userId;
    json["room_id"] = roomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL USER_ENTER_ROOM\n%1").arg(QString(jsonData));

    qDebug() << "Sending join room request: " << dataString;

    if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket->connectToHost("localhost", 8080);
        if (!tcpSocket->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket->errorString();
        return;
    }

    if (!tcpSocket->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket->errorString();
        return;
    }

    qDebug() << "Join room request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ExamRoomList::handleJoinRoomResponse);
}

void ExamRoomList::handleJoinRoomResponse() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    qDebug() << "Join room response from server:" << responseString;

    // Process the response as needed
}

void ExamRoomList::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    if (responseString.startsWith("DATA JSON GET_ROOM_LIST")) {
            qDebug() << "Room List Response:" << responseString;

            // Extract JSON part from the response
            int jsonStartIndex = responseString.indexOf('{');
            int jsonEndIndex = responseString.lastIndexOf('}');
            if (jsonStartIndex != -1 && jsonEndIndex != -1) {
                QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
                QJsonParseError parseError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
                if (parseError.error == QJsonParseError::NoError) {
                    QJsonObject jsonObj = jsonDoc.object();
                    QJsonArray roomList = jsonObj["data"].toArray();
                    populateExamRoomList(roomList);
                } else {
                    qDebug() << "JSON Parse Error:" << parseError.errorString();
                }
            } else {
                qDebug() << "Invalid JSON format in response";
            }
        } else {
            qDebug() << "Unknown response from server:" << responseString;
    }

}

void ExamRoomList::onConnected() {
    qDebug() << "Connected to server.";
}

void ExamRoomList::onDisconnected() {
    qDebug() << "Disconnected from server.";
}