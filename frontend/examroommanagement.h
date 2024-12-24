#ifndef EXAMROOMMANAGEMENT_H
#define EXAMROOMMANAGEMENT_H

#include <QTcpSocket>
#include <QWidget>
#include "examroomdialog.h"

namespace Ui {
class ExamRoomManagement;
}

class ExamRoomManagement : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomManagement(QWidget *parent = nullptr);
    ~ExamRoomManagement();

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void showExamRoomList();
    void showUserManagement();
    void showProfile();
    void logout();

private slots:
    void onViewButtonClicked(int row);
    void onCreateExamRoomBtn();
    void showMenuNavigator();
    void handleGetExamRoom();
    void handleGetExamRoomResponse();

private:
    Ui::ExamRoomManagement *ui;
    QTcpSocket *tcpSocket; // Call API get exam room list
    void populateTable();
};

#endif // EXAMROOMMANAGEMENT_H
