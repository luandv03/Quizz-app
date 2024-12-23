/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *header;
    QHBoxLayout *horizontalLayout;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *avatarButton;
    QWidget *profileDetailsWidget;
    QFormLayout *profileDetailsLayout;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *dobLabel;
    QLineEdit *dobLineEdit;
    QLabel *passwordLabel;
    QHBoxLayout *passwordFieldLayout;
    QLineEdit *passwordLineEdit;
    QPushButton *togglePasswordButton;
    QPushButton *saveButton;

    void setupUi(QWidget *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(833, 800);
        verticalLayout = new QVBoxLayout(Profile);
        verticalLayout->setObjectName("verticalLayout");
        header = new QWidget(Profile);
        header->setObjectName("header");
        header->setMaximumHeight(43);
        header->setMinimumHeight(43);
        horizontalLayout = new QHBoxLayout(header);
        horizontalLayout->setObjectName("horizontalLayout");
        logoLabel = new QLabel(header);
        logoLabel->setObjectName("logoLabel");

        horizontalLayout->addWidget(logoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        avatarButton = new QPushButton(header);
        avatarButton->setObjectName("avatarButton");

        horizontalLayout->addWidget(avatarButton);


        verticalLayout->addWidget(header);

        profileDetailsWidget = new QWidget(Profile);
        profileDetailsWidget->setObjectName("profileDetailsWidget");
        profileDetailsLayout = new QFormLayout(profileDetailsWidget);
        profileDetailsLayout->setObjectName("profileDetailsLayout");
        profileDetailsLayout->setContentsMargins(0, 0, 0, 0);
        userNameLabel = new QLabel(profileDetailsWidget);
        userNameLabel->setObjectName("userNameLabel");

        profileDetailsLayout->setWidget(0, QFormLayout::LabelRole, userNameLabel);

        userNameLineEdit = new QLineEdit(profileDetailsWidget);
        userNameLineEdit->setObjectName("userNameLineEdit");

        profileDetailsLayout->setWidget(0, QFormLayout::FieldRole, userNameLineEdit);

        emailLabel = new QLabel(profileDetailsWidget);
        emailLabel->setObjectName("emailLabel");

        profileDetailsLayout->setWidget(1, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(profileDetailsWidget);
        emailLineEdit->setObjectName("emailLineEdit");

        profileDetailsLayout->setWidget(1, QFormLayout::FieldRole, emailLineEdit);

        dobLabel = new QLabel(profileDetailsWidget);
        dobLabel->setObjectName("dobLabel");

        profileDetailsLayout->setWidget(2, QFormLayout::LabelRole, dobLabel);

        dobLineEdit = new QLineEdit(profileDetailsWidget);
        dobLineEdit->setObjectName("dobLineEdit");

        profileDetailsLayout->setWidget(2, QFormLayout::FieldRole, dobLineEdit);

        passwordLabel = new QLabel(profileDetailsWidget);
        passwordLabel->setObjectName("passwordLabel");

        profileDetailsLayout->setWidget(3, QFormLayout::LabelRole, passwordLabel);

        passwordFieldLayout = new QHBoxLayout();
        passwordFieldLayout->setObjectName("passwordFieldLayout");
        passwordLineEdit = new QLineEdit(profileDetailsWidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        passwordFieldLayout->addWidget(passwordLineEdit);

        togglePasswordButton = new QPushButton(profileDetailsWidget);
        togglePasswordButton->setObjectName("togglePasswordButton");

        passwordFieldLayout->addWidget(togglePasswordButton);


        profileDetailsLayout->setLayout(3, QFormLayout::FieldRole, passwordFieldLayout);

        saveButton = new QPushButton(profileDetailsWidget);
        saveButton->setObjectName("saveButton");
        saveButton->setEnabled(false);

        profileDetailsLayout->setWidget(4, QFormLayout::FieldRole, saveButton);


        verticalLayout->addWidget(profileDetailsWidget);


        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QWidget *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Profile", nullptr));
        logoLabel->setText(QCoreApplication::translate("Profile", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("Profile", "Avatar", nullptr));
        userNameLabel->setText(QCoreApplication::translate("Profile", "UserName", nullptr));
        emailLabel->setText(QCoreApplication::translate("Profile", "Email", nullptr));
        dobLabel->setText(QCoreApplication::translate("Profile", "Date of Birth", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Profile", "Password", nullptr));
        togglePasswordButton->setText(QCoreApplication::translate("Profile", "\360\237\221\201\357\270\217", nullptr));
        saveButton->setText(QCoreApplication::translate("Profile", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
