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

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void showExamRoomDetail(int roomId);
    void showUserManagement();
    void showExamRoomManagement();
    void showProfile();
    void logout();

private slots:
    void on_searchButton_clicked();
    void on_avatarButton_clicked();
    void onReadyRead();
    void handleJoinRoomResponse();
    void handleJoinButtonClicked(int roomId);
    void onConnected();
    void onDisconnected();
    void showMenuNavigator();

private:
    Ui::ExamRoomList *ui;
    QTcpSocket *tcpSocket;
    void populateExamRoomList(const QJsonArray &examRooms);
    void createExamRoomItem(const QJsonObject &examRoom);
    void callApiJoinExamRoom(int userId, int roomId);

};

#endif // EXAMROOMLIST_H
