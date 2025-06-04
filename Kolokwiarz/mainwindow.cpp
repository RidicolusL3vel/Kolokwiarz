#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils/utils.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    userManager = new UserManager();
    userManager->loadUsersFromFile(getUsersFilePath());
    quizManager = new QuizManager();
    rankingWindow = new RankingWindow(userManager, this);
    loginWindow = new LoginWindow(userManager, this);
    quizWindow = new QuizWindow(quizManager, currentUser, this);
    mainMenu = new MainMenu(this);

    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);

    connect(loginWindow, &LoginWindow::backToMainWindowRequested, this, [this](){
        stackedWidget->setCurrentWidget(ui->centralwidget);
    });

    connect(mainMenu, &MainMenu::backToMainWindowRequested, this, [this](){
        stackedWidget->setCurrentWidget(ui->centralwidget);
    });

    connect(quizWindow, &QuizWindow::backToMainMenuRequested, this, &MainWindow::showMainMenu);

    connect(mainMenu, &MainMenu::startQuiz, this, &MainWindow::handleQuizStart);

    connect(quizWindow, &QuizWindow::quizCompleted, this, &MainWindow::onQuizCompleted);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(ui->centralwidget);
    stackedWidget->addWidget(loginWindow);
    stackedWidget->addWidget(quizWindow);
    stackedWidget->addWidget(rankingWindow);
    stackedWidget->addWidget(mainMenu);
    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
    delete userManager;
    delete quizManager;
    delete ui;
}

bool MainWindow::isLoggedIn() const{
    if(userLoginStatus)
        return true;
    else
        return false;
}


void MainWindow::setUserLoginStatus(bool status){
    userLoginStatus = status;
    if(status){
        ui->loginButton->setText("WYLOGUJ");
    }else{
        ui->loginButton->setText("ZALOGUJ");
    }
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

void MainWindow::logoutUser()
{
    currentUser = nullptr;
    ui->username->clear();
    ui->username->setText("BRAK ZALOGOWANEGO UŻYTKOWNIKA");
    stackedWidget->setCurrentWidget(ui->centralwidget);
}

void MainWindow::onLoginSuccess(std::shared_ptr<User> loggedInUser)
{
    if (!loggedInUser) {
        qWarning() << "Logged in user is null!";
        return;
    }

    currentUser = loggedInUser;

    userManager->saveUsersToFile(getUsersFilePath());

    setUserLoginStatus(true);

    stackedWidget->setCurrentWidget(ui->centralwidget);

    ui->username->setText(currentUser->getUsername());

    ui->loginButton->setText("WYLOGUJ");
}

void MainWindow::on_loginButton_clicked()
{
    if(ui->loginButton->text() == "ZALOGUJ")
        showLoginWindow();
    else{
        setUserLoginStatus(false);
        logoutUser();
    }
}

void MainWindow::handleQuizStart(QString selectedTopic, bool isTrainingMode, int questionAmount)
{
    quizWindow->setMode(isTrainingMode);
    quizWindow->startQuiz(selectedTopic, questionAmount);
    stackedWidget->setCurrentWidget(quizWindow);
}

void MainWindow::on_playButton_clicked()
{
    if(!isLoggedIn()){
        QMessageBox::critical(this, "BŁĄD", "Aby zagrać musisz być zalogowany.");
    }else{
        showMainMenu();
    }
}

void MainWindow::showMainMenu(){
    if(mainMenu){
        stackedWidget->setCurrentWidget(mainMenu);
    }else{
        qWarning() << "mainMenu is nullptr!";
    }
}

void MainWindow::onQuizCompleted(const QString& topicName
                                 , int score
                                 , int correctAnswers)
{
    if (!currentUser) {
        qWarning() << "Current user is null!";
        return;
    }
    if(endWindow){
        delete endWindow; // usuwamy poprzednie okno
    }

    endWindow = new EndWindow(currentUser, this);
    stackedWidget->addWidget(endWindow);
    connect(endWindow, &EndWindow::quizFinished, this, &MainWindow::handleQuizFinished);
    endWindow->setResults(topicName, score, correctAnswers);
    stackedWidget->setCurrentWidget(endWindow);
}

void MainWindow::handleQuizFinished(int score)
{
    if (!currentUser) {
        qWarning() << "Current user is null!";
        return;
    }

    currentUser->addPoints(score);
    currentUser->incrementGames();
    userManager->saveUsersToFile(getUsersFilePath());

    stackedWidget->setCurrentWidget(mainMenu);
    ui->username->setText(currentUser->getUsername());
}
