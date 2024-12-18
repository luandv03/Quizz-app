// frontend/sources/examroomlist.h
#ifndef EXAMROOMLIST_H
#define EXAMROOMLIST_H

#include <QWidget>
#include <QListWidgetItem>
#include <QJsonArray>
#include <QJsonObject>
#include <QTcpSocket>

namespace Ui {
class ExamRoomList;
}

class ExamRoomList : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomList(QWidget *parent = nullptr);
    ~ExamRoomList();

signals:
    void showExamRoomDetail();
    void showUserManagement();
    void showExamRoomManagement();

private slots:
    void on_searchButton_clicked();
    void on_avatarButton_clicked();
    void handleJoinButtonClicked(QListWidgetItem *item);

private:
    Ui::ExamRoomList *ui;
    QTcpSocket *tcpSocket;
    void populateExamRoomList(const QJsonArray &examRooms);
    void createExamRoomItem(const QJsonObject &examRoom);
    void onReadyRead();
};

#endif // EXAMROOMLIST_H
