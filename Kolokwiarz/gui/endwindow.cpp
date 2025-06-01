#include "endwindow.h"
#include "gui/ui_endwindow.h"

EndWindow::EndWindow(std::shared_ptr<User> loggedInUser, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EndWindow)
    , loggedInUser(loggedInUser)
{
    ui->setupUi(this);


}

EndWindow::~EndWindow()
{
    delete ui;
}
