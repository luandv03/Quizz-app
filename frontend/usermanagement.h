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

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void showExamRoomList();
    void showExamRoomManagement();
    void showProfile();
    void logout();
    
private slots:
    void onViewButtonClicked(int row);
    void showMenuNavigator();

private:
    Ui::UserManagement *ui;
    void populateTable();
};

#endif // USERMANAGEMENT_H
