#include "quizmanager.h"
#include <algorithm>
#include <random>

QuizManager::QuizManager() {}

void QuizManager::setQuestionSource(std::unique_ptr<QuestionSource> source) {
    questionSource = std::move(source);
}

int QuizManager::getCorrectAnswerCount() const{
    return correctAnswers;
}

void QuizManager::setTopicName(const QString& topicName) {
    this->quizTopic = topicName;
}

QString QuizManager::getTopicName() const {
    return quizTopic;
}

QVector<TextQuestion> QuizManager::randomizeQuestions(const QVector<TextQuestion>& questions) {
    QVector<TextQuestion> randomizedQuestions = questions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(randomizedQuestions.begin(), randomizedQuestions.end(), gen);
    return randomizedQuestions;
}

void QuizManager::randomizeQuestions(int questionAmount) {
    if (questionAmount > questions.size()) {
        qWarning() << "Podana ilosć pytań jest większa niż dostępne pytania.";
        return ;
    }
    QVector<TextQuestion> randomizedQuestions = randomizeQuestions(questions);
    randomizedQuestions.resize(questionAmount);
    for(auto& question : randomizedQuestions){
        question.shuffleOptions();
    }
    this->questions = randomizedQuestions;
    return;
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

void QuizManager::calculateScore(int selectedIndex) {
    double elapsed = getTimeSinceQuestionStart();
    if (elapsed > timeLimit) {
        qWarning() << "Czas minął! Aktualny wynik: " << currentScore;
        return;
    }

    const auto& question = questions[currentQuestionIndex];
    if (selectedIndex != question.getCorrectIndex()) {
        qDebug() << "Odpowiedź błędna! Aktualny wynik: " << currentScore;
        return;
    }

    double ratio = elapsed / timeLimit;

    if (ratio <= 0.1) {
        currentScore += 200;
        qDebug() << "Ekspresowa odpowiedź! +" << 200 << ", wynik: " << currentScore;
    } else if (ratio <= 0.5) {
        currentScore += 150;
        qDebug() << "Szybka odpowiedź! +" << 150 << ", wynik: " << currentScore;
    } else if (ratio <= 0.9) {
        currentScore += 100;
        qDebug() << "Poprawna odpowiedź! +" << 100 << ", wynik: " << currentScore;
    } else {
        currentScore += 50;
        qDebug() << "Odpowiedź na styk, ale poprawna. +" << 50 << ", wynik: " << currentScore;
    }
}

void QuizManager::resetQuiz() {
    currentScore = 0;
    currentQuestionIndex = 0;
    correctAnswers = 0;
    timer.invalidate();
}

void QuizManager::setTimeLimit(int seconds) {
    timeLimit = seconds;
}

int QuizManager::getTimeLimit() const {
    return timeLimit;
}

void QuizManager::markQuestionStart() {
    startTime = timer.elapsed();
}

double QuizManager::getTimeSinceQuestionStart() const {
    return (timer.elapsed() - startTime) / 1000.0; // zwraca czas w sekundach od rozpoczęcia pytania
}

void QuizManager::submitAnswer(int selectedIndex) {
    qDebug() << "Wywołano submitAnswer z selectedIndex =" << selectedIndex;
    if (currentQuestionIndex >= questions.size()) return;

    const auto& question = questions[currentQuestionIndex];
    qDebug() << "Poprawny indeks odpowiedzi to:" << question.getCorrectIndex();

    if (selectedIndex == question.getCorrectIndex()) {
        ++correctAnswers;
        qDebug() << "Poprawna odpowiedź! Liczba poprawnych:" << correctAnswers;
    } else {
        qDebug() << "Błędna odpowiedź.";
    }
}
