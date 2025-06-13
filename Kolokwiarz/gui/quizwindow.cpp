#include "quizwindow.h"
#include "gui/ui_quizwindow.h"
#include "../utils/utils.h"
#include "../core/jsonquestionsource.h"

QuizWindow::QuizWindow(QuizManager* quizManager, std::shared_ptr<User> loggedInUser, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QuizWindow)
    , quizManager(quizManager)
    , loggedInUser(loggedInUser)
{
    ui->setupUi(this);

    countdownTimer = new QTimer(this);
    countdownTimer->setInterval(1000); // 1 sekunda
    connect(countdownTimer, &QTimer::timeout, this, &QuizWindow::updateTimerDisplay);
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::setMode(bool isTraining){
    this->isTrainingMode = isTraining;
}

void QuizWindow::handleAnswerTimeout() {
    on_confirmButton_clicked(); // automatycznie potwierdź odpowiedź
}


void QuizWindow::showCurrentQuestion(){
    ui->confirmButton->setEnabled(true);
    hasAnswered = false;
    const auto& question = quizManager->getCurrentQuestion();
    ui->questionLabel->setText(question.getQuestionText());
    const auto& options = question.getOptions();

    QList<QLabel*> labels = { ui->answer_1, ui->answer_2, ui->answer_3, ui->answer_4 };
    QList<QRadioButton*> radios = { ui->Aradio, ui->Bradio, ui->Cradio, ui->Dradio };

    for (int i = 0; i < 4; ++i) {
        labels[i]->setText(options[i]);
        labels[i]->setStyleSheet("");
        radios[i]->setAutoExclusive(false);
        radios[i]->setChecked(false);
        radios[i]->setAutoExclusive(true);
    }
    quizManager->markQuestionStart();
    if(!isTrainingMode)
        countdownTimer->start();
    updateTimerDisplay();
}

void QuizWindow::updateTimerDisplay() {
    double elapsed = quizManager->getTimeSinceQuestionStart();
    int remaining = quizManager->getTimeLimit() - static_cast<int>(elapsed);
    if (remaining < 0) remaining = 0;

    ui->timer->display(remaining);

    if (remaining <= 0) {
        countdownTimer->stop();
        handleAnswerTimeout(); // automatycznie obsłuż pytanie
    }
}

void QuizWindow::startQuiz(const QString& topicName, int questionAmount)
{
    if (topicName.isEmpty()) {
        qWarning() << "Nazwa tematu jest pusta, nie można rozpocząć quizu.";
        return;
    }

    quizManager->setTopicName(""); // resetuje poprzedni temat
    quizManager->setTopicName(topicName);

    if(!isTrainingMode){
        countdownTimer->start();
    }

    auto source = std::make_unique<JSONQuestionSource>(getQuestionsFilePath(topicName));
    quizManager->setTimeLimit(30); // przykładowy limit
    quizManager->setQuestionSource(std::move(source));
    quizManager->loadQuestions();

    // losujemy odpowiednią liczbę pytań
    quizManager->randomizeQuestions(questionAmount);
    quizManager->startQuiz();

    showCurrentQuestion();
}

void QuizWindow::on_quitButton_clicked()
{
    emit backToMainMenuRequested();
}

void QuizWindow::checkAnswerAndColorize()
{
    int selected = -1;
    if (ui->Aradio->isChecked()) selected = 0;
    else if (ui->Bradio->isChecked()) selected = 1;
    else if (ui->Cradio->isChecked()) selected = 2;
    else if (ui->Dradio->isChecked()) selected = 3;

    quizManager->submitAnswer(selected);
    if(!isTrainingMode)
        quizManager->calculateScore(selected);
    const auto& question = quizManager->getCurrentQuestion();
    int correct = question.getCorrectIndex();

    QList<QLabel*> labels = { ui->answer_1, ui->answer_2, ui->answer_3, ui->answer_4 };
    if (selected != -1 && selected != correct)
        labels[selected]->setStyleSheet("color: red;");
    else if(selected == -1){
        qWarning() << "Nie wybrano żadnej odpowiedzi!";
        for (int i = 0; i < labels.size(); ++i) {
            labels[i]->setStyleSheet("color: red;");
            if(labels[i] == labels[correct]){
                labels[i]->setStyleSheet("color: green;");
            }
        }
    }
    labels[correct]->setStyleSheet("color: green;");
}


void QuizWindow::on_confirmButton_clicked()
{
    countdownTimer->stop();
    ui->confirmButton->setEnabled(false);

    if (hasAnswered) {
        qWarning() << "Odpowiedź już została udzielona.";
        return;
    }
    hasAnswered = true;
    checkAnswerAndColorize();

    QTimer::singleShot(3000, this, [this]() {
        if (quizManager->hasNextQuestion()) {
            quizManager->nextQuestion();
            showCurrentQuestion();
        } else {
            emit quizCompleted(quizManager->getTopicName(),
                               quizManager->getCurrentScore(),
                               quizManager->getCorrectAnswerCount());
        }
    });
}

