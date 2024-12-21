#include "createexamroom.h"
#include "ui_createexamroom.h"

#include <QDebug>
#include <QDialog>

CreateExamRoom::CreateExamRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateExamRoom)
{
    ui->setupUi(this);

    // Kết nối nút "Lưu" với slot onSaveButtonClicked
    connect(ui->pushButton, &QPushButton::clicked, this, &CreateExamRoom::onSaveButtonClicked);

    // Kết nối các trường nhập liệu với hàm validateInputs để kiểm tra dữ liệu mỗi khi thay đổi
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_2, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_3, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->spinBox_4, qOverload<int>(&QSpinBox::valueChanged), this, &CreateExamRoom::validateInputs);
    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &CreateExamRoom::validateInputs);
    connect(ui->dateTimeEdit_2, &QDateTimeEdit::dateTimeChanged, this, &CreateExamRoom::validateInputs);

    // Gọi validateInputs để disable nút "Lưu" ban đầu nếu có trường trống
    validateInputs();
}

CreateExamRoom::~CreateExamRoom()
{
    delete ui;
}

// Hàm kiểm tra dữ liệu và disable nút "Lưu" nếu có trường trống
void CreateExamRoom::validateInputs()
{
    bool isValid = !ui->lineEdit->text().isEmpty() &&
                   !ui->lineEdit_2->text().isEmpty() &&
                   ui->spinBox->value() > 0 &&
                   ui->spinBox_2->value() > 0 &&
                   ui->spinBox_3->value() > 0 &&
                   ui->spinBox_4->value() > 0 &&
                   ui->dateTimeEdit->dateTime() < ui->dateTimeEdit_2->dateTime();

    ui->pushButton->setEnabled(isValid);
}

// Slot xử lý khi bấm nút "Lưu"
void CreateExamRoom::onSaveButtonClicked()
{
    QString examRoomName = ui->lineEdit->text();
    QString description = ui->lineEdit_2->text();
    int easyQuestions = ui->spinBox->value();
    int mediumQuestions = ui->spinBox_2->value();
    int hardQuestions = ui->spinBox_3->value();
    int timeLimit = ui->spinBox_4->value();
    QDateTime startTime = ui->dateTimeEdit->dateTime();
    QDateTime endTime = ui->dateTimeEdit_2->dateTime();

    QString result = QString("Tên phòng thi: %1\n"
                             "Mô tả: %2\n"
                             "Số câu dễ: %3\n"
                             "Số câu trung bình: %4\n"
                             "Số câu khó: %5\n"
                             "Thời gian làm bài: %6 phút\n"
                             "Thời gian bắt đầu: %7\n"
                             "Thời gian kết thúc: %8")
                             .arg(examRoomName)
                             .arg(description)
                             .arg(easyQuestions)
                             .arg(mediumQuestions)
                             .arg(hardQuestions)
                             .arg(timeLimit)
                             .arg(startTime.toString())
                             .arg(endTime.toString());

    qDebug() << result;

    // Close the parent QDialog
    QDialog *dialog = qobject_cast<QDialog *>(this->parentWidget());
    if (dialog) {
        dialog->close();
    }

    // QMessageBox::information(this, "Thông tin phòng thi", result);
}
