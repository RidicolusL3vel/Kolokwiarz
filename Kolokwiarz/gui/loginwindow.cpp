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


void LoginWindow::attemptLogin(){
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if(userManager->validatePassword(username, password)){
        auto user = userManager->loginOrRegister(username, password);
        if(user){
            emit loginSuccess(user.get());
            this->hide();
        } else {
            ui->errorLabel->setText("Błąd logowania. Spróbuj ponownie.");
        }
    } else {
        ui->errorLabel->setText("Nieprawidłowa nazwa użytkownika lub hasło.");
        ui->errorLabel->setStyleSheet("color: red;");
    }
}


