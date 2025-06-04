#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QWidget>
#include "../core/user.h"

namespace Ui {
class EndWindow;
}

class EndWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndWindow(std::shared_ptr<User> loggedInUser, QWidget *parent = nullptr);
    ~EndWindow();

    void setResults(const QString& topicName, int score, int correctAnswers);

private slots:
    void on_endButton_clicked();

signals:
    void quizFinished(int score);

private:
    Ui::EndWindow *ui;

    std::shared_ptr<User> loggedInUser;
    QString topicName;
    int score = 0;
    int correctAnswers = 0;
};

#endif // ENDWINDOW_H
