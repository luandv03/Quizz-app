// frontend/sources/examroomlist.cpp
#include "profile.h"
#include "ui_profile.h"

#include "userdata.h"

#include <QMenu>

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

    qDebug() << "Profile constructor";

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListACtion = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *userManagementAction = new QAction("User Management", this);
    QAction *examRoomManagementAction = new QAction("Exam Room Management", this);
    QAction *practicesAction = new QAction("Logout", this);

    menu->addAction(examRoomListACtion);
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

    connect(examRoomListACtion, &QAction::triggered, [this]() {
        emit showExamRoomList();
    });


    // Giả lập dữ liệu từ backend
    QString userName = UserData::instance().getUserName();
    QString email = UserData::instance().getEmail();
    QString dob = UserData::instance().getDob();
    QString password = "password123";

    // Gán dữ liệu cho QLineEdit
    ui->userNameLineEdit->setText(userName);
    ui->emailLineEdit->setText(email);
    ui->dobLineEdit->setText(dob);
    ui->passwordLineEdit->setText(password);
    
    ui->saveButton->setCursor(Qt::PointingHandCursor);

    // Kết nối sự kiện thay đổi để kích hoạt nút Save
    connect(ui->userNameLineEdit, &QLineEdit::textChanged, this, &Profile::checkForChanges);
    connect(ui->emailLineEdit, &QLineEdit::textChanged, this, &Profile::checkForChanges);
    connect(ui->dobLineEdit, &QLineEdit::textChanged, this, &Profile::checkForChanges);
    connect(ui->passwordLineEdit, &QLineEdit::textChanged, this, &Profile::checkForChanges);

    // Xử lý hiện/ẩn mật khẩu
    connect(ui->togglePasswordButton, &QPushButton::clicked, this, &Profile::togglePasswordVisibility);

    // Xử lý lưu dữ liệu
    connect(ui->saveButton, &QPushButton::clicked, this, &Profile::saveProfile);

}

Profile::~Profile()
{
    delete ui;
}

void Profile::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    
    // Giả lập dữ liệu từ backend
    QString userName = UserData::instance().getUserName();
    QString email = UserData::instance().getEmail();
    QString dob = UserData::instance().getDob();
    QString password = "password123";

    // Gán dữ liệu cho QLineEdit
    ui->userNameLineEdit->setText(userName);
    ui->emailLineEdit->setText(email);
    ui->dobLineEdit->setText(dob);
    ui->passwordLineEdit->setText(password);
}

void Profile::checkForChanges()
{
    // Kích hoạt nút Save nếu có sự thay đổi
    bool isModified = (
        ui->userNameLineEdit->isModified() ||
        ui->emailLineEdit->isModified() ||
        ui->dobLineEdit->isModified() ||
        ui->passwordLineEdit->isModified()
    );

    ui->saveButton->setEnabled(isModified);
}

void Profile::togglePasswordVisibility()
{
    // Hiện hoặc ẩn mật khẩu
    if (ui->passwordLineEdit->echoMode() == QLineEdit::Password) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setText("🔒");
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setText("👁️");
    }
}

void Profile::saveProfile()
{
    // Lấy dữ liệu từ các QLineEdit
    QString userName = ui->userNameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString dob = ui->dobLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    qDebug() << "Saving profile with the following data:";
    qDebug() << "UserName:" << userName;
    qDebug() << "Email:" << email;
    qDebug() << "Date of Birth:" << dob;
    qDebug() << "Password:" << password;

    // Thực hiện lưu dữ liệu lên backend (ví dụ giả lập)
    ui->saveButton->setEnabled(false);
}

