/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QPushButton *signupNavButton;
    QPushButton *signinNavButton;

    void setupUi(QWidget *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(400, 300);
        verticalLayout = new QVBoxLayout(Home);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(Home);
        welcomeLabel->setObjectName("welcomeLabel");

        verticalLayout->addWidget(welcomeLabel);

        signupNavButton = new QPushButton(Home);
        signupNavButton->setObjectName("signupNavButton");

        verticalLayout->addWidget(signupNavButton);

        signinNavButton = new QPushButton(Home);
        signinNavButton->setObjectName("signinNavButton");

        verticalLayout->addWidget(signinNavButton);


        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QWidget *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "Home", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("Home", "Welcome to the Home Page", nullptr));
        signupNavButton->setText(QCoreApplication::translate("Home", "Go to Signup", nullptr));
        signinNavButton->setText(QCoreApplication::translate("Home", "Go to Signin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
