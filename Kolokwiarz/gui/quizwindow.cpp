#include "quizwindow.h"
#include "ui_quizwindow.h"
#include "../utils/utils.h"
#include "../core/jsonquestionsource.h"

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

void QuizWindow::setMode(bool isTraining){
    this->isTrainingMode = isTraining;
}

void QuizWindow::startQuiz(const QString& topicName) {
    if (topicName.isEmpty()) {
        qWarning() << "Nazwa tematu jest pusta, nie można rozpocząć quizu.";
        return;
    }

    auto source = std::make_unique<JSONQuestionSource>(getQuestionsFilePath(topicName));

    quizManager->setTimeLimit(30); // Ustawienie limitu czasu na 30 sekund
    quizManager->setQuestionSource(std::move(source));
    quizManager->loadQuestions(); // Załaduj pytania z wybranego tematu
    quizManager->startQuiz(); // Rozpocznij quiz
}
