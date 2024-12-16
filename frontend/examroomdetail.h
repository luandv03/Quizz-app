// frontend/sources/examroomdetail.h
#ifndef EXAMROOMDETAIL_H
#define EXAMROOMDETAIL_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>  // Thêm thư viện QTime để làm việc với thời gian

namespace Ui {
class ExamRoomDetail;
}

class ExamRoomDetail : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomDetail(QWidget *parent = nullptr);
    ~ExamRoomDetail();

signals:
    void showExamRoomList();

private:
    Ui::ExamRoomDetail *ui;
    QTimer *countdownTimer;     // Bộ đếm thời gian
    QTime remainingTime;        // Thời gian còn lại
    void displayQuestions(const QJsonArray &questionsArray);
    void createQuestionItem(const QJsonObject &questionObj);
    void updateCountdown();
    void disableSendButtons(QWidget *widget);
};

#endif // EXAMROOMDETAIL_H
