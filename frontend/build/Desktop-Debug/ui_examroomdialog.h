/********************************************************************************
** Form generated from reading UI file 'examroomdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMROOMDIALOG_H
#define UI_EXAMROOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamRoomDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QTabWidget *tabWidget;
    QWidget *tabExamRoomDetail;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *roomName;
    QLabel *description;
    QLabel *timelimit;
    QLabel *starttime;
    QLabel *endtime;
    QLabel *status;
    QPushButton *startExam;
    QLabel *label_8;
    QPushButton *addQuestion;
    QListWidget *listWidget;
    QWidget *tabUser;
    QLabel *label_7;
    QWidget *searchBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *searchLabel;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *addUser;
    QTableWidget *userTableWidget;

    void setupUi(QWidget *ExamRoomDialog)
    {
        if (ExamRoomDialog->objectName().isEmpty())
            ExamRoomDialog->setObjectName("ExamRoomDialog");
        ExamRoomDialog->resize(898, 800);
        ExamRoomDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(ExamRoomDialog);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(ExamRoomDialog);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 30));
        widget->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(widget);

        tabWidget = new QTabWidget(ExamRoomDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabExamRoomDetail = new QWidget();
        tabExamRoomDetail->setObjectName("tabExamRoomDetail");
        label = new QLabel(tabExamRoomDetail);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 101, 17));
        label_2 = new QLabel(tabExamRoomDetail);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 67, 17));
        label_3 = new QLabel(tabExamRoomDetail);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 67, 17));
        label_4 = new QLabel(tabExamRoomDetail);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 100, 101, 17));
        label_5 = new QLabel(tabExamRoomDetail);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 130, 111, 17));
        label_6 = new QLabel(tabExamRoomDetail);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 160, 81, 17));
        roomName = new QLabel(tabExamRoomDetail);
        roomName->setObjectName("roomName");
        roomName->setGeometry(QRect(160, 10, 191, 17));
        description = new QLabel(tabExamRoomDetail);
        description->setObjectName("description");
        description->setGeometry(QRect(160, 40, 67, 17));
        timelimit = new QLabel(tabExamRoomDetail);
        timelimit->setObjectName("timelimit");
        timelimit->setGeometry(QRect(160, 70, 67, 17));
        starttime = new QLabel(tabExamRoomDetail);
        starttime->setObjectName("starttime");
        starttime->setGeometry(QRect(160, 100, 141, 17));
        endtime = new QLabel(tabExamRoomDetail);
        endtime->setObjectName("endtime");
        endtime->setGeometry(QRect(160, 130, 141, 17));
        status = new QLabel(tabExamRoomDetail);
        status->setObjectName("status");
        status->setGeometry(QRect(160, 160, 141, 17));
        startExam = new QPushButton(tabExamRoomDetail);
        startExam->setObjectName("startExam");
        startExam->setGeometry(QRect(160, 180, 89, 25));
        startExam->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        startExam->setAutoFillBackground(false);
        label_8 = new QLabel(tabExamRoomDetail);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 230, 141, 17));
        addQuestion = new QPushButton(tabExamRoomDetail);
        addQuestion->setObjectName("addQuestion");
        addQuestion->setGeometry(QRect(760, 220, 111, 25));
        addQuestion->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        listWidget = new QListWidget(tabExamRoomDetail);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 250, 871, 271));
        listWidget->setMinimumSize(QSize(800, 0));
        tabWidget->addTab(tabExamRoomDetail, QString());
        tabUser = new QWidget();
        tabUser->setObjectName("tabUser");
        label_7 = new QLabel(tabUser);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 241, 17));
        searchBar = new QWidget(tabUser);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(0, 40, 782, 43));
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
        searchButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_2->addWidget(searchButton);

        addUser = new QPushButton(tabUser);
        addUser->setObjectName("addUser");
        addUser->setGeometry(QRect(680, 10, 91, 25));
        addUser->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        userTableWidget = new QTableWidget(tabUser);
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
        userTableWidget->setGeometry(QRect(0, 80, 782, 684));
        tabWidget->addTab(tabUser, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ExamRoomDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ExamRoomDialog);
    } // setupUi

    void retranslateUi(QWidget *ExamRoomDialog)
    {
        ExamRoomDialog->setWindowTitle(QCoreApplication::translate("ExamRoomDialog", "Exam Room Details", nullptr));
        label->setText(QCoreApplication::translate("ExamRoomDialog", "T\303\252n ph\303\262ng thi", nullptr));
        label_2->setText(QCoreApplication::translate("ExamRoomDialog", "M\303\264 t\341\272\243", nullptr));
        label_3->setText(QCoreApplication::translate("ExamRoomDialog", "Time limit", nullptr));
        label_4->setText(QCoreApplication::translate("ExamRoomDialog", "Ng\303\240y b\341\272\257t \304\221\341\272\247u", nullptr));
        label_5->setText(QCoreApplication::translate("ExamRoomDialog", "Ng\303\240y k\341\272\277t th\303\272c", nullptr));
        label_6->setText(QCoreApplication::translate("ExamRoomDialog", "Tr\341\272\241ng th\303\241i", nullptr));
        roomName->setText(QCoreApplication::translate("ExamRoomDialog", "Thi cuoi ky lap trinh mang", nullptr));
        description->setText(QCoreApplication::translate("ExamRoomDialog", "Mo ta", nullptr));
        timelimit->setText(QCoreApplication::translate("ExamRoomDialog", "60 ph\303\272t", nullptr));
        starttime->setText(QCoreApplication::translate("ExamRoomDialog", "2024-11-12 10:00:00", nullptr));
        endtime->setText(QCoreApplication::translate("ExamRoomDialog", "2024-11-14 10:00:00", nullptr));
        status->setText(QCoreApplication::translate("ExamRoomDialog", "Ch\306\260a b\341\272\257t \304\221\341\272\247u", nullptr));
        startExam->setText(QCoreApplication::translate("ExamRoomDialog", "Ph\303\241t \304\221\341\273\201", nullptr));
        label_8->setText(QCoreApplication::translate("ExamRoomDialog", "Ng\303\242n h\303\240ng c\303\242u h\341\273\217i", nullptr));
        addQuestion->setText(QCoreApplication::translate("ExamRoomDialog", "Th\303\252m c\303\242u h\341\273\217i", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabExamRoomDetail), QCoreApplication::translate("ExamRoomDialog", "Chi tiet phong thi", nullptr));
        label_7->setText(QCoreApplication::translate("ExamRoomDialog", "Danh s\303\241ch ng\306\260\341\273\235i trong ph\303\262ng thi", nullptr));
        searchLabel->setText(QCoreApplication::translate("ExamRoomDialog", "Search User", nullptr));
        searchButton->setText(QCoreApplication::translate("ExamRoomDialog", "Search", nullptr));
        addUser->setText(QCoreApplication::translate("ExamRoomDialog", "Th\303\252m User", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ExamRoomDialog", "userId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ExamRoomDialog", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = userTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ExamRoomDialog", "email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = userTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ExamRoomDialog", "dob", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = userTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ExamRoomDialog", "view", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabUser), QCoreApplication::translate("ExamRoomDialog", "Danh sach nguoi tham gia", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomDialog: public Ui_ExamRoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMDIALOG_H
