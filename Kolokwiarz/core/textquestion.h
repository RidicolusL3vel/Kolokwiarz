#ifndef TEXTQUESTION_H
#define TEXTQUESTION_H

#include "question.h"

class TextQuestion : public Question
{
private:
    QString text;
    QStringList options;
    int correctOptionIndex;
public:
    TextQuestion();
    TextQuestion(const QString &text, const QStringList &options, int correctOptionIndex);

    QString getQuestionText() const override;
    QStringList getOptions() const override;
    int getCorrectIndex() const override;
    bool isCorrect(int optionIndex) const override;

    void shuffleOptions();
};

#endif // TEXTQUESTION_H
