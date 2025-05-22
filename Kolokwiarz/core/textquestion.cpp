#include "textquestion.h"
#include <random>
#include <algorithm>

TextQuestion::TextQuestion(const QString &text, const QStringList &options, int correctOptionIndex)
    : text(text), options(options), correctOptionIndex(correctOptionIndex) {}

QString TextQuestion::getQuestionText() const {
    return text;
}

QStringList TextQuestion::getOptions() const {
    return options;
}

int TextQuestion::getCorrectIndex() const {
    return correctOptionIndex;
}

bool TextQuestion::isCorrect(int userAnswerIndex) const {
    return userAnswerIndex == correctOptionIndex;
}

void TextQuestion::shuffleOptions() {
    QString correctOption = options[correctOptionIndex];

    std::random_device rd; //nowy randomizer w c++11, podobno wolny, ale lepszy od rand() i prostszy
    std::mt19937 g(rd()); //generator liczb pseudolosowych dla seed'u stworzonego przez random_device
    std::shuffle(options.begin(), options.end(), g); //przetasowanie opcji wg. generatora

    correctOptionIndex = options.indexOf(correctOption); //ustawienie nowego indeksu poprawnej odpowiedzi
}
