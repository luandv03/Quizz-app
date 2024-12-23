#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void showMenuNavigator();

signals:
    void showProfile();
    void showExamRoomList();
    void showUserManagement();
    void showExamRoomManagement();
    void logout();

private:
    Ui::Profile *ui;
    void checkForChanges();
    void togglePasswordVisibility();
    void saveProfile();
};

#endif // PROFILE_H
