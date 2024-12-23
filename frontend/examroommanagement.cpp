#include "examroommanagement.h"
#include "ui_examroommanagement.h"
#include "examroomdialog.h"
#include "createexamroom.h"

#include <QMenu>
#include <QMessageBox>
#include <QScreen>

ExamRoomManagement::ExamRoomManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomManagement)
{
    ui->setupUi(this);

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

    connect(examRoomListAction, &QAction::triggered, [this]() {
        emit showExamRoomList();
    });

    connect(userManagementAction, &QAction::triggered, [this]() {
        emit showUserManagement();
    });

    // Set up the table columns
    ui->examRoomTableWidget->setColumnCount(6);
    QStringList headers = {"Id", "Ten phong thi", "Mo ta", "Time Limit", "Trang thai",  "Hanh dong"};
    ui->examRoomTableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with example data
    populateTable();

    // show modal to create exam room
    connect(ui->createExamRoomBtn, &QPushButton::clicked, [this]() {
        onCreateExamRoomBtn();
    });
}

ExamRoomManagement::~ExamRoomManagement()
{
    delete ui;
}

void ExamRoomManagement::populateTable()
{
    // Example data
    QList<QList<QString>> examRoomList = {
        {"1", "Thi cuoi ky lap trinh mabg", "Thi cuoi ky lap trinh mang 2024", "60 phut", "Chua bat dau"},
        {"2", "Thi cuoi ky Chuong trinh dich", "Thi cuoi ky Chuong trinh dich 2024", "1 gio 30 phut", "Da thi"},
        {"3", "Thi cuoi ky Mang may tinh", "Thi cuoi ky Mang may tinh 2024", "80 phut", "Chua bat dau"},
        {"4", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"5", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"6", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"7", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"8", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"9", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"},
        {"10", "Thi cuoi ky Toan roi rac", "Thi cuoi ky Toan roi rac 2024", "2 gio", "Chua bat dau"}
        
    };

    for (int i = 0; i < examRoomList.size(); ++i) {
        ui->examRoomTableWidget->insertRow(i);
        for (int j = 0; j < examRoomList[i].size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(examRoomList[i][j]);
            ui->examRoomTableWidget->setItem(i, j, item);
        }

        // Add view button
        QPushButton *viewButton = new QPushButton("View");
        ui->examRoomTableWidget->setCellWidget(i, 5, viewButton);

        // Connect the view button signal to the slot
        connect(viewButton, &QPushButton::clicked, [this, i]() {
            onViewButtonClicked(i);
        });
    }
}

void ExamRoomManagement::onViewButtonClicked(int row)
{
    // Get user details from the table
    QString roomId = ui->examRoomTableWidget->item(row, 0)->text();
    QString roomName = ui->examRoomTableWidget->item(row, 1)->text();
    QString description = ui->examRoomTableWidget->item(row, 2)->text();
    QString timeLimit = ui->examRoomTableWidget->item(row, 3)->text();
    QString status = ui->examRoomTableWidget->item(row, 4)->text();

    // Create the parent dialog
    QDialog *parentDialog = new QDialog(this);
    parentDialog->setWindowTitle("Exam Room Details");
    parentDialog->resize(900, 800);  // Set desired size for the dialog

    // Create and configure the custom widget
    ExamRoomDialog *examRoomDialog = new ExamRoomDialog(parentDialog);
    examRoomDialog->setRoomDetails(roomId, roomName, description, timeLimit, status);
    examRoomDialog->setParent(parentDialog);

    // Add the custom widget to the parent dialog's layout
    QVBoxLayout *layout = new QVBoxLayout(parentDialog);
    layout->addWidget(examRoomDialog);
    parentDialog->setLayout(layout);

    // Show the parent dialog as modal
    parentDialog->exec();
}

void ExamRoomManagement::onCreateExamRoomBtn()
{
    // Create the parent dialog
    QDialog *parentDialog = new QDialog(this);
    parentDialog->setWindowTitle("Create Exam Room");
    parentDialog->resize(900, 800);  // Set desired size for the dialog

    // Create and configure the custom widget
    CreateExamRoom *createExamRoom = new CreateExamRoom(parentDialog);
    createExamRoom->setParent(parentDialog);

    // Add the custom widget to the parent dialog's layout
    QVBoxLayout *layout = new QVBoxLayout(parentDialog);
    layout->addWidget(createExamRoom);
    parentDialog->setLayout(layout);

    // Show the parent dialog as modal
    parentDialog->exec();
}



