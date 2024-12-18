#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class UserManagement;
}

class UserManagement : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagement(QWidget *parent = nullptr);
    ~UserManagement();

signals:
    void showExamRoomList();
    void showExamRoomManagement();

private slots:
    void onViewButtonClicked(int row);

private:
    Ui::UserManagement *ui;
    void populateTable();
};

#endif // USERMANAGEMENT_H
