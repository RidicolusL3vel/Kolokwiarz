#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainMenu *ui;
    struct QuizTopic;

signals:
    void startQuiz();

private slots:
    void setChosenOptions();
};

#endif // MAINMENU_H
