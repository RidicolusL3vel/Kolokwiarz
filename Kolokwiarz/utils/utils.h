#ifndef UTILS_H
#define UTILS_H

#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QString>

QString getUsersFilePath();

struct QuizTopic{
    QString name;
    QString category;
};
#endif // UTILS_H
