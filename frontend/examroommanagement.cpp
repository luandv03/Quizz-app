#include "examroommanagement.h"
#include "ui_examroommanagement.h"
#include "examroomdialog.h"
#include "createexamroom.h"
#include "userdata.h"

#include <QMenu>
#include <QMessageBox>
#include <QScreen>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "config.h"
ExamRoomManagement::ExamRoomManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomManagement),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    showMenuNavigator();

    // Set up the table columns
    ui->examRoomTableWidget->setColumnCount(11);
    QStringList headers = {"Id", "Ten phong thi", "Mo ta", "Time Limit", "So cau de",  "So cau trung binh", "So cau kho", "Start time", "End time", "Trang thai", "Hanh dong"};
    ui->examRoomTableWidget->setHorizontalHeaderLabels(headers);

    // Make the header bold
    QHeaderView *header = ui->examRoomTableWidget->horizontalHeader();
    QFont headerFont = header->font();
    headerFont.setBold(true);
    header->setFont(headerFont);

    // Optional: Adjust alignment and resize behavior
    header->setDefaultAlignment(Qt::AlignCenter); // Center alignment for the headers
    ui->examRoomTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Adjust columns to fill the table width

    // show modal to create exam room
    connect(ui->createExamRoomBtn, &QPushButton::clicked, [this]() {
        onCreateExamRoomBtn();
    });
}

ExamRoomManagement::~ExamRoomManagement()
{
    delete ui;
}

void ExamRoomManagement::showEvent(QShowEvent *event) {
    showMenuNavigator();

    handleGetExamRoom();
}

void ExamRoomManagement::showMenuNavigator()
{
    // Implement search functionality here
    QString role = UserData::instance().getRole();

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);

    if (role == "admin") {
        QAction *profileAction = new QAction("Profile", this);
        QAction *userManagementAction = new QAction("User Management", this);
        QAction *examRoomManagementAction = new QAction("Exam Room Management", this);
        QAction *logoutAction = new QAction("Logout", this);

        menu->addAction(profileAction);
        menu->addAction(userManagementAction);
        menu->addAction(examRoomManagementAction);
        menu->addAction(logoutAction);

        ui->avatarButton->setMenu(menu);

        connect(profileAction, &QAction::triggered, [this]() {
            emit showProfile();
        });

        connect(userManagementAction, &QAction::triggered, [this]() {
            emit showUserManagement();
        });

        connect(logoutAction, &QAction::triggered, [this]() {
            emit logout();
        });
    } else {
        QAction *examRoomListAction = new QAction("Exam Room List", this);
        QAction *profileAction = new QAction("Profile", this);
        QAction *logoutAction = new QAction("Logout", this);

        menu->addAction(examRoomListAction);
        menu->addAction(profileAction);
        menu->addAction(logoutAction);

        ui->avatarButton->setMenu(menu);

        connect(examRoomListAction, &QAction::triggered, [this]() {
            emit showExamRoomList();
        });

        connect(logoutAction, &QAction::triggered, [this]() {
            emit logout();
        });
    }

    ui->avatarButton->setText(UserData::instance().getUserName());
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
    // Get exam room details from the table
    QString roomId = ui->examRoomTableWidget->item(row, 0)->text();
    QString roomName = ui->examRoomTableWidget->item(row, 1)->text();
    QString description = ui->examRoomTableWidget->item(row, 2)->text();
    QString timeLimit = ui->examRoomTableWidget->item(row, 3)->text();
    QString status = ui->examRoomTableWidget->item(row, 9)->text();
    QString start = ui->examRoomTableWidget->item(row, 7)->text();
    QString end = ui->examRoomTableWidget->item(row, 8)->text();

    qDebug() << "View button clicked for row:" << row << "Room ID:" << roomId;
    qDebug() << "Room Name:" << roomName << "Description:" << description << "Time Limit:" << timeLimit << "Status:" << status;

    // Create the parent dialog
    QDialog *parentDialog = new QDialog(this);
    parentDialog->setWindowTitle("Exam Room Details");
    parentDialog->resize(900, 800);  // Set desired size for the dialog

    // Create and configure the custom widget
    ExamRoomDialog *examRoomDialog = new ExamRoomDialog(parentDialog);
    examRoomDialog->setRoomDetails(roomId, roomName, description, timeLimit, status, start, end);
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

