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
    , examRoomListForm(new ExamRoomList(this))
{
    ui->setupUi(this);

    // Add forms to the stacked widget
    ui->stackedWidget->addWidget(homeForm);
    ui->stackedWidget->addWidget(signupForm);
    ui->stackedWidget->addWidget(signinForm);

    // Connect signals to slots
    connect(homeForm, &Home::showSignup, this, &MainWindow::showSignup);
    connect(homeForm, &Home::showSignin, this, &MainWindow::showSignin);
    connect(signupForm, &Signup::showHome, this, &MainWindow::showHome);
    connect(signinForm, &Signin::showHome, this, &MainWindow::showHome);
    // connect(signinForm, &Signin::showExamRoomList, this, &MainWindow::showExamRoomList);


    // Show the home form initially
    ui->stackedWidget->setCurrentWidget(homeForm);

    // // Show the home form initially
    // ui->stackedWidget->setCurrentWidget(examRoomListForm);
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

