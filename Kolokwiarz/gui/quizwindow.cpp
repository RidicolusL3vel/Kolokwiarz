#include "quizwindow.h"
#include "ui_quizwindow.h"

QuizWindow::QuizWindow(QuizManager* quizManager, std::shared_ptr<User> loggedInUser, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QuizWindow)
    , quizManager(quizManager)
    , loggedInUser(loggedInUser)
{
    ui->setupUi(this);
}

QuizWindow::~QuizWindow()
{
    delete ui;
}
