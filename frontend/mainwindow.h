// frontend/sources/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "signup.h"
#include "signin.h"
#include "home.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSignup();
    void showSignin();
    void showHome();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    Signup *signupForm;
    Signin *signinForm;
    Home *homeForm;
};

#endif // MAINWINDOW_H
