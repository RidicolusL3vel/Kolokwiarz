#ifndef QUESTIONSOURCE_H
#define QUESTIONSOURCE_H

#include <QVector>
#include "textquestion.h"
class QuestionSource
{
public:
    virtual QVector<TextQuestion> getQuestions() const = 0;
    virtual ~QuestionSource() = default;
};

#endif // QUESTIONSOURCE_H
