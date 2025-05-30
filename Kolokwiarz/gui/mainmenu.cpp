#include "mainmenu.h"
#include "gui/ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    quizTopics = {
        {"Miernictwo Elektroniczne", "Elektronika - Semestr 1"},
        {"Filozofia", "Elektronika - Semesetr 1"},
        {"Multimedia", "Elektronika - Semsestr 2"},
    };

    QSet<QString> uniqueCategories;
    for(const auto &topic : quizTopics){
        uniqueCategories.insert(topic.category);
    }

    ui->filterBox->addItem("Wszystko");
    for (const QString& category : uniqueCategories) {
        ui->filterBox->addItem(category);
    }

    connect(ui->filterBox, &QComboBox::currentTextChanged, this, &MainMenu::setTopicsByCategory);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int fontSizeBig = std::max(42, this->width()/20);
    int fontSizeSmall = std::max(14, this->width()/40);
    QFont fontBig = ui->instruction->font();
    QFont fontSmall_1 = ui->Filtr->font();
    QFont fontSmall_2 = ui->Temat->font();
    fontBig.setPointSize(fontSizeBig);
    ui->instruction->setFont(fontBig);

    fontSmall_1.setPointSize(fontSizeSmall);
    fontSmall_2.setPointSize(fontSizeSmall);
    ui->Filtr->setFont(fontSmall_1);
    ui->Temat->setFont(fontSmall_2);
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


void MainMenu::on_backButton_clicked()
{
    emit backToMainMenuRequested();
}

