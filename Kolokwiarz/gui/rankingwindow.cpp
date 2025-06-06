#include "rankingwindow.h"
#include "gui/ui_rankingwindow.h"
#include "../core/user.h"
#include <algorithm>
#include <QTableWidget>

RankingWindow::RankingWindow(UserManager *userManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RankingWindow)
    , userManager(userManager)
{
    ui->setupUi(this);

    ui->rankingTable->setColumnCount(3);
    ui->rankingTable->setHorizontalHeaderLabels({"Miejsce", "Nazwa\nużytkownika", "Punkty"});
    ui->rankingTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rankingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rankingTable->setSelectionMode(QAbstractItemView::NoSelection);


    updateRanking();
}

RankingWindow::~RankingWindow()
{
    delete ui;
}

void RankingWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int diag = std::sqrt(this->width() * this->width() + this->height() * this->height());

    //int fontSizeBig = std::max(42, diag / 20); //tutaj nie używane
    int fontSizeSmall = std::max(14, diag / 55);

    /*
    QFont bigFont = ui->top10Label->font();
    bigFont.setPointSize(fontSizeBig);
    ui->top10Label->setFont(bigFont);*/

    // Lista pozostałych labeli
    QList<QLabel*> smallLabels = { ui->firstPlace, ui->secondPlace, ui->thirdPlace, ui->top10Label };
    for (QLabel* label : smallLabels) {
        QFont font = label->font();
        font.setPointSize(fontSizeSmall);
        label->setFont(font);
    }
}

void RankingWindow::updateRanking() {
    QVector<std::shared_ptr<User>> allUsers = userManager->getUsers();

    // Sortowanie używając przeciążonego operatora na User. Trochę na siłę.
    std::sort(allUsers.begin(), allUsers.end(),
              [](const std::shared_ptr<User>& a, const std::shared_ptr<User>& b) {
                  return *b < *a;  // większe punkty → wyższa pozycja
              });

    int displayCount = std::min(10, (int)allUsers.size());
    ui->rankingTable->setRowCount(displayCount);

    for (int i = 0; i < displayCount; ++i) {
        const auto& user = allUsers[i];
        ui->rankingTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->rankingTable->setItem(i, 1, new QTableWidgetItem(user->getUsername()));
        ui->rankingTable->setItem(i, 2, new QTableWidgetItem(QString::number(user->getTotalPoints())));
    }
    setPodiumLabels();
}

void RankingWindow::setPodiumLabels(){
    if(ui->rankingTable->item(0,1)){
        ui->firstPlace->setText(ui->rankingTable->item(0, 1)->text());
    }else{
        ui->firstPlace->setText("");
    }
    if(ui->rankingTable->item(1,1)){
        ui->secondPlace->setText(ui->rankingTable->item(1, 1)->text());
    }else{
        ui->secondPlace->setText("");
    }
    if(ui->rankingTable->item(2,1)){
        ui->thirdPlace->setText(ui->rankingTable->item(2, 1)->text());
    }else{
        ui->thirdPlace->setText("");
    }
}

void RankingWindow::on_pushButton_clicked()
{
    emit backToMainWindow();
}

