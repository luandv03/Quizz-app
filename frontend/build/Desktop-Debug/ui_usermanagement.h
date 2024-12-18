/********************************************************************************
** Form generated from reading UI file 'usermanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGEMENT_H
#define UI_USERMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManagement
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *header;
    QHBoxLayout *horizontalLayout;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *avatarButton;
    QWidget *searchBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *searchLabel;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QTableWidget *userTableWidget;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(800, 800);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName("verticalLayout");
        header = new QWidget(Form);
        header->setObjectName("header");
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

        searchBar = new QWidget(Form);
        searchBar->setObjectName("searchBar");
        horizontalLayout_2 = new QHBoxLayout(searchBar);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        searchLabel = new QLabel(searchBar);
        searchLabel->setObjectName("searchLabel");

        horizontalLayout_2->addWidget(searchLabel);

        searchInput = new QLineEdit(searchBar);
        searchInput->setObjectName("searchInput");

        horizontalLayout_2->addWidget(searchInput);

        searchButton = new QPushButton(searchBar);
        searchButton->setObjectName("searchButton");

        horizontalLayout_2->addWidget(searchButton);


        verticalLayout->addWidget(searchBar);

        userTableWidget = new QTableWidget(Form);
        if (userTableWidget->columnCount() < 5)
            userTableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        userTableWidget->setObjectName("userTableWidget");

        verticalLayout->addWidget(userTableWidget);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("UserManagement", "User Management", nullptr));
        logoLabel->setText(QCoreApplication::translate("UserManagement", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("UserManagement", "Avatar", nullptr));
        searchLabel->setText(QCoreApplication::translate("UserManagement", "Search User", nullptr));
        searchButton->setText(QCoreApplication::translate("UserManagement", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserManagement", "userId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserManagement", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = userTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserManagement", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = userTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserManagement", "dob", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = userTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserManagement", "view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManagement: public Ui_UserManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEMENT_H
