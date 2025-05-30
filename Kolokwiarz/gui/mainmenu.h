#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "../utils/utils.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainMenu *ui;
    QList<QuizTopic> quizTopics;

signals:
    void startQuiz(QString selectedTopic, bool isTrainingMode);
    void backToMainMenuRequested();

private slots:
    void setTopicsByCategory();
    void on_backButton_clicked();
};

#endif // MAINMENU_H
