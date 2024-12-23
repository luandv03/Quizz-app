#include "createquestion.h"
#include "ui_createquestion.h"

#include <QDialog>

CreateQuestion::CreateQuestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateQuestion)
{
    ui->setupUi(this);

    // Tạo QListWidget để chứa các đáp án
    answerListWidget = new QListWidget(ui->answerContainer);

    // Đặt kích thước cho answerListWidget
    answerListWidget->setMinimumHeight(400);
    answerListWidget->setMinimumWidth(600);

    QVBoxLayout *containerLayout = new QVBoxLayout(ui->answerContainer);
    containerLayout->addWidget(answerListWidget);

    // Khởi tạo QButtonGroup để quản lý radio buttons
    radioButtonGroup = new QButtonGroup(this);
    radioButtonGroup->setExclusive(true);  // Đảm bảo chỉ chọn 1 đáp án đúng

    // Kết nối nút "Thêm đáp án" với slot
    connect(ui->addAnswerButton, &QPushButton::clicked, this, &CreateQuestion::onAddAnswerButtonClicked);

    // handle create question
    ui->addAnswerButton_2->setEnabled(false);

    connect(ui->textEdit, &QTextEdit::textChanged, this, &CreateQuestion::updateSaveButtonState);
}

CreateQuestion::~CreateQuestion()
{
    delete ui;
}

void CreateQuestion::onAddAnswerButtonClicked() {
    // Tạo QWidget chứa QPlainTextEdit và QRadioButton
    QWidget *answerWidget = new QWidget();
    answerWidget->setMinimumHeight(100);
    answerWidget->setMinimumWidth(600);

    // Tạo QPlainTextEdit cho đáp án
    QPlainTextEdit *answerTextEdit = new QPlainTextEdit();
    answerTextEdit->setPlaceholderText("Nhập đáp án");
    answerTextEdit->setFixedHeight(80);
    answerTextEdit->setMinimumWidth(500);

    // Tạo QRadioButton để chọn đáp án đúng
    QRadioButton *correctAnswerRadioButton = new QRadioButton("Đáp án đúng");

    // Tạo QPushButton để xóa đáp án
    QPushButton *deleteButton = new QPushButton("X");
    deleteButton->setFixedSize(30, 30); // Đặt kích thước cho nút xóa
    deleteButton->setCursor(QCursor(Qt::PointingHandCursor)); // Đổi con trỏ chuột khi rê chuột qua nút xóa

    // Thêm radio button vào QButtonGroup
    radioButtonGroup->addButton(correctAnswerRadioButton);

    // Layout ngang cho QPlainTextEdit và QRadioButton
    QHBoxLayout *answerRowLayout = new QHBoxLayout();
    answerRowLayout->addWidget(answerTextEdit);
    answerRowLayout->addWidget(correctAnswerRadioButton);
    answerRowLayout->addWidget(deleteButton);

    // Đặt layout cho answerWidget
    answerWidget->setLayout(answerRowLayout);

    // Thêm answerWidget vào QListWidget dưới dạng một item
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(answerWidget->sizeHint());
    answerListWidget->addItem(item);
    answerListWidget->setItemWidget(item, answerWidget);

    // Kết nối nút xóa với slot xóa, truyền item qua QObject::sender()
    connect(deleteButton, &QPushButton::clicked, this, &CreateQuestion::onDeleteAnswerButtonClicked);
    connect(correctAnswerRadioButton, &QRadioButton::toggled, this, &CreateQuestion::updateSaveButtonState);

    disconnect(ui->addAnswerButton_2, &QPushButton::clicked, this, &CreateQuestion::onSaveQuestionClicked);
    connect(ui->addAnswerButton_2, &QPushButton::clicked, this, &CreateQuestion::onSaveQuestionClicked);

    updateSaveButtonState();
}

