#ifndef EXAMROOMLIST_H
#define EXAMROOMLIST_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ExamRoomList;
}

class ExamRoomList : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomList(QWidget *parent = nullptr);
    ~ExamRoomList();

private slots:
    void on_searchButton_clicked();
    void on_avatarButton_clicked();
    void on_joinButton_clicked(QListWidgetItem *item);

private:
    Ui::ExamRoomList *ui;
    void populateExamRoomList();
};

#endif // EXAMROOMLIST_H
