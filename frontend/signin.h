// frontend/sources/signin.h
#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QTcpSocket>
#include "userdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Signin; }
QT_END_NAMESPACE

class Signin : public QWidget {
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

signals:
    void showHome();
    void showExamRoomList();

private slots:
    void on_signinButton_clicked();
    void onReadyRead();
    void onConnected();
    void onDisconnected();

    void getProfile();
    void onProfile();
   
private:
    Ui::Signin *ui;
    QTcpSocket *tcpSocket;
    QTcpSocket *tcpSocket2;
    

};

#endif // SIGNIN_H
