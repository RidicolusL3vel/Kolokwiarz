#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QWidget>
#include "../core/quizmanager.h"
#include "../core/user.h"

namespace Ui {
class QuizWindow;
}

class QuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QuizWindow(QuizManager* quizManager, User* loggedInUser, QWidget *parent = nullptr);
    ~QuizWindow();

private:
    Ui::QuizWindow *ui;

    QuizManager* quizManager;
    User* loggedInUser;
};

#endif // QUIZWINDOW_H
