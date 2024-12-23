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

signals:
    void showExamRoomList();
    void showUserManagement();
    void showProfile();

private slots:
    void onViewButtonClicked(int row);
    void onCreateExamRoomBtn();

private:
    Ui::ExamRoomManagement *ui;
    void populateTable();
};

#endif // EXAMROOMMANAGEMENT_H
