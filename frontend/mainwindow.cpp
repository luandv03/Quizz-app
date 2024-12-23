// frontend/sources/mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tcpSocket(new QTcpSocket(this))
    , signupForm(new Signup(this))
    , signinForm(new Signin(this))
    , homeForm(new Home(this))
    , profileForm(new Profile(this))
    , examRoomListForm(new ExamRoomList(this))
    , examRoomDetailForm(new ExamRoomDetail(this))
    , userManagement(new UserManagement(this))
    , examRoomManagement(new ExamRoomManagement(this))
{
    ui->setupUi(this);

    // Add forms to the stacked widget
    ui->stackedWidget->addWidget(homeForm);
    ui->stackedWidget->addWidget(signupForm);
    ui->stackedWidget->addWidget(signinForm);
    ui->stackedWidget->addWidget(examRoomListForm);
    ui->stackedWidget->addWidget(examRoomDetailForm);
    ui->stackedWidget->addWidget(userManagement);
    ui->stackedWidget->addWidget(examRoomManagement);
    ui->stackedWidget->addWidget(profileForm);

    // Connect signals to slots
    connect(homeForm, &Home::showSignup, this, &MainWindow::showSignup);
    connect(homeForm, &Home::showSignin, this, &MainWindow::showSignin);
    connect(signupForm, &Signup::showHome, this, &MainWindow::showHome);
    connect(signinForm, &Signin::showHome, this, &MainWindow::showHome);
    connect(signinForm, &Signin::showExamRoomList, this, &MainWindow::showExamRoomList);
    connect(signinForm, &Signin::showUserManagement, this, &MainWindow::showUserManagement);
    connect(profileForm, &Profile::showExamRoomList, this, &MainWindow::showExamRoomList);
    connect(profileForm, &Profile::showUserManagement, this, &MainWindow::showUserManagement);
    connect(profileForm, &Profile::logout, this, &MainWindow::logout);
    connect(profileForm, &Profile::showExamRoomManagement, this, &MainWindow::showExamRoomManagement);
    connect(examRoomListForm, &ExamRoomList::showExamRoomDetail, this, &MainWindow::showExamRoomDetail);
    connect(examRoomListForm, &ExamRoomList::showUserManagement, this, &MainWindow::showUserManagement);
    connect(examRoomListForm, &ExamRoomList::showExamRoomManagement, this, &MainWindow::showExamRoomManagement);
    connect(examRoomListForm, &ExamRoomList::showProfile, this, &MainWindow::showProfile);
    connect(examRoomListForm, &ExamRoomList::logout, this, &MainWindow::logout);
    connect(examRoomDetailForm, &ExamRoomDetail::showExamRoomList, this, &MainWindow::showExamRoomList);
    connect(examRoomDetailForm, &ExamRoomDetail::showUserManagement, this, &MainWindow::showUserManagement);
    connect(examRoomDetailForm, &ExamRoomDetail::showExamRoomManagement, this, &MainWindow::showExamRoomManagement);
    connect(examRoomDetailForm, &ExamRoomDetail::showProfile, this, &MainWindow::showProfile);
    connect(examRoomDetailForm, &ExamRoomDetail::logout, this, &MainWindow::logout);
    connect(userManagement, &UserManagement::showExamRoomList, this, &MainWindow::showExamRoomList);
    connect(userManagement, &UserManagement::showExamRoomManagement, this, &MainWindow::showExamRoomManagement);
    connect(userManagement, &UserManagement::showProfile, this, &MainWindow::showProfile);
    connect(userManagement, &UserManagement::logout, this, &MainWindow::logout);
    connect(examRoomManagement, &ExamRoomManagement::showExamRoomList, this, &MainWindow::showExamRoomList);
    connect(examRoomManagement, &ExamRoomManagement::showUserManagement, this, &MainWindow::showUserManagement);
    connect(examRoomManagement, &ExamRoomManagement::showProfile, this, &MainWindow::showProfile);
    connect(examRoomManagement, &ExamRoomManagement::logout, this, &MainWindow::logout);

    // Connect signals to slots
    // connect(signinForm->findChild<QPushButton *>("signinButton"), &QPushButton::clicked,
    //         this, &MainWindow::showExamRoomList);

    // Show the signin form initially
    ui->stackedWidget->setCurrentWidget(signinForm);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showSignup() {
    ui->stackedWidget->setCurrentWidget(signupForm);
}

void MainWindow::showSignin() {
    ui->stackedWidget->setCurrentWidget(signinForm);
}

void MainWindow::showHome() {
    ui->stackedWidget->setCurrentWidget(homeForm);
}

void MainWindow::showExamRoomList() {
    ui->stackedWidget->setCurrentWidget(examRoomListForm);
}

void MainWindow::showExamRoomDetail(int roomId) {
    qDebug() << "Switching to ExamRoomDetail UI";
    examRoomDetailForm->setRoomId(roomId); // Pass the roomId to ExamRoomDetail
    ui->stackedWidget->setCurrentWidget(examRoomDetailForm);
}

void MainWindow::showUserManagement() {
    ui->stackedWidget->setCurrentWidget(userManagement);
}

void MainWindow::showExamRoomManagement() {
    ui->stackedWidget->setCurrentWidget(examRoomManagement);
}

void MainWindow::showProfile() {
    ui->stackedWidget->setCurrentWidget(profileForm);
}

void MainWindow::logout() {
    UserData::instance().reset();
    emit showSignin();
}