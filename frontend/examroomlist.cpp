// frontend/sources/examroomlist.cpp
#include "examroomlist.h"
#include "ui_examroomlist.h"
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

    connect(userManagementAction, &QAction::triggered, [this]() {
        emit showUserManagement();
    });

    connect(examRoomManagementAction, &QAction::triggered, [this]() {
        qDebug() << "showExamRoomManagement";
        emit showExamRoomManagement();
    });

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_ROOM_LIST\n%1");

    tcpSocket->connectToHost("localhost", 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    }

}

ExamRoomList::~ExamRoomList()
{
    delete ui;
}

void ExamRoomList::on_searchButton_clicked()
{
    // Implement search functionality here
}

void ExamRoomList::on_avatarButton_clicked()
{
    // Implement avatar button functionality here
}

void ExamRoomList::handleJoinButtonClicked(QListWidgetItem *item)
{
    // Implement join button functionality here
    // For example, you can display a message box with the item text
    // QMessageBox::information(this, "Join Exam Room", "Joining " + item->text());
    // Emit signal to show Exam Room Detail UI
    emit showExamRoomDetail();
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

    QLabel *timeLimitLabel = new QLabel("Time Limit: " + QString::number(examRoom["time_limit"].toInt()) + " minutes");
    QLabel *startTimeLabel = new QLabel("Start Time: " + examRoom["start"].toString());
    QLabel *endTimeLabel = new QLabel("End Time: " + examRoom["end"].toString());

    QPushButton *joinButton = new QPushButton("Join");

    layout->addWidget(subjectLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(timeLimitLabel);
    layout->addWidget(startTimeLabel);
    layout->addWidget(endTimeLabel);
    layout->addWidget(joinButton);
    itemWidget->setLayout(layout);

    item->setSizeHint(itemWidget->sizeHint());  // Ensure the item has the correct size
    ui->examRoomList->addItem(item);
    ui->examRoomList->setItemWidget(item, itemWidget);

    connect(joinButton, &QPushButton::clicked, [this, item]() {
        handleJoinButtonClicked(item);
    });
}

void ExamRoomList::onReadyRead() {
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    if (responseString.startsWith("DATA JSON 1896 ALL_ROOM")) {
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
