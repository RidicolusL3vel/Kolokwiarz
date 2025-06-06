#include "questionadder.h"
#include "gui/ui_questionadder.h"
#include "../core/questioneditor.h"
#include "../core/textquestion.h"
#include "../core/jsonquestionsource.h"
#include "../utils/utils.h"
#include <QMessageBox>

QuestionAdder::QuestionAdder(const Admin& admin, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuestionAdder)
    , m_admin(admin)
{
    ui->setupUi(this);
}

QuestionAdder::~QuestionAdder()
{
    delete ui;
}

void QuestionAdder::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    int diag = std::sqrt(this->width() * this->width() + this->height() * this->height());

    int fontSizeSmall = std::max(12, diag / 60);

    QList<QLineEdit*> inputs = { ui->questionInput, ui->answer1, ui->answer2, ui->answer3, ui->answer4 };
    for (QLineEdit* input : inputs) {
        QFont font = input->font();
        font.setPointSize(fontSizeSmall);
        input->setFont(font);
    }

    fillTopics();
}

void QuestionAdder::fillTopics(){
    QStringList topics = { "Filozofia", "Miernictwo Elektroniczne", "Multimedia" };
    ui->topicComboBox->addItems(topics);
}

void QuestionAdder::on_buttonBox_accepted()
{
    QString questionText = ui->questionInput->text().trimmed();
    QStringList answers = {
        ui->answer1->text().trimmed(),
        ui->answer2->text().trimmed(),
        ui->answer3->text().trimmed(),
        ui->answer4->text().trimmed()
    };
    int correctIndex = ui->correctIndex->value() - 1;
    QString topic = ui->topicComboBox->currentText();

    auto source = std::make_unique<JSONQuestionSource>(getQuestionsFilePath(topic));
    // Walidacja
    if (questionText.isEmpty() || answers.contains("") || correctIndex < 0 || correctIndex >= 4) {
        QMessageBox::warning(this, "Błąd", "Uzupełnij wszystkie pola i upewnij się, że indeks poprawnej odpowiedzi jest poprawny.");
        return;
    }

    TextQuestion question(questionText, answers, correctIndex);

    if (!QuestionEditor::addQuestion(m_admin, question, *source)) {
        QMessageBox::critical(this, "Błąd", "Nie udało się zapisać pytania.");
    } else {
        QMessageBox::information(this, "Sukces", "Pytanie zostało dodane.");
        this->accept();
    }
}

void QuestionAdder::on_buttonBox_rejected()
{
    this->reject();
}

