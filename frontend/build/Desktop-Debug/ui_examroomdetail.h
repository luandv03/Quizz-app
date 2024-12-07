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
    QVBoxLayout *verticalLayout_2;
    QLabel *labelDetail;
    QWidget *tabDiscussion;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelDiscussion;

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
        verticalLayout_2 = new QVBoxLayout(tabDetail);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelDetail = new QLabel(tabDetail);
        labelDetail->setObjectName("labelDetail");

        verticalLayout_2->addWidget(labelDetail);

        tabWidget->addTab(tabDetail, QString());
        tabDiscussion = new QWidget();
        tabDiscussion->setObjectName("tabDiscussion");
        verticalLayout_3 = new QVBoxLayout(tabDiscussion);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelDiscussion = new QLabel(tabDiscussion);
        labelDiscussion->setObjectName("labelDiscussion");

        verticalLayout_3->addWidget(labelDiscussion);

        tabWidget->addTab(tabDiscussion, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ExamRoomDetail);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ExamRoomDetail);
    } // setupUi

    void retranslateUi(QWidget *ExamRoomDetail)
    {
        ExamRoomDetail->setWindowTitle(QCoreApplication::translate("ExamRoomDetail", "Exam Room Detail", nullptr));
        logoLabel->setText(QCoreApplication::translate("ExamRoomDetail", "QApp", nullptr));
        avatarButton->setText(QCoreApplication::translate("ExamRoomDetail", "Avatar", nullptr));
        labelDetail->setText(QCoreApplication::translate("ExamRoomDetail", "Exam Room Detail", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDetail), QCoreApplication::translate("ExamRoomDetail", "Detail", nullptr));
        labelDiscussion->setText(QCoreApplication::translate("ExamRoomDetail", "Discussion UI", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDiscussion), QCoreApplication::translate("ExamRoomDetail", "Discussion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomDetail: public Ui_ExamRoomDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMDETAIL_H
