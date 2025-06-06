#include "endwindow.h"
#include "gui/ui_endwindow.h"

EndWindow::EndWindow(std::shared_ptr<User> loggedInUser, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EndWindow)
    , loggedInUser(loggedInUser)
{
    ui->setupUi(this);
    if (!loggedInUser) {
        qWarning() << "Logged in user is null!";
        return;
    }

}

EndWindow::~EndWindow()
{
    delete ui;
}

void EndWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int diag = std::sqrt(this->width() * this->width() + this->height() * this->height());
    int fontSizeBig = std::max(42, diag / 20);
    int fontSizeSmall = std::max(14, diag / 55);

    QFont bigFont = ui->infoLabel->font();
    bigFont.setPointSize(fontSizeBig);
    ui->quizFinishedLabel->setFont(bigFont);

    QFont buttonFont = ui->endButton->font();
    buttonFont.setPointSize(fontSizeSmall);
    ui->endButton->setFont(buttonFont);
    ui->infoLabel->setFont(buttonFont);
}

void EndWindow::setResults(const QString& topicName, int score, int correctAnswers)
{
    if (!loggedInUser) {
        qWarning() << "Logged in user is null!";
        return;
    }
    this->topicName = topicName;
    this->score = score;
    this->correctAnswers = correctAnswers;

    ui->infoLabel->setText(QString("Gratulacje %1! Ukończyłeś quiz tematu: %2, Uzyskałeś %3 punktów, odpowiadając na %4 poprawnych odpowiedzi.")
                           .arg(this->loggedInUser->getUsername(), topicName)
                           .arg(score)
                           .arg(correctAnswers));
}

void EndWindow::on_endButton_clicked()
{
    emit quizFinished(score);
}

