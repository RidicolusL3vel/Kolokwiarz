#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core\jsonquestionsource.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*auto source = std::make_unique<JSONQuestionSource>(":/pytania/miernictwo.json");
    quizManager.setQuestionSource(std::move(source));
    quizManager.loadQuestions();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showLoginWindow()
{
    if (!loginWindow) {
        loginWindow = new LoginWindow(this);
        connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);
    }
    loginWindow->show();
    this->hide();
}

void MainWindow::onLoginSuccess(User* loggedInUser)
{
    currentUser = loggedInUser;

    userManager->saveUsersToFile("users.json");

    this->show();
    loginWindow->hide();
}
