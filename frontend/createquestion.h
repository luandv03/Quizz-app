#ifndef CREATEQUESTION_H
#define CREATEQUESTION_H

#include <QWidget>
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

private slots:
    void onAddAnswerButtonClicked();
    void onSubmitButtonClicked();
    void onDeleteAnswerButtonClicked();
    void onSaveQuestionClicked();
    void updateSaveButtonState();

private:
    Ui::CreateQuestion *ui;
    QListWidget *answerListWidget; // Thay thế answerLayout bằng QListWidget
    QButtonGroup *radioButtonGroup;  // Thêm QButtonGroup
};

#endif // CREATEQUESTION_H
