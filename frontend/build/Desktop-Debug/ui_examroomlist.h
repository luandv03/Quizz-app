/********************************************************************************
** Form generated from reading UI file 'examroomlist.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMROOMLIST_H
#define UI_EXAMROOMLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamRoomList
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
    QListWidget *examRoomList;

    void setupUi(QWidget *ExamRoomList)
    {
        if (ExamRoomList->objectName().isEmpty())
            ExamRoomList->setObjectName("ExamRoomList");
        ExamRoomList->resize(800, 600);
        verticalLayout = new QVBoxLayout(ExamRoomList);
        verticalLayout->setObjectName("verticalLayout");
        header = new QWidget(ExamRoomList);
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

        searchBar = new QWidget(ExamRoomList);
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

        examRoomList = new QListWidget(ExamRoomList);
        examRoomList->setObjectName("examRoomList");

        verticalLayout->addWidget(examRoomList);


        retranslateUi(ExamRoomList);

        QMetaObject::connectSlotsByName(ExamRoomList);
    } // setupUi

    void retranslateUi(QWidget *ExamRoomList)
    {
        ExamRoomList->setWindowTitle(QCoreApplication::translate("ExamRoomList", "Exam Room List", nullptr));
        logoLabel->setText(QCoreApplication::translate("ExamRoomList", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("ExamRoomList", "Avatar", nullptr));
        searchLabel->setText(QCoreApplication::translate("ExamRoomList", "Search Your Exam Room", nullptr));
        searchButton->setText(QCoreApplication::translate("ExamRoomList", "Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomList: public Ui_ExamRoomList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMLIST_H
