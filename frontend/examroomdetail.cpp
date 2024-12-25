// frontend/sources/examroomdetail.cpp
#include "examroomdetail.h"
#include "ui_examroomdetail.h"
#include "userdata.h"

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
#include <QThread>
#include "config.h"

ExamRoomDetail::ExamRoomDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamRoomDetail),
    tcpSocket(new QTcpSocket(this)),
    tcpSocket2(new QTcpSocket(this)),
    tcpSocket3(new QTcpSocket(this)),
    tcpSocket4(new QTcpSocket(this)),
    tcpSocket5(new QTcpSocket(this)),
    tcpSocket6(new QTcpSocket(this))
{
    ui->setupUi(this);

    showMenuNavigator();

    ui->viewExamResultBTn->setEnabled(false);

    // time counter
    // Countdown Timer Setup
    countdownTimer = new QTimer(this);
    // remainingTime = QTime(0, 1, 0);  // Đặt thời gian ban đầu là 1 giờ 30 phút

    // // Cập nhật `timerLabel` ban đầu
    // ui->timerLabel->setText(remainingTime.toString("hh:mm:ss"));
    // // Kết nối QTimer với hàm cập nhật thời gian
    // connect(countdownTimer, &QTimer::timeout, this, &ExamRoomDetail::updateCountdown);

    ui->endMyExamBtn->setCursor(Qt::PointingHandCursor);

    // Connect startExamButton to toggle visibility
    connect(ui->startExamButton, &QPushButton::clicked, [this]() {
        handleStartExam();
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
            
            handleSubmitExam();

            ui->startExamWidget->hide();
            ui->examDetailWidget->show();

            // reset UI
            // Ví dụ reset trạng thái của các thành phần UI
            ui->timerLabel->setText("00:00");
            ui->endMyExamBtn->setEnabled(true);  // Bật lại nút kết thúc bài thi nếu nó bị vô hiệu hóa
            ui->startExamButton->setEnabled(false);  // Vô hiệu hóa nút bắt đầu bài thi
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
        ui->examResultWidget_2->hide();
    });

    // connet to handle logic comment
    connect(ui->submitCommentButton, &QPushButton::clicked, this, &ExamRoomDetail::on_submitCommentButton_clicked);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &ExamRoomDetail::onReadyRead);
    connect(tcpSocket, &QTcpSocket::connected, this, &ExamRoomDetail::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ExamRoomDetail::onDisconnected);
    // Connect to TCP server
    tcpSocket->connectToHost(IPADDRESS, 12345);

    // Example JSON string for comments
    QString commentsJsonString = R"(
    {
        "comments": [
            {
                "id": 1,
                "content": "Bài thi hôm nay khó quá :<<<<",
                "sender_id": 1,
                "sender_name": "Duong Van Gioi",
                "time_send": "2024-12-16 10:20:00"
            },
            {
                "id": 2,
                "content": "De kho qua :>>>",
                "sender_id": 2,
                "sender_name": "Ngo Van Thuc",
                "time_send": "2024-12-16 11:20:00"
            },
            {
                "id": 3,
                "content": "MU vô địch",
                "sender_id": 3,
                "sender_name": "Hoang Hai Phong",
                "time_send": "2024-12-16 11:30:00"
            }
        ]
    }
    )";

    QJsonDocument commentsDoc = QJsonDocument::fromJson(commentsJsonString.toUtf8());
    QJsonArray commentsArray = commentsDoc.object()["comments"].toArray();
    updateCommentList(commentsArray);

    // handle logic practice
     // Connect startExamButton to toggle visibility
    connect(ui->startPracticeButton, &QPushButton::clicked, [this]() {
        ui->practiceDetailWidget->hide();
        ui->startPracticeWidget->show();

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
                                    }
                                ]
                            }
                            )");

        QJsonArray jsonString = doc.object()["questions"].toArray();
        displayQuestionsPractice(jsonString);
    });

    connect(ui->endMyPracticeBtn, &QPushButton::clicked, [this]() {
        QDialog dialog(this);
        dialog.setWindowTitle("Confirm");
        dialog.resize(500, 400);  // Đặt kích thước mong muốn

        // Đưa Dialog ra giữa màn hình
        dialog.move(QGuiApplication::primaryScreen()->geometry().center() - dialog.rect().center());

        // Thêm nội dung vào dialog
        QVBoxLayout layout(&dialog);
        QLabel label("Bạn có chắc chắn muốn kết thúc bài luyện tập không?", &dialog);
        layout.addWidget(&label);

        QDialogButtonBox buttonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, &dialog);
        layout.addWidget(&buttonBox);

        connect(&buttonBox, &QDialogButtonBox::accepted, [&]() {
            dialog.accept();

            // Thực hiện hành động kết thúc bài luyện tập nếu chọn Yes
            ui->timerPracticeLabel->setText("Practice Ended!");
            ui->startPracticeWidget->hide();
            ui->practiceDetailWidget->show();
        });

        connect(&buttonBox, &QDialogButtonBox::rejected, [&]() {
            dialog.reject();
        });

        dialog.exec();
    });
}

