#ifndef EXAMROOMDIALOG_H
#define EXAMROOMDIALOG_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ExamRoomDialog;
}

class ExamRoomDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomDialog(QWidget *parent = nullptr);
    ~ExamRoomDialog();
    void setRoomDetails(const QString &roomId, const QString &roomName, const QString &description, const QString &timeLimit, const QString &status, const QString &startTime, const QString &endTime);

private slots:
    void onAddQuestion();
    void handleGetQuestionBank(int roomId);
    void handleGetQuestionBankResponse();
    void handleGetUserInRoom(int roomId);
    void handleGetUserInRoomResponse();
    void handleGetExamResult(int roomId);
    void handleGetExamResultResponse();
    void handleStartExam();
    void handleStartExamResponse();
    void handleEndExam();
    void handleEndExamResponse();
    void handleGetExamResultChart();
    void handleGetExamResultChartResponse();

private:
    Ui::ExamRoomDialog *ui;
    QTcpSocket *tcpSocket; // Call API get ngan hang cau hoi
    QTcpSocket *tcpSocket1; // Call API get user in room
    QTcpSocket *tcpSocket2; // Call API get exam result
    QTcpSocket *tcpSocket3; // Call API start exam
    QTcpSocket *tcpSocket4; // Call API send answer
    QTcpSocket *tcpSocket5; // Call API get pho diem
    void setupScoreChart();

    int examRoomId; 
};

#endif // EXAMROOMDIALOG_H
