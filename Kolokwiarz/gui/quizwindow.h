#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QWidget>

namespace Ui {
class QuizWindow;
}

class QuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QuizWindow(QWidget *parent = nullptr);
    ~QuizWindow();

private:
    Ui::QuizWindow *ui;
};

#endif // QUIZWINDOW_H
