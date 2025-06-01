#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QWidget>
#include "../core/user.h"
#include "../gui/quizwindow.h"

namespace Ui {
class EndWindow;
}

class EndWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndWindow(QuizWindow *quizWindow, std::shared_ptr<User> loggedInUser, QWidget *parent = nullptr);
    ~EndWindow();

private:
    Ui::EndWindow *ui;

    std::shared_ptr<User> loggedInUser;
    QuizWindow *quizWindow;
};

#endif // ENDWINDOW_H
