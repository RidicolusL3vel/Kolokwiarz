#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core\usermanager.h"
#include "core\quizmanager.h"
#include "core\user.h"
#include "gui\loginwindow.h"
#include "gui\quizwindow.h"
#include "gui\rankingwindow.h"
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;

    UserManager* userManager;
    QuizManager* quizManager;
    User* currentUser = nullptr;

    LoginWindow* loginWindow;
    QuizWindow* quizWindow;
    RankingWindow* rankingWindow;

    void showLoginWindow();
    void showQuizWindow();
    void showRankingWindow();

private slots:
    void onLoginSuccess(User* loggedInUser);
//     void onQuizCompleted();
//     void onRankingRequested();
//     void onLogoutRequested();
//     void onExitRequested();
};
#endif // MAINWINDOW_H
