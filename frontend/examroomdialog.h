#ifndef EXAMROOMDIALOG_H
#define EXAMROOMDIALOG_H

#include <QWidget>

namespace Ui {
class ExamRoomDialog;
}

class ExamRoomDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ExamRoomDialog(QWidget *parent = nullptr);
    ~ExamRoomDialog();

    void setRoomDetails(const QString &roomId, const QString &roomName, const QString &description, const QString &timeLimit, const QString &status);

// private slots:
//     void onCloseButtonClicked();

private:
    Ui::ExamRoomDialog *ui;
};

#endif // EXAMROOMDIALOG_H