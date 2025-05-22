#include "questioneditor.h"
#include <QDebug>

bool QuestionEditor::addQuestion(const Admin& admin, const TextQuestion& question, JSONQuestionSource& source) {
    if (!admin.isAdmin()) {
        qDebug() << "Odmowa dostępu. Użytkownik nie jest administratorem.";
        return false;
    }
    QVector<TextQuestion> questions = source.getQuestions();
    questions.append(question);
    return source.saveQuestionsToFile(questions);
}

bool QuestionEditor::removeQuestion(const Admin& admin, int index, JSONQuestionSource& source) {
    if (!admin.isAdmin()) {
        qDebug() << "Odmowa dostępu. Użytkownik nie jest administratorem.";
        return false;
    }
    QVector<TextQuestion> questions = source.getQuestions();
    if (index < 0 || index >= questions.size()) {
        qDebug() << "Podany index poza zakresem.";
        return false;
    }
    questions.removeAt(index);
    return source.saveQuestionsToFile(questions);
}

bool QuestionEditor::editQuestion(const Admin& admin, int index, const TextQuestion& updatedQuestion, JSONQuestionSource& source) {
    if (!admin.isAdmin()) {
        qDebug() << "Odmowa dostępu. Użytkownik nie jest administratorem.";
        return false;
    }
    QVector<TextQuestion> questions = source.getQuestions();
    if (index < 0 || index >= questions.size()) {
        qDebug() << "Podany index poza zakresem.";
        return false;
    }
    questions[index] = updatedQuestion;
    return source.saveQuestionsToFile(questions);
}
