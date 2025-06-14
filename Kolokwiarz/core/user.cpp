#include "user.h"

User::User(QString name, QString pass, int points, int games, QDateTime login) :
    username(name), password(pass), totalPoints(points), totalGames(games), lastLogin(login) {}

void User::addPoints(int pts) {
    totalPoints += pts;
}

void User::incrementGames() {
    totalGames++;
}

QString User::getStats() const {
    return QString("Username: %1\nTotal Points: %2\nTotal Games: %3\nLast Login: %4")
            .arg(username)
            .arg(totalPoints)
            .arg(totalGames)
            .arg(lastLogin.toString());
}

QString User::getUsername() const {
    return username;
}

QString User::getPassword() const {
    return password;
}

int User::getTotalPoints() const {
    return totalPoints;
}

int User::getTotalGames() const {
    return totalGames;
}

QDateTime User::getLastLogin() const {
    return lastLogin;
}

void User::setLastLogin(QDateTime dateTime) {
    lastLogin = dateTime;
}

void User::resetStats() {
    totalPoints = 0;
    totalGames = 0;
}

bool User::operator<(const User &other) const {
    return totalPoints < other.totalPoints;
}
