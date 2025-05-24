#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    userManager = new UserManager();
    userManager->loadUsersFromFile(getUsersFilePath());
    quizManager = new QuizManager();
    rankingWindow = new RankingWindow(this);
    loginWindow = new LoginWindow(userManager, this);
    quizWindow = new QuizWindow(quizManager, currentUser, this);

    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);
    /*auto source = std::make_unique<JSONQuestionSource>(":/pytania/miernictwo.json");
    quizManager.setQuestionSource(std::move(source));
    quizManager.loadQuestions();
    */
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(ui->centralwidget);
    stackedWidget->addWidget(loginWindow);
    stackedWidget->addWidget(quizWindow);
    stackedWidget->addWidget(rankingWindow);
    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
    delete userManager;
    delete quizManager;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int fontSize = std::max(72, this->width()/12);
    QFont font = ui->title->font();
    font.setPointSize(fontSize);
    ui->title->setFont(font);
}


void MainWindow::showLoginWindow()
{
    if (loginWindow) {
        stackedWidget->setCurrentWidget(loginWindow);
    } else {
        qWarning() << "loginWindow is nullptr!";
    }
}

void MainWindow::onLoginSuccess(User* loggedInUser)
{
    currentUser = loggedInUser;

    userManager->saveUsersToFile(getUsersFilePath());

    stackedWidget->setCurrentWidget(ui->centralwidget);
}

void MainWindow::on_loginButton_clicked()
{
    showLoginWindow();
}