void CreateQuestion::onSubmitButtonClicked() {
    QList<QString> answers;
    QList<bool> correctAnswers;

    for (int i = 0; i < answerListWidget->count(); ++i) {
        QListWidgetItem *item = answerListWidget->item(i);
        QWidget *answerWidget = answerListWidget->itemWidget(item);

        // Lấy QPlainTextEdit và QRadioButton từ answerWidget
        QPlainTextEdit *textEdit = answerWidget->findChild<QPlainTextEdit *>();
        QRadioButton *radioButton = answerWidget->findChild<QRadioButton *>();

        if (textEdit) {
            answers.append(textEdit->toPlainText());
        }
        if (radioButton) {
            correctAnswers.append(radioButton->isChecked());
        }
    }

    // Xử lý dữ liệu đáp án ở đây (Ví dụ: gửi lên server)
}

void CreateQuestion::onSaveQuestionClicked() {
    // Get the question content
    QString questionContent = ui->textEdit->toPlainText();

    // Get the difficulty level
    int difficulty = ui->difficultyComboBox->currentIndex() + 1;
    QString difficultyText = ui->difficultyComboBox->currentText();

    // Collect answers and correct answers
    QList<QString> answers;
    QList<bool> correctAnswers;

    for (int i = 0; i < answerListWidget->count(); ++i) {
        QListWidgetItem *item = answerListWidget->item(i);
        QWidget *answerWidget = answerListWidget->itemWidget(item);

        // Get the QPlainTextEdit and QRadioButton from answerWidget
        QPlainTextEdit *textEdit = answerWidget->findChild<QPlainTextEdit *>();
        QRadioButton *radioButton = answerWidget->findChild<QRadioButton *>();

        if (textEdit) {
            answers.append(textEdit->toPlainText());
        }
        if (radioButton) {
            correctAnswers.append(radioButton->isChecked());
        }
    }

    // Print question and answers using qDebug()
    qDebug() << "Question:" << questionContent;
    qDebug() << "Difficulty:" << difficulty << "(" << difficultyText << ")";
    for (int i = 0; i < answers.size(); ++i) {
        qDebug() << "Answer" << i + 1 << ":" << answers[i] 
                 << "| Correct:" << (correctAnswers[i] ? "Yes" : "No");
    }

    // Close the parent QDialog
    QDialog *dialog = qobject_cast<QDialog *>(this->parentWidget());
    if (dialog) {
        dialog->close();
    }
}


void CreateQuestion::onDeleteAnswerButtonClicked() {
    // Xác định nút xóa được nhấn
    QPushButton *deleteButton = qobject_cast<QPushButton *>(sender());
    if (!deleteButton) return;

    // Tìm item chứa deleteButton
    for (int i = 0; i < answerListWidget->count(); ++i) {
        QListWidgetItem *item = answerListWidget->item(i);
        QWidget *answerWidget = answerListWidget->itemWidget(item);

        if (answerWidget && answerWidget->findChild<QPushButton *>() == deleteButton) {
            delete answerListWidget->takeItem(i); // Xóa item khỏi QListWidget
            updateSaveButtonState();
            break;
        }
    }

    updateSaveButtonState();
}

void CreateQuestion::updateSaveButtonState() {
    // Kiểm tra nếu nội dung câu hỏi trống
    bool isQuestionEmpty = ui->textEdit->toPlainText().trimmed().isEmpty();

    // Kiểm tra số lượng đáp án
    int answerCount = answerListWidget->count();

    // Kiểm tra có đáp án đúng nào được chọn không
    bool hasCorrectAnswer = false;
    for (int i = 0; i < answerCount; ++i) {
        QListWidgetItem *item = answerListWidget->item(i);
        QWidget *answerWidget = answerListWidget->itemWidget(item);
        QRadioButton *radioButton = answerWidget->findChild<QRadioButton *>();
        if (radioButton && radioButton->isChecked()) {
            hasCorrectAnswer = true;
            break;
        }
    }

    // Kích hoạt nút Lưu nếu tất cả điều kiện được thỏa mãn
    bool canSave = !isQuestionEmpty && answerCount >= 4 && hasCorrectAnswer;
    ui->addAnswerButton_2->setEnabled(canSave);
}
