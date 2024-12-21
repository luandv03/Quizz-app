/********************************************************************************
** Form generated from reading UI file 'createexamroom.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEXAMROOM_H
#define UI_CREATEEXAMROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateExamRoom
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QPushButton *pushButton;

    void setupUi(QWidget *CreateExamRoom)
    {
        if (CreateExamRoom->objectName().isEmpty())
            CreateExamRoom->setObjectName("CreateExamRoom");
        CreateExamRoom->resize(669, 467);
        label = new QLabel(CreateExamRoom);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 111, 17));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(CreateExamRoom);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 101, 17));
        label_2->setFont(font);
        label_3 = new QLabel(CreateExamRoom);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 101, 17));
        label_3->setFont(font);
        label_4 = new QLabel(CreateExamRoom);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 140, 141, 17));
        label_4->setFont(font);
        label_5 = new QLabel(CreateExamRoom);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 180, 121, 17));
        label_5->setFont(font);
        label_6 = new QLabel(CreateExamRoom);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 220, 131, 17));
        label_6->setFont(font);
        label_7 = new QLabel(CreateExamRoom);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 260, 121, 17));
        label_7->setFont(font);
        label_8 = new QLabel(CreateExamRoom);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 300, 121, 17));
        label_8->setFont(font);
        lineEdit = new QLineEdit(CreateExamRoom);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(150, 0, 481, 25));
        lineEdit_2 = new QLineEdit(CreateExamRoom);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(150, 50, 481, 31));
        spinBox = new QSpinBox(CreateExamRoom);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(150, 90, 44, 26));
        spinBox_2 = new QSpinBox(CreateExamRoom);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(150, 130, 44, 26));
        spinBox_3 = new QSpinBox(CreateExamRoom);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(150, 170, 44, 26));
        spinBox_4 = new QSpinBox(CreateExamRoom);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setGeometry(QRect(150, 210, 44, 26));
        dateTimeEdit = new QDateTimeEdit(CreateExamRoom);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(150, 250, 194, 26));
        dateTimeEdit_2 = new QDateTimeEdit(CreateExamRoom);
        dateTimeEdit_2->setObjectName("dateTimeEdit_2");
        dateTimeEdit_2->setGeometry(QRect(150, 290, 194, 26));
        pushButton = new QPushButton(CreateExamRoom);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 430, 89, 25));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:  #6600FF ; color:white;"));

        retranslateUi(CreateExamRoom);

        QMetaObject::connectSlotsByName(CreateExamRoom);
    } // setupUi

    void retranslateUi(QWidget *CreateExamRoom)
    {
        CreateExamRoom->setWindowTitle(QCoreApplication::translate("CreateExamRoom", "CreateExamRoom", nullptr));
        label->setText(QCoreApplication::translate("CreateExamRoom", "T\303\252n ph\303\262ng thi", nullptr));
        label_2->setText(QCoreApplication::translate("CreateExamRoom", "M\303\264 t\341\272\243", nullptr));
        label_3->setText(QCoreApplication::translate("CreateExamRoom", "S\341\273\221 c\303\242u d\341\273\205", nullptr));
        label_4->setText(QCoreApplication::translate("CreateExamRoom", "S\341\273\221 c\303\242u trung b\303\254nh", nullptr));
        label_5->setText(QCoreApplication::translate("CreateExamRoom", "S\341\273\221 c\303\242u kh\303\263", nullptr));
        label_6->setText(QCoreApplication::translate("CreateExamRoom", "Time Limit (ph\303\272t)", nullptr));
        label_7->setText(QCoreApplication::translate("CreateExamRoom", "Start time", nullptr));
        label_8->setText(QCoreApplication::translate("CreateExamRoom", "End Time", nullptr));
        pushButton->setText(QCoreApplication::translate("CreateExamRoom", "L\306\260u", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateExamRoom: public Ui_CreateExamRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEXAMROOM_H
