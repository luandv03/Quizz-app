// frontend/sources/examroomdetail.cpp
#include "examroomdetail.h"
#include "ui_examroomdetail.h"
#include <QMenu>
#include <QAction>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QRadioButton>
#include <QMessageBox>
#include <QScreen>  // Thêm dòng này để sử dụng QScreen
#include <QDialog>

ExamRoomDetail::ExamRoomDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDetail)
{
    ui->setupUi(this);

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);
    QAction *examRoomListAction = new QAction("Exam Room List", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *practicesAction = new QAction("Logout", this);

    menu->addAction(examRoomListAction);
    menu->addAction(profileAction);
    menu->addAction(practicesAction);

    ui->avatarButton->setMenu(menu);

    connect(examRoomListAction, &QAction::triggered, [this]() {
        emit showExamRoomList();
    });

    ui->viewExamResultBTn->setEnabled(false);

    // time counter
    // Countdown Timer Setup
    countdownTimer = new QTimer(this);
    remainingTime = QTime(0, 1, 0);  // Đặt thời gian ban đầu là 1 giờ 30 phút

    // Cập nhật `timerLabel` ban đầu
    ui->timerLabel->setText(remainingTime.toString("hh:mm:ss"));
    ui->endMyExamBtn->setCursor(Qt::PointingHandCursor);

    // Kết nối QTimer với hàm cập nhật thời gian
    connect(countdownTimer, &QTimer::timeout, this, &ExamRoomDetail::updateCountdown);

    // Connect startExamButton to toggle visibility
    connect(ui->startExamButton, &QPushButton::clicked, [this]() {
        ui->examDetailWidget->hide();
        ui->examResultWidget->hide();
        ui->startExamWidget->show();

        countdownTimer->start(1000);  // Cập nhật mỗi 1 giây

        // Gán dữ liệu JSON vào chuỗi
        QJsonDocument doc = QJsonDocument::fromJson(R"(
                            {
                                "questions": [
                                    {
                                        "question_id": 1,
                                        "content": "Git là gì?",
                                        "answer_of_question": [
                                            {
                                                "answer_of_question_id": 1,
                                                "content": "Một hệ thống quản lý phiên bản"
                                            },
                                            {
                                                "answer_of_question_id": 2,
                                                "content": "Một nền tảng lưu trữ trực tuyến"
                                            },
                                            {
                                                "answer_of_question_id": 3,
                                                "content": "Tên viết tắt của Gitlab và Github"
                                            },
                                            {
                                                "answer_of_question_id": 4,
                                                "content": "Một ngôn ngữ lập trình"
                                            }
                                        ]
                                    },
                                    {
                                        "question_id": 2,
                                        "content": "Java là gì?",
                                        "answer_of_question": [
                                            {
                                                "answer_of_question_id": 1,
                                                "content": "Một hệ thống quản lý phiên bản"
                                            },
                                            {
                                                "answer_of_question_id": 2,
                                                "content": "Một nền tảng lưu trữ trực tuyến"
                                            },
                                            {
                                                "answer_of_question_id": 3,
                                                "content": "Tên viết tắt của Gitlab và Github"
                                            },
                                            {
                                                "answer_of_question_id": 4,
                                                "content": "Một ngôn ngữ lập trình"
                                            }
                                        ]
                                    },
                                    {
                                        "question_id": 3,
                                        "content": "Tomcat là gì?",
                                        "answer_of_question": [
                                            {
                                                "answer_of_question_id": 1,
                                                "content": "Một hệ thống quản lý phiên bản"
                                            },
                                            {
                                                "answer_of_question_id": 2,
                                                "content": "Một nền tảng lưu trữ trực tuyến"
                                            },
                                            {
                                                "answer_of_question_id": 3,
                                                "content": "Tên viết tắt của Gitlab và Github"
                                            },
                                            {
                                                "answer_of_question_id": 4,
                                                "content": "Một ngôn ngữ lập trình"
                                            }
                                        ]
                                    },
                                    {
                                        "question_id": 4,
                                        "content": "Docker là gì?",
                                        "answer_of_question": [
                                            {
                                                "answer_of_question_id": 1,
                                                "content": "Một hệ thống quản lý phiên bản"
                                            },
                                            {
                                                "answer_of_question_id": 2,
                                                "content": "Một nền tảng lưu trữ trực tuyến"
                                            },
                                            {
                                                "answer_of_question_id": 3,
                                                "content": "Tên viết tắt của Gitlab và Github"
                                            },
                                            {
                                                "answer_of_question_id": 4,
                                                "content": "Một ngôn ngữ lập trình"
                                            }
                                        ]
                                    },
                                    {
                                        "question_id": 5,
                                        "content": "Linux là gì?",
                                        "answer_of_question": [
                                            {
                                                "answer_of_question_id": 1,
                                                "content": "Một hệ thống quản lý phiên bản"
                                            },
                                            {
                                                "answer_of_question_id": 2,
                                                "content": "Một nền tảng lưu trữ trực tuyến"
                                            },
                                            {
                                                "answer_of_question_id": 3,
                                                "content": "Tên viết tắt của Gitlab và Github"
                                            },
                                            {
                                                "answer_of_question_id": 4,
                                                "content": "Một ngôn ngữ lập trình"
                                            }
                                        ]
                                    }
                                ]
                            }
                            )");

        QJsonArray jsonString = doc.object()["questions"].toArray();
        displayQuestions(jsonString);
    });

    // show message when time exam expired
    connect(ui->endMyExamBtn, &QPushButton::clicked, [this]() {
        QDialog dialog(this);
        dialog.setWindowTitle("Confirm");
        dialog.resize(500, 400);  // Đặt kích thước mong muốn

        // Đưa Dialog ra giữa màn hình
        dialog.move(QGuiApplication::primaryScreen()->geometry().center() - dialog.rect().center());

        // Thêm nội dung vào dialog
        QVBoxLayout layout(&dialog);
        QLabel label("Bạn có chắc chắn muốn kết thúc bài thi không?", &dialog);
        layout.addWidget(&label);

        QDialogButtonBox buttonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, &dialog);
        layout.addWidget(&buttonBox);

        connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
            qDebug() << "Exam has ended.";
            dialog.accept();

            // Thực hiện hành động kết thúc bài thi nếu chọn Yes
            countdownTimer->stop();
            ui->timerLabel->setText("Exam Ended!");
            ui->startExamWidget->hide();
            ui->examDetailWidget->show();

            // reset UI
            // Ví dụ reset trạng thái của các thành phần UI
            ui->timerLabel->setText("00:00");
            ui->endMyExamBtn->setEnabled(true);  // Bật lại nút kết thúc bài thi nếu nó bị vô hiệu hóa
            qDebug() << "UI has been reset.";
            qDebug() << "Exam has ended.";
        });

        connect(&buttonBox, &QDialogButtonBox::rejected, [&]() {
            dialog.reject();
        });

        dialog.exec();
    });

    // show exam result ui
    connect(ui->viewExamResultBTn, &QPushButton::clicked, this, &ExamRoomDetail::viewExamResult);

    // back to exam detail ui
    connect(ui->backExamDetailWidget, &QPushButton::clicked, [this]() {
        ui->examDetailWidget->show();
        ui->examResultWidget->hide();
    });
}

