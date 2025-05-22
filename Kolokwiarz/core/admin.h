#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User
{
    friend class QuestionEditor;
protected:
    QString username;
    QString password; // Assuming password is stored as a hash or encrypted
    int totalPoints;
    int totalGames;
    QDateTime lastLogin;
public:
    Admin(QString name, QString pass, int points = 0, int games = 0, QDateTime login = QDateTime::currentDateTime());

    bool isAdmin() const override { return true; }
};

#endif // ADMIN_H
