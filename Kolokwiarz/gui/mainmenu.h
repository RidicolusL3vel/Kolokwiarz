#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "../utils/utils.h"
#include <QButtonGroup>

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
    QButtonGroup *modeButtonGroup = nullptr;

signals:
    void startQuiz(QString selectedTopic, bool isTrainingMode, int questionAmount = 10);
    void backToMainWindowRequested();

private slots:
    void setTopicsByCategory();
    void on_backButton_clicked();
    void on_startGameButton_clicked();
    void onTopicChanged(const QString &topicName);
};
#endif // MAINMENU_H
