// frontend/sources/home.cpp
#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    connect(ui->signupNavButton, &QPushButton::clicked, this, &Home::on_signupNavButton_clicked);
    connect(ui->signinNavButton, &QPushButton::clicked, this, &Home::on_signinNavButton_clicked);
}

Home::~Home() {
    delete ui;
}

void Home::on_signupNavButton_clicked() {
    emit showSignup();
}

void Home::on_signinNavButton_clicked() {
    emit showSignin();
}