ExamRoomDetail::~ExamRoomDetail()
{
    delete ui;
    tcpSocket->close();
    delete tcpSocket;
}

void ExamRoomDetail::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    showMenuNavigator();
}

void ExamRoomDetail::showMenuNavigator()
{
    // Implement search functionality here
    QString role = UserData::instance().getRole();

    // Set up the avatar button dropdown menu
    QMenu *menu = new QMenu(this);

    if (role == "admin") {
        QAction *profileAction = new QAction("Profile", this);
        QAction *userManagementAction = new QAction("User Management", this);
        QAction *examRoomManagementAction = new QAction("Exam Room Management", this);
        QAction *logoutAction = new QAction("Logout", this);

        menu->addAction(profileAction);
        menu->addAction(userManagementAction);
        menu->addAction(examRoomManagementAction);
        menu->addAction(logoutAction);

        ui->avatarButton->setMenu(menu);

        connect(profileAction, &QAction::triggered, [this]() {
            emit showProfile();
        });

        connect(userManagementAction, &QAction::triggered, [this]() {
            emit showUserManagement();
        });

        connect(examRoomManagementAction, &QAction::triggered, [this]() {
            qDebug() << "showExamRoomManagement";
            emit showExamRoomManagement();
        });

        connect(logoutAction, &QAction::triggered, [this]() {
            emit logout();
        });
    } else {
        QAction *examRoomListAction = new QAction("Exam Room List", this);
        QAction *profileAction = new QAction("Profile", this);
        QAction *logoutAction = new QAction("Logout", this);

        menu->addAction(examRoomListAction);
        menu->addAction(profileAction);
        menu->addAction(logoutAction);

        ui->avatarButton->setMenu(menu);

        connect(profileAction, &QAction::triggered, [this]() {
            emit showProfile();
        });

        connect(examRoomListAction, &QAction::triggered, [this]() {
            emit showExamRoomList();
        });

        connect(logoutAction, &QAction::triggered, [this]() {
            emit logout();
        });
    }

    ui->avatarButton->setText(UserData::instance().getUserName());
}

