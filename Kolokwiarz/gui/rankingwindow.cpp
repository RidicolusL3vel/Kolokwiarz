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
    ui->rankingTable->setHorizontalHeaderLabels({"Miejsce", "Nazwa użytkownika", "Punkty"});
    ui->rankingTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->rankingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rankingTable->setSelectionMode(QAbstractItemView::NoSelection);

    ui->podiumImg->setPixmap(QPixmap(":/images/podium.png").scaled(250, 200, Qt::KeepAspectRatio));
    ui->podiumImg->setAlignment(Qt::AlignCenter);

    updateRanking();
}

RankingWindow::~RankingWindow()
{
    delete ui;
}

void RankingWindow::updateRanking() {
    QVector<std::shared_ptr<User>> allUsers = userManager->getUsers();

    // Sortowanie — zakładamy, że operator< jest przeciążony tak, że lepsi użytkownicy są "mniejsi"
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
}
