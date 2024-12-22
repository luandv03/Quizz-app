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
#include <QtWidgets/QLineEdit>
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
    QLabel *subjectLabel;
    QPushButton *startExamButton;
    QLabel *label_2;
    QPushButton *viewExamResultBTn;
    QLabel *label_3;
    QLabel *statusLabel;
    QLabel *label_12;
    QLabel *numberOfHardQuestionLabel;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *timeLimitLabel;
    QLabel *numberOfMediumQuestionLabel;
    QLabel *numberOfEasyQuestionLabel;
    QWidget *startExamWidget;
    QVBoxLayout *verticalLayout_startExam;
    QHBoxLayout *horizontalLayout_endExam;
    QPushButton *endMyExamBtn;
    QLabel *timerLabel;
    QListWidget *questionListWidget;
    QWidget *examResultWidget;
    QLabel *label;
    QLabel *label_31;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QPushButton *backExamDetailWidget;
    QWidget *tabDiscussion;
    QVBoxLayout *verticalLayout_3;
    QListWidget *discussionListWidget;
    QHBoxLayout *horizontalLayout_commentInput;
    QLineEdit *commentLineEdit;
    QPushButton *submitCommentButton;

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
        examDetailWidget->setGeometry(QRect(0, 0, 780, 501));
        subjectLabel = new QLabel(examDetailWidget);
        subjectLabel->setObjectName("subjectLabel");
        subjectLabel->setGeometry(QRect(10, 0, 760, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        subjectLabel->setFont(font);
        startExamButton = new QPushButton(examDetailWidget);
        startExamButton->setObjectName("startExamButton");
        startExamButton->setGeometry(QRect(10, 220, 201, 25));
        startExamButton->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        startExamButton->setAutoFillBackground(true);
        label_2 = new QLabel(examDetailWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 270, 231, 17));
        viewExamResultBTn = new QPushButton(examDetailWidget);
        viewExamResultBTn->setObjectName("viewExamResultBTn");
        viewExamResultBTn->setGeometry(QRect(10, 300, 201, 25));
        viewExamResultBTn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        viewExamResultBTn->setAutoFillBackground(true);
        label_3 = new QLabel(examDetailWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 130, 71, 17));
        QFont font1;
        font1.setBold(true);
        label_3->setFont(font1);
        statusLabel = new QLabel(examDetailWidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(160, 160, 81, 17));
        label_12 = new QLabel(examDetailWidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 100, 81, 17));
        label_12->setFont(font1);
        numberOfHardQuestionLabel = new QLabel(examDetailWidget);
        numberOfHardQuestionLabel->setObjectName("numberOfHardQuestionLabel");
        numberOfHardQuestionLabel->setGeometry(QRect(160, 100, 81, 17));
        label_14 = new QLabel(examDetailWidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 70, 131, 17));
        label_14->setFont(font1);
        label_15 = new QLabel(examDetailWidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 40, 131, 17));
        label_15->setFont(font1);
        label_17 = new QLabel(examDetailWidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 160, 71, 17));
        label_17->setFont(font1);
        timeLimitLabel = new QLabel(examDetailWidget);
        timeLimitLabel->setObjectName("timeLimitLabel");
        timeLimitLabel->setGeometry(QRect(160, 130, 81, 17));
        numberOfMediumQuestionLabel = new QLabel(examDetailWidget);
        numberOfMediumQuestionLabel->setObjectName("numberOfMediumQuestionLabel");
        numberOfMediumQuestionLabel->setGeometry(QRect(160, 70, 81, 17));
        numberOfEasyQuestionLabel = new QLabel(examDetailWidget);
        numberOfEasyQuestionLabel->setObjectName("numberOfEasyQuestionLabel");
        numberOfEasyQuestionLabel->setGeometry(QRect(160, 40, 81, 17));
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

        examResultWidget = new QWidget(tabDetail);
        examResultWidget->setObjectName("examResultWidget");
        examResultWidget->setGeometry(QRect(0, 0, 780, 501));
        examResultWidget->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        examResultWidget->setVisible(false);
        label = new QLabel(examResultWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 760, 21));
        label->setFont(font);
        label_31 = new QLabel(examResultWidget);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 70, 91, 17));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label_31->setFont(font2);
        label_5 = new QLabel(examResultWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 67, 17));
        label_6 = new QLabel(examResultWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(160, 100, 111, 17));
        label_7 = new QLabel(examResultWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 130, 67, 17));
        label_8 = new QLabel(examResultWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(160, 130, 231, 17));
        label_9 = new QLabel(examResultWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 160, 67, 17));
        label_10 = new QLabel(examResultWidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(160, 160, 231, 17));
        label_11 = new QLabel(examResultWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 210, 201, 17));
        label_11->setFont(font2);
        label_21 = new QLabel(examResultWidget);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 240, 111, 17));
        label_22 = new QLabel(examResultWidget);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(160, 240, 111, 17));
        label_23 = new QLabel(examResultWidget);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 270, 141, 17));
        label_24 = new QLabel(examResultWidget);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(160, 270, 231, 17));
        label_25 = new QLabel(examResultWidget);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 300, 131, 17));
        label_26 = new QLabel(examResultWidget);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(160, 300, 231, 17));
        backExamDetailWidget = new QPushButton(examResultWidget);
        backExamDetailWidget->setObjectName("backExamDetailWidget");
        backExamDetailWidget->setGeometry(QRect(10, 10, 89, 25));
        backExamDetailWidget->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        backExamDetailWidget->setCheckable(false);
        tabWidget->addTab(tabDetail, QString());
        tabDiscussion = new QWidget();
        tabDiscussion->setObjectName("tabDiscussion");
        verticalLayout_3 = new QVBoxLayout(tabDiscussion);
        verticalLayout_3->setObjectName("verticalLayout_3");
        discussionListWidget = new QListWidget(tabDiscussion);
        discussionListWidget->setObjectName("discussionListWidget");
        sizePolicy.setHeightForWidth(discussionListWidget->sizePolicy().hasHeightForWidth());
        discussionListWidget->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(discussionListWidget);

        horizontalLayout_commentInput = new QHBoxLayout();
        horizontalLayout_commentInput->setObjectName("horizontalLayout_commentInput");
        commentLineEdit = new QLineEdit(tabDiscussion);
        commentLineEdit->setObjectName("commentLineEdit");

        horizontalLayout_commentInput->addWidget(commentLineEdit);

        submitCommentButton = new QPushButton(tabDiscussion);
        submitCommentButton->setObjectName("submitCommentButton");
        submitCommentButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_commentInput->addWidget(submitCommentButton);


        verticalLayout_3->addLayout(horizontalLayout_commentInput);

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
        subjectLabel->setText(QCoreApplication::translate("ExamRoomDetail", "Thi cuoi ky Lap tring mang", nullptr));
        startExamButton->setText(QCoreApplication::translate("ExamRoomDetail", "I am ready to start exam", nullptr));
        label_2->setText(QCoreApplication::translate("ExamRoomDetail", "Th\341\273\221ng k\341\272\277t qu\341\272\243 l\303\240m b\303\240i", nullptr));
        viewExamResultBTn->setText(QCoreApplication::translate("ExamRoomDetail", "Xem", nullptr));
        label_3->setText(QCoreApplication::translate("ExamRoomDetail", "Time limit:", nullptr));
        statusLabel->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        label_12->setText(QCoreApplication::translate("ExamRoomDetail", "S\341\273\221 c\303\242u kh\303\263", nullptr));
        numberOfHardQuestionLabel->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        label_14->setText(QCoreApplication::translate("ExamRoomDetail", "S\341\273\221 c\303\242u trung b\303\254nh", nullptr));
        label_15->setText(QCoreApplication::translate("ExamRoomDetail", "S\341\273\221 c\303\242u d\341\273\205", nullptr));
        label_17->setText(QCoreApplication::translate("ExamRoomDetail", "Status", nullptr));
        timeLimitLabel->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        numberOfMediumQuestionLabel->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        numberOfEasyQuestionLabel->setText(QCoreApplication::translate("ExamRoomDetail", "30 minutes", nullptr));
        endMyExamBtn->setText(QCoreApplication::translate("ExamRoomDetail", "End My Exam", nullptr));
        timerLabel->setText(QCoreApplication::translate("ExamRoomDetail", "01:30:00", nullptr));
        label->setText(QCoreApplication::translate("ExamRoomDetail", "Th\341\273\221ng k\303\252 b\303\240i l\303\240m Thi cuoi ky Lap trinh mang", nullptr));
        label_31->setText(QCoreApplication::translate("ExamRoomDetail", "Information", nullptr));
        label_5->setText(QCoreApplication::translate("ExamRoomDetail", "Fullname", nullptr));
        label_6->setText(QCoreApplication::translate("ExamRoomDetail", "\304\220Inh V\304\203n Lu\341\272\255n", nullptr));
        label_7->setText(QCoreApplication::translate("ExamRoomDetail", "Email", nullptr));
        label_8->setText(QCoreApplication::translate("ExamRoomDetail", "luan.dv215083@sis.hust.edu.vn", nullptr));
        label_9->setText(QCoreApplication::translate("ExamRoomDetail", "Exam", nullptr));
        label_10->setText(QCoreApplication::translate("ExamRoomDetail", "Thi cuoi ky Lap tring mang", nullptr));
        label_11->setText(QCoreApplication::translate("ExamRoomDetail", "Auto-graded questions", nullptr));
        label_21->setText(QCoreApplication::translate("ExamRoomDetail", "Total questions", nullptr));
        label_22->setText(QCoreApplication::translate("ExamRoomDetail", "30", nullptr));
        label_23->setText(QCoreApplication::translate("ExamRoomDetail", "Submitted answers", nullptr));
        label_24->setText(QCoreApplication::translate("ExamRoomDetail", "30", nullptr));
        label_25->setText(QCoreApplication::translate("ExamRoomDetail", "Correct answers", nullptr));
        label_26->setText(QCoreApplication::translate("ExamRoomDetail", "30", nullptr));
        backExamDetailWidget->setText(QCoreApplication::translate("ExamRoomDetail", "Quay l\341\272\241i", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDetail), QCoreApplication::translate("ExamRoomDetail", "Detail", nullptr));
        commentLineEdit->setPlaceholderText(QCoreApplication::translate("ExamRoomDetail", "Type your comment here...", nullptr));
        submitCommentButton->setText(QCoreApplication::translate("ExamRoomDetail", "Submit", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDiscussion), QCoreApplication::translate("ExamRoomDetail", "Discussion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExamRoomDetail: public Ui_ExamRoomDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMROOMDETAIL_H
