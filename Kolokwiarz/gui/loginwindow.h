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
    void backToStartWindow();
    void LOGIN();
    void REGISTER();
};

#endif // LOGINWINDOW_H
