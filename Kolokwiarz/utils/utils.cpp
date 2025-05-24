#include "utils.h"

QString getUsersFilePath() {
    QString appDir = QCoreApplication::applicationDirPath();

    QDir dir(appDir);
    dir.cdUp(); // Przechodzi do katalogu nadrzędnego, aby znaleźć users.json
    dir.cdUp(); // Dodatkowe przejście w górę, jeśli exe jest w podkatalogu

    QString usersFilePath = dir.filePath("users.json");

    qDebug() << "Ścieżka do users.json:" << usersFilePath;
    return usersFilePath;
}
