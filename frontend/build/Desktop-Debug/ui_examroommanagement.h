/********************************************************************************
** Form generated from reading UI file 'examroommanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMROOMMANAGEMENT_H
#define UI_EXAMROOMMANAGEMENT_H

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

class Ui_ExamRoomManagement
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
    QWidget *buttonContainer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *createExamRoomBtn;
    QTableWidget *examRoomTableWidget;

    void setupUi(QWidget *ExamRoomManagement)
    {
        if (ExamRoomManagement->objectName().isEmpty())
            ExamRoomManagement->setObjectName("ExamRoomManagement");
        ExamRoomManagement->resize(800, 800);
        verticalLayout = new QVBoxLayout(ExamRoomManagement);
        verticalLayout->setObjectName("verticalLayout");
        header = new QWidget(ExamRoomManagement);
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

        searchBar = new QWidget(ExamRoomManagement);
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

        buttonContainer = new QWidget(ExamRoomManagement);
        buttonContainer->setObjectName("buttonContainer");
        horizontalLayout_3 = new QHBoxLayout(buttonContainer);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        createExamRoomBtn = new QPushButton(buttonContainer);
        createExamRoomBtn->setObjectName("createExamRoomBtn");
        createExamRoomBtn->setMaximumSize(QSize(140, 25));
        createExamRoomBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_3->addWidget(createExamRoomBtn);


        verticalLayout->addWidget(buttonContainer);

        examRoomTableWidget = new QTableWidget(ExamRoomManagement);
        if (examRoomTableWidget->columnCount() < 6)
            examRoomTableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        examRoomTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        examRoomTableWidget->setObjectName("examRoomTableWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(examRoomTableWidget->sizePolicy().hasHeightForWidth());
        examRoomTableWidget->setSizePolicy(sizePolicy);
        examRoomTableWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CursorShape::PointingHandCursor)));

        verticalLayout->addWidget(examRoomTableWidget);


        retranslateUi(ExamRoomManagement);

        QMetaObject::connectSlotsByName(ExamRoomManagement);
    } // setupUi

    void retranslateUi(QWidget *ExamRoomManagement)
    {
        ExamRoomManagement->setWindowTitle(QCoreApplication::translate("ExamRoomManagement", "Exam Room Management", nullptr));
        logoLabel->setText(QCoreApplication::translate("ExamRoomManagement", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("ExamRoomManagement", "Avatar", nullptr));
        searchLabel->setText(QCoreApplication::translate("ExamRoomManagement", "Search Exam Room", nullptr));
        searchButton->setText(QCoreApplication::translate("ExamRoomManagement", "Search", nullptr));
        createExamRoomBtn->setText(QCoreApplication::translate("ExamRoomManagement", "T\341\272\241o ph\303\262ng thi", nullptr));
        QTableWidgetItem *___qtablewidgetitem = examRoomTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ExamRoomManagement", "roomId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = examRoomTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ExamRoomManagement", "roomName", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = examRoomTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ExamRoomManagement", "description", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = examRoomTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ExamRoomManagement", "timelimt", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = examRoomTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ExamRoomManagement", "status", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = examRoomTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ExamRoomManagement", "view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomManagement: public Ui_ExamRoomManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMMANAGEMENT_H
