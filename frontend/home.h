// frontend/sources/home.h
#ifndef HOME_H
#define HOME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QWidget {
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

signals:
    void showSignup();
    void showSignin();

private slots:
    void on_signupNavButton_clicked();
    void on_signinNavButton_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
