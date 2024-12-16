/********************************************************************************
** Form generated from reading UI file 'examroomdetail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMROOMDETAIL_H
#define UI_EXAMROOMDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExamRoomDetail
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *header;
    QHBoxLayout *horizontalLayout;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *avatarButton;
    QTabWidget *tabWidget;
    QWidget *tabDetail;
    QWidget *examDetailWidget;
    QLabel *label;
    QPushButton *startExamButton;
    QLabel *label_2;
    QPushButton *viewExamResultBTn;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *startExamWidget;
    QVBoxLayout *verticalLayout_startExam;
    QHBoxLayout *horizontalLayout_endExam;
    QPushButton *endMyExamBtn;
    QLabel *timerLabel;
    QListWidget *questionListWidget;
    QWidget *tabDiscussion;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QWidget *ExamRoomDetail)
    {
        if (ExamRoomDetail->objectName().isEmpty())
            ExamRoomDetail->setObjectName("ExamRoomDetail");
        ExamRoomDetail->resize(800, 600);
        verticalLayout = new QVBoxLayout(ExamRoomDetail);
        verticalLayout->setObjectName("verticalLayout");
        header = new QWidget(ExamRoomDetail);
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

        tabWidget = new QTabWidget(ExamRoomDetail);
        tabWidget->setObjectName("tabWidget");
        tabDetail = new QWidget();
        tabDetail->setObjectName("tabDetail");
        examDetailWidget = new QWidget(tabDetail);
        examDetailWidget->setObjectName("examDetailWidget");
        examDetailWidget->setGeometry(QRect(0, 0, 780, 165));
        label = new QLabel(examDetailWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 760, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        startExamButton = new QPushButton(examDetailWidget);
        startExamButton->setObjectName("startExamButton");
        startExamButton->setGeometry(QRect(10, 60, 201, 25));
        startExamButton->setAutoFillBackground(true);
        label_2 = new QLabel(examDetailWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 231, 17));
        viewExamResultBTn = new QPushButton(examDetailWidget);
        viewExamResultBTn->setObjectName("viewExamResultBTn");
        viewExamResultBTn->setGeometry(QRect(10, 140, 201, 25));
        viewExamResultBTn->setAutoFillBackground(true);
        label_3 = new QLabel(examDetailWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 71, 17));
        label_4 = new QLabel(examDetailWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(90, 30, 81, 17));
        startExamWidget = new QWidget(tabDetail);
        startExamWidget->setObjectName("startExamWidget");
        startExamWidget->setGeometry(QRect(0, 0, 12000, 800));
        startExamWidget->setVisible(false);
        verticalLayout_startExam = new QVBoxLayout(startExamWidget);
        verticalLayout_startExam->setObjectName("verticalLayout_startExam");
        verticalLayout_startExam->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_endExam = new QHBoxLayout();
        horizontalLayout_endExam->setObjectName("horizontalLayout_endExam");
        endMyExamBtn = new QPushButton(startExamWidget);
        endMyExamBtn->setObjectName("endMyExamBtn");
        endMyExamBtn->setMaximumSize(QSize(150, 40));

        horizontalLayout_endExam->addWidget(endMyExamBtn);

        timerLabel = new QLabel(startExamWidget);
        timerLabel->setObjectName("timerLabel");
        timerLabel->setFont(font);

        horizontalLayout_endExam->addWidget(timerLabel);


        verticalLayout_startExam->addLayout(horizontalLayout_endExam);

        questionListWidget = new QListWidget(startExamWidget);
        questionListWidget->setObjectName("questionListWidget");
        questionListWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(questionListWidget->sizePolicy().hasHeightForWidth());
        questionListWidget->setSizePolicy(sizePolicy);

        verticalLayout_startExam->addWidget(questionListWidget);

        tabWidget->addTab(tabDetail, QString());
        tabDiscussion = new QWidget();
        tabDiscussion->setObjectName("tabDiscussion");
        verticalLayout_3 = new QVBoxLayout(tabDiscussion);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tabWidget->addTab(tabDiscussion, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ExamRoomDetail);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExamRoomDetail);
    } // setupUi

    void retranslateUi(QWidget *ExamRoomDetail)
    {
        ExamRoomDetail->setWindowTitle(QCoreApplication::translate("ExamRoomDetail", "Exam Room Detail", nullptr));
        logoLabel->setText(QCoreApplication::translate("ExamRoomDetail", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("ExamRoomDetail", "Avatar", nullptr));
        label->setText(QCoreApplication::translate("ExamRoomDetail", "Thi cuoi ky Lap tring mang", nullptr));
        startExamButton->setText(QCoreApplication::translate("ExamRoomDetail", "I am ready to start exam", nullptr));
        label_2->setText(QCoreApplication::translate("ExamRoomDetail", "Th\341\273\221ng k\341\272\277t qu\341\272\243 l\303\240m b\303\240i", nullptr));
        viewExamResultBTn->setText(QCoreApplication::translate("ExamRoomDetail", "Xem", nullptr));
        label_3->setText(QCoreApplication::translate("ExamRoomDetail", "Time limit:", nullptr));
        label_4->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        endMyExamBtn->setText(QCoreApplication::translate("ExamRoomDetail", "End My Exam", nullptr));
        timerLabel->setText(QCoreApplication::translate("ExamRoomDetail", "01:30:00", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDetail), QCoreApplication::translate("ExamRoomDetail", "Detail", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDiscussion), QCoreApplication::translate("ExamRoomDetail", "Discussion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomDetail: public Ui_ExamRoomDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMDETAIL_H
