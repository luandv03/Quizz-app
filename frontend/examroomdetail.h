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

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void showExamRoomList();
    void showUserManagement();
    void showExamRoomManagement();
    void showProfile();
    void answerSubmittedSuccessfully();
    void logout();

private slots:
    void showMenuNavigator();
    void onConnected();
    void onDisconnected();
    void handleExamRoomDetailResponse();
    void handleGetExamRoomResultByUser();
    void handleGetExamRoomResultByUserResponse();

    // handle logic start exam
    void handleStartExam();
    void handleStartExamResponse();

    // handle logic send a answer of question
    void handleSendAnswer(int examQuestionId, int answerId);
    void handleSendAnswerResponse();

    // handle logic submit exam
    void handleSubmitExam();
    void handleSubmitExamResponse();

private:
    Ui::ExamRoomDetail *ui;
    QTcpSocket *tcpSocket;
    QTcpSocket *tcpSocket2; // call API get exam room detail
    QTcpSocket *tcpSocket3; // call API get exam room result by user
    QTcpSocket *tcpSocket4; // call API start exam
    QTcpSocket *tcpSocket5; // call API send 1 answer
    QTcpSocket *tcpSocket6; // call API submit exam
    QTimer *countdownTimer;     // Bộ đếm thời gian
    QTime remainingTime;        // Thời gian còn lại
    
    void displayQuestions(const QJsonArray &questionsArray);
    void createQuestionItem(const QJsonObject &questionObj);
    void displayQuestionsPractice(const QJsonArray &questionsArray);
    void createQuestionItemPractice(const QJsonObject &questionObj);
    void updateCountdown();
    void disableSendButtons(QWidget *widget);
    void viewExamResult();

    // handle logic comment
    void on_submitCommentButton_clicked();
    void onReadyRead();
    void updateCommentList(const QJsonArray &commentsArray);
    void createComment(const QString &senderName, const QString &timeSend, const QString &comment);

    int currentRoomId;
    int examId;
};

#endif // EXAMROOMDETAIL_H
