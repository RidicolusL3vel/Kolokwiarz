#ifndef UTILS_H
#define UTILS_H

#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QString>

QString getUsersFilePath();

QString getQuestionsFilePath(const QString &topicName);

QString getStyleFilePath(const QString &styleName);

struct QuizTopic{
    QString name;
    QString category;
};
#endif // UTILS_H
