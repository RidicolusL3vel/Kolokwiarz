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

    QVector<std::shared_ptr<User>> loadUsersFromFile(const QString& filepath);
    void saveUsersToFile(const QString& filepath);
    std::shared_ptr<User> loginOrRegister(const QString& username, const QString& password);
    void updateLastLogin(const QString& username);
    bool validatePassword(const QString& username, const QString& password) const;
};

#endif // USERMANAGER_H
