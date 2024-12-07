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
    ui(new Ui::ExamRoomList)
{
    ui->setupUi(this);

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListAction = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *practicesAction = new QAction("Practices", this);

    menu->addAction(examRoomListAction);
    menu->addAction(profileAction);
    menu->addAction(practicesAction);

    ui->avatarButton->setMenu(menu);

    // Example JSON data
    QString jsonData = R"(
    {
        "data": [
            {
                "id": 1,
                "subject": "Math",
                "description": "Basic math questions",
                "number_of_easy_question": 10,
                "number_of_medium_question": 5,
                "number_of_hard_question": 2,
                "time_limit": 60,
                "start": "2023-10-01 10:00:00",
                "end": "2023-10-01 11:00:00",
                "user_ids": [1, 2]
            },
            {
                "id": 4,
                "subject": "Geography",
                "description": "Geography questions",
                "number_of_easy_question": 7,
                "number_of_medium_question": 8,
                "number_of_hard_question": 6,
                "time_limit": 70,
                "start": "2023-10-05 15:00:00",
                "end": "2023-10-05 16:10:00",
                "user_ids": []
            }
        ]
    }
    )";

    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray examRooms = obj["data"].toArray();

    // Populate the exam room list
    populateExamRoomList(examRooms);
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
    QMessageBox::information(this, "Join Exam Room", "Joining " + item->text());
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