void ExamRoomDetail::setRoomId(int roomId) {
    currentRoomId = roomId;
    qDebug() << "ExamRoomDetail: Room ID set to" << currentRoomId;

    // Load the exam room details based on the roomId
    // Implement the logic to load and display the exam room details
    // Construct the JSON object for the request
    QJsonObject json;
    json["room_id"] = roomId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_ROOM_BY_ID\n%1").arg(QString(jsonData));

    qDebug() << "Sending join room request: " << dataString;

    if (tcpSocket2->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket2->connectToHost(IPADDRESS, 8080);
        if (!tcpSocket2->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket2->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket2->errorString();
        return;
    }

    if (!tcpSocket2->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket2->errorString();
        return;
    }

    qDebug() << "Join room request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket2, &QTcpSocket::readyRead, this, &ExamRoomDetail::handleExamRoomDetailResponse);
}

void ExamRoomDetail::handleExamRoomDetailResponse()
{
    QByteArray response = tcpSocket2->readAll();
    QString responseString(response);

    qDebug() << "Room Response:" << responseString;

    if (responseString.startsWith("DATA JSON GET_ROOM_BY_ID")) {
            // Extract JSON part from the response
            int jsonStartIndex = responseString.indexOf('{');
            int jsonEndIndex = responseString.lastIndexOf('}');
            if (jsonStartIndex != -1 && jsonEndIndex != -1) {
                QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
                QJsonParseError parseError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
                if (parseError.error == QJsonParseError::NoError) {
                    QJsonObject examRoom = jsonDoc.object();

                    qDebug() << "Exam Room:" << examRoom;

                    ui->subjectLabel->setText(examRoom["subject"].toString());

                    QLabel *descriptionLabel = new QLabel(examRoom["description"].toString());
                    descriptionLabel->setWordWrap(true);
                    descriptionLabel->setMaximumHeight(40);

                    ui->numberOfEasyQuestionLabel->setText(QString::number(examRoom["number_of_easy_question"].toInt()));
                    ui->numberOfMediumQuestionLabel->setText(QString::number(examRoom["number_of_medium_question"].toInt()));
                    ui->numberOfHardQuestionLabel->setText(QString::number(examRoom["number_of_hard_question"].toInt()));
                    ui->timeLimitLabel->setText(QString::number(examRoom["time_limit"].toInt()) + " phút");
                    // ui->startTimeLabel->setText("Start Time: " + examRoom["start"].toString());
                    // ui->endTimeLabel->setText("End Time: " + examRoom["end"].toString());
                    ui->statusLabel->setText(examRoom["status"].toString());

                    QString status = examRoom["status"].toString();

                    if (status == "Not started") {
                        ui->startExamButton->setEnabled(false);
                        ui->viewExamResultBTn->setEnabled(false);
                    } else if (status == "Ongoing")
                    {
                        ui->startExamButton->setEnabled(true);
                        ui->viewExamResultBTn->setEnabled(false);
                    } else {
                        ui->startExamButton->setEnabled(false);
                        ui->viewExamResultBTn->setEnabled(true);
                    }

                } else {
                    qDebug() << "JSON Parse Error:" << parseError.errorString();
                }
            } else {
                qDebug() << "Invalid JSON format in response";
            }
        } else {
            qDebug() << "Unknown response from server:" << responseString;
    }

    tcpSocket2->close();
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

    // Lấy giá trị `user_answer`
    int userAnswer = questionObj["user_answer"].toInt();

    qDebug() << "User answer for question:" << userAnswer;

    // Tạo các radio button cho các đáp án
    QJsonArray answersArray = questionObj["answer_of_question"].toArray();
    QList<QRadioButton*> answerButtons; // Lưu các radio button
    for (const QJsonValue &ansValue : answersArray) {
        QJsonObject ansObj = ansValue.toObject();
        QString answerText = ansObj["content"].toString();
        int answerId = ansObj["answer_id"].toInt();

        qDebug() << "Answer for question:" << ansObj["content"].toString();

        QRadioButton *optionButton = new QRadioButton(answerText);
        optionButton->setProperty("answerId", answerId); // Lưu `answerId` vào property
        layout->addWidget(optionButton);

         // Chọn radio button nếu `answerId` khớp với `user_answer`
        if (answerId == userAnswer) {
            optionButton->setChecked(true);
        }

        // Lưu radio button vào danh sách
        answerButtons.append(optionButton);
    }

    QPushButton *sendButton = new QPushButton("Gửi");
    sendButton->setMaximumSize(QSize(150, 40));
    sendButton->setCursor(Qt::PointingHandCursor);
    layout->addWidget(sendButton);

    QLabel *notiSendAnswer = new QLabel("Câu trả lời đã được gửi.");
    notiSendAnswer->setVisible(false); // Ẩn thông báo ban đầu
    layout->addWidget(notiSendAnswer);

    // Thiết lập layout cho câu hỏi
    questionWidget->setLayout(layout);

    // Đặt widget câu hỏi vào item
    item->setSizeHint(questionWidget->sizeHint());
    ui->questionListWidget->addItem(item);
    ui->questionListWidget->setItemWidget(item, questionWidget);

    // Kết nối sendButton với logic gửi câu trả lời
    int examQuestionId = questionObj["exam_question_id"].toInt(); // Lấy `question_id` từ dữ liệu
    connect(sendButton, &QPushButton::clicked, this, [=]() {
        // Kiểm tra radio button được chọn
        int selectedAnswerId = -1;
        for (QRadioButton *button : answerButtons) {
            if (button->isChecked()) {
                selectedAnswerId = button->property("answerId").toInt();
                break;
            }
        }

        if (selectedAnswerId != -1) {
            // Gửi câu trả lời
            handleSendAnswer(examQuestionId, selectedAnswerId);

            // Kết nối tín hiệu xử lý phản hồi
            connect(this, &ExamRoomDetail::answerSubmittedSuccessfully, [=]() {
                notiSendAnswer->setVisible(true); // Hiển thị thông báo nếu thành công
            });
        } else {
            qDebug() << "No answer selected.";
        }
    });
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

        // call func handle submit exam
        handleSubmitExam();
        QThread::msleep(100);

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

    handleGetExamRoomResultByUser();

    ui->examResultWidget_2->show();
}

// handle logic comment
void ExamRoomDetail::on_submitCommentButton_clicked()
{
    qDebug() << "commented";
    QString comment = ui->commentLineEdit->text();
    if (!comment.isEmpty()) {
        QJsonObject commentObj;
        commentObj["type"] = "comment";
        commentObj["content"] = comment;
        commentObj["sender_name"] = "Duong Van Gioi"; // Replace with actual sender name
        commentObj["time_send"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

        createComment("Duong Van Gioi", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"), comment);

        QJsonDocument doc(commentObj);
        QString message = doc.toJson(QJsonDocument::Compact);

        tcpSocket->write(message.toUtf8());
        ui->commentLineEdit->clear();
    }
}

void ExamRoomDetail::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    qDebug() << "comment:::" << obj["content"].toString();

    if (obj["type"] == "comment") {
        QString comment = obj["content"].toString();
        QString senderName = obj["sender_name"].toString();
        QString timeSend = obj["time_send"].toString();

        createComment(senderName, timeSend, comment);

        // // Tạo QWidget chứa thông tin bình luận
        // QWidget *commentWidget = new QWidget();
        // QVBoxLayout *mainLayout = new QVBoxLayout(commentWidget);

        // // Tạo layout cho sender_name và time_send (nằm cùng hàng)
        // QHBoxLayout *headerLayout = new QHBoxLayout();
        // QLabel *senderLabel = new QLabel(senderName);
        // senderLabel->setStyleSheet("font-weight: bold;");
        // QLabel *timeLabel = new QLabel(timeSend);
        // headerLayout->addWidget(senderLabel);
        // headerLayout->addWidget(timeLabel);

        // // Tạo phần content với border và tự động xuống dòng
        // QLabel *contentLabel = new QLabel(comment);
        // contentLabel->setWordWrap(true); // Cho phép xuống dòng
        // contentLabel->setStyleSheet("border: 1px solid black; padding: 5px;");

        // // Thêm các phần vào layout chính
        // mainLayout->addLayout(headerLayout);
        // mainLayout->addWidget(contentLabel);

        // // Thiết lập layout cho commentWidget
        // commentWidget->setLayout(mainLayout);

        // // Thêm commentWidget vào danh sách (QListWidget)
        // ui->discussionListWidget->addItem(new QListWidgetItem());
        // ui->discussionListWidget->item(ui->discussionListWidget->count() - 1)->setSizeHint(commentWidget->sizeHint());
        // ui->discussionListWidget->setItemWidget(ui->discussionListWidget->item(ui->discussionListWidget->count() - 1), commentWidget);
    }
}

void ExamRoomDetail::updateCommentList(const QJsonArray &commentsArray)
{
    // ui->discussionListWidget->clear();
    qDebug() << "Updating comments. Number of comments:" << commentsArray.size();

    foreach (const QJsonValue &value, commentsArray) {
        QJsonObject commentObj = value.toObject();
        QString comment = commentObj["content"].toString();
        QString senderName = commentObj["sender_name"].toString();
        QString timeSend = commentObj["time_send"].toString();

        createComment(senderName, timeSend, comment);

        // // Tạo QWidget chứa thông tin bình luận
        // QWidget *commentWidget = new QWidget();
        // QVBoxLayout *mainLayout = new QVBoxLayout(commentWidget);

        // // Tạo layout cho sender_name và time_send (nằm cùng hàng)
        // QHBoxLayout *headerLayout = new QHBoxLayout();
        // QLabel *senderLabel = new QLabel(senderName);
        // senderLabel->setStyleSheet("font-weight: bold;");
        // QLabel *timeLabel = new QLabel(timeSend);
        // headerLayout->addWidget(senderLabel);
        // headerLayout->addWidget(timeLabel);

        // // Tạo phần content với border và tự động xuống dòng
        // QLabel *contentLabel = new QLabel(comment);
        // contentLabel->setWordWrap(true); // Cho phép xuống dòng
        // contentLabel->setStyleSheet("border: 1px solid black; padding: 5px;");

        // // Thêm các phần vào layout chính
        // mainLayout->addLayout(headerLayout);
        // mainLayout->addWidget(contentLabel);

        // // Thiết lập layout cho commentWidget
        // commentWidget->setLayout(mainLayout);

        // // Thêm commentWidget vào danh sách (QListWidget)
        // ui->discussionListWidget->addItem(new QListWidgetItem());
        // ui->discussionListWidget->item(ui->discussionListWidget->count() - 1)->setSizeHint(commentWidget->sizeHint());
        // ui->discussionListWidget->setItemWidget(ui->discussionListWidget->item(ui->discussionListWidget->count() - 1), commentWidget);
    }
}

void ExamRoomDetail::createComment(const QString &senderName, const QString &timeSend, const QString &comment) {
    // Tạo QWidget chứa thông tin bình luận
    QWidget *commentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(commentWidget);

    // Tạo layout cho sender_name và time_send (nằm cùng hàng)
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *senderLabel = new QLabel(senderName);
    senderLabel->setStyleSheet("font-weight: bold;");
    QLabel *timeLabel = new QLabel(timeSend);
    headerLayout->addWidget(senderLabel);
    headerLayout->addWidget(timeLabel);

    // Tạo phần content với border và tự động xuống dòng
    QLabel *contentLabel = new QLabel(comment);
    contentLabel->setWordWrap(true); // Cho phép xuống dòng
    contentLabel->setStyleSheet("border: 1px solid black; padding: 5px;");

    // Thêm các phần vào layout chính
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(contentLabel);

    // Thiết lập layout cho commentWidget
    commentWidget->setLayout(mainLayout);

    // Thêm commentWidget vào danh sách (QListWidget)
    ui->discussionListWidget->addItem(new QListWidgetItem());
    ui->discussionListWidget->item(ui->discussionListWidget->count() - 1)->setSizeHint(commentWidget->sizeHint());
    ui->discussionListWidget->setItemWidget(ui->discussionListWidget->item(ui->discussionListWidget->count() - 1), commentWidget);
}

void ExamRoomDetail::onConnected() {
    qDebug() << "Connected to server.";
}

void ExamRoomDetail::onDisconnected() {
    qDebug() << "Disconnected from server.";
}

void ExamRoomDetail::handleGetExamRoomResultByUser() {
    // set exam result;
    QJsonObject json;
    json["room_id"] = currentRoomId;
    json["user_id"] = UserData::instance().getUserId();

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL GET_USER_EXAM_RESULT\n%1").arg(QString(jsonData));

    qDebug() << "Sending join room request: " << dataString;

    if (tcpSocket3->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket3->connectToHost(IPADDRESS, 8080);
        if (!tcpSocket3->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket3->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket3->errorString();
        return;
    }

    if (!tcpSocket3->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket3->errorString();
        return;
    }

    qDebug() << "Join room request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket3, &QTcpSocket::readyRead, this, &ExamRoomDetail::handleGetExamRoomResultByUserResponse);
}

void ExamRoomDetail::handleGetExamRoomResultByUserResponse() {
    QByteArray response = tcpSocket3->readAll();
    QString responseString(response);

    qDebug() << "Exam Room Result Response:" << responseString;

    if (responseString.startsWith("DATA JSON USER_EXAM_RESULT")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QJsonArray examResults = jsonObj["data"].toObject()["exam_results"].toArray();

                if (!examResults.isEmpty()) {
                    QJsonObject examResult = examResults.first().toObject();
                    int examId = examResult["exam_id"].toInt();
                    double score = examResult["score"].toDouble();
                    int totalQuestions = examResult["total_questions"].toInt();
                    int answeredQuestions = examResult["answered_questions"].toInt();
                    int correctAnswers = examResult["correct_answers"].toInt();

                    qDebug() << "Exam ID:" << examId;
                    qDebug() << "Score:" << score;
                    qDebug() << "Total Questions:" << totalQuestions;
                    qDebug() << "Answered Questions:" << answeredQuestions;
                    qDebug() << "Correct Answers:" << correctAnswers;

                    // Update UI with the extracted attributes
                    // ui->examIdLabel->setText(QString::number(examId));
                    ui->scoreLabel->setText(QString::number(score));
                    ui->totalQuestionsLabel->setText(QString::number(totalQuestions));
                    ui->answeredQuestionsLabel->setText(QString::number(answeredQuestions));
                    ui->correctAnswersLabel->setText(QString::number(correctAnswers));
                } else {
                    qDebug() << "No exam results found.";
                }
            } else {
                qDebug() << "Failed to parse exam results response JSON.";
            }
        } else {
            qDebug() << "Invalid exam results response format.";
        }
    }

}

void ExamRoomDetail::handleStartExam() {
    // set exam result;
    QJsonObject json;
    json["room_id"] = currentRoomId;
    json["user_id"] = UserData::instance().getUserId();

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL USER_START_EXAM\n%1").arg(QString(jsonData));

    qDebug() << "Sending start exam request: " << dataString;

    if (tcpSocket4->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket4->connectToHost(IPADDRESS, 8080);
        if (!tcpSocket4->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket4->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket4->errorString();
        return;
    }

    if (!tcpSocket4->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket4->errorString();
        return;
    }

    qDebug() << "Start exam request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket4, &QTcpSocket::readyRead, this, &ExamRoomDetail::handleStartExamResponse);
}

// "DATA JSON USER_START_EXAM
// {
//         ""room_id"":        4,
//         ""user_id"":        1,
//         ""exam_id"":        1,
//         ""start_time"":        ""2023-11-03 09:00:00"",
//         ""time_limit"":        60,
//         ""questions"":        [{
//                         ""question_id"":        91,
//                         ""content"":        ""Easy History Question 1"",
//                         ""answer_of_question"":        [{
//                                         ""answer_id"":        361,
//                                         ""content"":        ""Answer 1"",
//                                         ""is_true"":        false
//                                 }, {
//                                         ""answer_id"":        362,
//                                         ""content"":        ""Answer 2"",
//                                         ""is_true"":        true
//                                 }, {
//                                         ""answer_id"":        363,
//                                         ""content"":        ""Answer 3"",
//                                         ""is_true"":        false
//                                 }, {
//                                         ""answer_id"":        364,
//                                         ""content"":        ""Answer 4"",
//                                         ""is_true"":        false
//                                 }],
//                         ""user_answer"":        362
//                 },   
//         .........
//     ]
// }"
void ExamRoomDetail::handleStartExamResponse() {
    QByteArray response = tcpSocket4->readAll();
    QString responseString(response);

    qDebug() << "Start Exam Response:" << responseString;

    if (responseString.startsWith("DATA JSON USER_START_EXAM")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                examId = jsonObj["exam_id"].toInt();
                QString startTime = jsonObj["start_time"].toString(); 
                int timeLimit = jsonObj["time_limit"].toInt(); // Lấy giới hạn thời gian

                // Xử lý thời gian bắt đầu và giới hạn
                QDateTime startDateTime = QDateTime::fromString(startTime, "yyyy-MM-dd HH:mm:ss");
                if (!startDateTime.isValid()) {
                    qDebug() << "Invalid start time format.";
                    return;
                }
                QDateTime endDateTime = startDateTime.addSecs(timeLimit * 60); // Cộng thêm giới hạn thời gian (phút)
                QDateTime currentDateTime = QDateTime::currentDateTime();

                // Kiểm tra nếu thời gian hiện tại đã vượt qua thời gian kết thúc
                if (currentDateTime > endDateTime) {
                    qDebug() << "Time is up! The exam has ended.";
                    QMessageBox::information(this, "Time's up!", "Thời gian làm bài thi đã kết thúc. Bạn không thể tham gia.");
                    return;
                }

                QJsonArray questions = jsonObj["questions"].toArray();

                if (!questions.isEmpty()) {
                    displayQuestions(questions);

                    ui->examDetailWidget->hide();
                    ui->examResultWidget_2->hide();
                    ui->startExamWidget->show();

                    // Tính thời gian còn lại
                    qint64 secondsLeft = currentDateTime.secsTo(endDateTime);
                    if (secondsLeft <= 0) {
                        qDebug() << "Time is up! The exam has ended.";
                        return;
                    }

                    int minutesLeft = secondsLeft / 60;
                    int secondsRemaining = secondsLeft % 60;

                    qDebug() << "Time remaining:" << minutesLeft << "minutes" << secondsRemaining << "seconds";

                    // set Time limit for exam room
                    int timeLimit = jsonObj["time_limit"].toInt();
                    remainingTime = QTime(0, minutesLeft, secondsRemaining);  //
                    // Cập nhật `timerLabel` ban đầu
                    ui->timerLabel->setText(remainingTime.toString("hh:mm:ss"));

                    countdownTimer->start(1000);  // Cập nhật mỗi 1 giây
                    // Kết nối QTimer với hàm cập nhật thời gian
                    connect(countdownTimer, &QTimer::timeout, this, &ExamRoomDetail::updateCountdown);
                } else {
                    qDebug() << "No questions found.";
                }
                
            } else {
                qDebug() << "Failed to parse exam questions response JSON.";
            }
        } else {
            qDebug() << "Invalid exam results response format.";
        }
    }
}

