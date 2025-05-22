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
    QVector<TextQuestion> questions;
    std::unique_ptr<QuestionSource> questionSource;
    QElapsedTimer timer;
    int timeLimit = 30; // czas na odpowiedź w sekundach
public:
    QuizManager();

    /*~~Inicjalizacja~~*/
    void setQuestionSource(std::unique_ptr<QuestionSource> source); // ustawienie źródła pytań
    void setQuestions(const QVector<TextQuestion>& questions); // ustawienie pytań ze źródła
    QVector<TextQuestion> randomizeQuestions(const QVector<TextQuestion>& questions);
    /* ^^przetasowuje wszystkie pytania; zwraca pełny wektor^^ */
    QVector<TextQuestion> randomizeQuestions(const QVector<TextQuestion>& questions, int questionAmount);
    /* ^^przetasowuje pytania, a następnie zwraca wektor przycięty do ilości pytań wskazanych przez questionAmount^^ */

    /*~~Obsługa Quizu~~*/
    void loadQuestions(); // załaduj pytania z źródła
    void startQuiz();
    void startTimer(); // rozpocznij odliczanie czasu
    double getTimeInSeconds() const; // pobierz czas w sekundach

    /*~~Obsługa Pytań~~*/
    TextQuestion getCurrentQuestion() const; // pobierz aktualne pytanie
    void nextQuestion(); // przejdź do następnego pytania
    bool checkAnswer(int answerIndex); // sprawdź odpowiedź użytkownika
    bool hasNextQuestion() const; // sprawdź czy są jeszcze pytania

    /*~~Statystyki~~*/
    int getCurrentScore() const; // pobierz aktualny wynik
    int getCurrentQuestionIndex() const; // pobierz aktualny indeks pytania
    int getTotalQuestions() const; // pobierz całkowitą liczbę pytań
    void calculateScore(); // oblicz wynik na podstawie czasu i odpowiedzi
    void resetQuiz(); // zresetuj quiz
    void setTimeLimit(int seconds); // ustaw limit czasu na odpowiedź
};

#endif // QUIZMANAGER_H
