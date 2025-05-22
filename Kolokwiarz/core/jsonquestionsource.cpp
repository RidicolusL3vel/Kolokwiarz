#include "jsonquestionsource.h"

JSONQuestionSource::JSONQuestionSource(const QString &path) : filePath(path) { loadQuestionsFromFile(); }

void JSONQuestionSource::loadQuestionsFromFile(){

    QFile questionsBase(filePath);
    if (!questionsBase.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie udało się otworzyć pliku: " << questionsBase.errorString();
        return;
    }

    QByteArray data = questionsBase.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = jsonDoc.array();

    for(const QJsonValue &value : std::as_const(jsonArray)) {
        QJsonObject jsonObj = value.toObject();
        QString questionText = jsonObj["question"].toString();
        QStringList options;
        for(const QJsonValue &option : jsonObj["options"].toArray()) {
            options.append(option.toString());
        }
        int correctIndex = jsonObj["correctIndex"].toInt();

        questions.append(TextQuestion(questionText, options, correctIndex));
    }
}

bool JSONQuestionSource::saveQuestionsToFile(const QVector<TextQuestion> &questions) {
    QFile questionsBase(filePath);
    if (!questionsBase.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie udało się otworzyć pliku do zapisu: " << questionsBase.errorString();
        return false;
    }

    QJsonArray jsonArray;
    for(const TextQuestion &question : std::as_const(questions)) {
        QJsonObject jsonObj;
        jsonObj["question"] = question.getQuestionText();
        jsonObj["options"] = QJsonArray::fromStringList(question.getOptions());
        jsonObj["correctIndex"] = question.getCorrectIndex();
        jsonArray.append(jsonObj);
    }

    QJsonDocument jsonDoc(jsonArray);
    questionsBase.write(jsonDoc.toJson());
    return true;
}

QVector<TextQuestion> JSONQuestionSource::getQuestions() const {
    return questions;
}
