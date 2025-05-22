#include "usermanager.h"
#include "admin.h"

UserManager::UserManager() {}

QVector<std::shared_ptr<User>> UserManager::loadUsersFromFile(const QString& filepath){
    QVector<std::shared_ptr<User>> users;
    QFile file(filepath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Nie udało się otworzyć pliku użytkowników.";
        return {};
    }

    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonArray userArray = jsonDoc.array();

    for(const QJsonValue& value : userArray){
        QJsonObject usersJson = value.toObject();
        QString username = usersJson["username"].toString();
        QString password = usersJson["password"].toString();
        int totalPoints = usersJson["totalPoints"].toInt();
        int totalGames = usersJson["totalGames"].toInt();
        QDateTime lastLogin = QDateTime::fromString(usersJson["lastLogin"].toString(), Qt::ISODate);
        bool isAdmin = usersJson["isAdmin"].toBool();

        if(isAdmin){
            users.append(std::make_shared<Admin>(username, password, totalPoints, totalGames, lastLogin));
        } else{
            users.append(std::make_shared<User>(username, password, totalPoints, totalGames, lastLogin));
        }
    }

    return users;
}

void UserManager::saveUsersToFile(const QString& filepath){
    QJsonArray userArray;
    for(const auto& user : users){
        QJsonObject obj;
        obj["username"] = user->getUsername();
        obj["password"] = user->getPassword();
        obj["totalPoints"] = user->getTotalPoints();
        obj["totalGames"] = user->getTotalGames();
        obj["lastLogin"] = user->getLastLogin().toString(Qt::ISODate);
        obj["isAdmin"] = dynamic_cast<Admin*>(user.get()) != nullptr;

        userArray.append(obj);
    }

    QJsonDocument doc(userArray);
    QFile users(filepath);
    if(users.open(QIODevice::WriteOnly | QIODevice::Text)){
        users.write(doc.toJson());
        users.close();
    }
}

std::shared_ptr<User> UserManager::loginOrRegister(const QString& username, const QString& password){
    for (const auto& user : users){
        if(user->getUsername() == username){
            if(user->getPassword() == password){
                user->setLastLogin(QDateTime::currentDateTime());
                return user;
            } else{
                qWarning() << "Błędne hasło.";
                return nullptr;
            }
        }
    }

    if(users.isEmpty()){
        auto admin = std::make_shared<Admin>(username, password);
        users.append(admin);
        return admin;
    }

    auto newUser = std::make_shared<User>(username, password);
    users.append(newUser);
    return newUser;
}

void UserManager::updateLastLogin(const QString& username){
    for (const auto& user : users){
        if(user->getUsername() == username){
            user->setLastLogin(QDateTime::currentDateTime());
            return;
        }
    }
}

bool UserManager::validatePassword(const QString& username, const QString& password) const{
    for (const auto& user : users){
        if(user->getUsername() == username && user->getPassword() == password){
            return true;
        }
    }
    return false;
}