ExamRoomDetail::~ExamRoomDetail()
{
    delete ui;
}

void ExamRoomDetail::displayQuestions(const QJsonArray &questionsArray)
{
    // ui->questionListWidget->clear();  // Xóa các mục cũ
    qDebug() << "Populating questions. Number of questions:" << questionsArray.size();

    foreach (const QJsonValue &value, questionsArray) {
        QJsonObject questionObj = value.toObject();
        qDebug() << "Creating item for question:" << questionObj["content"].toString();

        createQuestionItem(questionObj);
    }

    qDebug() << "Finished populating questions.";
}

void ExamRoomDetail::createQuestionItem(const QJsonObject &questionObj)
{
    // Tạo một widget mới để hiển thị câu hỏi
    QListWidgetItem *item = new QListWidgetItem(ui->questionListWidget);

    // Tạo một widget để chứa câu hỏi và các lựa chọn
    QWidget *questionWidget = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(questionWidget);

    // Tạo label cho câu hỏi
    QLabel *questionLabel = new QLabel(questionObj["content"].toString());
    QFont questionFont;
    questionFont.setPointSize(12);
    questionFont.setBold(true);
    questionLabel->setFont(questionFont);
    layout->addWidget(questionLabel);

    // Tạo các radio button cho các đáp án
    QJsonArray answersArray = questionObj["answer_of_question"].toArray();
    for (const QJsonValue &ansValue : answersArray) {
        QJsonObject ansObj = ansValue.toObject();
        QString answerText = ansObj["content"].toString();

        qDebug() << "Answer for question:" << ansObj["content"].toString();

        QRadioButton *optionButton = new QRadioButton(answerText);
        layout->addWidget(optionButton);
    }

    QPushButton *sendButton = new QPushButton("Gửi");
    sendButton->setMaximumSize(QSize(150, 40));
    sendButton->setCursor(Qt::PointingHandCursor);
    layout->addWidget(sendButton);

    QLabel *notiSendAnswer = new QLabel("Câu trả lời đã được gửi.");
    layout->addWidget(notiSendAnswer);

    // Thiết lập layout cho câu hỏi
    questionWidget->setLayout(layout);

    // Đặt widget câu hỏi vào item
    item->setSizeHint(questionWidget->sizeHint());
    ui->questionListWidget->addItem(item);
    ui->questionListWidget->setItemWidget(item, questionWidget);
}

void ExamRoomDetail::updateCountdown()
{
    if (remainingTime == QTime(0, 0, 0)) {
        countdownTimer->stop();  // Dừng bộ đếm khi hết giờ
        ui->timerLabel->setText("Time's up!");
        disableSendButtons(this); // 'this' là widget cha chứa các QPushButton

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);  // Loại thông báo (Information)
        msgBox.setWindowTitle("Hết thời gian");
        msgBox.setText("Đã hết thời gian làm bài. Kết quả đã được tự động submit lên hệ thống.");

        // Thêm chỉ một nút "Exit"
        QPushButton *exitButton = msgBox.addButton("Exit", QMessageBox::AcceptRole);

        // Hiển thị hộp thoại và đợi người dùng nhấn nút
        msgBox.exec();

        ui->startExamWidget->hide();
        ui->examDetailWidget->show();

        ui->startExamButton->setEnabled(false);
        ui->viewExamResultBTn->setEnabled(true);

        qDebug() << "Out room:";

        return;
    }

    // Giảm thời gian đi 1 giây
    remainingTime = remainingTime.addSecs(-1);
    ui->timerLabel->setText(remainingTime.toString("hh:mm:ss"));
}

void ExamRoomDetail::disableSendButtons(QWidget *widget) {
    for (QObject *child : widget->children()) {
        if (QPushButton *button = qobject_cast<QPushButton *>(child)) {
            if (button->text() == "Gửi" || button->text() == "End My Exam") {
                button->setDisabled(true);
            }
        } else if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            disableSendButtons(childWidget); // Đệ quy nếu có widget lồng nhau
        }
    }
}

void ExamRoomDetail::viewExamResult()
{
    ui->examDetailWidget->hide();
    ui->startExamWidget->hide();
    ui->examResultWidget->show();
}

