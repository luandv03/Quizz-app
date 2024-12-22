// frontend/sources/examroomdetail.h
#ifndef EXAMROOMDETAIL_H
#define EXAMROOMDETAIL_H

#include <QTcpSocket>
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

public slots:
    void setRoomId(int roomId);

signals:
    void showExamRoomList();
    void showUserManagement();
    void showExamRoomManagement();
    void showProfile();

private slots:
    void onConnected();
    void onDisconnected();
    void handleExamRoomDetailResponse();

private:
    Ui::ExamRoomDetail *ui;
    QTcpSocket *tcpSocket;
    QTcpSocket *tcpSocket2;
    QTimer *countdownTimer;     // Bộ đếm thời gian
    QTime remainingTime;        // Thời gian còn lại
    void displayQuestions(const QJsonArray &questionsArray);
    void createQuestionItem(const QJsonObject &questionObj);
    void updateCountdown();
    void disableSendButtons(QWidget *widget);
    void viewExamResult();

    // handle logic comment
    void on_submitCommentButton_clicked();
    void onReadyRead();
    void updateCommentList(const QJsonArray &commentsArray);
    void createComment(const QString &senderName, const QString &timeSend, const QString &comment);

    int currentRoomId;
};

#endif // EXAMROOMDETAIL_H