void ExamRoomManagement::handleGetExamRoom(){
    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_ROOM_LIST\n%1");

    tcpSocket->connectToHost(IPADDRESS, 8080);
    if (tcpSocket->waitForConnected()) {
        tcpSocket->write(dataString.toUtf8());
        tcpSocket->flush();
    } else {
        qDebug() << "Failed to connect to server";
    }

    connect(tcpSocket, &QTcpSocket::readyRead, this, &ExamRoomManagement::handleGetExamRoomResponse);
}

void ExamRoomManagement::handleGetExamRoomResponse(){
    QByteArray response = tcpSocket->readAll();
    QString responseString(response);

    qDebug() << "Get exam room response from server:" << responseString;

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
                    QJsonObject jsonObject = jsonDoc.object();
                    QJsonArray examRoomList = jsonObject["data"].toArray();

                    // Clear the table before populating
                    ui->examRoomTableWidget->setRowCount(0);

                    for (int i = 0; i < examRoomList.size(); ++i) {
                        QJsonObject examRoom = examRoomList[i].toObject();
                        QString id = QString::number(examRoom["id"].toInt());
                        QString subject = examRoom["subject"].toString();
                        QString description = examRoom["description"].toString();
                        QString timeLimit = QString::number(examRoom["time_limit"].toInt());
                        QString numberOfEasyQuestion = QString::number(examRoom["number_of_easy_question"].toInt());
                        QString numberOfMediumQuestion = QString::number(examRoom["number_of_medium_question"].toInt());
                        QString numberOfHardQuestion = QString::number(examRoom["number_of_hard_question"].toInt());
                        QString status = examRoom["status"].toString();
                        QString start = examRoom["start"].toString();
                        QString end = examRoom["end"].toString();

                        // Add the exam room to the table
                        ui->examRoomTableWidget->insertRow(i);
                        QTableWidgetItem *idItem = new QTableWidgetItem(id);
                        QTableWidgetItem *subjectItem = new QTableWidgetItem(subject);
                        QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);
                        QTableWidgetItem *timeLimitItem = new QTableWidgetItem(timeLimit);
                        QTableWidgetItem *numberOfEasyQuestionLabel = new QTableWidgetItem(numberOfEasyQuestion);
                        QTableWidgetItem *numberOfMediumQuestionLabel = new QTableWidgetItem(numberOfMediumQuestion);
                        QTableWidgetItem *numberOfHardQuestionLabel = new QTableWidgetItem(numberOfHardQuestion);
                        QTableWidgetItem *startTimeLabel = new QTableWidgetItem(start);
                        QTableWidgetItem *endTimeLabel = new QTableWidgetItem(end);
                        QTableWidgetItem *statusItem = new QTableWidgetItem(status);

                        ui->examRoomTableWidget->setItem(i, 0, idItem);
                        ui->examRoomTableWidget->setItem(i, 1, subjectItem);
                        ui->examRoomTableWidget->setItem(i, 2, descriptionItem);
                        ui->examRoomTableWidget->setItem(i, 3, timeLimitItem);
                        ui->examRoomTableWidget->setItem(i, 4, numberOfEasyQuestionLabel);
                        ui->examRoomTableWidget->setItem(i, 5, numberOfMediumQuestionLabel);
                        ui->examRoomTableWidget->setItem(i, 6, numberOfHardQuestionLabel);
                        ui->examRoomTableWidget->setItem(i, 7, startTimeLabel);
                        ui->examRoomTableWidget->setItem(i, 8, endTimeLabel);
                        ui->examRoomTableWidget->setItem(i, 9, statusItem);

                        // Add view button
                        QPushButton *viewButton = new QPushButton("View");
                        ui->examRoomTableWidget->setCellWidget(i, 10, viewButton);

                        // Connect the view button signal to the slot
                        connect(viewButton, &QPushButton::clicked, [this, i]() {
                            onViewButtonClicked(i);
                        });
                    }

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

