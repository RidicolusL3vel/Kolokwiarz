#include "mainmenu.h"
#include "gui/ui_mainmenu.h"
#include "../utils/utils.h"
#include "../core/jsonquestionsource.h"
#include <QMessageBox>
#include <cmath>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    quizTopics = {
        {"Miernictwo Elektroniczne", "Elektronika - Semestr 1"},
        {"Filozofia", "Elektronika - Semestr 1"},
        {"Multimedia", "Elektronika - Semestr 2"},
    };

    QSet<QString> uniqueCategories;
    for(const auto &topic : quizTopics){
        uniqueCategories.insert(topic.category);
    }

    ui->filterBox->addItem("Wszystko");
    for (const QString& category : uniqueCategories) {
        if(ui->filterBox->findText(category) != -1)
            continue; // Zapobieganie duplikatom
        ui->filterBox->addItem(category);
    }

    connect(ui->topicBox, &QComboBox::currentTextChanged, this, &MainMenu::onTopicChanged);
    connect(ui->filterBox, &QComboBox::currentTextChanged, this, &MainMenu::setTopicsByCategory);
    setTopicsByCategory();
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int diag = std::sqrt(this->width() * this->width() + this->height() * this->height());

    int fontSizeBig = std::max(42, diag/20);
    int fontSizeSmall = std::max(14, diag/40);
    // Duży label
    QFont bigFont = ui->instruction->font();
    bigFont.setPointSize(fontSizeBig);
    ui->instruction->setFont(bigFont);

    // Lista pozostałych labeli
    QList<QLabel*> smallLabels = { ui->Filtr, ui->Temat, ui->ilePytan };
    for (QLabel* label : smallLabels) {
        QFont font = label->font();
        font.setPointSize(fontSizeSmall);
        label->setFont(font);
    }
}

void MainMenu::setTopicsByCategory(){
    QString selectedCategory = ui->filterBox->currentText();
    ui->topicBox->clear();

    for(const auto &topic : quizTopics){
        if(selectedCategory == "Wszystko" || topic.category == selectedCategory){
            ui->topicBox->addItem(topic.name);
        }
    }
}

void MainMenu::onTopicChanged(const QString &topicName){
    QString path = getQuestionsFilePath(topicName);

    if(path.isEmpty()){
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pliku pytań dla wybranego tematu.");
        return;
    }

    JSONQuestionSource tempSource(path);
    QVector<TextQuestion> questions = tempSource.getQuestions();

    int availableCount = questions.size();

    ui->questionCountSpinBox->setMaximum(availableCount);
    ui->questionCountSpinBox->setValue(qMin(1, availableCount)); // domyślnie 10

    ui->ilePytan->setText(QString("Ile pytan (z %1)").arg(availableCount));
}

void MainMenu::on_backButton_clicked()
{
    emit backToMainWindowRequested();
}


void MainMenu::on_startGameButton_clicked()
{
    QString selectedTopic = ui->topicBox->currentText();
    int questionCount = ui->questionCountSpinBox->value();
    bool isTrainingMode = ui->trainingRadio->isChecked();

    if(selectedTopic.isEmpty()){
        QMessageBox::warning(this, "Błąd", "Proszę wybrać temat quizu.");
        return;
    }

    emit startQuiz(selectedTopic, isTrainingMode, questionCount);
}

