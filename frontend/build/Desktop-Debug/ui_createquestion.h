/********************************************************************************
** Form generated from reading UI file 'createquestion.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEQUESTION_H
#define UI_CREATEQUESTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateQuestion
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *labelDifficulty;
    QComboBox *difficultyComboBox;
    QTextEdit *textEdit;
    QLabel *label_3;
    QPushButton *addAnswerButton;
    QWidget *answerContainer;
    QPushButton *addAnswerButton_2;

    void setupUi(QWidget *CreateQuestion)
    {
        if (CreateQuestion->objectName().isEmpty())
            CreateQuestion->setObjectName("CreateQuestion");
        CreateQuestion->resize(717, 468);
        QFont font;
        font.setBold(false);
        CreateQuestion->setFont(font);
        label = new QLabel(CreateQuestion);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 0, 101, 17));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(CreateQuestion);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 121, 17));
        label_2->setFont(font1);
        labelDifficulty = new QLabel(CreateQuestion);
        labelDifficulty->setObjectName("labelDifficulty");
        labelDifficulty->setGeometry(QRect(10, 120, 100, 17));
        labelDifficulty->setFont(font1);
        difficultyComboBox = new QComboBox(CreateQuestion);
        difficultyComboBox->addItem(QString());
        difficultyComboBox->addItem(QString());
        difficultyComboBox->addItem(QString());
        difficultyComboBox->setObjectName("difficultyComboBox");
        difficultyComboBox->setGeometry(QRect(100, 110, 150, 25));
        textEdit = new QTextEdit(CreateQuestion);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 50, 691, 51));
        label_3 = new QLabel(CreateQuestion);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 160, 91, 17));
        label_3->setFont(font1);
        addAnswerButton = new QPushButton(CreateQuestion);
        addAnswerButton->setObjectName("addAnswerButton");
        addAnswerButton->setGeometry(QRect(10, 190, 121, 30));
        addAnswerButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        answerContainer = new QWidget(CreateQuestion);
        answerContainer->setObjectName("answerContainer");
        answerContainer->setGeometry(QRect(10, 220, 800, 600));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(answerContainer->sizePolicy().hasHeightForWidth());
        answerContainer->setSizePolicy(sizePolicy);
        addAnswerButton_2 = new QPushButton(CreateQuestion);
        addAnswerButton_2->setObjectName("addAnswerButton_2");
        addAnswerButton_2->setGeometry(QRect(590, 190, 121, 30));
        addAnswerButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        addAnswerButton_2->setStyleSheet(QString::fromUtf8("background-color:  #6600FF ; color:white;"));

        retranslateUi(CreateQuestion);

        QMetaObject::connectSlotsByName(CreateQuestion);
    } // setupUi

    void retranslateUi(QWidget *CreateQuestion)
    {
        CreateQuestion->setWindowTitle(QCoreApplication::translate("CreateQuestion", "CreateQuestion", nullptr));
        label->setText(QCoreApplication::translate("CreateQuestion", "T\341\272\241o c\303\242u h\341\273\217i", nullptr));
        label_2->setText(QCoreApplication::translate("CreateQuestion", "N\341\273\231i dung c\303\242u h\341\273\217i", nullptr));
        labelDifficulty->setText(QCoreApplication::translate("CreateQuestion", "\304\220\341\273\231 kh\303\263", nullptr));
        difficultyComboBox->setItemText(0, QCoreApplication::translate("CreateQuestion", "D\341\273\205", nullptr));
        difficultyComboBox->setItemText(1, QCoreApplication::translate("CreateQuestion", "Trung b\303\254nh", nullptr));
        difficultyComboBox->setItemText(2, QCoreApplication::translate("CreateQuestion", "Kh\303\263", nullptr));

        label_3->setText(QCoreApplication::translate("CreateQuestion", "C\303\241c \304\221\303\241p \303\241n", nullptr));
        addAnswerButton->setText(QCoreApplication::translate("CreateQuestion", "Th\303\252m \304\221\303\241p \303\241n", nullptr));
        addAnswerButton_2->setText(QCoreApplication::translate("CreateQuestion", "L\306\260u", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateQuestion: public Ui_CreateQuestion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEQUESTION_H
