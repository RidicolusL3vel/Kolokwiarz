#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/jsonquestionsource.h"

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
