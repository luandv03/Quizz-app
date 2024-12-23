#include "examroomdialog.h"
#include "ui_examroomdialog.h"
#include "createquestion.h"

#include <QDialog>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

ExamRoomDialog::ExamRoomDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDialog)
{
    ui->setupUi(this);

    // Connect the close button signal to the slot
    // connect(ui->closeButton, &QPushButton::clicked, this, &ExamRoomDialog::onCloseButtonClicked);
    connect(ui->addQuestionButton, &QPushButton::clicked, this, &ExamRoomDialog::onAddQuestion);

    // Gọi hàm để tạo chart khi khởi tạo dialog
    setupScoreChart();
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

void ExamRoomDialog::onAddQuestion()
{
    // Create the parent dialog
    QDialog *parentDialog = new QDialog(this);
    parentDialog->setWindowTitle("Create Question");
    parentDialog->resize(900, 800);  // Set desired size for the dialog

    // Create and configure the custom widget
    CreateQuestion *createQuestion = new CreateQuestion(parentDialog);
    // CreateQuestion->setRoomDetails(roomId, roomName, description, timeLimit, status);
    createQuestion->setParent(parentDialog);

    // Add the custom widget to the parent dialog's layout
    QVBoxLayout *layout = new QVBoxLayout(parentDialog);
    layout->addWidget(createQuestion);
    parentDialog->setLayout(layout);

    // Show the parent dialog as modal
    parentDialog->exec();
}

// build Exam Reult Charts
void ExamRoomDialog::setupScoreChart()
{
    // Tạo dữ liệu cho phổ điểm (điểm từ 1-10)
    QBarSet *set = new QBarSet("Phổ điểm");
    *set << 1 << 2 << 5 << 8 << 10 << 12 << 7 << 6 << 3 << 2;  // Ví dụ dữ liệu phổ điểm

    // Tạo series
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Tạo chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Phổ điểm phòng thi");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Tạo trục cho chart
    QStringList categories;
    for (int i = 1; i <= 10; ++i)
        categories << QString::number(i);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Số lượng");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Tạo chart view và gán chart vào tab
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Thêm chart vào layout của tabExamResultChart
    QVBoxLayout *layout = new QVBoxLayout(ui->tabExamResultChart);
    layout->addWidget(chartView);
    ui->tabExamResultChart->setLayout(layout);
}
