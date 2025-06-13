#ifndef USER_H
#define USER_H
#include <QString>
#include <QDateTime>

class User
{
protected:
    QString username;
    QString password;
    int totalPoints;
    int totalGames;
    QDateTime lastLogin;
public:
    User(QString name, QString pass, int points = 0, int games = 0, QDateTime login = QDateTime::currentDateTime());

    void addPoints(int pts);
    void incrementGames();
    QString getStats() const;
    QString getUsername() const;
    QString getPassword() const;
    int getTotalPoints() const;
    int getTotalGames() const;
    QDateTime getLastLogin() const;
    void setLastLogin(QDateTime dateTime);
    void resetStats();

    bool operator<(const User &other) const;

    virtual bool isAdmin() const { return false; }

    virtual ~User() = default;
};

#endif // USER_H
