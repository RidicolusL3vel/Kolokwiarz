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

    displayTimer = new QTimer(this);
    connect(displayTimer, &QTimer::timeout, this, [this, &quizManager]() {
        double elapsed = quizManager->getTimeInSeconds();
        int remaining = quizManager->getTimeLimit() - static_cast<int>(elapsed);

        if (remaining <= 0) {
            ui->timer->display("0");
            displayTimer->stop();
            handleAnswerTimeout();
            return;
        }

        ui->timer->display(QString::number(remaining));
    });
}

QuizWindow::~QuizWindow()
{
    delete ui;
}

void QuizWindow::setMode(bool isTraining){
    this->isTrainingMode = isTraining;
}

void QuizWindow::handleAnswerTimeout() {
    const auto& question = quizManager->getCurrentQuestion();
    int correct = question.getCorrectIndex();

    QList<QLabel*> labels = { ui->answer_1, ui->answer_2, ui->answer_3, ui->answer_4 };
    labels[correct]->setStyleSheet("color: green;");

    QTimer::singleShot(3000, this, [this]() {
        if (quizManager->hasNextQuestion()) {
            quizManager->nextQuestion();
            if (!isTrainingMode) {
                quizManager->startTimer();
                displayTimer->start(100);
            }
            showCurrentQuestion();
        } else {
            emit quizCompleted();
        }
    });
}


void QuizWindow::showCurrentQuestion(){
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
}

void QuizWindow::startQuiz(const QString& topicName, int questionAmount)
{
    if (topicName.isEmpty()) {
        qWarning() << "Nazwa tematu jest pusta, nie można rozpocząć quizu.";
        return;
    }

    if(!isTrainingMode){
        quizManager->startTimer();
        displayTimer->start(100); // aktualizacja co 100ms
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


void QuizWindow::on_confirmButton_clicked()
{
    int selected = -1;
    if (ui->Aradio->isChecked()) selected = 0;
    else if (ui->Bradio->isChecked()) selected = 1;
    else if (ui->Cradio->isChecked()) selected = 2;
    else if (ui->Dradio->isChecked()) selected = 3;

    const auto& question = quizManager->getCurrentQuestion();
    int correct = question.getCorrectIndex();

    QList<QLabel*> labels = { ui->answer_1, ui->answer_2, ui->answer_3, ui->answer_4 };
    if (selected != -1 && selected != correct)
        labels[selected]->setStyleSheet("color: red;");
    labels[correct]->setStyleSheet("color: green;");

    displayTimer->stop();

    QTimer::singleShot(3000, this, [this]() {
        if (quizManager->hasNextQuestion()) {
            quizManager->nextQuestion();
            if (!isTrainingMode) {
                quizManager->startTimer();
                displayTimer->start(100);
            }
            showCurrentQuestion();
        } else {
            emit quizCompleted();
        }
    });
}

