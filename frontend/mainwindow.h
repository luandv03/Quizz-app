// frontend/sources/mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "signup.h"
#include "signin.h"
#include "home.h"
#include "examroomlist.h"
#include "examroomdetail.h"

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
    void showExamRoomList();
    void showExamRoomDetail();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    Signup *signupForm;
    Signin *signinForm;
    Home *homeForm;
    ExamRoomList *examRoomListForm;
    ExamRoomDetail *examRoomDetailForm;
};

#endif // MAINWINDOW_H