void ExamRoomDetail::handleSendAnswer(int examQuestionId, int answerId)
{
    // set exam result;
    QJsonObject json;
    json["exam_question_id"] = examQuestionId;
    json["answer_id"] = answerId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL SUBMIT_EXAM_QUESTION\n%1").arg(QString(jsonData));

    qDebug() << "Sending send answer request: " << dataString;

    if (tcpSocket5->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket5->connectToHost(IPADDRESS, 8080);
        if (!tcpSocket5->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket5->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket5->errorString();
        return;
    }

    if (!tcpSocket5->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket5->errorString();
        return;
    }

    qDebug() << "Send answer request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket5, &QTcpSocket::readyRead, this, &ExamRoomDetail::handleSendAnswerResponse);
}

void ExamRoomDetail::handleSendAnswerResponse() {
    QByteArray response = tcpSocket5->readAll();
    QString responseString(response);

    qDebug() << "Send Answer Response:" << responseString;

    if (responseString.startsWith("NOTIFICATION SUBMIT_EXAM_QUESTION_SUCCESS")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                QString message = jsonObj["message"].toString();

                emit answerSubmittedSuccessfully();

                qDebug() << "Message:" << message;
                
            } else {
                qDebug() << "Failed to parse exam results response JSON.";
            }
        } else {
            qDebug() << "Invalid exam results response format.";
        }
    }
}

