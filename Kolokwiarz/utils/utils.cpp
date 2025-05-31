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

QString getQuestionsFilePath(const QString &topicName){
    QString normalized = topicName.toLower().replace(' ', '_');
    QString appDir = QCoreApplication::applicationDirPath();

    QDir dir(appDir);
    dir.cdUp();
    dir.cdUp();

    if(topicName.isEmpty()) {
        qWarning() << "Nazwa tematu jest pusta, zwracam pustą ścieżkę.";
        return QString();
    }

    QString questionsFilePath = dir.filePath("base/" + normalized + ".json");

    if (!QFile::exists(questionsFilePath)) {
        qWarning() << "Plik pytań dla tematu" << topicName << "nie istnieje!";
        return QString();
    }

    qDebug() << "Ścieżka do pliku pytań dla tematu" << topicName << ":" << questionsFilePath;

    return questionsFilePath;
}
