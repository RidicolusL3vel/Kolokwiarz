#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "..\core\usermanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(UserManager* userManager, QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

    UserManager* userManager;

signals:
    void loginSuccess(User* loggedInUser);

private slots:
    void attemptLogin();
};

#endif // LOGINWINDOW_H
