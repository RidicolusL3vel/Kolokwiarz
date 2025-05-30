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
    clearFields();
    emit loginSuccess(loggedInUser);
}

void LoginWindow::attemptRegister(){
    QString username = ui->registerLoginEdit->text();
    QString password = ui->registerPassEdit->text();
    QString errorMsg;

    auto newUser = userManager->registerUser(username, password, &errorMsg);

    if(!newUser){
        ui->registerErrorLabel->setText(errorMsg);
        ui->registerErrorLabel->setStyleSheet("color: red;");
        return;
    }
    clearFields();
    emit loginSuccess(newUser);
}


void LoginWindow::on_backButton_clicked()
{
    emit backToMainMenuRequested();
    clearFields();
}


void LoginWindow::on_registerButton_clicked()
{
    attemptRegister();
    return;
}


void LoginWindow::on_loginButton_clicked()
{
    attemptLogin();
    return;
}

void LoginWindow::clearFields()
{
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    ui->registerLoginEdit->clear();
    ui->registerPassEdit->clear();
    ui->loginErrorLabel->clear();
    ui->registerErrorLabel->clear();
}
