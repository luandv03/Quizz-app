#include "examroomlist.h"
#include "ui_examroomlist.h"
#include <QMenu>
#include <QAction>
#include <QListWidgetItem>

ExamRoomList::ExamRoomList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomList)
{
    ui->setupUi(this);

    // Populate the exam room list
    populateExamRoomList();

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListAction = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *practicesAction = new QAction("Practices", this);

    menu->addAction(examRoomListAction);
    menu->addAction(profileAction);
    menu->addAction(practicesAction);

    ui->avatarButton->setMenu(menu);

    // Connect the join button signal to the slot
    connect(ui->examRoomList, &QListWidget::itemClicked, this, &ExamRoomList::on_joinButton_clicked);
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

void ExamRoomList::on_joinButton_clicked(QListWidgetItem *item)
{
    // Implement join button functionality here
}

void ExamRoomList::populateExamRoomList()
{
    // Example data
    QStringList examRooms = {
        "Exam Room 1",
        "Exam Room 2",
        "Exam Room 3"
    };

    foreach (const QString &room, examRooms) {
        QListWidgetItem *item = new QListWidgetItem(room, ui->examRoomList);
        QPushButton *joinButton = new QPushButton("Join", ui->examRoomList);
        ui->examRoomList->addItem(item);
        ui->examRoomList->setItemWidget(item, joinButton);

        // Connect the join button signal to the slot
        connect(joinButton, &QPushButton::clicked, [this, item]() {
            on_joinButton_clicked(item);
        });
    }
}
