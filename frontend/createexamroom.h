#ifndef CREATEEXAMROOM_H
#define CREATEEXAMROOM_H

#include <QWidget>

namespace Ui {
class CreateExamRoom;
}

class CreateExamRoom : public QWidget
{
    Q_OBJECT

public:
    explicit CreateExamRoom(QWidget *parent = nullptr);
    ~CreateExamRoom();

private slots:
    void onSaveButtonClicked();
    void validateInputs();

private:
    Ui::CreateExamRoom *ui;
};

#endif // CREATEEXAMROOM_H
