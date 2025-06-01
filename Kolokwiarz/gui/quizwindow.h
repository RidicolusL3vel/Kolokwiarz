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
    void quizCompleted();

private slots:
    void on_quitButton_clicked();
    void handleAnswerTimeout();

    void on_confirmButton_clicked();

private:
    Ui::QuizWindow *ui;

    QTimer* displayTimer;

    QuizManager* quizManager;
    std::shared_ptr<User> loggedInUser;
    bool isTrainingMode;
};

#endif // QUIZWINDOW_H
