#ifndef CREATEQUESTION_H
#define CREATEQUESTION_H

#include <QWidget>
#include <QTcpSocket>  // Thêm include cho QTcpSocket
#include <QListWidget>
#include <QPlainTextEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>  // Thêm include cho QButtonGroup

namespace Ui {
class CreateQuestion;
}

class CreateQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit CreateQuestion(QWidget *parent = nullptr);
    ~CreateQuestion();

public slots:
    void setRoomId(int roomId);

private slots:
    void onAddAnswerButtonClicked();
    void onSubmitButtonClicked();
    void onDeleteAnswerButtonClicked();
    void onSaveQuestionClicked();
    void updateSaveButtonState();
    void handleCreateQuestion();  // Thêm slot xử lý response từ server
    void handleCreateQuestionResponse();

private:
    Ui::CreateQuestion *ui;
    QTcpSocket *tcpSocket; // call API create question
    QListWidget *answerListWidget; // Thay thế answerLayout bằng QListWidget
    QButtonGroup *radioButtonGroup;  // Thêm QButtonGroup

    int roomId = 0;  // Thêm roomId để lưu trữ id của phòng thi
};

#endif // CREATEQUESTION_H
