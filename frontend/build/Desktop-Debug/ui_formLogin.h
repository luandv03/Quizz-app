/********************************************************************************
** Form generated from reading UI file 'formLogin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOGIN_H
#define UI_FORMLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *email_input;
    QLineEdit *password_input;
    QLabel *label_5;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1110, 554);
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(80, 20, 851, 521));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(200, 140, 81, 21));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(200, 250, 131, 41));
        label_2->setFont(font);
        email_input = new QLineEdit(groupBox);
        email_input->setObjectName("email_input");
        email_input->setGeometry(QRect(200, 170, 450, 50));
        password_input = new QLineEdit(groupBox);
        password_input->setObjectName("password_input");
        password_input->setGeometry(QRect(200, 300, 450, 50));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(340, 60, 161, 41));
        QFont font1;
        font1.setPointSize(24);
        label_5->setFont(font1);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(370, 400, 131, 51));
        pushButton->setFont(font);
        pushButton->setAutoFillBackground(false);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("Form", "Email", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Password", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "Login Page", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOGIN_H
