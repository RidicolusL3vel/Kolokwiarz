#include "admin.h"

Admin::Admin(QString name, QString pass, int points, int games, QDateTime login) :
    User(name, pass, points, games, login) {}

// The Admin class currently does not add any new functionality or data members
