#include "loginwindow.h"
#include "gui\ui_loginwindow.h"

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
    return;
}
