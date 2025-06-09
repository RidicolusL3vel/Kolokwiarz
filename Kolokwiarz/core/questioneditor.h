#ifndef QUESTIONEDITOR_H
#define QUESTIONEDITOR_H

#include "admin.h"
#include "textquestion.h"
#include "jsonquestionsource.h"

class QuestionEditor
{
    friend class QuestionAdder;
private:
    static bool addQuestion(const Admin& admin, const TextQuestion& question, JSONQuestionSource& source);
    static bool removeQuestion(const Admin& admin, int index, JSONQuestionSource& source);
    static bool editQuestion(const Admin& admin, int index, const TextQuestion& updatedQuestion, JSONQuestionSource& source);
};

#endif // QUESTIONEDITOR_H
