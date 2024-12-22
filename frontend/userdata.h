#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QJsonObject>

class UserData
{
public:
    static UserData& instance() {
        static UserData instance;
        return instance;
    }

    void setUserData(const QJsonObject &data) {
        userData = data;
    }

    void setUserName(const QString &name) {
        userData["name"] = name;
    }

    void setEmail(const QString &email) {
        userData["email"] = email;
    }

    void setDob(const QString &dob) {
        userData["dob"] = dob;
    }

    QString getUserName() const {
        if (userData.contains("name")) {
            return userData["name"].toString();
        }
        return QString();
    }

    QString getEmail() const {
        if (userData.contains("email")) {
            return userData["email"].toString();
        }
        return QString();
    }

    QString getDob() const {
        if (userData.contains("dob")) {
            return userData["dob"].toString();
        }
        return QString();
    }

    QJsonObject getUserData() const {
        return userData;
    }

    int getUserId() const {
        if (userData.contains("user_id")) {
            return userData["user_id"].toInt();
        }
        return -1; // Return an invalid ID if not found
    }

    void reset() {
        userData = QJsonObject();
    }

private:
    UserData() {}
    ~UserData() {}
    UserData(const UserData&) = delete;
    UserData& operator=(const UserData&) = delete;

    QJsonObject userData;
};

#endif // USERDATA_H
