#include "loginwindow.h"
#include "gui/ui_loginwindow.h"

LoginWindow::LoginWindow(UserManager* manager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow), userManager(manager)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int fontSize = std::max(48, this->width()/12);
    QFont font = ui->label->font();
    font.setPointSize(fontSize);
    ui->label->setFont(font);
}


void LoginWindow::attemptLogin(){
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    if(username.isEmpty() || password.isEmpty()){
        ui->loginErrorLabel->setText("Nazwa użytkownika i hasło nie mogą być puste.");
        ui->loginErrorLabel->setStyleSheet("color: red;");
        return;
    }
    auto loggedInUser = userManager->login(username, password);

    if(!loggedInUser){
        ui->loginErrorLabel->setText("Błędny login lub hasło.");
        ui->loginErrorLabel->setStyleSheet("color: red;");
        return;
    }
    emit loginSuccess(loggedInUser);
}

void LoginWindow::attemptRegister(){
    QString username = ui->registerLoginEdit->text();
    QString password = ui->registerPassEdit->text();
    QString errorMsg;

    auto newUser = userManager->registerUser(username, password);

    if(!newUser){
        ui->registerErrorLabel->setText(errorMsg);
        ui->registerErrorLabel->setStyleSheet("color: red;");
        return;
    }
    emit loginSuccess(newUser);
}


void LoginWindow::backToStartWindow()
{
    emit backToMainMenuRequested();
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    ui->registerLoginEdit->clear();
    ui->registerPassEdit->clear();
    ui->loginErrorLabel->clear();
    ui->registerErrorLabel->clear();
}


void LoginWindow::LOGIN()
{
    attemptLogin();
    return;
}


void LoginWindow::REGISTER()
{
    attemptRegister();
    return;
}

