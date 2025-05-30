#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core\usermanager.h"
#include "core\quizmanager.h"
#include "core\user.h"
#include "gui\loginwindow.h"
#include "gui\quizwindow.h"
#include "gui\rankingwindow.h"
#include "gui\mainmenu.h"
#include <QResizeEvent>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class LoginWindow; // Allow LoginWindow to access private members

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;

    QStackedWidget *stackedWidget;

    UserManager* userManager;
    QuizManager* quizManager;
    std::shared_ptr<User> currentUser = nullptr;

    LoginWindow* loginWindow;
    QuizWindow* quizWindow;
    MainMenu* mainMenu;
    RankingWindow* rankingWindow;

    void showLoginWindow();
    void showQuizWindow();
    void showMainMenu();
    void showRankingWindow();
    void logoutUser();

    bool userLoginStatus = false;
    void setUserLoginStatus(bool status);
    bool isLoggedIn() const;

private slots:
    void onLoginSuccess(std::shared_ptr<User> loggedInUser);
//     void onQuizCompleted();
//     void onRankingRequested();
//     void onLogoutRequested();
//     void onExitRequested();
    void on_loginButton_clicked();
    void handleQuizStart(QString selectedTopic, bool isTrainingMode);
    void on_playButton_clicked();
};
#endif // MAINWINDOW_H
