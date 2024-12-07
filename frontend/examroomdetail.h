// frontend/sources/examroomdetail.h
#ifndef EXAMROOMDETAIL_H
#define EXAMROOMDETAIL_H

#include <QWidget>

namespace Ui {
class ExamRoomDetail;
}

class ExamRoomDetail : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomDetail(QWidget *parent = nullptr);
    ~ExamRoomDetail();

private:
    Ui::ExamRoomDetail *ui;
};

#endif // EXAMROOMDETAIL_H
