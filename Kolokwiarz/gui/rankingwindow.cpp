#include "rankingwindow.h"
#include "ui_rankingwindow.h"

RankingWindow::RankingWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RankingWindow)
{
    ui->setupUi(this);
}

RankingWindow::~RankingWindow()
{
    delete ui;
}
