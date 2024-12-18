#include "examroomdialog.h"
#include "ui_examroomdialog.h"

ExamRoomDialog::ExamRoomDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDialog)
{
    ui->setupUi(this);

    // Connect the close button signal to the slot
    // connect(ui->closeButton, &QPushButton::clicked, this, &ExamRoomDialog::onCloseButtonClicked);
}

ExamRoomDialog::~ExamRoomDialog()
{
    delete ui;
}

void ExamRoomDialog::setRoomDetails(const QString &roomId, const QString &roomName, const QString &description, const QString &timeLimit, const QString &status)
{
    // ui->roomIdLabel->setText("Room ID: " + roomId);
    // ui->roomNameLabel->setText("Room Name: " + roomName);
    // ui->descriptionLabel->setText("Description: " + description);
    // ui->timeLimitLabel->setText("Time Limit: " + timeLimit);
    // ui->statusLabel->setText("Status: " + status);
}

// void ExamRoomDialog::onCloseButtonClicked()
// {
//     this->close();
// }
