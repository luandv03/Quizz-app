#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SignupWindow; }
QT_END_NAMESPACE

class SignupWindow : public QDialog {
    Q_OBJECT

public:
    SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void on_signupButton_clicked();

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H
