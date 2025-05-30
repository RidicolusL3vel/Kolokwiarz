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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::LoginWindow *ui;

    UserManager* userManager;

signals:
    void loginSuccess(std::shared_ptr<User> loggedInUser);
    void backToMainMenuRequested();

private slots:
    void attemptLogin();
    void attemptRegister();
    void on_backButton_clicked();
    void on_registerButton_clicked();
    void on_loginButton_clicked();
    void clearFields();
};
#endif // LOGINWINDOW_H
