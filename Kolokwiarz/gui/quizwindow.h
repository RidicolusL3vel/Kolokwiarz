#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QWidget>
#include <QTimer>
#include "../core/quizmanager.h"
#include "../core/user.h"

namespace Ui {
class QuizWindow;
}

class QuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QuizWindow(QuizManager* quizManager, std::shared_ptr<User> loggedInUser, QWidget *parent = nullptr);
    ~QuizWindow();

    void setMode(bool isTraining);

    void startQuiz(const QString& topicName, int questionAmount = 10);
    void showCurrentQuestion();

signals:
    void backToMainMenuRequested();
    void quizCompleted(const QString& topicName, int score, int correctAnswers);

private slots:
    void on_quitButton_clicked();
    void handleAnswerTimeout();

    void on_confirmButton_clicked();

private:
    Ui::QuizWindow *ui;

    bool hasAnswered = false;

    QTimer* countdownTimer;
    void updateTimerDisplay();

    QuizManager* quizManager;
    std::shared_ptr<User> loggedInUser = nullptr;
    bool isTrainingMode;

    void checkAnswerAndColorize();
};

#endif // QUIZWINDOW_H