// handle user submit exam
void ExamRoomDetail::handleSubmitExam(){
    // set exam result;
    QJsonObject json;
    json["examId"] = examId;

    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    // Construct the data string in the specified format
    QString dataString = QString("CONTROL SUBMIT_EXAM\n%1").arg(QString(jsonData));

    qDebug() << "Sending submit exam request: " << dataString;

    if (tcpSocket6->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket6->connectToHost(IPADDRESS, 8080);
        if (!tcpSocket6->waitForConnected(3000)) {
            qDebug() << "Failed to connect to server.";
            return;
        }
    }

    qint64 bytesWritten = tcpSocket6->write(dataString.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write to socket: " << tcpSocket6->errorString();
        return;
    }

    if (!tcpSocket6->flush()) {
        qDebug() << "Failed to flush socket: " << tcpSocket6->errorString();
        return;
    }

    qDebug() << "Submit exam request sent, bytes written: " << bytesWritten;
    // Connect the readyRead signal to handle the response
    connect(tcpSocket6, &QTcpSocket::readyRead, this, &ExamRoomDetail::handleSubmitExamResponse);
}

// "NOTIFICATION SUBMIT_EXAM_SUCCESS 2024-12-19T00:12:55
// {
//         ""total_questions"":        30,
//         ""answered_questions"":        30,
//         ""correct_answers"":        30,
//         ""incorrect_answers"":        0
// }"
void ExamRoomDetail::handleSubmitExamResponse() {
    QByteArray response = tcpSocket6->readAll();
    QString responseString(response);

    qDebug() << "Submit Exam Response:" << responseString;

    if (responseString.startsWith("NOTIFICATION SUBMIT_EXAM_SUCCESS")) {
        // Extract JSON part from the response
        int jsonStartIndex = responseString.indexOf('{');
        int jsonEndIndex = responseString.lastIndexOf('}');
        if (jsonStartIndex != -1 && jsonEndIndex != -1) {
            QString jsonString = responseString.mid(jsonStartIndex, jsonEndIndex - jsonStartIndex + 1);
            QJsonParseError parseError;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                QJsonObject jsonObj = jsonDoc.object();
                int totalQuestions = jsonObj["total_questions"].toInt();
                int answeredQuestions = jsonObj["answered_questions"].toInt();
                int correctAnswers = jsonObj["correct_answers"].toInt();
                int incorrectAnswers = jsonObj["incorrect_answers"].toInt();

                qDebug() << "Total Questions:" << totalQuestions;
                qDebug() << "Answered Questions:" << answeredQuestions;
                qDebug() << "Correct Answers:" << correctAnswers;
                qDebug() << "Incorrect Answers:" << incorrectAnswers;
                
            } else {
                qDebug() << "Failed to parse exam results response JSON.";
            }
        } else {
            qDebug() << "Invalid exam results response format.";
        }
    }
}


void ExamRoomDetail::displayQuestionsPractice(const QJsonArray &questionsArray)
{
    // ui->questionListWidget->clear();  // Xóa các mục cũ
    qDebug() << "Populating questions. Number of questions:" << questionsArray.size();

    foreach (const QJsonValue &value, questionsArray) {
        QJsonObject questionObj = value.toObject();
        qDebug() << "Creating item for question:" << questionObj["content"].toString();

        createQuestionItemPractice(questionObj);
    }

    qDebug() << "Finished populating questions.";
}

void ExamRoomDetail::createQuestionItemPractice(const QJsonObject &questionObj)
{
    // Tạo một widget mới để hiển thị câu hỏi
    QListWidgetItem *item = new QListWidgetItem(ui->questionListPracticeWidget);

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
    ui->questionListPracticeWidget->addItem(item);
    ui->questionListPracticeWidget->setItemWidget(item, questionWidget);
}
