#ifndef QUESTIONEDITOR_H
#define QUESTIONEDITOR_H

#include "admin.h"
#include "textquestion.h"
#include "jsonquestionsource.h"

class QuestionEditor
{
public:
    static bool addQuestion(const Admin& admin, const TextQuestion& question, JSONQuestionSource& source);
};

#endif // QUESTIONEDITOR_H
