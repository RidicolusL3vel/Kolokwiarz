#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QVector>
#include <QString>
#include "user.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class UserManager
{
private:
    QVector<std::shared_ptr<User>> users; // wektor wskaźników do użytkowników
public:
    UserManager();

    void loadUsersFromFile(const QString& filepath);
    void saveUsersToFile(const QString& filepath);
    std::shared_ptr<User> login(const QString& username, const QString& password);
    std::shared_ptr<User> registerUser(const QString& username, const QString& password, QString* error = nullptr);
    bool validatePassword(const QString& username, const QString& password) const;
};

#endif // USERMANAGER_H
