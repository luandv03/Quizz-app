#include "usermanagement.h"
#include "ui_usermanagement.h"

#include <QMenu>
#include <QMessageBox>
#include <QScreen>

UserManagement::UserManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagement)
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
        qDebug() << "show exam roomlist";
        emit showExamRoomList();
    });

    connect(examRoomManagementAction, &QAction::triggered, [this]() {
        qDebug() << "showExamRoomManagement";
        emit showExamRoomManagement();
    });

    // Set up the table columns
    ui->userTableWidget->setColumnCount(5);
    QStringList headers = {"userId", "name", "email", "dob", "view"};
    ui->userTableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with example data
    populateTable();
}

UserManagement::~UserManagement()
{
    delete ui;
}

void UserManagement::populateTable()
{
    // Example data
    QList<QList<QString>> users = {
        {"1", "John Doe", "john@example.com", "1990-01-01"},
        {"2", "Jane Smith", "jane@example.com", "1992-02-02"},
        {"3", "Alice Johnson", "alice@example.com", "1994-03-03"}
    };

    for (int i = 0; i < users.size(); ++i) {
        ui->userTableWidget->insertRow(i);
        for (int j = 0; j < users[i].size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(users[i][j]);
            ui->userTableWidget->setItem(i, j, item);
        }

        // Add view button
        QPushButton *viewButton = new QPushButton("View");
        ui->userTableWidget->setCellWidget(i, 4, viewButton);

        // Connect the view button signal to the slot
        connect(viewButton, &QPushButton::clicked, [this, i]() {
            onViewButtonClicked(i);
        });
    }
}

void UserManagement::onViewButtonClicked(int row)
{
    // Get user details from the table
    QString userId = ui->userTableWidget->item(row, 0)->text();
    QString name = ui->userTableWidget->item(row, 1)->text();
    QString email = ui->userTableWidget->item(row, 2)->text();
    QString dob = ui->userTableWidget->item(row, 3)->text();

    // Create and configure the dialog
    QDialog userDetailDialog(this);
    userDetailDialog.setWindowTitle("User Details");

    QVBoxLayout *layout = new QVBoxLayout(&userDetailDialog);

    QLabel *userIdLabel = new QLabel("User ID: " + userId);
    QLabel *nameLabel = new QLabel("Name: " + name);
    QLabel *emailLabel = new QLabel("Email: " + email);
    QLabel *dobLabel = new QLabel("DOB: " + dob);

    layout->addWidget(userIdLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(emailLabel);
    layout->addWidget(dobLabel);

    // Set the dialog size to match the screen size
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    userDetailDialog.setGeometry(screenGeometry);

    // Show the dialog as a modal
    userDetailDialog.exec();

    // Hide user management view (optional)
    // this->hide();
}



