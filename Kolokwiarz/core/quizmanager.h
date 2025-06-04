#ifndef QUIZMANAGER_H
#define QUIZMANAGER_H

#include <QVector>
#include "textquestion.h"
#include "questionsource.h"
#include <QElapsedTimer>
#include <memory>
#include <QDebug>
class QuizManager
{
private:
    int currentScore = 0;
    int currentQuestionIndex = 0;
    int correctAnswers = 0;
    QVector<TextQuestion> questions;
    std::unique_ptr<QuestionSource> questionSource;
    QElapsedTimer timer;
    QString quizTopic;
    qint64 startTime;
    int timeLimit = 30; // czas na odpowiedź w sekundach
public:
    QuizManager();

    /*~~Inicjalizacja~~*/
    void setQuestionSource(std::unique_ptr<QuestionSource> source); // ustawienie źródła pytań
    QVector<TextQuestion> randomizeQuestions(const QVector<TextQuestion>& questions);
    /* ^^przetasowuje wszystkie pytania; zwraca pełny wektor^^ */
    void randomizeQuestions(int questionAmount);
    /* ^^przetasowuje pytania, a następnie zwraca wektor przycięty do ilości pytań wskazanych przez questionAmount^^ */

    /*~~Obsługa Quizu~~*/
    void loadQuestions(); // załaduj pytania z źródła
    void startQuiz();
    void startTimer(); // rozpocznij odliczanie czasu
    double getTimeInSeconds() const; // pobierz czas w sekundach
    void markQuestionStart();
    double getTimeSinceQuestionStart() const;
    void setTopicName(const QString& topicName);
    QString getTopicName() const;

    /*~~Obsługa Pytań~~*/
    TextQuestion getCurrentQuestion() const; // pobierz aktualne pytanie
    void nextQuestion(); // przejdź do następnego pytania
    bool checkAnswer(int answerIndex); // sprawdź odpowiedź użytkownika
    bool hasNextQuestion() const; // sprawdź czy są jeszcze pytania
    void submitAnswer(int answerIndex); // zatwierdź odpowiedź użytkownika

    /*~~Statystyki~~*/
    int getCurrentScore() const; // pobierz aktualny wynik
    int getCurrentQuestionIndex() const; // pobierz aktualny indeks pytania
    int getTotalQuestions() const; // pobierz całkowitą liczbę pytań
    int getCorrectAnswerCount() const;
    void calculateScore(int selectedIndex); // oblicz wynik na podstawie czasu i odpowiedzi
    void resetQuiz(); // zresetuj quiz
    void setTimeLimit(int seconds); // ustaw limit czasu na odpowiedź
    int getTimeLimit() const; // pobierz limit czasu na odpowiedź
};

#endif // QUIZMANAGER_H
