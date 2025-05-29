#include "mainmenu.h"
#include "gui/ui_mainmenu.h"

struct QuizTopic
{
    QString name;
    QString category;
};

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int fontSizeBig = std::max(48, this->width()/12);
    int fontSizeSmall = std::max(24, this->width()/24);
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
