#include "usermanager.h"
#include "admin.h"
#include <QDir>

UserManager::UserManager() { qDebug() << "Current working directory:" << QDir::currentPath(); }

void UserManager::loadUsersFromFile(const QString& filepath){
    this->users.clear(); // Czyści pole w razie gdyby coś tam się znajdowało

    QVector<std::shared_ptr<User>> users;
    QFile file(filepath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Nie udało się otworzyć pliku użytkowników.";
        return ;
    }

    QByteArray data = file.readAll();

    if(data.isEmpty()){
        qWarning() << "Plik użytkowników jest pusty.";
        this->users = users; // Zwraca pusty wektor
        return;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Błąd parsowania JSON: " << parseError.errorString();
        return ;
    }

    if(!jsonDoc.isArray()){
        qWarning() << "Oczekiwano tablicy JSON.";
        return ;
    }

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

    this->users = users;
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
        return;
    }else{
        qWarning() << "Nie udało się zapisać pliku użytkowników.";
        return;
    }
}

std::shared_ptr<User> UserManager::login(const QString& username, const QString& password){
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
    return nullptr;
}

std::shared_ptr<User> UserManager::registerUser(const QString& username, const QString& password, QString* error){
    for (const auto& user : users){ // Sprawdza czy użytkownik o tej nazwie już istnieje
        if(user->getUsername() == username){
            if(error) *error = "Użytkownik o tej nazwie już istnieje.";
            return nullptr;
        }
    }
    // Sprawdza czy nazwa użytkownika i hasło są puste lub zawierają spacje
    if(username.isEmpty() || password.isEmpty()){
        if(error) *error = "Nazwa użytkownika i hasło nie mogą być puste.";
        return nullptr;
    }

    if(username.contains(' ') || password.contains(' ')){
        if(error) *error = "Nazwa użytkownika i hasło nie mogą zawierać spacji.";
        return nullptr;
    }
    // Jeśli nie ma żadnych użytkowników, tworzy pierwszego użytkownika jako admina
    if(users.isEmpty()){
        auto admin = std::make_shared<Admin>(username, password);
        admin->setLastLogin(QDateTime::currentDateTime());
        users.append(admin);
        return admin;
    }

    auto newUser = std::make_shared<User>(username, password);
    newUser->setLastLogin(QDateTime::currentDateTime());
    users.append(newUser);
    return newUser;
}


bool UserManager::validatePassword(const QString& username, const QString& password) const{
    for (const auto& user : users){
        if(user->getUsername() == username && user->getPassword() == password){
            return true;
        }
    }
    return false;
}

QVector<std::shared_ptr<User>> UserManager::getUsers() const {
    return users;
}
