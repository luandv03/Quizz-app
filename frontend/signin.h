// frontend/sources/signin.h
#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QTcpSocket>

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

private slots:
    void on_signinButton_clicked();
    void onReadyRead();

private:
    Ui::Signin *ui;
    QTcpSocket *tcpSocket;
};

#endif // SIGNIN_H
