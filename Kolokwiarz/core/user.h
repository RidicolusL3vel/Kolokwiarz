#ifndef USER_H
#define USER_H
#include <QString>
#include <QDateTime>

class User
{
protected:
    QString username;
    QString password; // Assuming password is stored as a hash or encrypted
    int totalPoints;
    int totalGames;
    QDateTime lastLogin;
public:
    User(QString name, QString pass, int points = 0, int games = 0, QDateTime login = QDateTime::currentDateTime());

    void addPoints(int pts);
    QString getStats() const;
    QString getUsername() const;
    QString getPassword() const;
    int getTotalPoints() const;
    int getTotalGames() const;
    QDateTime getLastLogin() const;
    void setLastLogin(QDateTime dateTime);
    void resetStats();

    bool operator==(const User &other) const;
    bool operator!=(const User &other) const;
    bool operator<(const User &other) const;

    virtual bool isAdmin() const { return false; }

    virtual ~User() = default; // Virtual destructor for proper cleanup of derived classes
};

#endif // USER_H
