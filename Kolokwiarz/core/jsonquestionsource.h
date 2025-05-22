#ifndef JSONQUESTIONSOURCE_H
#define JSONQUESTIONSOURCE_H

#include "questionsource.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QDebug>

class JSONQuestionSource : public QuestionSource
{
    friend class QuestionEditor; // Allow QuestionEditor to access private members if needed
private:
    QString filePath;
    QVector<TextQuestion> questions;

    void loadQuestionsFromFile();
    bool saveQuestionsToFile(const QVector<TextQuestion> &questions);
public:
    explicit JSONQuestionSource(const QString &path);
    QVector<TextQuestion> getQuestions() const override;
};

#endif // JSONQUESTIONSOURCE_H
