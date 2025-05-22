#include "quizmanager.h"
#include <algorithm>
#include <random>

QuizManager::QuizManager() {}

void QuizManager::setQuestionSource(std::unique_ptr<QuestionSource> source) {
    questionSource = std::move(source);
}

void QuizManager::setQuestions(const QVector<TextQuestion>& questions) {
    this->questions = questions;
}

QVector<TextQuestion> QuizManager::randomizeQuestions(const QVector<TextQuestion>& questions) {
    QVector<TextQuestion> randomizedQuestions = questions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(randomizedQuestions.begin(), randomizedQuestions.end(), gen);
    return randomizedQuestions;
}

QVector<TextQuestion> QuizManager::randomizeQuestions(const QVector<TextQuestion>& questions, int questionAmount) {
    if (questionAmount > questions.size()) {
        qWarning() << "Podana ilosć pytań jest większa niż dostępne pytania.";
        return {};
    }
    QVector<TextQuestion> randomizedQuestions = randomizeQuestions(questions);
    randomizedQuestions.resize(questionAmount);
    return randomizedQuestions;
}

void QuizManager::loadQuestions() {
    if (questionSource) {
        questions = questionSource->getQuestions();
    } else {
        qWarning() << "Nie ustawiono źródła pytań.";
        return;
    }
}

void QuizManager::startQuiz() {
    currentScore = 0;
    currentQuestionIndex = 0;
    startTimer();
}

void QuizManager::startTimer() {
    timer.start();
}

double QuizManager::getTimeInSeconds() const {
    return timer.elapsed() / 1000.0;
}

TextQuestion QuizManager::getCurrentQuestion() const {
    if (currentQuestionIndex < questions.size()) {
        return questions[currentQuestionIndex];
    }
    return TextQuestion(); // Zwróć pusty obiekt, jeśli nie ma więcej pytań
}

void QuizManager::nextQuestion() {
    if (hasNextQuestion()) {
        currentQuestionIndex++;
    }
}

bool QuizManager::checkAnswer(int answerIndex) {
    if (currentQuestionIndex < questions.size()) {
        return questions[currentQuestionIndex].isCorrect(answerIndex);
    }
    return false;
}

bool QuizManager::hasNextQuestion() const {
    return currentQuestionIndex < questions.size() - 1;
}

int QuizManager::getCurrentScore() const {
    return currentScore;
}

int QuizManager::getCurrentQuestionIndex() const {
    return currentQuestionIndex;
}

int QuizManager::getTotalQuestions() const {
    return questions.size();
}

void QuizManager::calculateScore() {
    if(getTimeInSeconds() > timeLimit) {
        qWarning() << "Czas minął! Aktualny wynik: " << currentScore;
        return;
    } else if(!checkAnswer(currentQuestionIndex)) {
        qDebug() << "Odpowiedź błędna! Aktualny wynik: " << currentScore;
        return;
    } else if(getTimeInSeconds() / timeLimit == 1){
        currentScore += 200;
        qDebug() << "Niemożliwe do osiągnięcia!\nAle odpowiedź poprawna, aktualny wynik: " << currentScore;
    } else if(getTimeInSeconds() / timeLimit >= 0.9){
        currentScore += 100;
        qDebug() << "Odpowiedź poprawna! Aktualny wynik: " << currentScore;
    } else if(getTimeInSeconds() / timeLimit > 0){
        double answerTimePenalty = getTimeInSeconds() / timeLimit;
        currentScore += static_cast<int>(answerTimePenalty * 100);
    }
}

void QuizManager::resetQuiz() {
    currentScore = 0;
    currentQuestionIndex = 0;
    timer.invalidate();
}

void QuizManager::setTimeLimit(int seconds) {
    timeLimit = seconds;
}
