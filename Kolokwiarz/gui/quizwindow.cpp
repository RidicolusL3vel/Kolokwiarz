#include "quizwindow.h"
#include "ui_quizwindow.h"

QuizWindow::QuizWindow(QuizManager* quizManager, User* loggedInUser, QWidget *parent)
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
