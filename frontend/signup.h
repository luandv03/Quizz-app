// frontend/sources/signup.h
#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Signup; }
QT_END_NAMESPACE

class Signup : public QWidget {
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

signals:
    void showSignin();

private slots:
    void on_signupButton_clicked();
    void onReadyRead();

private:
    Ui::Signup *ui;
    QTcpSocket *tcpSocket;
};

#endif // SIGNUP_H
